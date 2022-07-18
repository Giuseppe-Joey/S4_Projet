/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Digilent

  @File Name
    audio.h

  @Description
    This file groups the declarations of the functions that implement
    the Audio module (defined in audio.c). 
    Include the file in the project when the Audio library is needed.
 */
/* ************************************************************************** */

#ifndef _APP_H    /* Guard against multiple inclusion */
#define _APP_H



void APP_lcd_time_date(unsigned int seconde, char strDate[]);
void APP_set_date(char strDate[]);
unsigned int APP_set_time();

void APP_Affichage_1(unsigned int seconde);
void APP_Affichage_2();

void APP_SPIFLASH(unsigned int seconde);

void APP_writeACL_GValues();
void APP_writePOT_Value();
void APP_writeACL_RawValues();

void APP_square_wave_PMOD();





#endif /* _APP_H */

/* *****************************************************************************
 End of File
 */
