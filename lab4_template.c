/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"

#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#include "cyBot_Scan.h"  // For scan sensors


#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();

  // initialize the cyBot UART1 before trying to use it

  // (Uncomment ME for PuTTy to CyBot UART init part of lab)
	cyBot_uart_init_clean();  // Clean UART initialization, before running your UART GPIO init code

	// Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART GPIO init code)
mm      SYSCTL_RCGCGPIO_R |= 0b000010;
	    while ((SYSCTL_PRGPIO_R & 0b000010) == 0) {};
      GPIO_PORTB_AFSEL_R |= 0b00000011;
      GPIO_PORTB_PCTL_R &= 0x00000000;     // Force 0's in the desired locations
      GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the desired locations
		 // Or see the notes for a coding alternative to assign a value to the PCTL field
      GPIO_PORTB_DEN_R |= 0b00000011;
      GPIO_PORTB_DIR_R &= 0b11111110;      // Force 0's in the desired locations
      GPIO_PORTB_DIR_R |= 0b00000001;      // Force 1's in the desired locations

    // (Uncomment ME for UART init part of lab)
		 cyBot_uart_init_last_half();  // Complete the UART device configuration

	// Initialze scan sensors
    cyBOT_init_Scan();

    cyBOT_Scan_t scan;

	while(1)
	{

	    char data = cyBot_getByte_blocking();
	    if(data == 'm'){
	        int angle = 0;
	        for(angle = 0; angle <= 180; angle+=5){
	            cyBOT_Scan(angle, &scan);

	            cyBot_sendByte(angle);
	            cyBot_sendByte('\t');
	            cyBot_sendByte(scan.sound_dist);
	            cyBot_sendByte('\t');
	            cyBot_sendByte(scan.IR_raw_val);
	            cyBot_sendByte('\r');
	            cyBot_sendByte('\n');

	        }
	    }

	    //cyBot_sendByte(data);
	    // lcd_printf("%c", data);
	}

}
