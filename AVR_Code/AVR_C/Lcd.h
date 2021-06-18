/*
 * LCD_I2C.c
 *
 * Created: 04/09/2017 07:37:47 p. m.
 * Author : Seniru Dissanayake
 */ 

#include <avr/io.h>
#include <util/delay.h>


#define BV(x)		(1 << x)
#define setBit(P,B)		P |= BV(B)
#define clearBit(P,B)		P &= ~BV(B)
#define toggleBit(P,B)                   P ^= BV(B)
#define RS                  PORTB0
#define En                  PORTB1


//-----Prototypes-------//
void lcdInit();
void lcdCmdWrite( char cmd);
void lcdDataWrite( char data);
void lcdSetCursor(char row, char col);
void lcdPrint(char *string_ptr);
void lcdClear();
int digitalRead(int x);
//----------------------//




void lcdInit()
{
	_delay_ms(20);
	lcdCmdWrite(0x02);	      //Initialize the LCD in 4bit Mode
	lcdCmdWrite(0x28);       //to initialize LCD in 2 lines, 5X7 dots and 4bit mode.
	lcdCmdWrite(0x0C);	      // Display ON cursor OFF
	lcdCmdWrite(0x06);        // Auto increment Cursor
	lcdCmdWrite(0x01);	      // Clear the LCD
	lcdCmdWrite(0x80);	      // Move the Cursor to First line First Position
	
	
}

void lcdCmdWrite( char cmd)
{
	
	PORTB = (cmd & 0xf0);        // Send the Higher Nibble of the command to LCD
	clearBit(PORTB,RS);			 // Register select = 0
	setBit(PORTB,En);            // Enable high to low
	_delay_us(120);
	clearBit(PORTB,En);
	
	_delay_us(10);
	
	PORTB = ((cmd<<4) & 0xf0);   // Send the Lower Nibble of the command to LCD
	clearBit(PORTB,RS);          // Register select = 0
	setBit(PORTB,En);			 // Enable high to low
	_delay_us(120);
	clearBit(PORTB,En);
	_delay_ms(1);

}

void lcdDataWrite( char data)
{
	PORTB = (data & 0xf0);	  // Send the Higher Nibble of the Data to LCD
	setBit(PORTB,RS);         // Register select = 1
	setBit(PORTB,En);		  // Enable high to low
	_delay_us(120);
	clearBit(PORTB,En);
	
	_delay_us(10);
	
	PORTB = ((data <<4) & 0xf0); // Send the Lower Nibble of the Data to LCD
	setBit(PORTB,RS);            // Register select = 1
	setBit(PORTB,En);   		 // Enable high to low
	_delay_us(120);
	clearBit(PORTB,En);
	_delay_ms(1);
	
}

void lcdClear()
{
	lcdCmdWrite(0x01);	// Clear the LCD and go to First line First Position
	lcdCmdWrite(0x80);
}

void lcdPrint(char *string_ptr)
{
	while(*string_ptr)
	lcdDataWrite(*string_ptr++);
}

void lcdSetCursor(char col, char row)
{
	if (row == 0 && col<16)
	lcdCmdWrite((col & 0x0F)|0x80);
	else if (row == 1 && col<16)
	lcdCmdWrite((col & 0x0F)|0xC0);
	else if (row == 2 && col<16)
	lcdCmdWrite(((col) & 0x0F)| 0x90);
	else if (row == 3 && col<16)
	lcdCmdWrite(((col) & 0x0F)|0xD0);
	lcdCmdWrite(0x0C); //enable cursor
}

void lcdClearLine(int row){
	lcdSetCursor(0,row-1);
	for(int i=0 ; i<16;i++)
		lcdPrint(" ");
	
}
int digitalRead(int x){
	if (~PIND & BV(x))
	return 1;
	else
	return 0;

}

