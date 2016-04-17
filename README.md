# FFT
An FFT to run on the MSP-EXP432P401R and EK-TM4C123GXL LaunchPads

Uses fix_fft.c - Fixed-point in-place Fast Fourier Transform
Inspired by Shane Ormonde's post on wattnotion: http://www.wattnotions.com/tiva-c-launchpad-fft-with-real-time-plotting-using-pyqtgraph/

Additions, enhancements, and changes:
1) Number of samples can be specified (powers of 2)
2) Frequency resolution in bins can be set
3) Frequency measurement to ~5 kHz or more possible
4) Bin readings matched with corresponding frequency down to ~2% accuracy or better

Tested: MSP-EXP432401R LaunchPad with Energia v17
        EK-TM4C123GXL LaunchPad with Energia v17
      
User needs to change the analog resolution in fix_fft.h as well as debug print statements to match the microcontroller that they are using.
  
Frank Milburn   January 2016
Released into the public domain
