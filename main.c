// For testing purposes

#include "pwm-weather.h"
#include <stdio.h>

int main()
{
    WeatherDataAsPWMValues wd;

    convert_temperature_to_pwm(-250.4f, &wd);
    printf("%d\n", wd.temperature);

    return 0;
}
