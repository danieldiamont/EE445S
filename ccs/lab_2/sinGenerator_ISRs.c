// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2017

///////////////////////////////////////////////////////////////////////
// Filename: ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
#include <math.h>   
  
// Data is received as 2 16-bit words (left/right) packed into one
// 32-bit word.  The union allows the data to be accessed as a single 
// entity when transferring to and from the serial port, but still be 
// able to manipulate the left and right channels independently.

#define LEFT  0
#define RIGHT 1

volatile union {
	Uint32 UINT;
	Int16 Channel[2];
} CodecDataIn, CodecDataOut;


/* add any global variables here */
float A = 16000;		/* signal's amplitude */
float fDesired = 1000;  /* signal's frequency */
float phase = 0;        /* signal's initial phase */

float pi = 3.1415927;	/* value of pi */
float phaseIncrement;   /* incremental phase */

float fs = 8000;       /* sample frequency */

float y1[3] = {0, 1, 0};
float y2[3] = {0, 1, 0};

interrupt void Codec_ISR()
///////////////////////////////////////////////////////////////////////
// Purpose:   Codec interface interrupt service routine  
//
// Input:     None
//
// Returns:   Nothing
//
// Calls:     CheckForOverrun, ReadCodecData, WriteCodecData
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
{                    
	/* add any local variables here */
    float theta1 = (2*pi*6000.0/fs);
    float theta2 = (2*pi*2000.0/fs);

 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

  	CodecDataIn.UINT = ReadCodecData();		// get input data samples
	
	/* algorithm begins here */

  	/*
	phaseIncrement = 2*pi*fDesired/fs;  /* calculate the phase increment
	phase += phaseIncrement;            /* calculate the next phase
	
	if (phase >= 2*pi) phase -= 2*pi;    /* modulus 2*pi operation
	
	CodecDataOut.Channel[ LEFT] = A*sinf(phase); /* scaled L output
	CodecDataOut.Channel[RIGHT] = A*cosf(phase); /* scaled R output
	/* algorithm ends here
	*/

  	/* Difference Equation */

  	y1[0] = 2*cosf(theta1)*y1[1] - y1[2];
  	y1[2] = y1[1];
  	y1[1] = y1[0];

    y2[0] = 2*cosf(theta2)*y2[1] - y2[2];
    y2[2] = y2[1];
    y2[1] = y2[0];


    CodecDataOut.Channel[LEFT] = A*sinf(theta1)*y1[0]; /* scaled L output */
    CodecDataOut.Channel[RIGHT] = A*sinf(theta2)*y2[0]; /* scaled R output */

	WriteCodecData(CodecDataOut.UINT);		// send output data to  port
}

