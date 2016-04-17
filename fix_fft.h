#ifndef fix_fft_h
#define fix_fft_h

#include <Energia.h>

#define DEBUG              1     //debug print, 0 = no debug print

/*
Highest valid frequency measured
        |                          FREQ_RESOLUTION
  LOG2N |     5       10       20       40       50      100      200      500     
  ===== | ========|========|========|========|========|========|========|========|
    5   |                               600      750     1500     3000     7500   
    6   |                      620     1240     1550     3100     6200  
    7   |             630     1260     2520     3150     6300    12600
    8   |    635     1270     2540     5080     6350    12700
    9   |   1275     2550     5100    10200    12750
   10   |   2555     5110    10220

Milliseconds for one conversion   
           |                          FREQ_RESOLUTION
  LOG2N |     5       10       20       40       50      100      200      500     
  ===== | ========|========|========|========|========|========|========|========|
    5   |                               28       22       12       6        3   
    6   |                      53       27       22       12       5  
    7   |            105       54       29       24       12       9
    8   |    209     108       57       32       24       18
    9   |    215     115       65       40       36
   10   |    229     130       81
*/
                                 
#define LOG2N              9     //log base 2 of the number of points, e.g. LOG2N = 8 is 256 points
#define FREQ_RESOLUTION   20     //Frequency resolution of output in Hz
#define ANALOG_IN          6     //analog input pin
#define ANALOG_RESOLUTION 14     //CPU specific - e.g. set to 12 for TM4C123/129 and 14 for MSP432

const int nPts = pow(2,LOG2N);
const int hiFreq = FREQ_RESOLUTION * (nPts/2 - 1);

inline int FIX_MPY(int a, int b);
int fix_fft(int fr[], int fi[], int m, int inverse);
int fix_fftr(int f[], int m, int inverse);

#endif
