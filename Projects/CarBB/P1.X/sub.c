/*
 * File:   sub.c
 * Author: Rahul H H
 *
 * Created on March 5, 2025, 2:15 PM
 */


#include <xc.h>
#include "p1.h"
#include "External_eeprom.h"
#include "ds1307.h"
#include "i2c.h"


extern unsigned char flag;
unsigned int event_index; 
extern unsigned char key;
unsigned int speed =0;
unsigned char lap;
 

        
void dashboard(void)
{
    clcd_print("TIME     EV   SP", LINE1(0));  // default 1 st line will print i.e, dashboard
    
   
    clcd_print(time, LINE2(0));  // printing time
    
    speed = read_adc()/10.33;  // reading adc value to know the speed, dividing by 10.33 to convert the range from 0- 1023 to 0 - 99
    
    if(key == 2) // decrement , switch 2
    {
        if(event_index == 8) // if accident means , if we press switch 2 means , it should print GN
            event_index =2;
        else if(event_index <7) // incrementing till G5 only
            event_index++;
        
        store_data(); // function call to store the data every time when we press the key
        CLEAR_DISP_SCREEN;
    }
    else if(key == 3) // increment , switch 3
    {
        if(event_index == 8) // if accident means , if we press switch 3 means , it should print GN
            event_index =2;
        else if(event_index > 1) // decrementing till GR only
            event_index--;
        
        store_data(); // function call to store the data every time when we press the key
        CLEAR_DISP_SCREEN;
    }
    else if(key == 1) // collision / accident , switch 1
    {
        event_index =8; // printing C
        
        store_data(); // function call to store the data every time when we press the key
        CLEAR_DISP_SCREEN;
    }
    
    
    clcd_print(event[event_index], LINE2(9)); // printing the event
    clcd_putch((speed/10)+48, LINE2(14));  // printing 1st character of speed
    clcd_putch((speed%10)+48, LINE2(15));  // printing 2nd character of speed
    
}

void store_data(void)
{
    // storing the data of dashboard in runtime after getting data from dashboard at runtime
    
    store[0] = ((time[0] - 48) *10 + (time[1] - 48));
    store[1] = ((time[3] - 48) *10 + (time[4] - 48));
    store[2] = ((time[6] - 48) *10 + (time[7] - 48));
    store[3] =  event_index;
    store[4] =  speed;
   
    
    if(lap == 10)  // storing 50 bytes of data i.e last 10 data in 5 bytes
    {
        
        lap = 9; // resetting lap to 9 , to erase 1st data
        for(unsigned int k=5;k<50;k++)
        {
            char temp = read_external_eeprom(k); // reading each character
            write_external_eeprom(k-5, temp); // writing that read character starting from 0 position 
        }
    }
    
    // storing total of 50 bytes of data
    for(int i=0;i<5;i++) // storing in 5 bytes of memory
    {
        write_external_eeprom(i+(lap * 5), store[i]); // converting into character 
    }
    lap++;
}

unsigned char menu_index=0, star_flag=0;
void menu(void)
{
  
   
   clcd_print(menu_data[ menu_index], LINE1(1)); // printing the event
   clcd_print(menu_data[ menu_index+1], LINE2(1)); // printing the event
   
     if( star_flag)
    {
        clcd_print(" ", LINE1(0));
        clcd_print("*", LINE2(0));
    }
    else
    {
        clcd_print("*", LINE1(0));
        clcd_print(" ", LINE2(0));
    }
   
  
   
   if(key == 3) // scroll down
   {
       if(star_flag == 0)
           star_flag =1;
       else if( menu_index != 2)
         menu_index++;
       CLEAR_DISP_SCREEN;
   }
   else if(key == 2) // scroll up
   {
       if(star_flag ==1)
           star_flag =0;
       else if( menu_index != 0)
          menu_index--;
       CLEAR_DISP_SCREEN;
   }
   
   if(key == 5)
    {
       flag = DASHBOARD;
       CLEAR_DISP_SCREEN;
    }
   
}


