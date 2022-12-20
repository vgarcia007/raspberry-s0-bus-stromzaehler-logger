#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>


// What GPIO input are we using?
//	This is a wiringPi pin number

#define	BUTTON_PIN	9

// globalCounter:
//	Global variable to count interrupts
//	Should be declared volatile to make sure the compiler doesn't cache it.

static volatile int globalCounter = 0 ;


/*
 * myInterrupt:
 *********************************************************************************
 */

void myInterrupt (void)
{
  ++globalCounter ;
}


/*
 *********************************************************************************
 * main
 *********************************************************************************
 */

int main (void)
{
  int myCounter = 0 ;
  FILE *datei;
  int number = 0;

  if (wiringPiSetup () < 0)
  {
    fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &myInterrupt) < 0)
  {
    fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
    return 1 ;
  }


  for (;;)
  {
    while (myCounter == globalCounter)
      delay (50) ;

    datei = fopen ("/home/pi/raspberry-s0-bus-stromzaehler-logger/stromcounter", "r");
    fscanf(datei, "%d", &number) ;
    fclose (datei);
    //printf("Hello, please enter your age:\n");
    datei = fopen ("/home/pi/raspberry-s0-bus-stromzaehler-logger/stromcounter", "w");
    number = number + 1 ;
    fprintf (datei, "%d\n", number);
    fclose (datei);

    myCounter = globalCounter ;
  }

  return 0 ;
}
