// For testing purposes

#include "pwm-weather.h"
#include <iostream>

int main()
{
    WeatherDataAsPWMValues wd;

    convert_humidity_to_pwm(50.1f, &wd);
    int a = wd.temperature;
    std::cout << a << std::endl;

    return 0;
}
