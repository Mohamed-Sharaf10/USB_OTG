#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H


/*==================[inclusions]=============================================*/
#include <stdint.h>

/*==================[macros]=================================================*/

#if (!defined TRUE)
#define TRUE 1U
#endif

/* !LINKSTO PLATFORM054,1 */
#if (!defined FALSE)
#define FALSE 0U
#endif

/*==================[type definitions]======================================*/

typedef unsigned char boolean;

typedef signed char sint8;

typedef signed short sint16;

typedef signed long sint32;

typedef uint8_t uint8;

typedef uint16_t uint16;

typedef uint32_t uint32;

typedef signed char sint8_least;

typedef unsigned char uint8_least;

typedef signed short sint16_least;

typedef unsigned short uint16_least;

typedef signed long sint32_least;

typedef unsigned long uint32_least;

typedef float float32;

typedef double float64;


#endif
