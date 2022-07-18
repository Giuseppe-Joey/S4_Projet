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




// sgit pour SPIFLASH
#define SPIFLASH_PROG_SIZE  256
#define SPIFLASH_PROG_ADDR  0

#define DEBOUNCE_BUTTON_VAL 5


#define RECEIVE_BUFFER_LEN cchRxMax










// this is a demo from Digilent github master Demos
void APP_SPIFLASH_3()
{
//    
//    unsigned char spiFlashPageW[SPIFLASH_PROG_SIZE]; // 256 bytes
//    unsigned char spiFlashPageR[SPIFLASH_PROG_SIZE]; // 256 bytes
//    
//    
//    unsigned char valSpiFlash = 'C';
//    float rgACLGVals[3];  
//    char strMsg[80];    
//    unsigned int wCnt = 0, baseCnt = 0, valPot, addrSpiFlash, addrInPage;
//    
//    
//    char tableau[5] = {'A', 'B', 'C', 'D', 'E'};
//    
//    
//    LCD_Init(); 
//    LCD_WriteStringAtPos("SPI Flash test", 0, 0);
//    LCD_WriteStringAtPos("Erase Flash ...", 1, 0);
//    
//    
//    
//    SPIFLASH_Init();
//    
//        // erase all flash
//    SPIFLASH_EraseAll();
//    
//    
//    // initialize the write and read buffers 
////    for(addrInPage = 0; addrInPage < SPIFLASH_PROG_SIZE; addrInPage++)
////    {
////        spiFlashPageW[addrInPage] = addrInPage << 1; // address multiplied by 2
//       spiFlashPageR[addrInPage] = 0xFF;           // this should be overwritten by read values
////    }
//    
//    
//    
//    
//    
//    
//    int i = 0;
//    
//
//    
//    for (i = 0; i < 5; i++)    {
//                LCD_WriteStringAtPos("Write buffer ...", 1, 0);
//    SPIFLASH_ProgramPage(SPIFLASH_PROG_ADDR + i, tableau[i], 1);
//
//    LCD_WriteStringAtPos("Read buffer ...", 1, 0);
//    SPIFLASH_Read(SPIFLASH_PROG_ADDR + i, spiFlashPageR[i], 1);
//    }
//
//  
//
//    while(1)
//    {
//        if(++baseCnt == 400000)
//        {
//                
//            baseCnt = 0;        
////            addrInPage = wCnt & 0xFF;                         // available for SPIFLASH_PROG_SIZE = 256
////            addrInPage = wCnt & (SPIFLASH_PROG_SIZE - 1);     // available for SPIFLASH_PROG_SIZE power of 2
//            //addrInPage = wCnt % SPIFLASH_PROG_SIZE;      
//            
//            addrInPage += 1;
//            sprintf(strMsg, "ADDR:%02d  Val:%03d", addrInPage, spiFlashPageR[addrInPage]);        
//            LCD_WriteStringAtPos(strMsg, 1, 0);     
//            //SSD_WriteDigitsGrouped(wCnt++, 0);
//        }
//    }    
}


















// this is a demo from Digilent github master Demos
void APP_SPIFLASH_1(unsigned int *seconde)
{
           LCD_Init(); 
    AIC_Init();
    ACL_Init();
    
    unsigned char spiFlashPageW[SPIFLASH_PROG_SIZE]; // 256 bytes
    unsigned char spiFlashPageR[SPIFLASH_PROG_SIZE]; // 256 bytes
//    unsigned char valSpiFlash = 'C';
    float rgACLGVals[3];  
    char strMsg[80];   
    
    
    unsigned int debounce_button_up = 0;
    
    
    unsigned int wCnt = 0, baseCnt = 0, potValue, addrSpiFlash, addrInPage;

    
    
    // Read the digital value corresponding to the AIC module
    potValue = AIC_Val(); 
    
        // get G values from X, Y and Z
    ACL_ReadGValues(rgACLGVals);

    

    LCD_WriteStringAtPos("SPI Flash test", 0, 0);
    LCD_WriteStringAtPos("Erase Flash ...", 1, 0);
    SPIFLASH_Init();
    
    // erase all flash
    SPIFLASH_EraseAll();
    
    
    unsigned int i = 0;
    unsigned int j = 0;
    
    // initialize the write and read buffers 
    for(addrInPage = 0; addrInPage < SPIFLASH_PROG_SIZE; addrInPage++)
    {
        for (i = addrInPage; i < 3; i++) {
            spiFlashPageW[i] = ((int)rgACLGVals[j]); 
            j++;
        }
        
        spiFlashPageW[addrInPage] = potValue; 
        spiFlashPageR[addrInPage] = 0xFF;           // this should be overwritten by read values
    }
    

    

    
    LCD_WriteStringAtPos("Write buffer ...", 1, 0);
    SPIFLASH_ProgramPage(SPIFLASH_PROG_ADDR, spiFlashPageW, SPIFLASH_PROG_SIZE);

    LCD_WriteStringAtPos("Read buffer ...", 1, 0);
    SPIFLASH_Read(SPIFLASH_PROG_ADDR, spiFlashPageR, SPIFLASH_PROG_SIZE);
 

    addrInPage = 0;
    
    while(1)
    {
        
        
                        sprintf(strMsg, "ADR:%02dVal:%d", addrInPage, (spiFlashPageR[addrInPage]));        
                LCD_WriteStringAtPos(strMsg, 1, 0);  
                
                if(++baseCnt == 400000) {
                    baseCnt = 0;
//                
////        if (BTN_GetValue('U') == 1){
////            debounce_button_up += 1;
////            if(debounce_button_up > DEBOUNCE_BUTTON_VAL)   {
////                debounce_button_up = 0; 
//                
                addrInPage += 1;
                //           addrInPage = wCnt & 0xFF;                         // available for SPIFLASH_PROG_SIZE = 256
//            addrInPage = wCnt & (SPIFLASH_PROG_SIZE - 1);     // available for SPIFLASH_PROG_SIZE power of 2
//            addrInPage = wCnt % SPIFLASH_PROG_SIZE; 
            

                sprintf(strMsg, "ADR:%02dVal:%d", addrInPage, (spiFlashPageR[addrInPage]));        
                LCD_WriteStringAtPos(strMsg, 1, 0);    
            }
                                       
                }
            
}
        

                 







// this is a demo from Digilent github master Demos
void APP_SPIFLASH_2(unsigned int *seconde)
{
    
    unsigned char spiFlashPageW[SPIFLASH_PROG_SIZE]; // 256 bytes
    unsigned char spiFlashPageR[SPIFLASH_PROG_SIZE]; // 256 bytes
    unsigned char valSpiFlash = 'C';
    float rgACLGVals[3];  
    char strMsg[80];    
    unsigned int wCnt = 0, baseCnt = 0, valPot, addrSpiFlash, addrInPage;
    LCD_Init(); 
    LCD_WriteStringAtPos("SPI Flash test", 0, 0);
    LCD_WriteStringAtPos("Erase Flash ...", 1, 0);
    SPIFLASH_Init();
        // erase all flash
    SPIFLASH_EraseAll();
    // initialize the write and read buffers 
    for(addrInPage = 0; addrInPage < SPIFLASH_PROG_SIZE; addrInPage++)
    {
        spiFlashPageW[addrInPage] = addrInPage << 1; // address multiplied by 2
        spiFlashPageR[addrInPage] = 0xFF;           // this should be overwritten by read values
    }
    LCD_WriteStringAtPos("Write buffer ...", 1, 0);
    SPIFLASH_ProgramPage(SPIFLASH_PROG_ADDR, spiFlashPageW, SPIFLASH_PROG_SIZE);

    LCD_WriteStringAtPos("Read buffer ...", 1, 0);
    SPIFLASH_Read(SPIFLASH_PROG_ADDR, spiFlashPageR, SPIFLASH_PROG_SIZE);
    //SSD_Init();    

    while(1)
    {
        if(++baseCnt == 400000)
        {
            
            baseCnt = 0;        
//            addrInPage = wCnt & 0xFF;                         // available for SPIFLASH_PROG_SIZE = 256
//            addrInPage = wCnt & (SPIFLASH_PROG_SIZE - 1);     // available for SPIFLASH_PROG_SIZE power of 2
            addrInPage = wCnt % SPIFLASH_PROG_SIZE;                     
            sprintf(strMsg, "ADDR:%02d  Val:%03d", addrInPage, spiFlashPageR[addrInPage]);        
            LCD_WriteStringAtPos(strMsg, 1, 0);     
            //SSD_WriteDigitsGrouped(wCnt++, 0);
        }
    }    
}









void APP_UARTJB_USB() {
    
    // this is pmod (a=0 b=1, pmod pin, output = 0 input=1, nopullup=0, nopulldown=0)
    PMODS_InitPin(1,1,1,0,0); // initialisation du JB1 (RD9))
    
    UARTJB_Init(9600);
    
    LCD_Init();
    
    //UARTJB_ConfigureUartRXInt(9600);
    
    char received_buffer[80];
    
    LCD_DisplayClear();
    
    while(1)    {
        unsigned char len = UARTJB_GetString(received_buffer, RECEIVE_BUFFER_LEN);
        
        if (len > 0)    {
//            LCD_DisplayClear();
            //DelayAprox10Us(100);

            LCD_WriteStringAtPos(received_buffer, 1, 1);
                        UARTJB_PutString(received_buffer);
            UARTJB_PutChar('\n');
            UARTJB_PutChar('\r');
        }
    }
}











// dans spiflash_ProgramPage(ceci est ladresse, ceci est le pointeur (tableau de  ce quon veut ecrire), ce param est  );


// tu veut ensuite tu fais un masque et tu veut tous des zeros car 















// function of JP
void LCD_seconde(unsigned int seconde) { 
    LCD_WriteIntAtPos(seconde%60, 3, 0, 13, 0);     
    LCD_WriteStringAtPos(":", 0, 13); // affichage des secondes
    LCD_WriteIntAtPos(seconde/60%60, 3, 0, 10, 0);  
    LCD_WriteStringAtPos(":", 0, 10); // affichage des secondes
    LCD_WriteIntAtPos(seconde/3600%24, 3, 0, 7, 0);  
}










void APP_uartJB_poll()  {
    
    //UARTJB_Init();
    LCD_Init();
    
    UARTJB_ConfigureUartRXInt(9600);
    
    char strMsg[80];
    char strUART[80];
    
    unsigned char c;
    
    
    
    
    while(1)    {
        
    //UARTJB_GetStringPoll(strUART);
    c = UARTJB_GetCharPoll();
    //strcat(strMsg, strUART);
    
    // initialize UARTJB in the receive polling mode, baud 9600, no parity and 1 stop bit

    LCD_WriteIntAtPos(c, 1, 1, 1, 0);
    }
    
}










void APP_UARTJB_Int(){
        
    char strTxti[cchRxMax];   
    unsigned char cchi;
    //UART and LCD basic initializations
    UARTJB_Init(9600); 
    LCD_Init();
    //send a text to UART terminal on PC
    UARTJB_PutString("UART Demo \n\r");
    UARTJB_PutString("Send a text file\n\r");
    LCD_WriteStringAtPos(" UART Demo Int", 0, 0);
    //LCD_DisplayClear();
    //when sending a text file, make sure the content ends with CR+LF and your terminal is also setup accordingly, to transmit both characters
    //otherwise, the file sending will not function correctly
    while(1){    
        cchi = UARTJB_GetString(strTxti, cchRxMax);
        if(cchi > 0)
        {
          //display the received string on the LCD
          LCD_WriteStringAtPos(strTxti, 0, 0);
          LCD_WriteStringAtPos("UART Int Demo", 1, 0);
          //send the content of the file back to UART to be visualized
          UARTJB_PutString(strTxti);
        }  
    }    
}


























/***	UARTDemoInt
**
**	Parameters:
**		
**
**	Return Value:
**		
**
**	Description:
**		This function initializes the LCD and UART interface and calls specific UART interrupt based functions 
**      to send and receive a string to/from the terminal
**          
*/
void UARTDemoInt(){
    
    char strTxti[cchRxMax];   
    unsigned char cchi;
    //UART and LCD basic initializations
    UART_Init(9600); 
    LCD_Init();
    //send a text to UART terminal on PC
    UART_PutString("UART Demo \n\r");
    UART_PutString("Send a text file\n\r");
    LCD_WriteStringAtPos(" UART Demo Int", 0, 0);
    LCD_DisplayClear();
    //when sending a text file, make sure the content ends with CR+LF and your terminal is also setup accordingly, to transmit both characters
    //otherwise, the file sending will not function correctly
    while(1){    
        cchi = UART_GetString(strTxti, cchRxMax);
        if(cchi > 0)
        {
          //display the received string on the LCD
          LCD_WriteStringAtPos(strTxti, 0, 0);
          LCD_WriteStringAtPos("UART Int Demo", 1, 0);
          //send the content of the file back to UART to be visualized
          UART_PutString(strTxti);
        }  
    }    
}








/***	UARTDemoPoll
**
**	Parameters:
**		
**
**	Return Value:
**		
**
**	Description:
**		This function initializes the LCD and UART interface and calls specific UART polling based functions 
**      to send and receive a character to/from the terminal
**          
*/
void UARTDemoPoll()
{
    char strTxtp[cchRxMax];   
    unsigned char cch;
    //UART and LCD basic initializations
    UART_InitPoll(9600); 
    LCD_Init();
    //send a text to UART terminal on PC
    UART_PutString("UART Demo \n\r");
    UART_PutString("Send a char to UART\n\r");
    //write to the LCD as well
    LCD_WriteStringAtPos(" UART Demo Poll", 0, 0);
    LCD_DisplayClear();
    while(1)
    {    
        LCD_DisplayClear();
        cch = UART_GetCharPoll();
        //use the LCD display to visualize the received chars
        sprintf(strTxtp, " Received %c\n", cch);
        LCD_WriteStringAtPos(strTxtp, 1, 0);
        //send the char back to UART
        UART_PutChar(cch);
    }
}





/***	UARTDemoPmod
**
**	Parameters:
**		
**
**	Return Value:
**		
**
**	Description:
**		This function initializes the LCD and UART interface and calls specific UART polling based functions 
**      to send and receive a character to/from the terminal
**          
*/
void UARTDemoPmod()
{
    char strTxt[cchRxMax];   
    unsigned char cch;
    //UARTJB and LCD basic initializations
    UARTJB_Init(9600); 
    LCD_Init();
    //send a text to UART terminal on PC using UARTJB library
    UARTJB_PutString("UART Demo \n\r");
    UARTJB_PutString("Send a text file\n\r");
    LCD_WriteStringAtPos(" UART Demo Pmod", 0, 0);
    LCD_DisplayClear();
    //when sending a text file, make sure the content ends with CR+LF and your terminal is also setup accordingly, to transmit both characters
    //otherwise, the file sending will not function correctly
    while(1){  
        
        cch = UARTJB_GetString(strTxt, cchRxMax);
        if(cch > 0)
        {
           // LCD_DisplayClear();
          LCD_WriteStringAtPos(strTxt, 0, 0);
          LCD_WriteStringAtPos(" UART Demo Pmod", 1, 0);
          //send the content of the file back to UART to be visualized
          UARTJB_PutString(strTxt);
        }  
    }    
}
//the code below is used as part of the UARTDemoPmod function, when polling mode is needed
//replace the code above with the commented section below
/*char strTxtpmd[cchRxMax];   
    unsigned char cchp;
    //UART and LCD basic initializations
    UARTJB_InitPoll(9600); 
    LCD_Init();
    //send a text to UART terminal on PC
    UARTJB_PutString("UART Demo \n\r");
    UARTJB_PutString("Send a char to UART\n\r");
    //write to the LCD as well
    LCD_WriteStringAtPos(" UART Demo Pmod", 0, 0);
    
    while(1)
    {    
        cchp = UARTJB_GetCharPoll();
        //use the LCD display to visualize the received chars
        sprintf(strTxtpmd, "Received %c", cchp);
        LCD_WriteStringAtPos(strTxtpmd, 1, 0);
        //send the char back to UART
        UARTJB_PutChar(cchp);
    }
    }
     */












// this is a demo from Digilent github master Demos
void ACLDemo(){
    float rgACLGVals[3];  
    char strMsg[80];    
    unsigned int baseCnt = 0;
    ACL_Init();
    LCD_Init(); 
    LCD_WriteStringAtPos("ACL Demo", 0, 0);
    LCD_WriteStringAtPos("Digilent", 1, 0);

    while(1)
    {
       //perform ACL readings only once in a while, to be able to visualize the results
        if(++baseCnt == 400000)
       {
            baseCnt = 0;        
            ACL_ReadGValues(rgACLGVals);
            //display on the LCD screen the X values, first row
            sprintf(strMsg, "ACLDemo X:%6.3f", rgACLGVals[0]);
            LCD_WriteStringAtPos(strMsg, 0, 0);
            //display on the LCD screen the Y and Z values, second row
            sprintf(strMsg, "Y:%6.3fZ:%6.3f", rgACLGVals[1], rgACLGVals[2]);            
            LCD_WriteStringAtPos(strMsg, 1, 0);     
        }
    }  
}















// this is a demo from Digilent github master Demos
void SPIFLASH_Demo()
{
    
    unsigned char spiFlashPageW[SPIFLASH_PROG_SIZE]; // 256 bytes
    unsigned char spiFlashPageR[SPIFLASH_PROG_SIZE]; // 256 bytes
    unsigned char valSpiFlash = 'C';
    float rgACLGVals[3];  
    char strMsg[80];    
    unsigned int wCnt = 0, baseCnt = 0, valPot, addrSpiFlash, addrInPage;
    LCD_Init(); 
    LCD_WriteStringAtPos("SPI Flash test", 0, 0);
    LCD_WriteStringAtPos("Erase Flash ...", 1, 0);
    SPIFLASH_Init();
        // erase all flash
    SPIFLASH_EraseAll();
    // initialize the write and read buffers 
    for(addrInPage = 0; addrInPage < SPIFLASH_PROG_SIZE; addrInPage++)
    {
        spiFlashPageW[addrInPage] = addrInPage << 1; // address multiplied by 2
        spiFlashPageR[addrInPage] = 0xFF;           // this should be overwritten by read values
    }
    LCD_WriteStringAtPos("Write buffer ...", 1, 0);
    SPIFLASH_ProgramPage(SPIFLASH_PROG_ADDR, spiFlashPageW, SPIFLASH_PROG_SIZE);

    LCD_WriteStringAtPos("Read buffer ...", 1, 0);
    SPIFLASH_Read(SPIFLASH_PROG_ADDR, spiFlashPageR, SPIFLASH_PROG_SIZE);
    //SSD_Init();    

    while(1)
    {
        if(++baseCnt == 400000)
        {

            baseCnt = 0;        
//            addrInPage = wCnt & 0xFF;                         // available for SPIFLASH_PROG_SIZE = 256
//            addrInPage = wCnt & (SPIFLASH_PROG_SIZE - 1);     // available for SPIFLASH_PROG_SIZE power of 2
            addrInPage = wCnt % SPIFLASH_PROG_SIZE;                     
            sprintf(strMsg, "ADDR:%02d  Val:%03d", addrInPage, spiFlashPageR[addrInPage]);        
            LCD_WriteStringAtPos(strMsg, 1, 0);     
            //SSD_WriteDigitsGrouped(wCnt++, 0);
        }
    }    
}



























/* *****************************************************************************
 End of File
 */
