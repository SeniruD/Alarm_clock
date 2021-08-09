/*------------------------Header File for Time and Alarm formatting functions------------------------*/
#include <avr/io.h>
#define F_CPU 8000000UL
#define SCL_CLOCK  100000L
#define Device_Write_address	0xD0
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdio.h>


extern int page;

const int del=200;		//debounce delay
int sec;
int starthour;		//time counting variables
int startmins;
int startdate;
int startmnth;
int startyr;

int startAlarmHr=0;	
int startAlarmMin=0;

/*--------------------------------------------------------------------------------------------*/

int alarmHoursList[7] = {0};	//Contains alarm hours of 7 alarms
int alarmMinsList[7] = {0};		//Contains alarm minutes of 7 alarms

int alarmStatus[7] = {0};		//status of each alarm; 0 = off, 1 = on
	
/*--------------------------------------------------------------------------------------------*/

int noOfSetAlarms = 0;

int alarmNo = 0;				//alarm number counter
	
int mins = startmins;	
int hours = starthour;
int date = startdate;
int month = startmnth;
int yr = startyr;
/*--------------------------------------------------------------------------------------------*/

int dateTimeArray[] = {mins,hours,date,month,yr};	//contains user input date and time 
	
/*--------------------------------------------------------------------------------------------*/


bool pressed_button (int btn);
void dateTimeSetInt();
void alarmListInt();
void alarmDisplay(int alarmNo);
void deleteAlarm(int alarmNo);



void dateTimeSetInt()		//set date and time
{
	
	
	while(true)
	{
		
		
		
		lcdSetCursor(0,0);
		lcdPrint("   Enter Hr:    ");
		char str_sthour[10];
		sprintf(str_sthour,"%x",hours);
		lcdSetCursor(7,1);
		lcdPrint(str_sthour);
		lcdPrint(" ");
		
		if (pressed_button(PIND5))
		{
			hours++;
			hours%=24;
		}
		else if (pressed_button(PIND7))
		{
			hours--;
			if (hor<0)
			{
				hours=23;
			}
		}
		else if (pressed_button(PIND6))
		{
			hor=hours;
			break;
		}
		else if (pressed_button(PIND4))
		{
			break;
		}
		_delay_ms(del);
	}
	_delay_ms(del);
	while(true)
	{
		lcdSetCursor(0,0);
		lcdPrint("  Enter Mins :  ");
		char str_stmin[10];
		sprintf(str_stmin,"%x",min);
		lcdSetCursor(7,1);
		lcdPrint(str_stmin);
		lcdPrint(" ");
		
		if (pressed_button(PIND5))
		{
			mins++;
			mins%=60;
		}
		else if (pressed_button(PIND7))
		{
			mins--;
			if (mins<0)
			{
				mins=59;
			}
		}
		else if(pressed_button(PIND6))
		{
			min=mins;
			break;
		}
		else if (pressed_button(PIND4))
		{
			break;
		}
		_delay_ms(del);
	}
	_delay_ms(del);
	while(true)
	{
		lcdSetCursor(0,0);
		lcdPrint("   Enter Date:    ");
		char str_date[10];
		sprintf(str_date,"%d",startdate);
		lcdSetCursor(7,1);
		lcdPrint(str_date);
		lcdPrint(" ");
		
		if (pressed_button(PIND5))
		{
			startdate++;
			startdate%=32;
			
		}
		else if (pressed_button(PIND7))
		{
			startdate--;
			if (startdate<1)
			{
				startdate=31;
			}
		}
		else if (pressed_button(PIND6))
		{
			date=startdate;
			break;
		}
		else if (pressed_button(PIND4))
		{
			break;
		}
		_delay_ms(del);
	}
	_delay_ms(del);
	while(true)
	{
		lcdSetCursor(0,0);
		lcdPrint("  Enter Month:    ");
		char str_mnth[10];
		sprintf(str_mnth,"%d",startmnth);
		lcdSetCursor(7,1);
		lcdPrint(str_mnth);
		lcdPrint(" ");
		
		if (pressed_button(PIND5))
		{
			startmnth++;
			startmnth%=13;
			
		}
		else if (pressed_button(PIND7))
		{
			startmnth--;
			if (startmnth<1)
			{
				startmnth=12;
			}
		}
		else if (pressed_button(PIND6))
		{
			month=startmnth;
			break;
		}
		else if (pressed_button(PIND4))
		{
			break;
		}
		_delay_ms(del);
	}
	_delay_ms(del);
	while(true)
	{
		lcdSetCursor(0,0);
		lcdPrint("  Enter Year:    ");
		char str_yr[10];
		sprintf(str_yr,"%d",startyr);
		lcdSetCursor(5,1);
		lcdPrint(str_yr);
		lcdPrint(" ");
		
		if (pressed_button(PIND5))
		{
			startyr++;
			
		}
		else if (pressed_button(PIND7))
		{
			startyr--;
		}
		else if (pressed_button(PIND6))
		{
			yr=startyr;
			break;
		}
		else if (pressed_button(PIND4))
		{
			break;
		}
		_delay_ms(del);
	}
	lcdClear();
	lcdPrint("  Time is set!   ");
	_delay_ms(1000);
	lcdClear();
	page=1;
}

void alarmListInt(){		//prints list of alarms
	
	lcdSetCursor(3, 0);
	lcdPrint("ALARM LIST");
	if (menuitem == 1)
	{
		alarmNo = 1;
		alarmDisplay(alarmNo);
	}
	else if (menuitem == 2)
	{
		alarmNo = 2;
		alarmDisplay(alarmNo);
	}
	else if (menuitem == 3)
	{
		alarmNo = 3;
		alarmDisplay(alarmNo);
	}
	else if (menuitem == 4)
	{
		alarmNo = 4;
		alarmDisplay(alarmNo);
	}
	else if (menuitem == 5)
	{
		alarmNo = 5;
		alarmDisplay(alarmNo);
	}
	else if (menuitem == 6)
	{
		alarmNo = 6;
		alarmDisplay(alarmNo);
	}
	else if (menuitem == 7)
	{
		alarmNo = 7;
		alarmDisplay(alarmNo);
	}
}

void editAlarmInt(int currentAlarm)		//set or modify alarms
{
	while(true)
	{
		lcdSetCursor(0,0);
		lcdPrint("   Enter Hr:    ");
		char str_sthour[10];
		sprintf(str_sthour,"%d",startAlarmHr);
		lcdSetCursor(7,1);
		lcdPrint(str_sthour);
		lcdPrint(" ");
		
		if (pressed_button(PIND5))
		{
			startAlarmHr++;
			startAlarmHr%=24;
		}
		else if (pressed_button(PIND7))
		{
			startAlarmHr--;
			if (startAlarmHr<0)
			{
				startAlarmHr=23;
			}
		}
		else if (pressed_button(PIND6))
		{
			alarmHoursList[currentAlarm-1]=startAlarmHr;
			
			break;
		}
		else if (pressed_button(PIND4))
		{
			break;
		}
		_delay_ms(del);
	}
	_delay_ms(del);
	while(true)
	{
		lcdSetCursor(0,0);
		lcdPrint("  Enter Mins :  ");
		char str_stmin[10];
		sprintf(str_stmin,"%d",startAlarmMin);
		lcdSetCursor(7,1);
		lcdPrint(str_stmin);
		lcdPrint(" ");
		
		if (pressed_button(PIND5))
		{
			startAlarmMin++;
			startAlarmMin%=60;
		}
		else if (pressed_button(PIND7))
		{
			startAlarmMin--;
			if (startAlarmMin<0)
			{
				startAlarmMin=59;
			}
		}
		else if(pressed_button(PIND6))
		{
			alarmMinsList[currentAlarm-1]=startAlarmMin;
			
			break;
		}
		else if (pressed_button(PIND4))
		{
			break;
		}
		_delay_ms(del);
	}
	if (alarmStatus[currentAlarm-1]==0)
	{
		alarmStatus[currentAlarm-1]=1;
		noOfSetAlarms+=1;
		lcdClear();
		lcdPrint("  Alarm is set!   ");
		_delay_ms(1000);
		page = 8;
		lcdClear();
	}
	else
	{
		lcdClear();
		lcdPrint("  Alarm is set!   ");
		_delay_ms(1000);
		page = 8;
		lcdClear();
	}
}

bool pressed_button (int btn)		//determines whether the given button is pressed or not
{
	if (!(PIND & (1<<btn)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void alarmDisplay(int alarmNo)		
{
	char Hr[10];
	sprintf(Hr,"%d",alarmHoursList[alarmNo-1]);
	
	char Min[10];
	sprintf(Min,"%d",alarmMinsList[alarmNo-1]);
	
	if (alarmStatus[alarmNo-1]==1)
	{
		lcdSetCursor(5, 1);
		lcdPrint(Hr);
		lcdSetCursor(7, 1);
		lcdPrint(":");
		lcdSetCursor(10, 1);
		lcdPrint(Min);
	}
	else
	{
		lcdSetCursor(1, 1);
		lcdPrint("<<Empty Alarm>>");
	}
}

void deleteAlarm(int alarmNo)		//for changing alarm status (0 and 1)
{
	alarmStatus[alarmNo-1]=0;
	lcdClear();
	lcdPrint("  Alarm Deleted ");
	_delay_ms(1000);
	lcdClear();
	page = 8;
}

