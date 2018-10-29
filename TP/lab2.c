#include <stdio.h>
#include <system.h>
#include <io.h>
  
//        sw_sliders
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
 
//      pushbuttons
#define  KEY1 0x0000000E
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
#define DIR_LED LED9
#define DIR_PB KEY1
#define ERROR_LED LED8

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
 
int digit_to_hex(int value);
 
int main()
{
    int pb = 0;
    int flagDirection = 0; 				// 0 => dol, lewo; 				1 => gora, prawo
    int osobyS1 = 0;
    int osobyS2 = 0;
    int osobyS3 = 0;
    int osobyS4 = 0;
    int osobyS5 = 0;
    int sliders = 0;
    int flag0 = 0;
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;
    int flag5 = 0;
    int flag6 = 0;
    int flag7 = 0;
    int flag8 = 0;
    int flag9 = 0;
    int leds = 0;
 
    while(1)
    {
      pb = IORD(PUSHBUTTON_BASE, 0);
      if(pb == KEY1){
          if(flagDirection==0){
              leds |= DIR_LED;
              flagDirection = 1;
          } else {
              leds &= ~(DIR_LED);
              flagDirection = 0;
          }
      }
      sliders = IORD(SW_SLIDERS_BASE, 0);
      switch(sliders){
      case CD1:
          if(flag0 == 0){
              if(flagDirection == 0)
                  osobyS5++;
              else
                  osobyS5--;
              flag0 = 1;
          }
          break;
      case CD2:
          if(flag1 == 0){
			  if(flagDirection == 0)
				  osobyS1++;
			  else
				  osobyS1--;
			  flag1 = 1;
		  }
          break;
      case CD3:
          if(flag2 == 0){
			  if(flagDirection == 0)
				  osobyS3++;
			  else
				  osobyS3--;
			  flag2 = 1;
          }
          break;

      case CD4:
          if(flag3 == 0){
			  if(flagDirection == 0){
				  osobyS3--;
				  osobyS1++;
			  }
			  else {
				  osobyS1--;
				  osobyS3++;
			  }
			  flag3 = 1;
          }
          break;

      case CD5:
          if(flag4 == 0){
			  if(flagDirection == 0) {
				  osobyS1--;
				  osobyS5++;
			  }
			  else {
				  osobyS1++;
				  osobyS5--;
			  }
			  flag4 = 1;
          }
          break;
      case CD6:
          if(flag5 == 0){
			  if(flagDirection == 0)
			  {
    	    	  osobyS5--;
    	    	  osobyS4++;
			  }
			  else
				  osobyS5++;
				  osobyS4--;
			  flag5 = 1;
		  }
		  break;
      case CD7:
          if(flag6 == 0){
			  if(flagDirection == 0)
				  osobyS4++;
			  else
				  osobyS4--;
			  flag6 = 1;
		  }
		  break;
      case CD8:
          if(flag7 == 0){
			  if(flagDirection == 0)
				  osobyS2--;
			  else
				  osobyS2++;
			  flag7 = 1;
		  }
		  break;
      case CD9:
          if(flag8 == 0){
			  if(flagDirection == 0)
				  osobyS2++;
			  else
				  osobyS2--;
			  flag8 = 1;
		  }
		  break;
      case CD10:
          if(flag9 == 0){
			  if(flagDirection == 0) {
				  osobyS2--;
				  osobyS4++;
			  }
			  else
			  {
				  osobyS4--;
				  osobyS2++;
			  }
			  flag9 = 1;
          }
          break;
      default:
          flag0 = 0;
          flag1 = 0;
          flag2 = 0;
          flag3 = 0;
          flag4 = 0;
          flag5 = 0;
          flag6 = 0;
          flag7 = 0;
          flag8 = 0;
          flag9 = 0;
      }
 
      if(osobyS1 > 0)
          leds |= LED_S1;
      else
          leds &= ~(LED_S1);
 
      if(osobyS2 > 0)
          leds |= LED_S2;
      else
    	  leds &= ~(LED_S2);

      if(osobyS3 > 0)
		  leds |= LED_S3;
	  else
		  leds &= ~(LED_S3);

      if(osobyS4 > 0)
		  leds |= LED_S4;
      else
		  leds &= ~(LED_S4);

      if(osobyS5 > 0)
		  leds |= LED_S5;
      else
		  leds &= ~(LED_S5);

      if(osobyS1 < 0 || osobyS2 < 0 || osobyS3 < 0 || osobyS4 < 0 || osobyS5)
      	leds |= ERROR_LED;
      else
      	leds &= ~(ERROR_LED);


      IOWR(LEDS_BASE, 0, leds);

      IOWR(HEX_BASE, 0, digit_to_hex(osobyS1));
	  IOWR(HEX_BASE, 1, digit_to_hex(osobyS2));
	  IOWR(HEX_BASE, 2, digit_to_hex(osobyS3));
	  IOWR(HEX_BASE, 3, digit_to_hex(osobyS4));
	  IOWR(HEX_BASE, 4, digit_to_hex(osobyS5));


      //printf("S0: %d S1: %d S2: %d S3: %d S4: %d\n", osobyS1, osobyS2, osobyS3, osobyS4, osobyS5);
    }
  return 0;
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

