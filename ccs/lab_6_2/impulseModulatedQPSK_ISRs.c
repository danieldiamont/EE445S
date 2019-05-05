// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2017

///////////////////////////////////////////////////////////////////////
// Filename: impulseModulatedQPSK_ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
#include "pulse.h"   // load the filter coefficients, B[n] ... extern
#include "sos.h"
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
Int32 carrier_index = 0;

#define QPSK_SCALE 16000
const Int32 samplesPerSymbol = 20;
const Int32 span = 4;

#define SQRT_3_DIV_2 0.866025403784438
const float cosine[6] = {1.0, 1.0/2.0, -1.0/2.0, -1.0, -1.0/2.0, 1.0/2.0};
const float sine[6] = {0, SQRT_3_DIV_2, SQRT_3_DIV_2, 0, -SQRT_3_DIV_2, -SQRT_3_DIV_2};

const float QPSK_LUT[4][2] = {
// left (quadrature), right (in-phase)
{     1 * QPSK_SCALE,  1 * QPSK_SCALE}, /* QPSK_LUT[0]  */
{     1 * QPSK_SCALE, -1 * QPSK_SCALE}, /* QPSK_LUT[1]  */
{    -1 * QPSK_SCALE,  1 * QPSK_SCALE}, /* QPSK_LUT[2]  */
{    -1 * QPSK_SCALE, -1 * QPSK_SCALE}, /* QPSK_LUT[3]  */
};

int SSRG_state = 6;
int SSRG_update(int *);

//biquad
float biquad_x_inphase[SOS_SIZE][N+1] = {0};   // input value (buffered)
float biquad_y_inphase[SOS_SIZE][N+1] = {0};   // output values (buffered)

float biquad_x_quad[SOS_SIZE][N+1] = {0};   // input value (buffered)
float biquad_y_quad[SOS_SIZE][N+1] = {0};   // output values (buffered)

float biquad_inphase(int, float);
float biquad_quadrature(int, float);

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

		xI[0]  = QPSK_LUT[symbol][RIGHT];  
		xQ[0]  = QPSK_LUT[symbol][ LEFT];   
	}

	// perform impulse modulation based on the FIR filter, B[N]
	yI = 0;
	yQ = 0;

	for (i = 0; i < span; i++) {
		yI += xI[i]*pulse[counter + samplesPerSymbol*i];	// perform the "I" dot-product
		yQ += xQ[i]*pulse[counter + samplesPerSymbol*i];	// perform the "Q" dot-product
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
	carrier_index = (carrier_index + 1) % 6;

	output = output_gain*(yI*cosine[carrier_index] - yQ*sine[carrier_index]);
	// end of my impulse modulated QPSK routine

	/* end your demod code here */
	//demodulate in-phase and quadrature
    float demod_inphase = 2*output*cosine[carrier_index];
    float demod_quad = -2*output*sine[carrier_index];

    //LPF
    biquad_x_inphase[0][0] = demod_inphase;
    biquad_x_quad[0][0] = demod_quad;

    float output_inphase = G[0] * biquad_inphase(0, biquad_x_inphase[0][0]);
    float output_quad = G[0] * biquad_quadrature(0, biquad_x_quad[0][0]);

    CodecDataOut.Channel[LEFT]  = output_quad; // setup the LEFT  value
    CodecDataOut.Channel[RIGHT] = yQ; // setup the RIGHT value
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

float biquad_inphase(int index, float value)
{
    biquad_x_inphase[index][0] = value;

    float ret_val = SOS[index][0]*biquad_x_inphase[index][0] + SOS[index][1]*biquad_x_inphase[index][1] + SOS[index][2]*biquad_x_inphase[index][2] +
                    SOS[index][3]*biquad_y_inphase[index][1] + SOS[index][4]*biquad_y_inphase[index][2];

    biquad_y_inphase[index][0] = ret_val;

    biquad_x_inphase[index][2] = biquad_x_inphase[index][1];
    biquad_x_inphase[index][1] = biquad_x_inphase[index][0];

    biquad_y_inphase[index][2] = biquad_y_inphase[index][1];
    biquad_y_inphase[index][1] = biquad_y_inphase[index][0];

    return ret_val;
}

float biquad_quadrature(int index, float value)
{
    biquad_x_quad[index][0] = value;

    float ret_val = SOS[index][0]*biquad_x_quad[index][0] + SOS[index][1]*biquad_x_quad[index][1] + SOS[index][2]*biquad_x_quad[index][2] +
                    SOS[index][3]*biquad_y_quad[index][1] + SOS[index][4]*biquad_y_quad[index][2];

    biquad_y_quad[index][0] = ret_val;

    biquad_x_quad[index][2] = biquad_x_quad[index][1];
    biquad_x_quad[index][1] = biquad_x_quad[index][0];

    biquad_y_quad[index][2] = biquad_y_quad[index][1];
    biquad_y_quad[index][1] = biquad_y_quad[index][0];

    return ret_val;
}
