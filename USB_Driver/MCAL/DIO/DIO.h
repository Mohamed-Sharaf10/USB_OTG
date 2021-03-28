#include "std.h"
#include "mcu_driver.h"
#include "DIO_Cfg.h"
typedef uint8	Dio_ChannelType;

typedef uint8	Dio_LevelType;

void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level );

Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId );

