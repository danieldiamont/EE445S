// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2017

///////////////////////////////////////////////////////////////////////
// Filename: FIRmono_ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
#include "coeff.h"	// load the filter coefficients, B[n] ... extern
  
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
float xLeft[N+1];
float yLeft;
float *pLeft = xLeft;
Int32 i;


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
    float output;
    float *p;


 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

  	CodecDataIn.UINT = ReadCodecData();		// get input data samples
	

    /********************Linear Buffer********************/
	xLeft[0]  = CodecDataIn.Channel[LEFT];	// current LEFT input value
	yLeft = 0;				// initialize the output value

	for (i = 0; i <= N; i++) {
		yLeft += xLeft[i]*B[i];		// perform the dot-product
	}
	
	for (i = N; i > 0; i--) {
		xLeft[i] = xLeft[i-1];		// shift for the next input
	}
	
	CodecDataOut.Channel[LEFT]  = yLeft;	// output the value	
	/*******************************************************/






	/********************Circular Buffer********************/
    /*
    *pLeft  = CodecDataIn.Channel[LEFT];    // store LEFT input value

    output = 0;                             // set up for LEFT channel
    p = pLeft;                              // save current sample pointer
    if(++pLeft > &xLeft[N])                 // update pointer, wrap if necessary
        pLeft = xLeft;                      // and store
    for (i = 0; i <= N; i++) {              // do LEFT channel FIR
            output += *p-- * B[i];          // multiply and accumulate
            if(p < &xLeft[0])               // check for pointer wrap around
                p = &xLeft[N];
    }

    CodecDataOut.Channel[LEFT]  = output; // store filtered value
    CodecDataOut.Channel[RIGHT] = output; // store filtered value
    */


	WriteCodecData(CodecDataOut.UINT);		// send output data to  port
}

