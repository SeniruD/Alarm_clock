 /*Code by Yasara Hasini
 Audio Output of Digital Alarm Clock */
 
//define music notes with their frequencies
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

#define F_CPU 16000000UL  //16MHz

#define __DELAY_BACKWARD_COMPATIBLE__     //define backward compatible to use delay_ms with changing value(variable)

#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>
#include <stdlib.h>

//Zelda's Lullaby - The Legend of Zelda Ocarina of Time.
int melody1[] = {NOTE_E4,2, NOTE_G4,4,NOTE_D4,2, NOTE_C4,8, NOTE_D4,8,NOTE_E4,2, NOTE_G4,4,NOTE_D4,-2,NOTE_E4,2, NOTE_G4,4,NOTE_D5,2, NOTE_C5,4,NOTE_G4,2, NOTE_F4,8, NOTE_E4,8,NOTE_D4,-2,NOTE_E4,2, NOTE_G4,4,NOTE_D4,2, NOTE_C4,8, NOTE_D4,8,NOTE_E4,2, NOTE_G4,4,NOTE_D4,-2,NOTE_E4,2, NOTE_G4,4,NOTE_D5,2, NOTE_C5,4,NOTE_G4,2, NOTE_F4,8, NOTE_E4,8,NOTE_F4,8, NOTE_E4,8, NOTE_C4,2,NOTE_F4,2, NOTE_E4,8, NOTE_D4,8,NOTE_E4,8, NOTE_D4,8, NOTE_A3,2,NOTE_G4,2, NOTE_F4,8, NOTE_E4,8,NOTE_F4,8, NOTE_E4,8, NOTE_C4,4, NOTE_F4,4,NOTE_C5,-2};
//Greensleeves
int melody2[] = {NOTE_G4,8,NOTE_AS4,4, NOTE_C5,8, NOTE_D5,-8, NOTE_DS5,16, NOTE_D5,8,NOTE_C5,4, NOTE_A4,8, NOTE_F4,-8, NOTE_G4,16, NOTE_A4,8,NOTE_AS4,4, NOTE_G4,8, NOTE_G4,-8, NOTE_FS4,16, NOTE_G4,8,NOTE_A4,4, NOTE_FS4,8, NOTE_D4,4, NOTE_G4,8,NOTE_AS4,4, NOTE_C5,8, NOTE_D5,-8, NOTE_DS5,16, NOTE_D5,8,NOTE_C5,4, NOTE_A4,8, NOTE_F4,-8, NOTE_G4,16, NOTE_A4,8,NOTE_AS4,-8, NOTE_A4,16, NOTE_G4,8, NOTE_FS4,-8, NOTE_E4,16, NOTE_FS4,8,NOTE_G4,-2, NOTE_F5,2, NOTE_E5,16, NOTE_D5,8,NOTE_C5,4, NOTE_A4,8, NOTE_F4,-8, NOTE_G4,16, NOTE_A4,8,NOTE_AS4,4, NOTE_G4,8, NOTE_G4,-8, NOTE_FS4,16, NOTE_G4,8,NOTE_A4,4, NOTE_FS4,8, NOTE_D4,04,NOTE_F5,2, NOTE_E5,16, NOTE_D5,8,NOTE_C5,4, NOTE_A4,8, NOTE_F4,-8, NOTE_G4,16, NOTE_A4,8,NOTE_AS4,-8, NOTE_A4,16, NOTE_G4,8, NOTE_FS4,-8, NOTE_E4,16, NOTE_FS4,8,NOTE_G4,-2};
//Cantina Band - Star Wars
int melody3[] = {NOTE_B4,-4, NOTE_E5,-4, NOTE_B4,-4, NOTE_E5,-4,NOTE_B4,8,  NOTE_E5,-4, NOTE_B4,8, REST,8,  NOTE_AS4,8, NOTE_B4,8,NOTE_B4,8,  NOTE_AS4,8, NOTE_B4,8, NOTE_A4,8, REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_G4,8,NOTE_G4,4,  NOTE_E4,-2,NOTE_B4,-4, NOTE_E5,-4, NOTE_B4,-4, NOTE_E5,-4,NOTE_B4,8,  NOTE_E5,-4, NOTE_B4,8, REST,8,  NOTE_AS4,8, NOTE_B4,8, NOTE_A4,-4, NOTE_A4,-4, NOTE_GS4,8, NOTE_A4,-4,NOTE_D5,8,  NOTE_C5,-4, NOTE_B4,-4, NOTE_A4,-4,NOTE_B4,-4, NOTE_E5,-4, NOTE_B4,-4, NOTE_E5,-4,NOTE_B4,8,  NOTE_E5,-4, NOTE_B4,8, REST,8,  NOTE_AS4,8, NOTE_B4,8,NOTE_D5,4, NOTE_D5,-4, NOTE_B4,8, NOTE_A4,-4,NOTE_G4,-4, NOTE_E4,-2,NOTE_E4, 2, NOTE_G4,2, NOTE_B4, 2, NOTE_D5,2,  NOTE_F5, -4, NOTE_E5,-4, NOTE_AS4,8, NOTE_AS4,8, NOTE_B4,4, NOTE_G4,4};
//Hedwig's theme from harry potter movies
int melody4[] = { NOTE_D4, 4,NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,NOTE_G4, 2, NOTE_D5, 4,NOTE_C5, -2, NOTE_A4, -2,NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,NOTE_F4, 2, NOTE_GS4, 4,NOTE_D4, -1,NOTE_D4, 4,NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,NOTE_G4, 2, NOTE_D5, 4,NOTE_F5, 2, NOTE_E5, 4,NOTE_DS5, 2, NOTE_B4, 4,NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,NOTE_CS4, 2, NOTE_B4, 4,NOTE_G4, -1,NOTE_AS4, 4,NOTE_D5, 2, NOTE_AS4, 4,NOTE_D5, 2, NOTE_AS4, 4,NOTE_DS5, 2, NOTE_D5, 4, NOTE_CS5, 2, NOTE_A4, 4, NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4, NOTE_CS4, 2, NOTE_D4, 4,NOTE_D5, -1,REST,4, NOTE_AS4,4,NOTE_D5, 2, NOTE_AS4, 4,NOTE_D5, 2, NOTE_AS4, 4,NOTE_F5, 2, NOTE_E5, 4,NOTE_DS5, 2, NOTE_B4, 4,NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,NOTE_CS4, 2, NOTE_AS4, 4,NOTE_G4, -1};
//Song of storms - The Legend of Zelda Ocarina of Time
int melody5[] = {NOTE_D4,4, NOTE_A4,4, NOTE_A4,4,REST,8, NOTE_E4,8, NOTE_B4,2,NOTE_F4,4, NOTE_C5,4, NOTE_C5,4,REST,8, NOTE_E4,8, NOTE_B4,2,NOTE_D4,4, NOTE_A4,4, NOTE_A4,4,REST,8, NOTE_E4,8, NOTE_B4,2,NOTE_F4,4, NOTE_C5,4, NOTE_C5,4,REST,8, NOTE_E4,8, NOTE_B4,2,NOTE_D4,8, NOTE_F4,8, NOTE_D5,2, NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,NOTE_E5,-4, NOTE_F5,8, NOTE_E5,8, NOTE_E5,8,NOTE_E5,8, NOTE_C5,8, NOTE_A4,2,NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,NOTE_A4,-2,NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,NOTE_E4,-2,NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,NOTE_D4,8, NOTE_F4,8, NOTE_D5,2,NOTE_E5,-4, NOTE_F5,8, NOTE_E5,8, NOTE_E5,8,NOTE_E5,8, NOTE_C5,8, NOTE_A4,2,NOTE_A4,4, NOTE_D4,4, NOTE_F4,8, NOTE_G4,8,NOTE_A4,2, NOTE_A4,4,NOTE_D4,1};


void musicplay(int melody[],int sizex, int sizey, int tempo) {
	int notes = sizex/sizey/2 ;         //number of frequencies in melody list
	int wholenote = (60000 * 4) / tempo;  
	int divider = 0, noteDuration = 0;
	
	for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
		divider = melody[thisNote + 1];
		
		if (divider > 0) {
			noteDuration = (wholenote) / divider;
		}
		else if (divider < 0) {
			noteDuration = (wholenote) / abs(divider);
			noteDuration *= 1.5;
		}

		if (!(PIND & 0x80)){      //check whether the stop button is pressed, if so, stop melody
			PORTB &= 0x00;
			break;
		}
		uint16_t delay = 1000000/(2*melody[thisNote]);    //time for one frequency(half period in micro seconds)
		uint16_t tmp = 5*noteDuration;                  //speed of the sound track
		uint16_t delaysm = delay/50;               
		uint16_t cycles = tmp/delaysm;                
		while (cycles>0)
		{  //frequency generator loop
			PORTB |= (1<<PORTB2);      
		    _delay_us(delay);
			PORTB &= ~(1<<PORTB2);
			_delay_us(delay);
			cycles--;
			
			if (!(PIND & 0x80)){      //check whether the stop button is pressed, if so, stop melody
				PORTB &= 0x00;
				break;
			}
		}
		}
	}
		

int main(void)
{
	DDRD = 0x00;    //Set PORTD s to inputs
	DDRB = 0x04;    //Set PORTB2 to output
	PORTD = 0xFC;   //Set PORTD s to input pull ups
	PORTB = 0x00;

	while (1)
	{
		if (!(PIND & 0x04)) {
			musicplay(melody1, sizeof(melody1), sizeof(melody1[0]),108);
		}

		if( !(PIND & 0x08)){
			musicplay(melody2, sizeof(melody2), sizeof(melody2[0]),70);
		}
		
		if( !(PIND & 0x10)){
			musicplay(melody3, sizeof(melody3), sizeof(melody3[0]),140);
		}

		if( (!(PIND & 0x20))){
			musicplay(melody4, sizeof(melody4), sizeof(melody4[0]),144);
		}

		if( !(PIND & 0x40)){
			musicplay(melody5, sizeof(melody5), sizeof(melody5[0]),108);
		}
		_delay_ms(10);
		
	}
}
