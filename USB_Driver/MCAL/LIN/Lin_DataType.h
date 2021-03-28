

#ifndef _LIN_DATA_TYPE_H
#define _LIN_DATA_TYPE_H

#include "std.h"


/* Public data types */

/*
 * !Description: LIN Channel ID
 * !Range: mc dependent
 */
typedef uint8	LinChannel ;

/*
 * !Description: LIN data size
 * !Range: 1 to 8 bytes
 */

typedef uint8	LinDataSize;

/*
 * !Description: LIN data
 * !Range: 0 to 255
 */

typedef uint8	LinData ;

/*
 * !Description: LIN checksum data
 * !Range: 0 to 255
 */

typedef uint8	LinChecksum ;

/*
 * !Description: LIN frame ID
 * !Range: 0 to 59 [ For Signal carrying frames ]
 *         60 and 61 [For Diagnostic frames ]
 */

typedef uint8 LinFrameId ;


typedef LinFrameId * LinFrameIdRef ;


typedef uint16 LinBitRate ;

/*
 * !Description: struct define LIN response
 * 				contains==>
 * 							Size of data that will be sent
 * 							Array of data that will be sent
 * 							Checksum byte
 */

typedef struct{

	LinDataSize		size ;
	LinData			*linData; /*Array of data that will be sent*/
	LinChecksum		checksum ;

}LinFrameResponse;


typedef struct {

	LinChannel 		channelId ;
	LinFrameIdRef	rxFrameIDs; /*Array of RX frame IDs*/
	uint8			rxFrameIDsSize ; /*Size of rxFrameIDs array*/
	LinFrameIdRef	txFrameIDs; /*Array of TX frame IDs*/
	uint8			txFrameIDsSize ; /*Size of txFrameIDs array*/
	LinBitRate		bitrate;

}LinConfigType;


typedef enum{IDLE , RECEIVE_PID , RECEIVE_DATA ,
			RECEIVE_CHECKSUM , TRANSMIT_DATA , TRANSMIT_CHECKSUM}LinSlaveState;

#endif
