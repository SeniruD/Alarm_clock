/* Heder file for Interfaces */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define F_CPU 8000000UL
#define SCL_CLOCK  100000L
#define Device_Write_address	0xD0

#include <avr/interrupt.h>



extern int page;


//-------------------------Interface functions prototypes------

#define BV(x)				(1 << x)
#define setBit(P,B)			P |= BV(B)
#define clearBit(P,B)		P &= ~BV(B)
#define toggleBit(P,B)      P ^= BV(B)

void mainMenuInt();
void alarmMenuInt();
void settingMenuInt();
void volumeInt();
void contrastInt();
void alarmTonesInt();
void alarmSettingInt();
void editAlarmInt(int currentAlarm);
void timeDisplayInt();
void resetDefaults();
void setContrast();
void turnBacklightOn();
void turnBacklightOff();

//--------------------------------------------------------

extern bool backlight;
extern int contrast;
extern int volume;
extern int menuitem;
int secs;
int hor;
int min;
int y;
int m;
int d;
typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc_t;
void i2c_init()           //Initializing i2c Communication
{
	TWSR=0x00;
	TWBR=((F_CPU/SCL_CLOCK)-16)/2;
}


void i2c_start()          //Starting I2C communication
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while((TWCR &(1<<TWINT))==0);
}

void i2c_stop()            //Stopping I2C communication
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void i2c_write(char data)       //Writing through I2C
{
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR &(1<<TWINT))==0);
}

unsigned char i2c_read()        //Read through I2C
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(!(TWCR &(1<<TWINT)));
	return TWDR;
}
unsigned char i2c_readNak(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	return TWDR;
}
void time_set(void)         //Setting time
{
	i2c_init();
	i2c_start();
	i2c_write(0xD0);       //Setting writing address
	i2c_write(0x07);
	i2c_write(0x00);
	i2c_stop();
	_delay_ms(2);
}

void RTC_set(rtc_t *rtc)
{
	
	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x00);
	i2c_write(rtc->sec);
	i2c_write(rtc->min);
	i2c_write(rtc->hour);
	i2c_write(rtc->weekDay);
	i2c_write(rtc->date);
	i2c_write(rtc->month);
	i2c_write(rtc->year);
	i2c_stop();
	
}
void RTC_Read_Clock(rtc_t *rtc)
{
	i2c_start();/* Start I2C communication with RTC */
	i2c_write(0xD0);
	i2c_write(0x00);
	i2c_stop();
	i2c_start();
	i2c_write(0xD1);	/* Write address to read */
	rtc->sec = i2c_read();                // read second and return Positive ACK
	rtc->min = i2c_read();                 // read minute and return Positive ACK
	rtc->hour= i2c_read();               // read hour and return Negative/No ACK
	rtc->weekDay = i2c_read();           // read weekDay and return Positive ACK
	rtc->date= i2c_read();              // read Date and return Positive ACK
	rtc->month=i2c_read();            // read Month and return Positive ACK
	rtc->year =i2c_readNak();             // read Year and return Negative/No ACK

	
	i2c_stop();			/* Stop i2C communication */

}
void timeDisplayInt(){
	char clck[10];
	char date[20];
	rtc_t rtc;
	i2c_init();
	time_set();
	RTC_Read_Clock(&rtc);
	secs=((uint16_t)rtc.sec);
	min=((uint16_t)rtc.min);
	hor=((uint16_t)rtc.hour);
	y=((uint16_t)rtc.year);
	m=((uint16_t)rtc.month);
	d=((uint16_t)rtc.date);
	sprintf(clck,"%02x:%02x:%02x",(hor),(min),(secs));
	sprintf(date,"%02x:%02x:%02x",(d),(m),(y));
	
	lcdSetCursor(4, 0);
	lcdPrint(clck);
	lcdSetCursor(4, 1);
	lcdPrint(date);
	

		
		
	
}





void mainMenuInt(){
	lcdSetCursor(4, 0);
	lcdPrint("MAIN MENU");

	if (menuitem == 1)
	{
		lcdSetCursor(3, 1);
		lcdPrint("<< Alarm >>");
	}
	else if (menuitem == 2)
	{
		lcdSetCursor(1, 1);
		lcdPrint("<<Date & Time>>");
	}
	
	else if (menuitem == 3)
	{
		lcdSetCursor(1, 1);
		lcdPrint("<< Settings >>");
	}

	//lcd.display();
}

	

void alarmMenuInt(){
	
	lcdSetCursor(4, 0);
	lcdPrint("ALARM MENU");
	if (menuitem == 1)
	{
		lcdSetCursor(1, 1);
		lcdPrint("<Manage Alarms>");
	}
	else if (menuitem == 2)
	{
		lcdSetCursor(1, 1);
		lcdPrint("<Alarm Tones>");
	}

}

void settingMenuInt(){
	
	lcdSetCursor(4, 0);
	lcdPrint("SETTINGS");
	
	if (menuitem == 1)
	{
		lcdSetCursor(3, 1);
		lcdPrint("<<Volume>>");
	}
	else if (menuitem == 2)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<<Contrast>>");
	}
	
	else if (menuitem == 3)
	{
		lcdSetCursor(4, 1);
		lcdPrint("<<Reset>>");
	}
	
}

void volumeInt(){
	
	lcdSetCursor(5, 0);
	lcdPrint("---Volume---");
	lcdSetCursor(7, 1);
	char s_volume[10];
	itoa(volume,s_volume,10);
	lcdPrint(s_volume);
	//lcd.display();
}

void contrastInt(){
	
	lcdSetCursor(4, 0);
	lcdPrint("--Contrast--");
	lcdSetCursor(7, 1);
	char s_contrast[10];
	itoa(contrast,s_contrast,10);
	lcdPrint(s_contrast);
	//lcd.display();
}

void alarmTonesInt(){
	
	lcdSetCursor(3, 0);
	lcdPrint("ALARM TONES");
	if (menuitem == 1)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Zelda AT1>");
	}
	else if (menuitem == 2)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Green Slaves>");
	}
	else if (menuitem == 3)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Star Wars>");
	}
	else if (menuitem == 4)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Harry Potter>");
	}
	else if (menuitem == 5)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Zelda AT2>");
	}
}

void alarmSettingInt(){
	lcdSetCursor(1, 0);
	lcdPrint("ALARM SETTINGS");
	if (menuitem == 1)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Edit Alarm>");
	}
	else if (menuitem == 2)
	{
		lcdSetCursor(1, 1);
		lcdPrint("<Delete Alarm>");
	}
}

void resetDefaults()
{
	volume = 10;
	contrast = 50;
	setContrast();
	backlight = true;
	turnBacklightOn();
}


void setContrast()
{
	//lcd.backlight(contrast);
}

void turnBacklightOn()
{
	setBit(PORTD,0);
}

void turnBacklightOff()
{
	clearBit(PORTD,0);
}

