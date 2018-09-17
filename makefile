CC=g++
CCFLAGS=-lm -Wall -Wextra
PROGRAMNAME=pwm-weather.out
DEPENDENCIES=dependencies/tinyxml2.o

all:    main.o pwm-weather.o
	$(CC) main.o pwm-weather.o $(DEPENDENCIES) $(CCFLAGS) -o $(PROGRAMNAME)

main.o: pwm-weather.h weather-codes.h custom-ranges.h
	$(CC) -c main.cpp $(CCFLAGS)

pwm-weather.o: pwm-weather.h weather-codes.h custom-ranges.h
	$(CC) -c pwm-weather.cpp $(CCFLAGS)

tinyxml.o: dependencies/tinyxml.cpp dependencies/tinyxml.h
	$(CC) -c dependencies/tinyxml.o $(CCFLAGS)

clean:
	rm *.o *.out
