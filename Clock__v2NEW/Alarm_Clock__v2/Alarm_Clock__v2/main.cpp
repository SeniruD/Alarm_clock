/*
 * AVR_C.c
 *
 * Created: 5/17/2021 12:23:07 PM
 * Author : SENIRU
 */ 

#define F_CPU	8000000UL // 8 MHz clock speed


#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Lcd.h"
#include "Interfaces.h"
#include "TimeInputInterfaces.h"
#include "Alarmtones.h"


#include <stdio.h>

#define F_CPU 8000000UL
#define SCL_CLOCK  100000L
#define Device_Write_address	0xD0

#include <avr/interrupt.h>


extern bool backlight;
extern int contrast;
extern int volume;
extern int menuitem;

bool backlight = false;
int contrast = 10;
int volume = 10;
int menuitem = 1;
extern int page = 0;

volatile bool up = false;
volatile bool down = false;
volatile bool select = false;
volatile bool back = false;
volatile bool play_music = false;


int downButtonState = 0;
int upButtonState = 0;
int selectButtonState = 0;
int backButtonState = 0;
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;
int lastBackButtonState = 0;

void drawMenu();
void checkIfDownButtonIsPressed();
void checkIfUpButtonIsPressed();
void checkIfSelectButtonIsPressed();
void checkIfBackButtonIsPressed();


int main(void)
{
	
	DDRD = 0x01; //Set PORTD 4,5,6,7 pins as input pins & Set PORTD0 pin as output
    PORTD = 0xF0; //Set PD0, PD1, PD6, PD7 to INPUT PULL_UP and LOW pin0
	DDRB = 0xFF; // Set all PORTB as output
	setBit(DDRC,3);
	//clearBit(PORTD,0);   //Turn backlight off 
	lcdInit();
	
	
    while (1) 
    {
		
		drawMenu();

		downButtonState = digitalRead(7);
		selectButtonState = digitalRead(6);
		upButtonState =   digitalRead(5);
		backButtonState =   digitalRead(4);

		checkIfDownButtonIsPressed();
		checkIfUpButtonIsPressed();
		checkIfSelectButtonIsPressed();
		checkIfBackButtonIsPressed();
		char n[6];
		sprintf(n,"%02x%02x",(hor),(min));
		for (int i = 0; i <= alarmNo;i++){
			if ((alarmHoursList[i]==atoi(n)/100) && (alarmMinsList[i]==atoi(n)%100)){
				switch(alarmMelodyList[i]){
					case 1:
					musicplay(melody1, sizeof(melody1), sizeof(melody1[0]),108);
					break;
					case 2:
					musicplay(melody2, sizeof(melody2), sizeof(melody2[0]),70);
					break;
					case 3:
					musicplay(melody3, sizeof(melody3), sizeof(melody3[0]),140);
					break;
					case 4:
					musicplay(melody4, sizeof(melody4), sizeof(melody4[0]),144);
					break;
					case 5:
					musicplay(melody5, sizeof(melody5), sizeof(melody5[0]),108);
				}
			}
		}

        // --------------------------------UP button functions------------------------------------------------------------------
 		if (up && page == 1 ) {
			up = false;
			lcdClearLine(2);
			menuitem--;
			if (menuitem == 0){
				menuitem = 3;
			}
		 }
		else if (up && page == 2 ) {
			up = false;
		}
	    else if (up && page == 3 ) {
			up = false;
			lcdClearLine(2);
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 2;
			}
		}
		
		else if (up && page == 4 ) {
			up = false;
			lcdClearLine(2);
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 3;
			}
		}
		else if (down && page == 5 ) {
			down = false;
			lcdClearLine(2);
			volume++;
		}
		else if (up && page == 6 ) {
			up = false;
			lcdClearLine(2);
			contrast--;
			//setContrast();
		}
		else if (up && page == 8 ) {
			up = false;
			lcdClearLine(2);
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 7;
			}
		}
		else if (up && page == 9 ) {
			up = false;
			lcdClearLine(2);
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 5;
			}
		}
		else if (up && page == 10 ) {
			up = false;
			lcdClearLine(2);
			menuitem--;
			if (menuitem == 0)
			{
				menuitem = 2;
			}
		}


        //-------------------------------------- DOWN button functions------------------------------------------------------
		if (down && page == 1) {
			down = false;
			lcdClearLine(2);
			menuitem++;
			if (menuitem == 4)
			{
				menuitem = 1;
			}
		}
		else if (down && page == 2) {
			down = false;
		}
		else if (down && page == 3) {
			down = false;
			lcdClearLine(2);
			menuitem++;
			if (menuitem == 3)
			{
				menuitem = 1;
			}
		}
		else if (down && page == 4) {
			down = false;
			lcdClearLine(2);
			menuitem++;
			if (menuitem == 4)
			{
				menuitem = 1;
			}
		}

		else if (up && page == 5 ) {
			up = false;
			lcdClearLine(2);
			volume--;
		}
		
		else if (down && page == 6 ) {
			down = false;
			lcdClearLine(2);
			contrast++;
			//setContrast();
		}

		else if (down && page == 8) {
			down = false;
			lcdClearLine(2);
			menuitem++;
			if (menuitem == 8)
			{
				menuitem = 1;
			}
		}

		else if (down && page == 9) {
			down = false;
			lcdClearLine(2);
			menuitem++;
			if (menuitem == 6)
			{
				menuitem = 1;
			}
		}
		else if (down && page == 10 ) {
			down = false;
			lcdClearLine(2);
			menuitem++;
			if (menuitem == 3)
			{
				menuitem = 1;
			}
		}




		

        //---------------------------------------------SELECT button functions---------------------------------------
		if (select) {
			select = false;

			if (page == 0)
			{
				lcdClear();
				page = 1;
				menuitem = 1;
				
			}
			else if (page == 1 && menuitem == 1)
			{
				lcdClear();
				page = 3;
				menuitem = 1;
			}
			else if (page == 1 && menuitem == 2)
			{
				lcdClear();
				page = 2;
			}

			else if (page == 1 && menuitem == 3)
			{
				lcdClear();
				page = 4;
				menuitem = 1;

			}

			
			else if (page == 2)
			{
				lcdClear();
				page = 1;
			}
// 			else if (page == 3 && menuitem == 1)
// 			{
// 				lcdClear();
// 				page = 7;
// 			}
			else if (page == 3 && menuitem == 1)
			{
				lcdClear();
				page = 8;
				menuitem = 1;
			}
			else if (page == 3 && menuitem == 2)
			{
				lcdClear();
				page = 9;
				menuitem = 1;
			}
			else if (page == 4 && menuitem == 1)
			{
				lcdClear();
				page = 5;
			}
			else if (page == 4 && menuitem == 2)
			{
				lcdClear();
				page = 6;
			}
			else if (page == 4 && menuitem == 3)
			{
				resetDefaults();
			}
			else if (page == 5)
			{
				lcdClear();
				page = 4;
				menuitem = 1;
			}
			else if (page == 6)
			{
				lcdClear();
				page = 4;
				menuitem = 2;
			}
			else if (page == 7)
			{
				lcdClear();
				page = 3;
				menuitem = 1;
			}else if (page == 8)
			{
				lcdClear();
				page = 10;
				menuitem = 1;
			}else if (page == 10 && menuitem == 1)
			{
				lcdClear();
				page = 11;
			}
			else if (page == 10 && menuitem == 2)
			{
				lcdClear();
				page = 12;
				menuitem = 1;
			}
			else if (page == 9)
			{
					if(menuitem == 1){
						musicplay(melody1, sizeof(melody1), sizeof(melody1[0]),108);
					}
					else if(menuitem == 2){
						musicplay(melody2, sizeof(melody2), sizeof(melody2[0]),70);
					}
					else if(menuitem == 3){
						musicplay(melody3, sizeof(melody3), sizeof(melody3[0]),140);
					}
					else if(menuitem == 4){
						musicplay(melody4, sizeof(melody4), sizeof(melody4[0]),144);
					}
					else if(menuitem == 5){
						musicplay(melody5, sizeof(melody5), sizeof(melody5[0]),108);
					}
				}
			}
		
		//---------------------------------------BACK button functions-------------------------------------------------------------- 
		if (back) {
			back = false;
			if (page == 0)
			{
				if (backlight)
				{
					backlight = false;
					turnBacklightOff();
				}
				else
				{
					backlight = true;
					turnBacklightOn();
				}
			}
			else if (page == 1)
			{
				lcdClear();
				page = 0;
			}
			else if (page == 2)
			{
				lcdClear();
				page = 1;
				menuitem = 2;
			}
			else if (page == 3)
			{
				lcdClear();
				page = 1;
				menuitem = 1;
			}
			else if (page == 4)
			{
				lcdClear();
				page = 1;
				menuitem = 3;
			}
			else if (page == 5)
			{
				lcdClear();
				page = 4;
				menuitem = 1;
			}
			else if (page == 6)
			{
				lcdClear();
				page = 4;
				menuitem = 2;
			}

			else if (page == 7)
			{
				lcdClear();
				page = 3;
				menuitem = 1;
			}
			else if (page == 8)
			{
				lcdClear();
				page = 3;
				menuitem = 2;
			}
			else if (page == 9)
			{
				lcdClear();
				page = 3;
				menuitem = 2;
			}
			else if (page == 10)
			{
				lcdClear();
				page = 8;
				menuitem = 1;
			}

		}

	}
}
void checkIfDownButtonIsPressed()
{
	if (downButtonState != lastDownButtonState)
	{
		if (downButtonState == 0)
		{
			down = true;
		}
		_delay_ms(20);
	}
	lastDownButtonState = downButtonState;
}

void checkIfUpButtonIsPressed()
{
	if (upButtonState != lastUpButtonState)
	{
		if (upButtonState == 0) {
			up = true;
		}
		_delay_ms(20);
	}
	lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
	if (selectButtonState != lastSelectButtonState)
	{
		if (selectButtonState == 0) {
			select = true;
		}
		_delay_ms(20);
	}
	lastSelectButtonState = selectButtonState;
}

void checkIfBackButtonIsPressed()
{
	if (backButtonState != lastBackButtonState)
	{
		if (backButtonState == 0) {
			back = true;
		}
		_delay_ms(20);
	}
	lastBackButtonState = backButtonState;
}

void drawMenu()
{
	switch(page){
		case 0:
		timeDisplayInt();
		break;
		case 1:
		mainMenuInt();
		break;
		case 2:
		dateTimeSetInt();
		break;
		case 3:
		alarmMenuInt();
		break;
		case 4:
		settingMenuInt();
		break;
		case 5:
		volumeInt();
		break;
		case 6:
		contrastInt();
		break;
		
		case 8:
		alarmListInt();
		break;
		case 9:
		alarmTonesInt();
		break;
		case 10:
		alarmSettingInt();
		break;
		case 11:
		editAlarmInt(alarmNo);
		break;
		case 12:
		deleteAlarm(alarmNo);
		break;
		// 		default:
		// 		editAlarmInt(alarmNo);
		
	}
	
}






