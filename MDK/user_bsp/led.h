#ifndef __LED_H
#define __LED_H
#include "main.h"
typedef enum
{
	Car_NCON,
	Car_CON,
	Car_Issue,
}Car_state;
typedef enum
{
	CT_internet,
	NCT_internet,
}INT_State;
typedef enum
{
	Plugged_ncharged,
	charging,
	compete,
}Carcon_state;
typedef enum
{
    FAULT_EMERGENCY_STOP,               /* 急停故障 常亮 */
    FAULT_UNDER_VOLTAGE,                /* 欠压故障 闪1次*/
    FAULT_OVER_VOLTAGE,                 /* 过压故障 闪2次*/
    FAULT_LEAKAGE,                      /* 漏电故障 闪3次*/
    FAULT_RESERVED_NETWORK,             /* 预留网络异常 闪4次*/
    FAULT_CARD_READER_COMM,             /* 刷卡板通讯异常 闪5次*/
    FAULT_OVER_CURRENT,                 /* 过流故障 闪6次*/
    FAULT_LOW_CURRENT,                  /* 低电流 闪7次*/
    FAULT_OVER_TEMPERATURE,             /* 过温故障 闪8次*/
    FAULT_VEHICLE_S2_SWITCH,            /* 汽车 S2 开关异常 闪9次*/
    FAULT_RELAY_WELDED,                 /* 继电器粘连故障 闪10次*/
    FAULT_GUN_SHORT_CIRCUIT,            /* 枪短路故障 闪12次*/
    FAULT_DIODE_MISSING,                /* 二极管不存在 闪13次*/
    FAULT_GROUND,                       /* 接地故障 闪11次*/
}FaultCode_t;
extern FaultCode_t Charging_issue;
extern Car_state car_state;
extern INT_State int_state;
extern Carcon_state carcon_state;
#define Blue_port GPIO_PORT_B
#define Blue_pin GPIO_PIN_04
#define Red_port GPIO_PORT_B
#define Red_pin GPIO_PIN_03
#define Green_port GPIO_PORT_D
#define Green_pin GPIO_PIN_07
#define blue_on() GPIO_SetPins(Blue_port,Blue_pin)
#define blue_off() GPIO_ResetPins(Blue_port,Blue_pin)
#define Red_on() GPIO_SetPins(Red_port,Red_pin)
#define Red_off() GPIO_ResetPins(Red_port,Red_pin)
#define Green_on() GPIO_SetPins(Green_port,Green_pin)
#define Green_off() GPIO_ResetPins(Green_port,Green_pin)
#define Alternat_flashtime 300
extern uint32_t nowtime;
extern uint32_t nowtime_red;
void led_Init(uint8_t u8Port, uint16_t u16Pin);
void led_slowflash(uint8_t u8Port, uint16_t u16Pin);
void led_greenblue(void);
void red_Flicker(uint8_t num);
void led_Language(void);
#endif
