#include "lin.h"


LinFrameId		rxFrameIDs[2] = {0x22 ,0x33} ;
LinFrameId		txFrameIDs[1] = {0x55} ;
LinConfigType	LinConfigArray[LIN_CHANNEL_SIZE] =
{
		LIN_CHANNEL_1 , /*Channel ID 1 */
		rxFrameIDs,
		2,
		txFrameIDs,
		1,
		20000 /*Bit rate*/

};
