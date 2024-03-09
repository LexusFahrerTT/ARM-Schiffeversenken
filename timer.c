#include <stdint.h>

#include "timer.h"
#include "nvic.h"

#include "register_access.h"


void timer_init_detailed(uint32_t prescaler, uint32_t bitmode, uint32_t compareValue) {

	// Instance[0] of the Timer uses Peripheral ID: 8

	// Prescaler --------------------------------------------------------------
	// Set the Prescaler to min (1 = 0b00000001)
	//register_write((TIMER0_BASE_ADDRESS + TIMER_PRESCALER), 1);

	// Set the Prescaler to max (15 = 0b00001111)
	//register_write((TIMER0_BASE_ADDRESS + TIMER_PRESCALER), 15);

	// Set the Prescaler to custom value from arguments
	register_write((TIMER0_BASE_ADDRESS + TIMER_PRESCALER), prescaler);

	// BitMode ----------------------------------------------------------------
	// set BitMode Register = use 8bit
	//register_write((TIMER0_BASE_ADDRESS + TIMER_BITMODE), 0);

	// set BitMode Register = use 32bit
	//register_write((TIMER0_BASE_ADDRESS + TIMER_BITMODE), 3);

	// set BitMode Register to custom value from arguments
	register_write((TIMER0_BASE_ADDRESS + TIMER_BITMODE), bitmode);

	// Compare Value ----------------------------------------------------------
	// Compare Value to 255
	//register_write((TIMER0_BASE_ADDRESS + TIMER_CC_0), 255); // fast as hell!

	// Compare/Count to ~4sek
	//register_write((TIMER0_BASE_ADDRESS + TIMER_CC_0), 1953); // ~4 sek

	// Compare/Count to custom value from arguments
	register_write((TIMER0_BASE_ADDRESS + TIMER_CC_0), compareValue); // ~4 sek


	// Optional: Shortcuts ----------------------------------------------------
	// Enable Shortcut between CC[0] and STOP + CLEAR
	//register_write((TIMER0_BASE_ADDRESS + TIMER_SHORTS), 0x101); // G=1 + A=1

	// Enable Shortcut between CC[0] and CLEAR
	register_write((TIMER0_BASE_ADDRESS + TIMER_SHORTS), 0x01); //  A=1 -- CLEAR on CC[0]

	// Start the Module -------------------------------------------------------

	// Enable Interrupt
	register_write((TIMER0_BASE_ADDRESS + TIMER_INTENSET), INT_COMPARE0); // Interrupt on Compare[0]

	// Start Timer
	register_write((TIMER0_BASE_ADDRESS + TIMER_START), TIMER_TASK_START);

	// Enable User-Interrupt from Cortex-M0
	// ID8 ist der Timer0
	register_write(Interrupt_Set_Enable, Interrupt_ID8);
}

void timer_init() {

	// Init Timer with an interval of ~4sek
	timer_init_detailed(15, 3, 1953);
}

void timer_disable(){
	register_write((TIMER0_BASE_ADDRESS + TIMER_STOP), TIMER_TASK_STOP);
}

void timer_clearCompareEvent() {

	// Write a `0` to the compare 0 Register.
	// This is sufficient, because this example only uses CC[0]
	// If you're using more, feel free to expand.
	register_write((TIMER0_BASE_ADDRESS + TIMER_COMPARE_0), TIMER_EVENT_CLEAR);

}
