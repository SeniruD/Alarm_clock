/* Heder file for Interfaces */

//-------------------------Interface functions prototypes------

#define BV(x)				(1 << x)
#define setBit(P,B)			P |= BV(B)
#define clearBit(P,B)		P &= ~BV(B)
#define toggleBit(P,B)      P ^= BV(B)

void timeDisplayInt();
void mainMenuInt();
void dateTimeSetInt();
void alarmMenuInt();
void settingMenuInt();
void volumeInt();
void contrastInt();
void setAlarmInt();
void alarmListInt();
void alarmTonesInt();
void alarmSettingInt();
void editAlarmInt();

void resetDefaults();
void setContrast();
void turnBacklightOn();
void turnBacklightOff();

//--------------------------------------------------------

extern bool backlight;
extern int contrast;
extern int volume;
extern int menuitem;

void timeDisplayInt(){
	lcdSetCursor(6, 0);
	lcdPrint("12:34");
	lcdSetCursor(4, 1);
	lcdPrint("29-04-2021");
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

void dateTimeSetInt(){
	
	lcdSetCursor(6, 0);
	lcdPrint("12:34");
	lcdSetCursor(4, 1);
	lcdPrint("29-04-2021");
}

void alarmMenuInt(){
	
	lcdSetCursor(4, 0);
	lcdPrint("ALARM MENU");
	if (menuitem == 1)
	{
		lcdSetCursor(1, 1);
		lcdPrint("<Set New Alarm>");
	}
	else if (menuitem == 2)
	{
		lcdSetCursor(1, 1);
		lcdPrint("<Manage Alarms>");
	}
	else if (menuitem == 3)
	{
		lcdSetCursor(2, 1);
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

void setAlarmInt(){
	lcdSetCursor(6, 0);
	lcdPrint("12:34");
	lcdSetCursor(4, 1);
	lcdPrint("29-04-2021");
}

void alarmListInt(){
	
	lcdSetCursor(3, 0);
	lcdPrint("ALARM LIST");
	if (menuitem == 1)
	{
		lcdSetCursor(3, 1);
		lcdPrint("< Alarm1 >");
	}
	else if (menuitem == 2)
	{
		lcdSetCursor(3, 1);
		lcdPrint("< Alarm2 >");
	}
	else if (menuitem == 3)
	{
		lcdSetCursor(3, 1);
		lcdPrint("< Alarm3 >");
	}
	else if (menuitem == 4)
	{
		lcdSetCursor(3, 1);
		lcdPrint("< Alarm4 >");
	}
	else if (menuitem == 5)
	{
		lcdSetCursor(3, 1);
		lcdPrint("< Alarm5 >");
	}
	else if (menuitem == 6)
	{
		lcdSetCursor(3, 1);
		lcdPrint("< Alarm6 >");
	}
	else if (menuitem == 7)
	{
		lcdSetCursor(3, 1);
		lcdPrint("< Alarm7 >");
	}
}

void alarmTonesInt(){
	
	lcdSetCursor(3, 0);
	lcdPrint("ALARM TONES");
	if (menuitem == 1)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Alarmtone1>");
	}
	else if (menuitem == 2)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Alarmtone2>");
	}
	else if (menuitem == 3)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Alarmtone3>");
	}
	else if (menuitem == 4)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Alarmtone4>");
	}
	else if (menuitem == 5)
	{
		lcdSetCursor(2, 1);
		lcdPrint("<Alarmtone5>");
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

void editAlarmInt(){
	lcdSetCursor(6, 0);
	lcdPrint("12:34");
	lcdSetCursor(4, 1);
	lcdPrint("29-04-2021");
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