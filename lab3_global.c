#include <stdio.h>
#include <io.h>
#include <system.h>
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"

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

//		leds
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
#define E_HEX SEGA | SEGD |SEGE | SEGF | SEGG
#define R_HEX SEGE | SEGG

/*  --------------------------------------------------------------------------------------------- */
#define HEX_SIZE 8
#define DIR_LED LED9
#define ERROR_LED LED10
#define DIR_PB KEY1

#define S1 0
#define S2 1
#define S3 2
#define S4 3
#define S5 4

#define LED_S1 LED0
#define LED_S2 LED1
#define LED_S3 LED2
#define LED_S4 LED3
#define LED_S5 LED4

#define CD1 SW0
#define CD2 SW1
#define CD3 SW2
#define CD4 SW3
#define CD5 SW4
#define CD6 SW5
#define CD7 SW6
#define CD8 SW7
#define CD9 SW8
#define CD10 SW9
/*  --------------------------------------------------------------------------------------------- */


struct interrupt_data
{
	volatile int* leds_addr;
	volatile int* sliders_addr;
	volatile int* pb_addr;
	volatile int* hex_addr;
};

static void handle_sliders_interrupt(struct interrupt_data* data);
static void handle_pushbuttons_interrupt(struct interrupt_data *data);

int digit_to_hex(int value);

int leds = 0;
int rooms[5] = {};
int dir = 0;
int flag = 0;
int sliders = 0;
int pb = 0;

int main()
{


  struct interrupt_data data;
  data.leds_addr = (int* )LEDS_BASE;
  data.sliders_addr = (int* )SW_SLIDERS_BASE;
  data.pb_addr = (int *) PUSHBUTTON_BASE;

  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PUSHBUTTON_BASE, 0b1111);
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SW_SLIDERS_BASE, 0b1111111111);

  alt_ic_isr_register(SW_SLIDERS_IRQ_INTERRUPT_CONTROLLER_ID, SW_SLIDERS_IRQ, handle_sliders_interrupt, &data, 0x0);
  alt_ic_isr_register(PUSHBUTTON_IRQ_INTERRUPT_CONTROLLER_ID, PUSHBUTTON_IRQ, handle_pushbuttons_interrupt, &data, 0x0);

  alt_ic_irq_enable(SW_SLIDERS_IRQ_INTERRUPT_CONTROLLER_ID, SW_SLIDERS_IRQ);
  alt_ic_irq_enable(PUSHBUTTON_IRQ_INTERRUPT_CONTROLLER_ID, PUSHBUTTON_IRQ);

  while(1);
  return 0;
}

static void handle_sliders_interrupt(struct interrupt_data* data)
{
    sliders = IORD(data->sliders_addr, 0);

    if(flag == 0 && sliders == 0)
    	flag = 1;

    if(flag == 1 && sliders != 0) {
    	if(sliders & CD1) {
    		if(dir == 0)
    			rooms[S5]++;
    		else
    			rooms[S5]--;
		}
		else if(sliders & CD2) {
			if(dir == 0)
				rooms[S1]++;
			else
				rooms[S1]--;
		  }
		else if(sliders & CD3) {
			if(dir == 0)
				rooms[S3]++;
			else
				rooms[S3]--;
		  }
		else if(sliders & CD4) {
			if(dir == 0) {
				rooms[S1]++;
				rooms[S3]--;
			}
			else {
				rooms[S1]--;
				rooms[S3]++;
			  }
		  }
		else if(sliders & CD5) {
			if(dir == 0) {
				rooms[S1]--;
				rooms[S5]++;
			  }
			else {
				rooms[S1]++;
				rooms[S5]--;
			}
		}
		else if(sliders & CD6) {
			if(dir == 0) {
				rooms[S5]--;
				rooms[S4]++;
			}
			else {
				rooms[S5]++;
				rooms[S4]--;
			}
		  }
		else if(sliders & CD7) {
			if(dir == 0)
				rooms[S4]--;
			else
				rooms[S4]++;
		}
		else if(sliders & CD8) {
			if(dir == 0)
				rooms[S2]--;
			else
				rooms[S2]++;
		}
		else if(sliders & CD9) {
			if(dir == 0)
				rooms[S2]++;
			else
				rooms[S2]--;
		}
		else if(sliders & CD10) {
			if(dir == 0) {
				rooms[S4]++;
				rooms[S2]--;
			}
			else {
				rooms[S4]--;
				rooms[S2]++;
			}
		}
    	flag = 0;
    }

    if(rooms[S1] > 0)
    	leds |= LED_S1;
    else
    	leds &= ~(LED_S1);

	if(rooms[S2] > 0)
		leds |= LED_S2;
	else
		leds &= ~(LED_S2);

	if(rooms[S3] > 0)
		leds |= LED_S3;
	else
		leds &= ~(LED_S3);

	if(rooms[S4] > 0)
		leds |= LED_S4;
	else
		leds &= ~(LED_S4);

	if(rooms[S5] > 0)
		leds |= LED_S5;
	else
		leds &= ~(LED_S5);


	if(rooms[S1] < 0 || rooms[S2] < 0 || rooms[S3] < 0 || rooms[S4] < 0 || rooms[S5])
		leds |= ERROR_LED;
	else
		leds &= ~(ERROR_LED);

	IOWR(data->leds_addr, 0, leds);


	if(leds & ERROR_LED) {
		IOWR(data->hex_addr, 0, ZERO);
		IOWR(data->hex_addr, 1, ZERO);
		IOWR(data->hex_addr, 2, ZERO);
		IOWR(data->hex_addr, 3, R_HEX);
		IOWR(data->hex_addr, 4, R_HEX);
		IOWR(data->hex_addr, 5, E_HEX);
	}
	else {
		IOWR(data->hex_addr, 0, digit_to_hex(rooms[S1]));
		IOWR(data->hex_addr, 1, digit_to_hex(rooms[S2]));
		IOWR(data->hex_addr, 2, digit_to_hex(rooms[S3]));
		IOWR(data->hex_addr, 3, digit_to_hex(rooms[S4]));
		IOWR(data->hex_addr, 4, digit_to_hex(rooms[S5]));
	}
}

static void handle_pushbuttons_interrupt(struct interrupt_data *data)
{
    // kirunek
    pb = IORD(data->pb_addr, 0);
    pb = DIR_PB & pb;
    if(!pb) {
        if(dir == 1)
            dir = 0;
        else
            dir = 1;
    }

    if(dir == 1)
    	leds |= DIR_LED;
    else
		leds &= ~(DIR_LED);

    IOWR(LEDS_BASE, 0, leds);
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
			return SEGG;
	}
}
