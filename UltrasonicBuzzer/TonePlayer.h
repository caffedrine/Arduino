/*
 
 Play tones with hardware timers
 Author: Nick Gammon
 Date:   1 April 2013
 
 
 PERMISSION TO DISTRIBUTE
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 and associated documentation files (the "Software"), to deal in the Software without restriction, 
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in 
 all copies or substantial portions of the Software.
 
 
 LIMITATION OF LIABILITY
 
 The software is provided "as is", without warranty of any kind, express or implied, 
 including but not limited to the warranties of merchantability, fitness for a particular 
 purpose and noninfringement. In no event shall the authors or copyright holders be liable 
 for any claim, damages or other liability, whether in an action of contract, 
 tort or otherwise, arising from, out of or in connection with the software 
 or the use or other dealings in the software. 
 
 */

#ifndef _TONE_PLAYER_
#define _TONE_PLAYER_

#include <Arduino.h>

class TonePlayer
  {
  // addresses of output ports - NULL if not applicable
  volatile byte * const timerRegA_;
  volatile byte * const timerRegB_;
  volatile byte * const timerOCRH_;
  volatile byte * const timerOCRL_;
  volatile byte * const timerTCNTH_;
  volatile byte * const timerTCNTL_;
  
  public:
    // constructor
    TonePlayer (
          // ports
          volatile byte & timerRegA, 
          volatile byte & timerRegB, 
          volatile byte & timerOCRH,
          volatile byte & timerOCRL, 
          volatile byte & timerTCNTH, 
          volatile byte & timerTCNTL)
       : 
         timerRegA_  (&timerRegA), 
         timerRegB_  (&timerRegB),
         timerOCRH_  (&timerOCRH), 
         timerOCRL_  (&timerOCRL), 
         timerTCNTH_ (&timerTCNTH), 
         timerTCNTL_ (&timerTCNTH)
  { }
    
    void tone (const unsigned int Hz);
    void noTone ();
    
  };  // end of TonePlayer

void TonePlayer::tone (const unsigned int Hz)
{
  // it takes two toggles for one "cycle"
  unsigned long ocr = F_CPU / Hz / 2;
  byte prescaler = _BV (CS10);  // start with prescaler of 1  (bits are the same for all timers)

  // too large? prescale it
  if (ocr > 0xFFFF)
    {
    prescaler |= _BV (CS11);    // now prescaler of 64
    ocr /= 64;
    }

  // stop timer
  *timerRegA_ = 0;
  *timerRegB_ = 0;

  // reset counter
  *timerTCNTH_ = 0;
  *timerTCNTL_ = 0;

  // what to count up to
  *timerOCRH_ = highByte (ocr);
  *timerOCRL_ = lowByte (ocr);

  *timerRegA_ = _BV (COM1A0);             // toggle output pin
  *timerRegB_ = _BV (WGM12) | prescaler;  // CTC
  }  // end of TonePlayer::tone

void TonePlayer::noTone ()
  {
  // stop timer
  *timerRegA_ = 0;
  *timerRegB_ = 0;
  } // end of TonePlayer::noTone

#endif // _TONE_PLAYER_
