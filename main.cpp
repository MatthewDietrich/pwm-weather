// For testing purposes

#include "pwm-weather.h"
#include <iostream>

int main()
{
    WeatherDataAsPWMValues wd = {0, 0, 0, 0};

    parse_weather_file("test.xml", &wd);

    std::cout << wd.temperature << std::endl
              << wd.humidity << std::endl
              << wd.condition << std::endl
              << wd.intensity << std::endl;

    return 0;
}
