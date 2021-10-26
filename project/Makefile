# makfile configuration
COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I./h -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: main.elf 

#additional rules for files
main.elf: main.o buzzer.o switch.o stateMachine.o lightControl-c.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ./lib/libTimer.a

main-s.elf: main.o buzzer.o switch.o stateMachine.o lightControl-s.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ./lib/libTimer.a

load: main.elf
	msp430loader.sh  $^

load2: main-s.elf
	msp430loader.sh  $^

clean: $^
	rm -f *.o *.elf


buzzer.o: buzzer.h
switch.o: switch.h stateMachine.h
stateMachine.o: stateMachine.h buzzer.h led.h switch.h sheetMusic.h
main.o: buzzer.h led.h switch.h stateMachine.h
lightControl-c.o: led.h
lightControl-s.o: led.h

wdInterruptHandler.o: stateMachine.h
