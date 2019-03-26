// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2017

///////////////////////////////////////////////////////////////////////
// Filename: ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
  
// Data is received as 2 16-bit words (left/right) packed into one
// 32-bit word.  The union allows the data to be accessed as a single 
// entity when transferring to and from the serial port, but still be 
// able to manipulate the left and right channels independently.

#define LEFT  0
#define RIGHT 1
#define A       32000
#define TAPS    5

volatile union {
	Uint32 UINT;
	Int16 Channel[2];
} CodecDataIn, CodecDataOut;


/* add any global variables here */
int SSRG_state = 1;

int state_list[101];

int SSRG_update(int *);

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
	float xLeft, xRight, yLeft, yRight;


 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

  	CodecDataIn.UINT = ReadCodecData();		// get input data samples
	
	/* add your code starting here */

	// this example simply copies sample data from in to out
  	/* TALK THROUGH
	xLeft  = CodecDataIn.Channel[ LEFT];
	xRight = CodecDataIn.Channel[ RIGHT];

	yLeft  = xLeft;
	yRight = xRight;
    */
  	static counter = 0;
  	if (counter <= 100) {
  	  state_list[counter] = SSRG_state;
  	  counter = counter + 1;
  	}

  	SSRG_update( &SSRG_state );

	CodecDataOut.Channel[ LEFT] = A * (( SSRG_state >> 4) & 1);
//	CodecDataOut.Channel[RIGHT] = yRight;

	/* end your code here */

	WriteCodecData(CodecDataOut.UINT);		// send output data to  port

}

int SSRG_update(int * state) {
    // compute feedback
    int fb5 = (*state)&1 ^ 1;
    int fb = ((*state >> 3)&1) ^ fb5;

    // shift state register
    *state = *state >> 1;

    // add feedback
    *state = (fb << 4) | *state;
    return fb;
}
