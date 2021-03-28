#ifndef _PORT_H
#define _PORT_H

#include "port_Cfg.h"
#include "mcu_driver.h"
#include "std.h"
/* Microcontroller dependent */
/*
 * Name: Port_PinType
 * Type: uint
 * Range: 0 - <number of port pins:>
 * Shall cover all available port pins.
 * The type should be chosen for the specific MCU platform (best performance).
 * Description: Data type for the symbolic name of a port pin.
 */
typedef uint8  Port_PinType ;

/*
 * Name: Port_PinDirectionType
 * Type: Enumeration
 * Range: PORT_PIN_IN -- Sets port pin as input.
 * 		  PORT_PIN_OUT-- Sets port pin as output.
 * Description: Possible directions of a port pin.
 */

/*Port direction values */
#define PORT_PIN_IN			(0x00U)
#define PORT_PIN_OUT		(0x01U)
#define PORT_PIN_AF_IN		(0x02U)
#define PORT_PIN_AF_OUT		(0x02U)

/*Port Direction data type*/
typedef uint8 Port_PinDirectionType;



typedef enum {PORT_LOW , PORT_HIGH} Port_PinInitValType ;

typedef enum {PUSH_PULL , OPEN_DRAIN,OUT_NOT_ACTIVE} Port_PinOutputModeType;

typedef enum {PUPD_OFF= 0x00U ,PU_ON=0x01 , PD_ON=0x10 } Port_PinPUPDActivationType;

//typedef enum {FLOATING = 0x00U , PULL_UP=0x01 , PULL_DOWN=0x10  } Port_PinInputModeType ;

typedef uint8  Port_PinModeType ;

/*Alternative Functions for STM32F429*/
#define PORT_MODE_AF0	   (0X00U)
#define PORT_MODE_AF1	   (0X01U)
#define PORT_MODE_AF2	   (0X02U)
#define PORT_MODE_AF3	   (0X03U)
#define PORT_MODE_AF4	   (0X04U)
#define PORT_MODE_AF5	   (0X05U)
#define PORT_MODE_AF6	   (0X06U)
#define PORT_MODE_AF7	   (0X07U)
#define PORT_MODE_AF8	   (0X08U)
#define PORT_MODE_AF9	   (0X09U)
#define PORT_MODE_AF10	   (0X0AU)
#define PORT_MODE_AF11	   (0X0BU)
#define PORT_MODE_AF12	   (0X0CU)
#define PORT_MODE_AF13	   (0X0DU)
#define PORT_MODE_AF14	   (0X0EU)
#define PORT_MODE_AF15	   (0X0FU)
#define PORT_MODE_GPIO     (0x10U)

/*Alternative Functions names */
#define PORT_MODE_USB_FS	PORT_MODE_AF12

/* Data structure defines the Configuration necessary for Interrupt/Event pin */
typedef enum {PORT_RISING_EDGE , PORT_FAILING_EDGE , PORT_RISING_FAILING_EDGE ,PORT_SW_TRIGERRING}Port_DetectionType ;

typedef enum {PORT_INTERRUPT_MODE , PORT_EVENT_MODE , PORT_INTERRUPT_EVENT_MODE}Port_InterruptEventType;

typedef struct {
	Port_DetectionType  		detectionType;
	Port_InterruptEventType		interruptEventSel ;
}Port_PinIntEvent_Type;
/* Data structure define configuration for each pin*/
typedef struct {
	/*TODO: Implement structure*/
	Port_PinType				pinName ; /* Symbolic name for port pin*/
	Port_PinModeType 			pinMode; /*whether it will be [ CAN ,DIO ,GPT ,ICU ,..]*/
	Port_PinDirectionType 		pinDirection; /*Direction of the pin [PORT_PIN_IN , PORT_PIN_OUT]*/
	Port_PinInitValType			pinInitValue; /*Port pin initial value*/
	Port_PinOutputModeType		pinOutputMode ; /*Type of output pin*/
	Port_PinPUPDActivationType 	pinPuPdActivation;/*Activation of Pull-up or Pull-down resistor*/
	/* Further parameters [ Locking , Speed , ..]*/
//	Port_PinIntEvent_Type		pinInterruptEventConfig; /*Configuration of interrupt/event external pin */
}Port_PinConfigType;

/* Data structure define configuration for each port*/

typedef struct {
	const Port_PinConfigType * pinConfig; /*Reference to pin configurations*/
	Port_PinType portPinNum ; /*Number of port pins*/
}Port_Type;

typedef struct {
	const Port_Type * portCofig ; /*Reference to port configurations*/
	Port_PinType portNum ; /*Number of ports*/
}Port_ConfigType;


extern Port_ConfigType portConfig ;
/*
 * Service name: Port_Init
 * Syntax: void Port_Init( const Port_ConfigType* ConfigPtr )
 * Service ID[hex]:0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in):  ConfigPtr  Pointer to configuration set.
 * Parameters (inout):  None
 * Parameters (out): None
 * Return value: None
 * Description:  Initializes the Port Driver module.
 */
void Port_Init( const Port_ConfigType* ConfigPtr );

#endif
