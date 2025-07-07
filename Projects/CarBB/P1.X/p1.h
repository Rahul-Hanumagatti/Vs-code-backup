/* 
 * File:   p1.h
 * Author: Rahul H H
 *
 * Created on March 5, 2025, 1:51 PM
 */

#ifndef P1_H
#define	P1_H

// matrix keypad declarations
#define MAX_ROW				4
#define MAX_COL				3


#define STATE_CHANGE				1
#define LEVEL_CHANGE				0
#define MATRIX_KEYPAD_PORT			PORTB
#define ROW3					PORTBbits.RB7
#define ROW2					PORTBbits.RB6
#define ROW1					PORTBbits.RB5
#define COL4					PORTBbits.RB4
#define COL3					PORTBbits.RB3
#define COL2					PORTBbits.RB2
#define COL1					PORTBbits.RB1


#define MK_SW1					1
#define MK_SW2					2
#define MK_SW3					3
#define MK_SW4					4
#define MK_SW5					5
#define MK_SW6					6
#define MK_SW7					7
#define MK_SW8					8
#define MK_SW9					9
#define MK_SW10				10
#define MK_SW11				11
#define MK_SW12				12

#define ALL_RELEASED	0xFF

#define HI				1
#define LO				0

void init_matrix_keypad(void);
unsigned char scan_key(void);
unsigned char read_switches(unsigned char detection_type);

char *org_password = "00001111";  // original password

// clcd declarations

#define CLCD_PORT			PORTD
#define CLCD_EN				RC2
#define CLCD_RS				RC1
#define CLCD_RW				RC0
#define CLCD_BUSY			RD7
#define PORT_DIR			TRISD7


#define HI												1
#define LO												0

#define INPUT											0xFF
#define OUTPUT											0x00

#define DATA_COMMAND									1
#define INSTRUCTION_COMMAND								0
#define _XTAL_FREQ                  20000000
#define LINE1(x)									(0x80 + (x))
#define LINE2(x)										(0xC0 + (x))

#define TWO_LINE_5x8_MATRIX_8_BIT					clcd_write(0x38, INSTRUCTION_COMMAND)
#define CLEAR_DISP_SCREEN				                clcd_write(0x01, INSTRUCTION_COMMAND)
#define CURSOR_HOME							clcd_write(0x02, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_OFF						clcd_write(0x0C, INSTRUCTION_COMMAND)
#define EIGHT_BIT_MODE   0x30 // 33
void init_clcd(void);
void clcd_print(const unsigned char *data, unsigned char addr);
void clcd_putch(const unsigned char data, unsigned char addr);
void clcd_write(unsigned char bit_values, unsigned char control_bit);


typedef enum status
{
    DASHBOARD,
    MENU,
    VIEW,
    DOWNLOAD,
    CLEAR,
    SET_TIME
           
}status;

void dashboard(void);
void init_adc(void);
void init_config(void);
unsigned short read_adc(void);

static void get_time(void);

char time[9]= "00:00:00";
char event[][3] ={"ON","GR","GN","G1","G2","G3","G4","G5","C "}; // to store the data of event, dashboard
char menu_data[][17] ={"View Log        ","Download Log    ","Clear Log       ","Set Time        "}; // to store the data of menu bar
char store[5]; // to store the data to eeprom

// function to write data to eeprom using address
void internal_eeprom_write(unsigned char addr, unsigned char data);

// function to read data from eeprom using address
unsigned char internal_eeprom_read(unsigned char addr);

void store_data(void);

void menu(void);

void view(void);

void download(void);

void clear(void);

void set_time(void);

// uart declarations

#define RX_PIN					TRISC7
#define TX_PIN					TRISC6

void init_uart(void);
void putch(unsigned char byte);
int puts(const char *s);
unsigned char getch(void);
unsigned char getch_with_timeout(unsigned short max_time);
unsigned char getche(void);



//unsigned char clock_reg[3];
#endif	/* P1_H */

