// For testing purposes

#include "pwm-weather.h"
#include <iostream>

int main()
{
    WeatherDataAsPWMValues wd;

    parse_weather_file("test.xml", &wd);

    return 0;
}
