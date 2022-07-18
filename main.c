/************************************
 * Name     :       main.c
 * Author   :       Giuseppe Lomonaco - lomg2301
 *                  Lucas Corrales - corl0701
 * Version  :       v1.3
 * Session  :       E22
 * Date     :       13 Juin 2022     
 ************************************/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"

#include "acl.h"
#include "aic.h"

#include "swt.h"
#include "lcd.h"
#include "spiflash.h"
#include "uart.h"
#include "uartjb.h"


#include "APP.h"
//#include "TEST.h"








// Since the flag is changed within an interrupt, we need the keyword volatile.
static volatile int Flag_1ms = 0;


void LCD_seconde(unsigned int seconde);
extern void pmod_s();
extern void babylon_s();




// Timer a JP
void __ISR(_TIMER_1_VECTOR, IPL2AUTO) Timer1ISR(void) 
{  
   Flag_1ms = 1;           //    Indique à la boucle principale qu'on doit traiter
   //Flag_16ms = 16;
   IFS0bits.T1IF = 0;     //    clear interrupt flag
}

#define TMR_TIME    0.001             // x us for each tick







void initialize_timer_interrupt(void) { 
  T1CONbits.TCKPS = 3;                //    256 prescaler value
  T1CONbits.TGATE = 0;                //    not gated input (the default)
  T1CONbits.TCS = 0;                  //    PCBLK input (the default)
  PR1 = (int)(((float)(TMR_TIME * PB_FRQ) / 256) + 0.5);   //set period register, generates one interrupt every 1 ms
                                      //    48 kHz * 1 ms / 256 = 188
  TMR1 = 0;                           //    initialize count to 0
  IPC1bits.T1IP = 2;                  //    INT step 4: priority
  IPC1bits.T1IS = 0;                  //    subpriority
  IFS0bits.T1IF = 0;                  //    clear interrupt flag
  IEC0bits.T1IE = 1;                  //    enable interrupt
  T1CONbits.ON = 1;                   //    turn on Timer5
} 








    
    



void main() {
     
    LCD_Init();
    LED_Init();
    RGBLED_Init();
    SWT_Init();   
    BTN_Init();
    SPIFLASH_Init();
    

    
    initialize_timer_interrupt();
    int count = 0;
    int count_16secs = 0;

    macro_enable_interrupts();
    
    
    // entering function to set time
    unsigned int seconde = 0;
    seconde = APP_set_time();

    // entering function to set date
    char strDate[80] = "";
    APP_set_date(strDate);
    
    // Main loop
    while(1) {       
        
        if(Flag_1ms)                 // Flag d'interruption à chaque 1 ms
        {
            Flag_1ms = 0;            // Reset the flag to capture the next event
            
            if (++count >= 1000) 
            {
                count = 0;
                
                // Main print time and date on LCD
                APP_lcd_time_date(++seconde, strDate);
                RGBLED_SetValue(0xFF, 0, 0); 
                
                // count each 16 secs turn and print on screen
                if (seconde%16 == 0){   
                }
    
                if (SWT_GetValue(0) == 1) {
                    LCD_DisplayClear();
                    APP_Affichage_1(seconde);
                }
                        
                else if (SWT_GetValue(1) == 1) {
                    LCD_DisplayClear();
                    APP_Affichage_2();
                } 
                
                else if (SWT_GetValue(2) == 1) {
                    LCD_DisplayClear();
                    APP_writePOT_Value();
                }
                 
                else if (SWT_GetValue(3) == 1) {
                    LCD_DisplayClear();
                    APP_SPIFLASH(seconde);
                }
       
                else if (SWT_GetValue(4) == 1) {
                    LCD_DisplayClear();
                    APP_writeACL_RawValues();
                }
        
                else if (SWT_GetValue(5) == 1) {
                    LCD_DisplayClear();
                    APP_writeACL_GValues();
                }
                         
                else if (SWT_GetValue(6) == 1) {
                    LCD_DisplayClear();
                    APP_square_wave_PMOD();
                }
                                        
                else if (SWT_GetValue(7) == 1) {
                    LCD_DisplayClear();  
                }
                


                // Flashing RGB accordingly
                if ((seconde&1))    // or simply (if(seconde%2 == 0))
                    RGBLED_SetValue(0, 0, 0xFF);

                if (seconde%10 == 0)
                    RGBLED_SetValue(0, 0xFF, 0);
                
            }
        }
    }
}
    
    














//          NOTES PRISES DURANT LA CONSULTATION DAPP
// --------------FLASH---------------------------
// la memoire fonctionne en 8 bits (spiflash), a toutes les 1 secondes on va :::
// et jp conseille dutiliser juste la flash avec
// des char et ensuite on utilise des int, exemple 4 cases memoires
// il faut travailler en 32 bit la variable seconde (tems) est deja 32 bits
// le pot est 10 bits
// laccelerometre cest 12 bits, 12 bits pour, x, 12 bits pour y et 12 bits pour z

// comment ecrire dans la spiflash, voir page 56 pour ecrire avec programPage

// si on met tout le tableau en 32 bits on aura 6 x 4 octects, donc 24 octects et a chaque secondes on va les ecrire en int

// en premier on reserve 4 case pour le temps, ensuite on reserve 4 cases pour le x, 4 case pour le y, etc

// on peut creer un tableau de 24 octects et dans ce tab;leau on ecrit toutes nos valeurs

// exemple unsigned char tableau[24]
// tableau[0] = temps nest pas bon car on veut ecrire 32 bits dans une case de 8 bits
//. on peut donc porendre les 32 bits les plus elebv/s pour les mettre dedans genre
// tableau[0] = temps(32 a 25)
// tableau[1] = temps (24 bits a 15bits)
// etc

//il y a aussi la fonction memcpy(pour memcpy) qui prend de la memoire pour y copier des trucs
// il y aussi les deu symboles >> qui se tasse des bits




// ------------UART ------------------
// on peut pas juste caster en char pour transmettre sur le UART
// quand on transmet on fait un shift vers la droite et 



// pour calculer la racine il faut 


//il faut faire deux masques de 16 bits pour le UART ^^^




// le bit 0 cest la patte 0 , le bit 1 cest la patte 1, et ainsi de suite pour les PMOD 
// on a 6 pattes de sorties a configurer pour le PMOD




