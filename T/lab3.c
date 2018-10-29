#include <stdio.h>
#include <io.h>
#include <system.h>
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
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
#define FOUR SEGA | SEGC | SEGG | SEGF
#define FIVE SEGA | SEGC | SEGD | SEGF  | SEGG
#define SIX SEGA | SEGC | SEGD | SEGE | SEGF | SEGG
#define SEVEN SEGA | SEGB | SEGC
#define EIGHT SEGA | SEGB | SEGC | SEGD |SEGE | SEGF | SEGG
#define NINE SEGA | SEGB | SEGC | SEGD | SEGF
#define E_HEX SEGA | SEGD |SEGE | SEGF | SEGG
#define R_HEX SEGE | SEGG
int get_hex(int value){
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
            return SEGA;
    }
}
 
struct interrupt_data
{
    volatile int* leds_addr;
    volatile int* sliders_addr;
    volatile int* hex_addr;
    volatile int* push_button_addr;
};
volatile int hexs[6]={0,0,0,0,0,0};
volatile int rooms[5];
volatile int flag0;
volatile int flagDirection;
volatile int errFlag=0;
/*
        volatile int rooms[5];
        volatile int flag0;
        volatile int flagDirection;
    zdefiniowane globalnie albo w struct
 
    */
static void handle_pushbuttons_interrupt(struct interrupt_data *data)
{
    volatile int leds = IORD(data->leds_addr,0);
    volatile int kierunek = IORD(data->push_button_addr,0);
 
          if(kierunek == KEY1){
          if(flagDirection==0){
              leds |= LED9;
              flagDirection = 1;
          } else {
              leds &= ~(LED9);
              flagDirection = 0;
          }
      }
      IOWR(data->leds_addr,0,leds);
}
 
static void handle_sliders_interrupt(struct interrupt_data *data)
{
    volatile int sw_state = IORD(data->sliders_addr,0);
    volatile int leds = IORD(data->leds_addr,0);
 
      switch(sw_state){
      case SW0:
          if(flag0 == 0){
              if(flagDirection == 0)
              {
                  rooms[0]++;
                  errFlag=0;
              }
              else
              {
                  if(rooms[0] == 0)
                  errFlag=1;
                  if(rooms[0] != 0){
                  rooms[0]--;
 
                  errFlag=0;
                  }
              }
              flag0 = 1;
          }
          break;
      case SW1:
          if(flag0 == 0){
                      if(flagDirection == 1)
                      {
                          rooms[2]++;
                          errFlag=0;
                      }
                      else
                      {
                           if(rooms[2] == 0)
                            errFlag=1;
                          if(rooms[2] != 0)
                          {
                              rooms[2]--;
                              errFlag=0;
                          }
                          }
                      flag0 = 1;
                  }
              break;
      case SW2:
          if(flag0 == 0){
                      if(flagDirection == 0)
                      {
                      if(rooms[0] == 0)
                        errFlag=1;
                        if(rooms[0] != 0)
                        {
 
                            errFlag=0;
                          rooms[0]--;
                          rooms[2]++;
                        }
                      }
                      else
                      {
                     if(rooms[2] == 0)
                        errFlag=1;
                        if(rooms[2] != 0)
                        {
                          rooms[0]++;
                          rooms[2]--;
                          errFlag=0;
                        }
                      }
                      flag0 = 1;
                  }
 
 
              break;
      case SW3:
          if(flag0 == 0){
                      if(flagDirection == 0)
                      {
                        if(rooms[1] == 0)
                        errFlag=1;
                        if(rooms[1] != 0)
                        {
                            errFlag=0;
                          rooms[1]--;
                          rooms[3]++;
                        }
                      }
                      else
                      {
                    if(rooms[3] == 0)
                    errFlag=1;
                        if(rooms[3] != 0){
                        rooms[3]--;
                        rooms[1]++;
                        errFlag=0;
                        }
                      }
                      flag0 = 1;
                  }
 
              break;
      case SW4:
          if(flag0 == 0){
                       if(flagDirection == 1)
                              {
                                rooms[3]++;
 
                                errFlag=0;
                              }
                              else
                              {
                            if(rooms[3] == 0)
                            errFlag=1;
                                if(rooms[3] != 0)
                                  rooms[3]--;
 
                                errFlag=0;
                              }
                              flag0 = 1;
                          }
              break;
      case SW5:
          if(flag0 == 0){
                      if(flagDirection == 0)
                      {
                          rooms[1]++;
 
                          errFlag=0;
                      }
                      else
                      {
                 if(rooms[1] == 0)
                  errFlag=1;
                        if(rooms[1] != 0)
                          rooms[1]--;
 
                        errFlag=0;
                      }
                      flag0 = 1;
                  }
 
 
              break;
      case SW6:
          if(flag0 == 0){
                      if(flagDirection == 1)
                      {
                          rooms[4]++;
 
                          errFlag=0;
                      }
                      else
                      {
                  if(rooms[4] == 0)
                  errFlag=1;
                        if(rooms[4] != 0)
                          rooms[4]--;
 
                        errFlag=0;
                      }
                      flag0 = 1;
                  }
 
              break;
      case SW7:
          if(flag0 == 0){
                      if(flagDirection == 0)
                      {
                  if(rooms[1] == 0)
                  errFlag=1;
                        if(rooms[1] != 0)
                        {
                          rooms[1]--;
                          rooms[4]++;
                          errFlag=0;
                        }
                      }
                      else
                      {
                  if(rooms[4] == 0)
                  errFlag=1;
                        if(rooms[4] != 0)
                        {
                         errFlag=0;
                          rooms[4]--;
                          rooms[1]++;
                        }
                      }
                      flag0 = 1;
                  }
 
              break;
      case SW8:
          if(flag0 == 0){
                              if(flagDirection == 0)
                             {
                        if(rooms[0] == 0)
                        errFlag=1;
                                if(rooms[0] != 0){
                                  rooms[0]--;
                                  rooms[1]++;
                                  errFlag=0;
                                }
                              }
                              else
                              {
 
                            if(rooms[1] == 0)
                            errFlag=1;
                                if(rooms[1] != 0){
                                  rooms[1]--;
                                  rooms[0]++;
                                  errFlag=0;
                                }
                              }
                              flag0 = 1;
                          }
 
              break;
      case SW9:
          if(flag0 == 0){
                              if(flagDirection == 0)
                              {
                            if(rooms[2] == 0)
                            errFlag=1;
                                if(rooms[2] != 0){
                                  rooms[2]--;
                                  rooms[3]++;
                                  errFlag=0;
                                }
                              }
                              else
                              {
                            if(rooms[3] == 0)
                            errFlag=1;
                                if(rooms[3] != 0)
                                {
                                  rooms[3]--;
                                  rooms[2]++;
                                  errFlag=0;
                                }
                              }
                              flag0 = 1;
                          }
              break;
      default:
          flag0 = 0;
      }
    /*  if(errFlag == 1)
      {
          IOWR(data->hex_addr,0,E_HEX);
          hexs[0] = E_HEX;
          hexs[4] = R_HEX;
          hexs[3] = R_HEX;
          leds |= LED8;
      }
 
 
    */
    /*  if(errFlag == 1 && (rooms[0] >= 0 && rooms[1] >= 0 && rooms[2] >= 0 && rooms[3] >= 0 && rooms[4] >= 0))
               {
                    errFlag=0;
                }
     */ if(rooms[0] > 0)
      {
          leds |= LED0;
      } else
      {
          leds &= ~(LED0);
      }
 
      if(rooms[1] > 0)
      {
 
              leds |= LED1;
          } else
          {
              leds &= ~(LED1);
          }
      if(rooms[2] > 0)
          {
                  leds |= LED2;
              } else
              {
                  leds &= ~(LED2);
              }
      if(rooms[3] > 0)
          {
               leds |= LED3;
              } else
              {
                  leds &= ~(LED3);
              }
      if(rooms[4] > 0)
          {
                 leds |= LED4;
              } else
              {
                  leds &= ~(LED4);
              }
 
      if(rooms[0] >= 0)
            {
              hexs[0] = get_hex(rooms[0]);
            }
            if(rooms[1] >= 0)
            {
              hexs[1] = get_hex(rooms[1]);
                }
            if(rooms[2] >= 0)
                {
                      hexs[2] = get_hex(rooms[2]);
                }
            if(rooms[3] >= 0)
                {
                   hexs[3] = get_hex(rooms[3]);
                }
            if(rooms[4] >= 0)
                {
                     hexs[4] = get_hex(rooms[4]);
                }
 
             if(errFlag == 1)
                  {
                      IOWR(data->hex_addr,3,R_HEX);
                      IOWR(data->hex_addr,4,R_HEX);
                      IOWR(data->hex_addr,5,E_HEX);
 
                //    leds |= LED8;
                  }
                else
                {
                    IOWR(data->hex_addr, 0, (hexs[0]));
                    IOWR(data->hex_addr, 1, (hexs[1]));
                    IOWR(data->hex_addr, 2, (hexs[2]));
                    IOWR(data->hex_addr, 3, (hexs[3]));
                    IOWR(data->hex_addr, 4, (hexs[4]));
                    IOWR(data->hex_addr, 5, (hexs[5]));
                    }
 
             IOWR(data->leds_addr, 0, leds);
 
 
}
 
 
int main()
{
      volatile int *leds = (int *)LEDS_BASE;
      volatile int *sliders = (int *)SW_SLIDERS_BASE;
      volatile int *hex = (int *)HEX_BASE;
      volatile int *push = (int *)PUSHBUTTON_BASE;
 
      IOWR(LEDS_BASE, 0, 0x00);
     // IOWR(HEX_BASE, 0, 0x3f);
 
      struct interrupt_data data;
 
      data.leds_addr = leds;
      data.sliders_addr = sliders;
      data.hex_addr = hex;
      data.push_button_addr = push;
 
 
      IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PUSHBUTTON_BASE, 0b1111);
        IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SW_SLIDERS_BASE, 0b1111111111);
 
        alt_ic_isr_register(SW_SLIDERS_IRQ_INTERRUPT_CONTROLLER_ID, SW_SLIDERS_IRQ, handle_sliders_interrupt, &data, 0x0);
        alt_ic_isr_register(PUSHBUTTON_IRQ_INTERRUPT_CONTROLLER_ID, PUSHBUTTON_IRQ, handle_pushbuttons_interrupt, &data, 0x0);
 
        alt_ic_irq_enable(SW_SLIDERS_IRQ_INTERRUPT_CONTROLLER_ID, SW_SLIDERS_IRQ);
        alt_ic_irq_enable(SW_SLIDERS_IRQ_INTERRUPT_CONTROLLER_ID, PUSHBUTTON_IRQ);
 
 
     while(1){}
 
 
 
 
 
  return 0;
}