/*
 * File:   p1.c
 * Author: Rahul H H
 *
 * Created on March 5, 2025, 1:51 PM
 */


#include <xc.h>
#include "p1.h"
#include "ds1307.h"
#include "i2c.h"
#include "External_eeprom.h"

unsigned char flag =0;
unsigned char key;
extern unsigned char menu_index; 
extern unsigned char  star_flag=0;

static void get_time(void)
{
	unsigned char hr = read_ds1307(HOUR_ADDR);
	unsigned char min = read_ds1307(MIN_ADDR);
	unsigned char sec = read_ds1307(SEC_ADDR);

	if (hr & 0x40)
	{
		time[0] = '0' + ((hr >> 4) & 0x01);
		time[1] = '0' + (hr & 0x0F);
	}
	else
	{
		time[0] = '0' + ((hr >> 4) & 0x03);
		time[1] = '0' + (hr & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((min >> 4) & 0x0F);
	time[4] = '0' + (min & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((sec >> 4) & 0x0F);
	time[7] = '0' + (sec & 0x0F);
	time[8] = '\0';
}


void init_config(void)
{
	init_matrix_keypad();  // initializing matrix keypad
	init_clcd(); // initializing clcd
    init_adc(); // initializing adc
    init_uart(); // initializing uart
    init_i2c();
    init_ds1307();
}


void main(void)
{
    init_config(); // calling configuration function to configure matrix keypad, clcd peripherals
   
    while(1)
    {
         get_time();
        key = read_switches(1); // edge triggering
        
        if(flag == DASHBOARD)  // default case
        { 
            //CLEAR_DISP_SCREEN;
            dashboard();
            if(key == 4) // switch 4 press
                flag = MENU;
            else if(key == 5)
                flag = DASHBOARD;  
            
        }
        else if(flag == MENU)
        {
            //CLEAR_DISP_SCREEN;
            menu();
            if(key == 4)
            {
                if((star_flag + menu_index + 2) == VIEW)
                {
                    flag = VIEW;
                }
                else if((star_flag + menu_index + 2) == DOWNLOAD)
                {
                    flag = DOWNLOAD;
                }
                else if((star_flag + menu_index + 2) == CLEAR)
                {
                    flag = CLEAR;
                }
                else if((star_flag + menu_index + 2) == SET_TIME)
                {
                    flag = SET_TIME; 
                }
            }
            
        }
        else if(flag == VIEW)
        {
            //CLEAR_DISP_SCREEN;
            view();
        }
        else if(flag == DOWNLOAD)
        {
            //CLEAR_DISP_SCREEN;
            download();
        }
        else if(flag == CLEAR)
        {
            //CLEAR_DISP_SCREEN;
            clear();
        }
        else if(flag == SET_TIME)
        {
            //CLEAR_DISP_SCREEN;
            set_time();
        }
        
        
        
    }
    
    return;
}
