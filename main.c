// For testing purposes

#include "pwm-weather.h"
#include <stdio.h>

int main()
{
    WeatherDataAsPWMValues wd;

    convert_humidity_to_pwm(50.1f, &wd);
    printf("%d\n", wd.temperature);

    return 0;
}
