// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2017

///////////////////////////////////////////////////////////////////////
// Filename: impulseModulatedQPSK_ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
#include "coeff.h"   // load the filter coefficients, B[n] ... extern
#include <stdlib.h>  // needed to call the rand() function
  
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
Int32 counter = 0;
#define QPSK_SCALE 160000
const Int32 samplesPerSymbol = 20;
const Int32 span = 6;
const Int32 cosine[4] = {1, 0, -1, 0};
const Int32 sine[4] = {0, 1, 0, -1};

const float QPSK_LUT[16][2] = {
// left (quadrature), right (in-phase)
{     -3 * QPSK_SCALE,  -3 * QPSK_SCALE}, /* QPSK_LUT[0]  */
{     -3 * QPSK_SCALE, -1 * QPSK_SCALE}, /* QPSK_LUT[1]  */
{    -3 * QPSK_SCALE,  3 * QPSK_SCALE}, /* QPSK_LUT[2]  */
{    -3 * QPSK_SCALE,  1 * QPSK_SCALE}, /* QPSK_LUT[3]  */
{    -1 * QPSK_SCALE, -3 * QPSK_SCALE}, /* QPSK_LUT[4]  */
{    -1 * QPSK_SCALE, -1 * QPSK_SCALE}, /* QPSK_LUT[5]  */
{    -1 * QPSK_SCALE,  3 * QPSK_SCALE}, /* QPSK_LUT[6]  */
{    -1 * QPSK_SCALE,  1 * QPSK_SCALE}, /* QPSK_LUT[7]  */
{     3 * QPSK_SCALE, -3 * QPSK_SCALE}, /* QPSK_LUT[8]  */
{     3 * QPSK_SCALE, -1 * QPSK_SCALE}, /* QPSK_LUT[9]  */
{     3 * QPSK_SCALE,  3 * QPSK_SCALE}, /* QPSK_LUT[10]  */
{     3 * QPSK_SCALE,  1 * QPSK_SCALE}, /* QPSK_LUT[11]  */
{     1 * QPSK_SCALE, -3 * QPSK_SCALE}, /* QPSK_LUT[12]  */
{     1 * QPSK_SCALE, -1 * QPSK_SCALE}, /* QPSK_LUT[13]  */
{     1 * QPSK_SCALE,  3 * QPSK_SCALE}, /* QPSK_LUT[14]  */
{     1 * QPSK_SCALE, -1 * QPSK_SCALE}, /* QPSK_LUT[15]  */
};

int SSRG_state = 6;
int SSRG_update(int *);

float output_gain = 1.0;
float xI[6];
float xQ[6];
float yI;
float yQ;
float output;


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
	Int32 symbol;
	Int32 i;

 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

  	CodecDataIn.UINT = ReadCodecData();		// get input data samples
	
	/* add your code starting here */

	// I added my impulse modulated QPSK routine here
	if (counter == 0) {
		symbol = SSRG_update(&SSRG_state); /* generate 2 random bits */
		symbol = (symbol << 1) + SSRG_update(&SSRG_state);

		symbol = rand() & 0xF;

		xI[0]  = QPSK_LUT[symbol][RIGHT];  
		xQ[0]  = QPSK_LUT[symbol][ LEFT];   
	}

	// perform impulse modulation based on the FIR filter, B[N]
	yI = 0;
	yQ = 0;

	for (i = 0; i < span; i++) {
		yI += xI[i]*B[counter + samplesPerSymbol*i];	// perform the "I" dot-product
		yQ += xQ[i]*B[counter + samplesPerSymbol*i];	// perform the "Q" dot-product
	}
    
	if (counter >= (samplesPerSymbol - 1)) {
		counter = -1; 

		/* shift xI[] and xQ[] in preparation to receive the next input */
		for (i = 5; i > 0; i--) {
			xI[i] = xI[i-1];  // setup xI[] for the next input value
			xQ[i] = xQ[i-1];  // setup xQ[] for the next input value
		}
	}

	counter++;

	output = output_gain*(yI*cosine[counter & 3] - yQ*sine[counter & 3]);
	
	CodecDataOut.Channel[LEFT]  = output_gain*yI; // setup the LEFT  value
	CodecDataOut.Channel[RIGHT] = output_gain*yQ; // setup the RIGHT value
	// end of my impulse modulated QPSK routine

	/* end your code here */

	WriteCodecData(CodecDataOut.UINT);		// send output data to  port
}

int SSRG_update(int * state) {
    //polynomial
    //ssrg size: 23
    //feedback: 18

    // compute feedback
    int fb23 = (*state)&1;
    int fb = ((*state >> 18)&1) ^ fb23;

    // shift state register
    *state = *state >> 1;

    // add feedback
    *state = (fb << 22) | *state;
    return fb23;
}
