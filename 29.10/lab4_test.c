#include <stdio.h>
#include <io.h>
#include <system.h>
#include "alt_types.h"
#include "sys/alt_irq.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_timestamp.h"
#include <unistd.h>

#define  SW0 0x00000001
#define  SW1 0x00000002
#define  SW2 0x00000004
#define  SW3 0x00000008
#define  SW4 0x00000010
#define  SW5 0x00000020
#define  SW6 0x00000040
#define  SW7 0x00000080
#define  SW8 0x00000100
#define  SW9 0x00000200
#define  SW10 0x00000400

//      pushbuttons
#define  KEY1 0x00000002
#define  KEY2 0x00000004
#define  KEY3 0x00000008
#define  KEY4 0x00000010

//      leds
#define  LED0 0x00000001
#define  LED1 0x00000002
#define  LED2 0x00000004
#define  LED3 0x00000008
#define  LED4 0x00000010
#define  LED5 0x00000020
#define  LED6 0x00000040
#define  LED7 0x00000080
#define  LED8 0x00000100
#define  LED9 0x00000200
#define  LED10 0x00000400

//      hex
#define  SEGA 0x00001
#define  SEGB 0x00002
#define  SEGC 0x00004
#define  SEGD 0x00008
#define  SEGE 0x00010
#define  SEGF 0x00020
#define  SEGG 0x00040

//     hex - numbers
#define ZERO SEGA | SEGB | SEGC | SEGD |SEGE | SEGF
#define ONE  SEGB | SEGC
#define TWO  SEGA | SEGB | SEGG | SEGE | SEGD
#define THREE SEGA | SEGB | SEGC | SEGD | SEGG
#define FOUR SEGC | SEGG | SEGF
#define FIVE SEGA | SEGC | SEGD | SEGF  | SEGG
#define SIX SEGA | SEGC | SEGD | SEGE | SEGF | SEGG
#define SEVEN SEGA | SEGB | SEGC
#define EIGHT SEGA | SEGB | SEGC | SEGD |SEGE | SEGF | SEGG
#define NINE SEGA | SEGB | SEGC | SEGD | SEGF | SEGG

/*  --------------------------------------------------------------------------------------------- */
#define HEX_SIZE 8
#define DIR_LED LED8
#define DIR_PB KEY1
#define ERROR_LED LED9
#define ERROR_RESET KEY2
#define SEC_TIMEOUT 2
#define E_HEX SEGA | SEGD |SEGE | SEGF | SEGG
#define R_HEX SEGE | SEGG

/*  --------------------------------------------------------------------------------------------- */

int digit_to_hex(int value);
double count_period_sec(int end, int start);

int main()
{
	if(alt_timestamp_start() != 0) {
		printf("timer error");
	}
	else {
		int sw = 0;
		while(1) {
			int start = alt_timestamp();
			sw = IORD(SW_SLIDERS_BASE, 0);
			if(SW0 & sw) {
				break;
			}
			int end = alt_timestamp();
			int freq = alt_timestamp_freq();
			int diff = (double)(end - start) / (double)freq;
			printf("FREQ = %d\n start = %d\n end = %d\n diff = %f",
					freq, start, end, diff);
		}

	}
  return 0;
}

double count_period_sec(int end, int start) {
	int freq = alt_timestamp_freq();
	return (double)(end - start) / (double)freq;
}

int digit_to_hex(int value){
    switch(value) {
        case 0:
            return ZERO;
            break;
        case 1:
            return ONE;
            break;
        case 2:
            return TWO;
            break;
        case 3:
            return THREE;
            break;
        case 4:
            return FOUR;
            break;
        case 5:
            return FIVE;
            break;
        case 6:
            return SIX;
            break;
        case 7:
            return SEVEN;
            break;
        case 8:
            return EIGHT;
            break;
        case 9:
            return NINE;
            break;
        default:
            return NINE;
    }
}
