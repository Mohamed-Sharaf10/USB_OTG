
#include "lin.h"

/*Private variables*/
static LinSlaveState 	slavesStates[LIN_CHANNEL_SIZE] ;

static LinFrameIdRef	linTxFrameIDs[LIN_CHANNEL_SIZE];

static LinFrameIdRef	linRxFrameIDs[LIN_CHANNEL_SIZE];
/*Public LIN interfaces*/
/*
 * !Description: Initialize LIN module
 * !Input_Parameter :
 * 						linConfig ==> Pointer to  Lin Configuration
 * 						contains : 	LIN TX and RX channels
 * 								 	LIN Baud Rate
 * 								 	LIN TX & RX frames IDs
 * */

Std_ReturnType lin_Init(const LinConfigType * linConfig)
{
	uint8 linChannelIndex  ;

	for(linChannelIndex = 0 ; linChannelIndex <LIN_CHANNEL_SIZE ; linChannelIndex++)
	{
		LinSlaveState[linChannelIndex] = IDLE ;
	}

}


/*
 * 	!Description:	Update function for LIN driver, used to update LIN state machine
 *
 */
void lin_main(void)
{

}

/*
 * 	!Description: 	This function used by upper layer [e.g LIN network management] to
 * 					change LIN mode [ Operational , Sleep , Wake-up]
 *
 * 	!Input_Parameter:
 * 					channel : LIN channel ID
 * 					mode	: Requested new mode
 * 	!Return:
 * 					Std_ReturnType: E_NOT_OK for the following cases
 * 											1- LIN channel is not initialized
 *
 * 									E_OK if transition was done successfully
 */

Std_ReturnType lin_RequestModeChange(LinChannel channelId , LinMode mode);
