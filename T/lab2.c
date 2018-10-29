#include <stdio.h>
#include <system.h>
#include <io.h>
 
/*
 * definition.h
 *
 *  Created on: 19 paź 2016
 *      Author: darek
 */
 
#ifndef DEFINITION_H_
#define DEFINITION_H_
 
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
//#define ZERO SEGA | SEGB | SEGC | SEGD |SEGE | SEGF
//#define ONE  SEGB | SEGC
//#define TWO  SEGA | SEGB | SEGG | SEGE | SEGD
//#define THREE SEGA | SEGB | SEGC | SEGD | SEGG
 
#endif /* DEFINITION_H_ */
 
 
int main()
{
    int kierunek = 0;
    int flagDirection = 0; // 0 => dol, prawo; 1 => gora, lewo
    int osobyS0 = 0;
    int osobyS1 = 0;
    int osobyS2 = 0;
    int osobyS3 = 0;
    int osobyS4 = 0;
    int temp = 0;
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
      kierunek = IORD(PUSHBUTTON_BASE, 0);
      if(kierunek == KEY1){
          if(flagDirection==0){
              leds |= LED9;
              flagDirection = 1;
          } else {
              leds &= ~(LED9);
              flagDirection = 0;
          }
      }
      temp = IORD(SW_SLIDERS_BASE, 0);
      switch(temp){
      case SW0:
          if(flag0 == 0){
              if(flagDirection == 0)
              {
                  osobyS0++;
              }
              else
                  if(osobyS0 != 0)
                  osobyS0--;
              flag0 = 1;
          }
          break;
      case SW1:
          if(flag1 == 0){
                      if(flagDirection == 1)
                      {
                          osobyS2++;
                      }
                      else
                          if(osobyS2 != 0)
                              osobyS2--;
                      flag1 = 1;
                  }
              break;
      case SW2:
          if(flag2 == 0){
                      if(flagDirection == 0)
                      {
                        if(osobyS0 != 0)
                        {
                          osobyS0--;
                          osobyS2++;
                        }
                      }
                      else
                      {
                        if(osobyS2 != 0)
                        {
                          osobyS0++;
                          osobyS2--;
                        }
                      }
                      flag2 = 1;
                  }
 
 
              break;
      case SW3:
          if(flag3 == 0){
                      if(flagDirection == 0)
                      {
                        if(osobyS1 != 0)
                        {
                          osobyS1--;
                          osobyS3++;
                        }
                      }
                      else
                      {
                        if(osobyS3 != 0){
                        osobyS3--;
                        osobyS1++;
                        }
                      }
                      flag3 = 1;
                  }
 
              break;
      case SW4:
          if(flag4 == 0){
                              if(flagDirection == 1)
                              {
                                  osobyS3++;
                              }
                              else
                                if(osobyS3 != 0)
                                  osobyS3--;
                              flag4 = 1;
                          }
              break;
      case SW5:
          if(flag5 == 0){
                      if(flagDirection == 0)
                      {
                          osobyS1++;
                      }
                      else
                        if(osobyS1 != 0)
                          osobyS1--;
                      flag5 = 1;
                  }
 
 
              break;
      case SW6:
          if(flag6 == 0){
                      if(flagDirection == 1)
                      {
                          osobyS4++;
                      }
                      else
                        if(osobyS4 != 0)
                          osobyS4--;
                      flag6 = 1;
                  }
 
              break;
      case SW7:
          if(flag7 == 0){
                      if(flagDirection == 0)
                      {
                        if(osobyS1 != 0)
                        {
                          osobyS1--;
                          osobyS4++;
                        }
                      }
                      else
                      {
                        if(osobyS4 != 0)
                        {
                          osobyS4--;
                          osobyS1++;
                        }
                      }
                      flag7 = 1;
                  }
 
              break;
      case SW8:
          if(flag8 == 0){
                              if(flagDirection == 0)
                              {
                                if(osobyS0 != 0){
                                  osobyS0--;
                                  osobyS1++;
                                }
                              }
                              else
                              {
                                if(osobyS1 != 0){
                                  osobyS1--;
                                  osobyS0++;
                                }
                              }
                              flag8 = 1;
                          }
 
              break;
      case SW9:
          if(flag9 == 0){
                              if(flagDirection == 0)
                              {
                                if(osobyS2 != 0){
                                  osobyS2--;
                                  osobyS3++;
                                }
                              }
                              else
                              {
                                if(osobyS3 != 0)
                                {
                                  osobyS3--;
                                  osobyS2++;
                                }
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
 
      if(osobyS0 > 0)
      {
          leds |= LED0;
      } else
      {
          leds &= ~(LED0);
      }
 
      if(osobyS1 > 0)
      {
              leds |= LED1;
          } else
          {
              leds &= ~(LED1);
          }
      if(osobyS2 > 0)
          {
                  leds |= LED2;
              } else
              {
                  leds &= ~(LED2);
              }
      if(osobyS3 > 0)
          {
                  leds |= LED3;
              } else
              {
                  leds &= ~(LED3);
              }
      if(osobyS4 > 0)
          {
                  leds |= LED4;
              } else
              {
                  leds &= ~(LED4);
              }
 
 
 
      printf("S0: %d S1: %d S2: %d S3: %d S4: %d\n", osobyS0, osobyS1, osobyS2, osobyS3, osobyS4);
 
 
 
 
      IOWR(LEDS_BASE, 0, leds);
 
    }
  return 0;
}