#ifndef _LIN_UPPER_CBK_H
#define _LIN_UPPER_CBK_H
#include "std.h"
/*
 * 	!Description:	Request from the upper layer to transmit response
 * 					corresponding to frameId
 *  !Input_Parameter:
 *  				frameId==> ID for the TX Frame
 */
Std_ReturnType lin_RequestTxFrame(LinFrameId frameId ,LinFrameResponse *frameData);
/*
 * 	!Description:	Request from the upper layer to transmit response
 * 					corresponding to frameId
 *  !Input_Parameter:
 *  				frameId==> ID for the TX Frame
 */

Std_ReturnType lin_ReceiveRxFrame(LinFrameId frameId ,const LinFrameResponse *frameData);
#endif
