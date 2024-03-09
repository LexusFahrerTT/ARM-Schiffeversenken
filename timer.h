#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

// Definitions ----------------------------------------------------------------

// Base Address (Instance)
#define TIMER0_BASE_ADDRESS    0x40008000
#define TIMER1_BASE_ADDRESS    0x40009000
#define TIMER2_BASE_ADDRESS    0x4000A000

// Register Offsets (from Table 141, page 100)
// Tasks:
#define TIMER_START         0x000    // Start Timer
#define TIMER_STOP          0x004    // Stop Timer
#define TIMER_COUNT         0x008    // Increment Timer (Counter mode only)
#define TIMER_CLEAR         0x00C    // Clear time
#define TIMER_SHUTDOWN      0x010    // Shut down timer

#define TIMER_CAPTURE_0     0x040    // Capture Timer value to CC[0] register
#define TIMER_CAPTURE_1     0x044    // Capture Timer value to CC[1] register
#define TIMER_CAPTURE_2     0x048    // Capture Timer value to CC[2] register
#define TIMER_CAPTURE_3     0x04C    // Capture Timer value to CC[3] register

// Events:
#define TIMER_COMPARE_0    0x140     // Compare event on CC[0] match
#define TIMER_COMPARE_1    0x144     // Compare event on CC[1] match
#define TIMER_COMPARE_2    0x148     // Compare event on CC[2] match
#define TIMER_COMPARE_3    0x14C     // Compare event on CC[3] match

// Registers:
#define TIMER_SHORTS       0x200     // Shortcut register
#define TIMER_INTENSET     0x304     // Enable interrupt
#define TIMER_INTENCLR     0x308     // Disable interrupt
#define TIMER_MODE         0x504     // Timer mode selection
#define TIMER_BITMODE      0x508     // Configure the number of bits used by the TIMER
#define TIMER_PRESCALER    0x510     // Timer prescaler register
#define TIMER_CC_0         0x540     // Capture/Compare register 0
#define TIMER_CC_1         0x544     // Capture/Compare register 1
#define TIMER_CC_2         0x548     // Capture/Compare register 2
#define TIMER_CC_3         0x54C     // Capture/Compare register 3

// Other:
#define TIMER_TASK_START       1     // Value for starting a Task
#define TIMER_TASK_STOP       1     // Value for starting a Task
#define TIMER_EVENT_TRIGGER    1     // Value for setting/starting an Event
#define TIMER_EVENT_CLEAR      0     // Value for clearing/stopping an Event

#define SHORTS_COMPARE0_CLEAR_ENABLE   (1 << 0)  // Shortcut between COMPARE[0] event and CLEAR task
#define SHORTS_COMPARE0_CLEAR_DISABLE  (0 << 0)  // Shortcut between COMPARE[0] event and CLEAR task
#define SHORTS_COMPARE1_CLEAR_ENABLE   (1 << 1)  // Shortcut between COMPARE[1] event and CLEAR task
#define SHORTS_COMPARE1_CLEAR_DISABLE  (0 << 1)  // Shortcut between COMPARE[1] event and CLEAR task

#define SHORTS_COMPARE0_STOP_ENABLE    (1 << 8)  // Shortcut between COMPARE[0] event and STOP task
#define SHORTS_COMPARE0_STOP_DISABLE   (0 << 8)  // Shortcut between COMPARE[0] event and STOP task
#define SHORTS_COMPARE1_STOP_ENABLE    (1 << 9)  // Shortcut between COMPARE[1] event and STOP task
#define SHORTS_COMPARE1_STOP_DISABLE   (0 << 9)  // Shortcut between COMPARE[1] event and STOP task

#define INT_COMPARE0  (1 << 16)  // Enable/Disable Interrupt on COMPARE[0] event
#define INT_COMPARE1  (1 << 17)  // Enable/Disable Interrupt on COMPARE[1] event
#define INT_COMPARE2  (1 << 18)  // Enable/Disable Interrupt on COMPARE[2] event
#define INT_COMPARE3  (1 << 19)  // Enable/Disable Interrupt on COMPARE[3] event

// C Function Definitions -----------------------------------------------------

/**
 * @brief Initializes the Timer[0] Peripheral to a value ~4sek
 * This is just for demonstration and could be changed to your needs
 */
void timer_init();


/**
 * @brief Initializes the Timer[0] Peripheral to the Values given
 * It also enable the shortcut between CC[0] and CLEAR, so that the timer
 * is cleared, when the compared value is reached.
 * 
 * Compare Value set is for CC[0]
 * 
 * @param prescaler    Register value according to `Table 147: PRESCALER`
 * @param bitmode      Register value according to `Table 146: BITMODE`
 * @param compareValue Register value according to `Table 148: CC[0]`
 */
void timer_init_detailed(uint32_t prescaler, uint32_t bitmode, uint32_t compareValue);

 
/**
 * @brief Clears the Compare Event for CC[0]
 * 
 * This could be useful for stopping the
 * timer from pulling the interrupt-line.
 */
void timer_clearCompareEvent();

#endif