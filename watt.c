#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/time.h>

// What GPIO input are we using?
//	This is a wiringPi pin number

#define	BUTTON_PIN	9


static volatile int globalCounter = 0 ;
struct timeval stop, start;

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
  FILE *datei_t;
  int timed;

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

    gettimeofday(&start, NULL);

    while (myCounter == globalCounter)
      delay (100) ;

    gettimeofday(&stop, NULL);

    timed = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    datei_t = fopen ("/home/pi/raspberry-s0-bus-stromzaehler-logger/stomtimed", "w");
    fprintf (datei_t, "%d\n", timed);
    fclose (datei_t);


    myCounter = globalCounter ;
  }

  return 0 ;
}
