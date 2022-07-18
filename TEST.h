/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _TEST_H    /* Guard against multiple inclusion */
#define _TEST_H





// Demo de github master Digilent
void ACLDemo();
void SPIFLASH_Demo();
void UARTDemoInt();
void UARTDemoPoll();
void UARTDemoPmod();






void APP_square_wave_PMOD();




// My functions
//void APP_writeACL_RawValues();
//void APP_writeACL_GValues();
void APP_lcd_seconde(unsigned int seconde); 
//void APP_writePOT_Value();


//unsigned int APP_set_time();
//void APP_set_date(char *date);
//void APP_lcd_time_date(unsigned int seconde, char *strDate);
//void APP_SPIFLASH_1();
//void APP_SPIFLASH_2();
//void APP_bastien_SPIFLASH_2(unsigned int seconde);


void APP_UARTJB_Int();
void APP_uartJB_poll();
void APP_UARTJB_USB();






#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
