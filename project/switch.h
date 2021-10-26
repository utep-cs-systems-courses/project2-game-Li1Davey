#ifndef switch_included
#define switch_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 |  SW2 |  SW3 | SW4) //(0xF)


void switch_init();
static char checkSwitches();
void switch_handle_switches();
void __interrupt_vec(PORT2_VECTOR) Port_2();

#endif
