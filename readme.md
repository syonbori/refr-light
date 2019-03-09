# ATTiny13A Child-toy refrigerator LED light controller

## AVR
ATTiny13A with 4.8MHz internal clock

## schematics
see refr-light.png
![schematics](https://raw.githubusercontent.com/syonbori/refr-light/master/refr-light.png "schematics")

## behavior
- when door closed, light turns off and enter sleep
- when door opened, light turns on and:
- after 60 seconds or door closed, light turns off and enter sleep
