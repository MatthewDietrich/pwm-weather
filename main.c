// For testing purposes

#include "pwm-weather.h"
#include <stdio.h>

int main()
{
    WeatherDataAsPWMValues wd;

    parse_weather_condition_code(WCC_TS, &wd);
    printf("%d %d\n", wd.condition, wd.intensity);

    return 0;
}
