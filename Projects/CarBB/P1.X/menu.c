/*
 * File:   menu.c
 * Author: Rahul H H
 *
 * Created on March 7, 2025, 3:44 PM
 */


#include <xc.h>
#include "p1.h"
#include "External_eeprom.h"
#include "ds1307.h"
#include "i2c.h"
#include "clcd.h"


extern unsigned char flag;
extern unsigned char key;
extern unsigned char lap;

static unsigned long delay = 0;
static unsigned long delay1 = 0;
unsigned long delay2 = 0;
static unsigned long delay3 = 0;
unsigned char fk = 0;

char serial = 0;
char uart_key = 0;

char setf = 0;

signed char fflag = -1;

unsigned char hr;
//unsigned char hr2 ;
unsigned char min;
//unsigned char min2 ;
unsigned char sec;
//unsigned char sec2 ;

unsigned char dy;
unsigned char dy2;
unsigned char dy3;

unsigned char temphr;
unsigned char tempmin;
unsigned char tempsec;

void view(void) {
    if (key == 5) {
        flag = MENU;
        serial = 0;
    }

    if (key == 3) {
        if (serial < lap - 1)
            serial++;

    } else if (key == 2) {
        if (serial > 0)
            serial--;
    }

    clcd_print("View Log :-     ", LINE1(0)); // default 1 st line will print i.e, 

    if (lap == 0) {
        clcd_print("!NO DATA SAVED!", LINE2(0));
        if (delay1++ == 1000) {
            delay1 = 0;
            flag = MENU;
        }
    } else {
        // serial number
        clcd_putch(serial + 48, LINE2(0)); // printing serial no on 0th position

        clcd_putch(' ', LINE2(1)); // printing space on 1st position

        // Time
        clcd_putch(read_external_eeprom(serial * 5) / 10 + 48, LINE2(2)); // 1st digit ,printing time on 2nd position
        clcd_putch(read_external_eeprom(serial * 5) % 10 + 48, LINE2(3)); // 2nd digit, printing time on  3rd position

        clcd_putch(':', LINE2(4)); // printing : 4th  position

        clcd_putch(read_external_eeprom(serial * 5 + 1) / 10 + 48, LINE2(5)); // 3rd digit ,printing time on 5th position
        clcd_putch(read_external_eeprom(serial * 5 + 1) % 10 + 48, LINE2(6)); // 4th digit ,printing time on 6th position

        clcd_putch(':', LINE2(7)); //  printing : 7th  position

        clcd_putch(read_external_eeprom(serial * 5 + 2) / 10 + 48, LINE2(8)); // 5th digit ,printing time on 8th position
        clcd_putch(read_external_eeprom(serial * 5 + 2) % 10 + 48, LINE2(9)); // 6th digit ,printing time on 9th position

        clcd_putch(' ', LINE2(10)); // printing space on 10th position

        // status of event
        clcd_print(event[read_external_eeprom(serial * 5 + 3)], LINE2(11)); // printing status no 11th position

        clcd_putch(' ', LINE2(13)); // printing space on 12th position

        // speed
        clcd_putch(read_external_eeprom(serial * 5 + 4) / 10 + 48, LINE2(14)); // printing speed 1st digit on 14th position
        clcd_putch(read_external_eeprom(serial * 5 + 4) % 10 + 48, LINE2(15)); // printing speed 2nd digit on 15th  position
    }
}

void download(void) {
    if (key == 5) {
        flag = MENU;
    }

    clcd_print("Download Log :-     ", LINE1(0)); // default 1 st line will print i.e, dashboard



    // puts("\n\r"); // to print next line 
    if (lap == 0)
    {
        clcd_print("!NO DATA SAVED!", LINE2(0));
        if (delay1++ == 1000) {
            delay1 = 0;
            flag = MENU;
        }
    } else {
        //clcd_print("DOWNLOAD SUCCESS",LINE2(0));  // printing on CLCD

        if (fk == 0) {
            puts("#  TIME    EV SP"); // printing space on 1st position
            puts("\n\r"); // to print next line 
            fk = 1;
        }

        clcd_print("DOWNLOAD SUCCESS", LINE2(0)); // printing on CLCD




        if (delay2++ >= 500) {
            delay2 = 0;
            putch(uart_key + 48); // printing serial no on 0th position

            putch(' '); // printing space on 1st position


            putch(read_external_eeprom(uart_key * 5) / 10 + 48); // 1st digit ,printing time on 2nd position
            putch(read_external_eeprom(uart_key * 5) % 10 + 48); //  2nd digit, printing time on  3rd position

            putch(':'); //  printing : 4th  position

            putch(read_external_eeprom(uart_key * 5 + 1) / 10 + 48); //  3rd digit ,printing time on 5th position
            putch(read_external_eeprom(uart_key * 5 + 1) % 10 + 48); // 4th digit ,printing time on 6th position

            putch(':'); //printing : 7th  position

            putch(read_external_eeprom(uart_key * 5 + 2) / 10 + 48); //  5th digit ,printing time on 8th position
            putch(read_external_eeprom(uart_key * 5 + 2) % 10 + 48); // 6th digit ,printing time on 9th position

            putch(' '); // printing space on 10th position

            puts(event[read_external_eeprom(uart_key * 5 + 3)]); // printing serial no on 1st position

            putch(' '); // printing space on 12th position

            putch(read_external_eeprom(uart_key * 5 + 4) / 10 + 48); // printing speed 1st digit on 14th position
            putch(read_external_eeprom(uart_key * 5 + 4) % 10 + 48); // printing speed 2nd digit on 15th  position

            puts("\n\r"); // to print next line 

            if (uart_key < lap)
                uart_key++;

            if (uart_key >= lap) {
                flag = MENU;
                uart_key = 0;
                puts("\n\r"); // to print next line 
            }
        }

    }






}

void clear(void) {
    if (key == 5) {
        setf = 0;
        flag = MENU;
    }

    clcd_print("Clear Log :-     ", LINE1(0)); // default 1 st line will print i.e, dashboard
    //clcd_print("                  ", LINE2(0));  // default 1 st line will print i.e, dashboard

    if (lap != 0) {

        clcd_print("SUCCESSFULLY    ", LINE2(0));

        if (delay++ == 1000) {
            delay = 0;
            lap = 0; // setting lap to 0.
            flag = MENU;
        }

    } else {
        clcd_print("!NO DATA SAVED!", LINE2(0));

        if (delay1++ == 1000) {
            delay1 = 0;
            flag = MENU;
        }

    }


}

void set_time(void) {
    if (key == 5) {
        flag = MENU;
    }

    //clcd_print("Set_Time :-     ", LINE1(0));  // default 1 st line will print i.e, dashboard
    clcd_print("    HH:MM:SS    ", LINE1(0));

    if (setf == 0) 
    {
        hr = ((time[0] - 48) *10) + time[1] - 48;
        
        min = ((time[3] - 48) *10) + time[4] - 48;
        
        sec = ((time[6] - 48) *10) + time[7] - 48;

        setf = 1;
    }


    clcd_print("    ", LINE2(0));
    clcd_putch(hr / 10 + 48, LINE2(4));
    clcd_putch(hr % 10 + 48, LINE2(5));
    clcd_putch(':', LINE2(6));
    clcd_putch(min / 10 + 48, LINE2(7));
    clcd_putch(min % 10 + 48, LINE2(8));
    clcd_putch(':', LINE2(9));
    clcd_putch(sec / 10 + 48, LINE2(10));
    clcd_putch(sec % 10 + 48, LINE2(11));
    clcd_print("    ", LINE2(12));

    
       //static int dy = 0, dy2 = 0, dy3 = 0;

    if (fflag == 0) { // Blink hours
        if (dy++ >= 500) dy = 0;
        if (dy < 250) {
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
        } else {
            clcd_putch(hr / 10 + 48, LINE2(4));
            clcd_putch(hr % 10 + 48, LINE2(5));
        }
    } else {
        clcd_putch(hr / 10 + 48, LINE2(4));
        clcd_putch(hr % 10 + 48, LINE2(5));
    }

    clcd_putch(':', LINE2(6));

    if (fflag == 1) { // Blink minutes
        if (dy2++ >= 500) dy2 = 0;
        if (dy2 < 250) {
            clcd_putch(' ', LINE2(7));
            clcd_putch(' ', LINE2(8));
        } else {
            clcd_putch(min / 10 + 48, LINE2(7));
            clcd_putch(min % 10 + 48, LINE2(8));
        }
    } else {
        clcd_putch(min / 10 + 48, LINE2(7));
        clcd_putch(min % 10 + 48, LINE2(8));
    }

    clcd_putch(':', LINE2(9));

    if (fflag == 2) { // Blink seconds
        if (dy3++ >= 500) dy3 = 0;
        if (dy3 < 250) {
            clcd_putch(' ', LINE2(10));
            clcd_putch(' ', LINE2(11));
        } else {
            clcd_putch(sec / 10 + 48, LINE2(10));
            clcd_putch(sec % 10 + 48, LINE2(11));
        }
    } else {
        clcd_putch(sec / 10 + 48, LINE2(10));
        clcd_putch(sec % 10 + 48, LINE2(11));
    }
    

    if (key == 2) // increment
    {

        if (fflag == 0) // hr
        {

            if (hr > 22)
                hr = 0;
            else
                hr++;


        } else if (fflag == 1) // min
        {

            if (min > 58)
                min = 0;
            else
                min++;
        } else if (fflag == 2) // sec
        {


            if (sec > 58)
                sec = 0;
            else
                sec++;


        }



    } else if (key == 3) // change field
    {
        if (fflag >= 2)
            fflag = 0;
        else
            fflag++;

    } else if (key == 4) // save in RTC and go back
    {
        // saving time before going back to menu

        hr = (hr / 10) << 4 | (hr % 10);
        write_ds1307(HOUR_ADDR, hr);


        min = (min / 10) << 4 | (min % 10);
        write_ds1307(MIN_ADDR, min);


        sec = (sec / 10) << 4 | (sec % 10);
        write_ds1307(SEC_ADDR, sec);

        setf = 0;
        flag = MENU;
    }


}
