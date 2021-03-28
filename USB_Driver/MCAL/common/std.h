#ifndef _STD_H_
#define _STD_H_
#include "Platform_Types.h"
#include "mcu_driver.h"
// Standard Return Type
typedef enum{E_OK , E_NOT_OK} Std_ReturnType;
#define PRIVATE static
#define STD_ON  0x01u
#define STD_OFF 0x00u

#define STD_LOW		0x00u
#define STD_HIGH	0x01u
#endif
