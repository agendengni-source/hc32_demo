#include "led.h"
#include "delay.h"
uint32_t nowtime=0;
uint32_t nowtime_red=0;
volatile uint8_t i=0;
FaultCode_t Charging_issue;
Car_state car_state;
INT_State int_state;
Carcon_state carcon_state;
void led_Init(uint8_t u8Port, uint16_t u16Pin)
{
	//LL_PERIPH_WE(LL_PERIPH_GPIO);
	stc_gpio_init_t stcGPIOInit;
	GPIO_StructInit(&stcGPIOInit);
	stcGPIOInit.u16PinOutputType=PIN_OUT_TYPE_CMOS;
	stcGPIOInit.u16PinState=PIN_STAT_RST;
	stcGPIOInit.u16PinDir=PIN_DIR_OUT;
	stcGPIOInit.u16PinDrv=PIN_HIGH_DRV;
	stcGPIOInit.u16PinAttr=PIN_ATTR_DIGITAL;
	GPIO_Init(u8Port,u16Pin,&stcGPIOInit);
//	LL_PERIPH_WP(LL_PERIPH_GPIO);
}
void led_slowflash(uint8_t u8Port, uint16_t u16Pin)
{
	if(led_slowtime[0]>=led_slowtime[1])
	{
		GPIO_TogglePins(u8Port,u16Pin);
		led_slowtime[0]=0;
	}
}
void led_greenblue(void)
{
	if(SysTick_GetTick()-nowtime>Alternat_flashtime)
	{
	en_pin_state_t led_flag=GPIO_ReadInputPins(Green_port,Green_pin);
	if(led_flag==SET)
	{
		Green_off();
		blue_on();
	}
	else
	{
		blue_off();
		Green_on();
	}
	nowtime=SysTick_GetTick();
}
}
void red_Flicker(uint8_t num)
{
	uint32_t now = SysTick_GetTick();

    if (num == 0 || num > 13)
        return;

    /* 已经闪完一组：保持灭灯，等待2秒 */
    if (i >= 2 * num)
    {
        if (now - nowtime_red < 2000)
            return;

        i = 0;  // 等待结束，允许开始下一组
    }

		if(now-nowtime_red>=Alternat_flashtime)
		{
			i++;
			GPIO_TogglePins(Red_port,Red_pin);
			nowtime_red=now;
		}
}
static void stop_char()
{
	switch(Charging_issue)
	{
		case FAULT_EMERGENCY_STOP:
			Red_on();
		break;
			case FAULT_UNDER_VOLTAGE:
				red_Flicker(1);
			break;
			case FAULT_OVER_VOLTAGE:
				red_Flicker(2);
			break;
			case FAULT_LEAKAGE:
				red_Flicker(3);
			break;
			case FAULT_RESERVED_NETWORK:
				red_Flicker(4);
			break;
			case FAULT_CARD_READER_COMM:
				red_Flicker(5);
			break;
			case FAULT_OVER_CURRENT:
				red_Flicker(6);
			break;
			case FAULT_LOW_CURRENT:
				red_Flicker(7);
			break;
			case FAULT_OVER_TEMPERATURE:
				red_Flicker(8);
			break;
			case FAULT_VEHICLE_S2_SWITCH:
				red_Flicker(9);
			break;
			case FAULT_RELAY_WELDED:
				red_Flicker(10);
			break;
			case FAULT_GUN_SHORT_CIRCUIT:
				red_Flicker(12);
			break;
			case FAULT_DIODE_MISSING:
				red_Flicker(13);
			break;
			case FAULT_GROUND:
				red_Flicker(11);
			break;
			default:
				break;
	}
}
static void no_char(void)
{
	switch(int_state)
	{
			case CT_internet:
				led_slowflash(Blue_port,Blue_pin);
				break;
			case NCT_internet:
				blue_on();
				break;
			default:
				break;
	}
}
static void carcon(void)
{
	switch(carcon_state)
	{
		case Plugged_ncharged:
			blue_off();
			Green_on();
			break;
			case charging:
				led_greenblue();
			break;
				case compete:
					blue_off(); 
					Green_on();
			break;
				default:
					break;
	}
}
void led_Language(void)
{
	 static Car_state last_car = Car_NCON;
   static FaultCode_t last_fault = FAULT_EMERGENCY_STOP;
	    if (car_state != last_car ||
        (car_state == Car_Issue && Charging_issue != last_fault))
    {
        Red_off();                         // 从灭灯开始
        i = 0;                             // 清除旧故障的次数
        nowtime_red = SysTick_GetTick();    // 重新开始计时
    }
		 last_car = car_state;
    last_fault = Charging_issue;
	switch(car_state)
	{
		case Car_NCON:
				Red_off(); 
		Green_off();
			no_char();
			break;
		case Car_CON:
			Red_off();
			carcon();
			break;
		case Car_Issue:
			blue_off();
		Green_off();
			 stop_char();
			break;
		default:
			break;
	}
}


