CC=g++
CCFLAGS=-lm -Wall -Wextra
PROGRAMNAME=pwm-weather.out
DEPENDENCIES=dependencies/tinyxml2.o

all:    main.o pwm-weather.o
	$(CC) main.o pwm-weather.o $(DEPENDENCIES) $(CCFLAGS) -o $(PROGRAMNAME)

main.o: main.cpp pwm-weather.h weather-codes.h custom-ranges.h
	$(CC) -c main.cpp $(CCFLAGS)

pwm-weather.o: pwm-weather.cpp pwm-weather.h weather-codes.h custom-ranges.h tinyxml.o
	$(CC) -c pwm-weather.cpp $(CCFLAGS)

tinyxml.o: dependencies/tinyxml2.cpp dependencies/tinyxml2.h
	$(CC) -c dependencies/tinyxml2.cpp $(CCFLAGS)

clean:
	rm *.o *.out
