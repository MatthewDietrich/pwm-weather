CC=g++
CCFLAGS=-lm -Wall -Wextra
PROGRAMNAME=pwm-weather.out

all:    main.o pwm-weather.o
	$(CC) main.o pwm-weather.o $(CCFLAGS) -o $(PROGRAMNAME)

main.o: pwm-weather.h weather-codes.h custom-ranges.h
	$(CC) -c main.cpp $(CCFLAGS)

pwm-weather.o: pwm-weather.h weather-codes.h custom-ranges.h
	$(CC) -c pwm-weather.cpp $(CCFLAGS)

clean:
	rm *.o *.out
