/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files */

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

/* ************************************************************************** */
/* ************************************************************************** */





#define DEBOUNCE_BUTTON_VAL 5










//
//void minimum_function (int *minimum_module, int module)  {
//    if(module < minimum_module) {
//        minimum_module = module;  
//        memcpy(minimum_module, module, sizeof(module));
//    }
//}
//
//
//
//
//void maximum_function (int *maximum_module, int module) {
//    if(module > maximum_module) {
//        maximum_module = module;  
//        memcpy(minimum_module, module, sizeof(module));
//    }
//}
//
//
//
//void moyenne_function(long long int *){
//    
//}













// function of the laboratory
void APP_square_wave_PMOD(){
    
    
    PMODS_InitPin(1,1,0,0,0); // initialisation du JB1 (RD9))
    unsigned char pmodValue = 0;
    
    LCD_WriteStringAtPos("PMOD Square Wave", 0, 0);
    
    //square wave on pmod pin 1
    pmodValue = PMODS_GetValue(1,1);        //
    pmodValue ^= 1;                         //XOR
    PMODS_SetValue(1, 1, pmodValue);        //
}














// this one print the the time and the pot values and the Awaiting ACK
void APP_Affichage_1(unsigned int seconde)  {
       
    LCD_Init();
    AIC_Init();
        
    char strMsg[80];

    // Read the digital value corresponding to the AIC module
    unsigned int potValue = AIC_Val(); 

    LCD_WriteIntAtPos(potValue, 5, 0, 0, 0);       
    LCD_WriteIntAtPos(seconde%60, 3, 0, 13, 0);     
    LCD_WriteStringAtPos(":", 0, 13); // affichage des secondes
    LCD_WriteIntAtPos(seconde/60%60, 3, 0, 10, 0);  
    LCD_WriteStringAtPos(":", 0, 10); // affichage des secondes
    LCD_WriteIntAtPos(seconde/3600%24, 3, 0, 7, 0);  
    
    //display on the LCD screen the Y and Z values, second row
    sprintf(strMsg, "Awaiting ACK...");            
    LCD_WriteStringAtPos(strMsg, 1, 0);  
    
}







// this one print the X, Y, Z and module values
void APP_Affichage_2()  {
    ACL_Init();
    LCD_Init();
    
    float rgACLGVals[3];  
    char strMsg[80];    
    
    // get G values from X, Y and Z
    ACL_ReadGValues(rgACLGVals);
    
    //display on the LCD screen the Y and Z values, second row
    sprintf(strMsg, "X:%6.3f%6.3f:Y", rgACLGVals[0], rgACLGVals[1]);            
    LCD_WriteStringAtPos(strMsg, 0, 0);  
    
    //display on the LCD screen the X values, first row
    sprintf(strMsg, "Z:%6.3f%6.3f:M", rgACLGVals[2], NULL);
    LCD_WriteStringAtPos(strMsg, 1, 0);
}









// main function that print time and date on screen
void APP_lcd_time_date(unsigned int seconde, char strDate[]) { 
    
    LCD_Init();
    
    // print time on string
    LCD_WriteStringAtPos("Heure: ", 0, 0);
    LCD_WriteIntAtPos(seconde%60, 3, 0, 13, 0);     
    LCD_WriteStringAtPos(":", 0, 13); // affichage des secondes
    LCD_WriteIntAtPos(seconde/60%60, 3, 0, 10, 0);  
    LCD_WriteStringAtPos(":", 0, 10); // affichage des secondes
    LCD_WriteIntAtPos(seconde/3600%24, 3, 0, 7, 0);  
    
    // printing date on screen
    LCD_WriteStringAtPos("Date: ", 1, 0);
    LCD_WriteStringAtPos(strDate, 1, 0);
}








// this function return a string containing date
void APP_set_date(char strDate[]){
    
    LCD_Init();
    BTN_Init();
    
    unsigned int day = 0;
    unsigned int month = 0;
    unsigned int year = 0;
    
    unsigned int debounce_button_up = 0;
    unsigned int debounce_button_down = 0;
    unsigned int debounce_button_left = 0;
    unsigned int debounce_button_right = 0;
    unsigned int debounce_button_center = 0;
    

    
    // this function will return this string
    char strMsg[80];
    
    // if current = 0 setting day, if current = 1 setting month, if current = 2 setting year
    int current = 0;

    // setting time is a boolean, if setting_time = 0, exit function
    unsigned int setting_date = 1;

        
    while(setting_date){   
        
        if (BTN_GetValue('U') == 1){
            debounce_button_up += 1;
            if(debounce_button_up > DEBOUNCE_BUTTON_VAL)   {
                if ((current == 0) && (day < 31))   {
                    ++day;
                    debounce_button_up = 0;
                }
                else if ((current == 1) && (month < 12))    {
                    ++month;
                    debounce_button_up = 0;

                }
                else if ((current == 2) && (year < 99)) {
                    ++year; 
                    debounce_button_up = 0;                    
                }
            }
            
        }
        
        
        // settings minuts
        if ((BTN_GetValue('R') == 1) && (current > 0))  {  
            debounce_button_right += 1;
            if (debounce_button_right > DEBOUNCE_BUTTON_VAL)    {
                --current;
                debounce_button_right = 0;
            }
        }
               
        // Button down
        if (BTN_GetValue('D') == 1){
            debounce_button_down += 1;
            if(debounce_button_down > DEBOUNCE_BUTTON_VAL)   {
                if ((current == 0) && (day > 0))    {  
                    --day;              
                    debounce_button_down = 0;
                }
                else if ((current == 1) && (month > 0)) {
                    --month;
                    debounce_button_down = 0;
                }    
                else if ((current == 2) && (year > 0))  {
                    --year;
                    debounce_button_down = 0;
                }                    
            }
        }

        // select setting hours
        if ((BTN_GetValue('L') == 1) && (current < 2)){
            debounce_button_left += 1;
            if (debounce_button_left > DEBOUNCE_BUTTON_VAL) {
                ++current;
                debounce_button_left = 0;
            }
        }

    

    
        
        if (current == 0)   {
            LCD_WriteStringAtPos("SetDay", 0, 0);
        }
        else if (current == 1)  {
            LCD_WriteStringAtPos("SetMth", 0, 0);
        }
        else if (current == 2)  {
            LCD_WriteStringAtPos("SetYer", 0, 0);
        }
        
        //LCD_WriteStringAtPos("Date:", 0, 0); // affichage des secondes
        LCD_WriteIntAtPos(day, 3, 0, 13, 0);     
        LCD_WriteStringAtPos("/", 0, 13); // affichage des secondes
        LCD_WriteIntAtPos(month, 3, 0, 10, 0);  
        LCD_WriteStringAtPos("/", 0, 10); // affichage des secondes
        LCD_WriteIntAtPos(year, 3, 0, 7, 0); 
        LCD_WriteStringAtPos("Press C to Exit", 1, 0); // affichage des secondes

        
        //exit function
        if (BTN_GetValue('C') == 1){    
            debounce_button_center += 1;
            if (debounce_button_center > DEBOUNCE_BUTTON_VAL)  {
                sprintf(strMsg, "Date:   %2d/%2d/%2d", year, month, day);
                memcpy(strDate, strMsg, strlen(strMsg));
                // Setting date to 0 to exit code
                setting_date = 0;  
            }
        }
    }      
}









unsigned int APP_set_time(){
    
    LCD_Init();
    BTN_Init();
    
    unsigned int seconde = 0;
    unsigned int minute = 0;
    unsigned int heure = 0;
    
    unsigned int debounce_button_up = 0;
    unsigned int debounce_button_down = 0;
    unsigned int debounce_button_left = 0;
    unsigned int debounce_button_right = 0;
    unsigned int debounce_button_center = 0;
    
    // if current = 0 setting minutes, if current = 1 setting hours
    int current = 0;

    // setting time is a boolean, if setting_time = 0, exit function
    unsigned int setting_time = 1;

    
    while(setting_time){
        
        if (BTN_GetValue('U') == 1) {
            debounce_button_up += 1;
            if(debounce_button_up > DEBOUNCE_BUTTON_VAL)   {
                if ((current == 0) && (minute < 60))    {
                    ++minute;
                    debounce_button_up = 0;
                }
                else if ((current != 0) && (heure < 23))    {
                    ++heure;
                    debounce_button_up = 0;
                }
            }
        }
         
        // settings minutes
        if (BTN_GetValue('R') == 1) {
            debounce_button_right += 1;
            if (debounce_button_right > DEBOUNCE_BUTTON_VAL)    {
                current = 0;
                debounce_button_right = 0;
            }
        }
            

               
        // Button down
        if (BTN_GetValue('D') == 1) {
            debounce_button_down += 1;
            if (debounce_button_down > DEBOUNCE_BUTTON_VAL)    {
                if ((current == 0) && (minute > 0)) {
                    --minute;
                    debounce_button_down = 0;
                }
                else if ((current != 0) && (heure > 0)) {
                    --heure;
                    debounce_button_down = 0;
                }
            }
        }

        // select setting hours
        if (BTN_GetValue('L') == 1) {
            debounce_button_left += 1;
            if (debounce_button_left > DEBOUNCE_BUTTON_VAL) {
                current = 1;
                debounce_button_left = 0; 
            }
        }

    
        //exit function
        if (BTN_GetValue('C') == 1){
            debounce_button_center += 1;
            if (debounce_button_center > DEBOUNCE_BUTTON_VAL)   {
                // Converting Hours and minutes on exit 
                seconde = seconde + (minute * 60) + (heure * 3600);
                // set setting time to 0 to exit function
                setting_time = 0;
                debounce_button_center = 0;
            }
            

        }
    

        LCD_WriteIntAtPos(0, 3, 0, 13, 0);     
        LCD_WriteStringAtPos(":", 0, 13); // affichage des secondes
        LCD_WriteIntAtPos(minute, 3, 0, 10, 0);  
        LCD_WriteStringAtPos(":", 0, 10); // affichage des secondes
        LCD_WriteIntAtPos(heure, 3, 0, 7, 0); 
        LCD_WriteStringAtPos("Press C to Exit", 1, 0); // affichage des secondes

        
        if (current == 0)
            LCD_WriteStringAtPos("SetMins", 0, 0);
        else
            LCD_WriteStringAtPos("SetHour", 0, 0);
    }   
    
    return seconde;
}












void APP_SPIFLASH(unsigned int seconde) {
     
    unsigned char temp_flash[320];
    unsigned char temp_flash1[256];
    unsigned char temp_flash2[64];
    
    int Read_acc_x[16];
    int Read_acc_y[16];
    int Read_acc_z[16];
    int Read_acc_mod[16];
    int Read_pot[16];
    
    
    //masks for converting chars into integrers
    int mask[4];
    mask[0] = 0b11111111000000000000000000000000;
    mask[1] = 0b00000000111111110000000000000000;
    mask[2] = 0b00000000000000001111111100000000;
    mask[3] = 0b00000000000000000000000011111111;
    
    
    //calculated outputs from every values read every 16 sec
    int min_x;
    int max_x;
    int moy_x;
    
    int min_y;
    int max_y;
    int moy_y;
    
    int min_z;
    int max_z;
    int moy_z;
    
    int min_mod;
    int max_mod;
    int moy_mod;
    
    int min_pot;
    int max_pot;
    int moy_pot;
    
    
    int tab_x[16], tab_y[16], tab_z[16], tab_mod[16], tab_pot[16];
    
        
    int acc_x, acc_y, acc_z, acc_mod = 0;   //donnees accelerometre
    int acc_tableau[5];                        //tableau donnees accelerometre
    unsigned char temp_tableau[20];

    unsigned int pot_value = 0;             //donnees potentiometre
    
    int signe_x, signe_y, signe_z = 0;      //variable signe conversion
    
    

    unsigned char acc_data[6];      //raw date accelerometer

    
    ACL_Init();  //initialize accelerometer
    LCD_Init(); //initialize LCD screen
    LED_Init(); //Initialize leds
    BTN_Init(); //initialize buttons
    AIC_Init(); //initialize adc for potentiometer
    
    
    
    LCD_WriteStringAtPos("SPI Flash test", 0, 0);
    LCD_WriteStringAtPos("Erase Flash ...", 1, 0);
    SPIFLASH_Init();    //initialize flash memory access
   

    int count = 0;  //count pour interrupt aux secondes
    int count2 = 0; //count pour interrupt aux 16 secondes 


    
    SPIFLASH_EraseAll();    //erase flash memory
     
     
     ///////////////////accelerometer
                ACL_ReadRawValues(acc_data);
                //accelerometer axis x
                acc_x = acc_data[0]*256 + acc_data[1];
                signe_x = (acc_x & (1<<15)) >> 15;  //MSB represente le signe
                signe_x = signe_x/4;
                
                if(signe_x)
                {
                    acc_x -= 16384/4; //changement de comp2
                }
                
                //accelerometer axis y
                acc_y = acc_data[2]*256 + acc_data[3];
                signe_y = (acc_y & (1<<15)) >> 15;  //MSB represente le signe
                signe_y = signe_y/4;
                
                if(signe_y)
                {
                    acc_y -= 16384/4; //changement de comp2
                }
                
                //accelerometer axis z
                acc_z = acc_data[4]*256 + acc_data[5];
                signe_z = (acc_z & (1<<15)) >> 15;  //MSB represente le signe
                signe_z = signe_z/4;
                if(signe_z)
                {
                    acc_z -= 16384/4; //changement de comp2
                }
                
                
                
                
                
                pot_value = AIC_Val();
                
                // acc_tableau is the acceleration and the pot value
                acc_tableau[0] = acc_x;
                acc_tableau[1] = acc_y;
                acc_tableau[2] = acc_z;
                acc_tableau[3] = acc_mod;
                acc_tableau[4] = pot_value;
                //module = calcul(acc_x, acc_y, acc_z);
                
                
                ///////
                //write in flash memory//
                ///////
               
                    int baseCnt = 0;
                    char strMsg[80];
                    int i, j, u;
               
                for (u=0; u<5; u++){
               
                     
                    temp_tableau[0 + u * 4] = (char) (acc_tableau[u] >> 24 & 0xff);
                    temp_tableau[1 + u * 4] = (char) (acc_tableau[u] >> 16 & 0xff);
                    temp_tableau[2 + u * 4] = (char) (acc_tableau[u] >> 8 & 0xff);
                    temp_tableau[3 + u * 4] = (char) (acc_tableau[u] & 0xff);
                    
                }
             
               
               // this is the temp_tableau len..... a voir
               unsigned int len = sizeof(temp_tableau);
//                              unsigned int len = 20;
               

                    LCD_WriteStringAtPos("Write buffer ...", 1, 0);
//                    SPIFLASH_ProgramPage(count2*20, temp_tableau, 20);
                    SPIFLASH_ProgramPage(count2*len, temp_tableau, len);

                    LCD_WriteStringAtPos("Read buffer ...", 1, 0);              
                    SPIFLASH_Read(0, temp_flash1, 256); //put the values from the flash memory inside temp_flash 
                    SPIFLASH_Read(256, temp_flash2, 64);

                    for(i=0; i< 320; i++)
                    {
                        if(i < 255)
                        {
                            temp_flash[i] = temp_flash1[i];
                        }
                        else
                        {
                            temp_flash[i] = temp_flash2[i-255];
                        }
                    }
                    
                    //Read_acc_x
                    for(i = 0; i <16; i++)
                    {
                        for(u = 0; u < 3; u++)
                        {
                            Read_acc_x[i] = temp_flash[u+i*20] & mask[u];
                        }
                    }
                    //Read_acc_y
                    for(i = 0; i <16; i++)
                    {
                        for(u = 0; u < 3; u++)
                        {
                            Read_acc_y[i] = temp_flash[u+4+i*20] & mask[u];
                        }
                    }
                    //Read_acc_z
                    for(i = 0; i <16; i++)
                    {
                        for(u = 0; u < 3; u++)
                        {
                            Read_acc_z[i] = temp_flash[u+8+i*20] & mask[u];
                        }
                    }
                    //Read_acc_mod
                    for(i = 0; i <16; i++)
                    {
                        for(u = 0; u < 3; u++)
                        {
                            Read_acc_mod[i] = temp_flash[u+12+i*20] & mask[u];
                        }
                    }
                    //Read_acc_pot
                    for(i = 0; i <16; i++)
                    {
                        for(u = 0; u < 3; u++)
                        {
                            Read_pot[i] = temp_flash[u+16+i*20] & mask[u];
                        }
                    }                        
                    
                    
                    
                    
                    i = 0;
                    
                    while(1)    {
                        if(++baseCnt == 200000)    {
                            baseCnt = 0;   
                            sprintf(strMsg, "Add:%3d Val:%3d", i, temp_flash[i]);        
                            LCD_WriteStringAtPos(strMsg, 1, 0);   

                            if (i == sizeof(temp_flash))
                                i = 0;
                            else
                                i++;
                    }
        }
}










void APP_writeACL_GValues(){
    
    ACL_Init();
    LCD_Init();
    
    float rgACLGVals[3];  
    char strMsg[80];    
    
    // get G values from X, Y and Z
    ACL_ReadGValues(rgACLGVals);
    
    //display on the LCD screen the X values, first row
    sprintf(strMsg, "ACLgVal X:%6.3f", rgACLGVals[0]);
    LCD_WriteStringAtPos(strMsg, 0, 0);
    
    //display on the LCD screen the Y and Z values, second row
    sprintf(strMsg, "Y:%6.3fZ:%6.3f", rgACLGVals[1], rgACLGVals[2]);            
    LCD_WriteStringAtPos(strMsg, 1, 0);     
    }











void APP_writePOT_Value(){
    
    AIC_Init();
    LCD_Init();
    
    char strMsg[80];   
    
    // Read the digital value corresponding to the AIC module
    unsigned int potValue = AIC_Val(); 
    
    //display on the LCD screen the X values, first row
    sprintf(strMsg, "POT_Val :%6d", potValue);
    LCD_WriteStringAtPos(strMsg, 0, 0);   
    }

















void APP_writeACL_RawValues(){
    
    ACL_Init();
    LCD_Init();
    
    char strMsg[80];
    unsigned char aclRawValues[6]; 
                
    // read values on accelerometer and return RAW values
    ACL_ReadRawValues(aclRawValues);
    
    int module_xAxis = aclRawValues[0]*256 + aclRawValues[1];
    int module_yAxis = aclRawValues[2]*256 + aclRawValues[3];
    int module_zAxis = aclRawValues[4]*256 + aclRawValues[5];
    
    // we look at bit 16 wich is the sign
    int tempo_xBit = (module_xAxis & (1<<15)) >> 15;
    if (tempo_xBit)  {
        module_xAxis = module_xAxis - 65536;
    }    
    
    int tempo_yBit = (module_yAxis & (1<<15)) >> 15;
    if (tempo_yBit)  {
        module_yAxis = module_yAxis - 65536;
    }    
    
    int tempo_zBit = (module_zAxis & (1<<15)) >> 15;
    if (tempo_zBit)  {
        module_zAxis = module_zAxis - 65536;
    }

    //display on the LCD screen the X values, first row
    sprintf(strMsg, "ACL_RAW X:%6d", module_xAxis);
    LCD_WriteStringAtPos(strMsg, 0, 0);
    
    //display on the LCD screen the Y and Z values, second row
    sprintf(strMsg, "Y:%6dZ:%6d", module_yAxis, module_zAxis);            
    LCD_WriteStringAtPos(strMsg, 1, 0);    
    
    }


/* *****************************************************************************
 End of File
 */
