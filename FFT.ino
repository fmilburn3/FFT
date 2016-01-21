/*
An Energia library that uses fix_fft.c - Fixed-point in-place Fast Fourier Transform
Inspired by Shane Ormonde's post on wattnotion: http://www.wattnotions.com/tiva-c-launchpad-fft-with-real-time-plotting-using-pyqtgraph/

Additions, enhancements, and changes:
1) Number of samples can be specified (powers of 2)
2) Frequency resolution in bins can be set
3) Frequency measurement to ~5 kHz or more possible
4) Bin readings matched with corresponding frequency down to ~2% accuracy or better

Tested: MSP-EXP432401R LaunchPad with Energia v17
        EK-TM4C123GXL LaunchPad with Energia v17
        
Frank Milburn   January 2016
Released into the public domain
*/
#include "fix_fft.h"

int real[nPts];
int imag[nPts];
int sampleInterval;            
 
void setup()
{
  Serial.begin(115200);
  delay(500);                   //give time for serial monitor to start up in Energia
  analogReadResolution(ANALOG_RESOLUTION);
        
  //****************** interval calculation *******************************  
  int unCorrectedSampleInterval = 500000/hiFreq;
  long startTime = micros();
  for(int i = 0; i < nPts; i++){             // determine total actual time for uncorrected interval
    real[i] = analogRead(ANALOG_IN);
    delayMicroseconds(unCorrectedSampleInterval);    // unadjusted sample interval
  }
  long endTime = micros();
  int totalTime = (int)(endTime - startTime);
  int expectedTime = nPts * unCorrectedSampleInterval;
  int errorTime = totalTime - expectedTime;
  sampleInterval = unCorrectedSampleInterval - errorTime/nPts;
  
  if (DEBUG) {
    Serial.println ("\nYou are now entering the frequency domain...\n");
    Serial.println ("Microcontroller   : MSP-EXP432401R");   
    Serial.print   ("Sample size       : ");
    Serial.println (nPts);
    Serial.print   ("Highest frequency : ");
    Serial.print   (hiFreq);
    Serial.println (" Hz");
    Serial.print   ("Resolution        : ");
    Serial.print   (FREQ_RESOLUTION);
    Serial.println (" Hz"); 
    Serial.print   ("\nunCorrectedSampleInterval = ");
    Serial.print   (unCorrectedSampleInterval);
    Serial.println (" micros");
    Serial.print   ("totalTime = ");
    Serial.print   (totalTime);
    Serial.println (" micros");    
    Serial.print   ("expectedTime = ");
    Serial.print   (expectedTime);
    Serial.println (" micros");
    Serial.print   ("errorTime = ");
    Serial.print   (errorTime);
    Serial.println (" micros");
    Serial.print   ("sampleInterval = ");
    Serial.print   (sampleInterval);
    Serial.println (" micros");
  }
}
 
void loop()
{
  int i;
  long startTime = micros();
  for (i=0; i<nPts; i++) {                   // read ADC pin nPts times at hiFreq kHz
    real[i] = analogRead(ANALOG_IN);
    delayMicroseconds(sampleInterval);       // adjusted sample interval
  }
  
  for( i=0; i<nPts; i++) imag[i] = 0;        // clear imaginary array
  
  fix_fft(real, imag, LOG2N, 0);             // perform fft on sampled points in real[i]
  
  for ( i = 0; i < nPts/2; i++)              //get the power magnitude in each bin
    {
      real[i] =sqrt((long)real[i] * (long)real[i] + (long)imag[i] * (long)imag[i]);        
    }
  if (DEBUG) {
    long endTime = micros();                 // All done, how long did it take?
    Serial.print   ("\nSampling time     : ");
    Serial.print   (endTime - startTime);
    Serial.println (" micro seconds");
    // find the peak
    int peakHz = 0;
    int peaki = 0;
    for (i = 1; i < nPts/2; i++) {          // bin 0 holds the summation - not peak
      if (real[i] > peakHz) {
        peakHz = real[i];
        peaki = i;
      }
    }
    peakHz = (peaki * FREQ_RESOLUTION) - FREQ_RESOLUTION/2;
    Serial.print   ("Peak frequency    : ");
    Serial.println (peakHz);
    Serial.println ("");
  }
  Serial.print     ("*\n");                //send fft results over serial to PC
  for (i=0; i<nPts/2; i++) {
    Serial.print   (real[i]);
    Serial.print   ("\n");
  } 

  while(1);
}
