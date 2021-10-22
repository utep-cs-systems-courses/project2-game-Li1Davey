# makfile configuration
COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: main.elf 

#additional rules for files
main.elf: ${COMMON_OBJECTS} main.o buzzer.o lightControl-c.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a
led-c.elf: ${COMMON_OBJECTS} lightControl-c.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a
buzzer.elf: ${COMMON_OBJECTS} buzzer.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load: main.elf
	msp430loader.sh  $^

clean: $^
	rm -f *.o *.elf


buzzer.o: buzzer.h
main.o: buzzer.h led.h sheetMusic.h
sheetMusic.o: sheetMusic.h
lightControl-c.o: led.h

wdInterruptHandler.o: led.h
light-on-c.o: led.h lightControl_c.c

