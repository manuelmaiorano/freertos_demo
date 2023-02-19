#include <FreeRTOS.h>
#include <task.h>
#include <stm32f7xx_hal.h>
#include <Nucleo_F767ZI_Init.h>

#include <SEGGER_SYSVIEW.h>

//Create a typedef defining a simple function pointer
//to be used for LED's
typedef void (*GPIOFunc)(void);

//this struct holds function pointers to turn each LED
//on and off
typedef struct
{
	const GPIOFunc On;
	const GPIOFunc Off;
}LED;

void Task1(void *argument);

void GreenOn ( void ) {HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);}
void GreenOff ( void ) {HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);}

LED GreenLed = {GreenOn, GreenOff};

int main(void)
{
	// some common variables to use for each task
	// 128 * 4 = 512 bytes
	//(recommended min stack size per task)
	const static uint32_t stackSize = 128;
	HWInit();
    SEGGER_SYSVIEW_Conf();
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);	//ensure proper priority grouping for freeRTOS

	if (xTaskCreate(Task1, "task1", stackSize, NULL, tskIDLE_PRIORITY + 2, NULL) == pdPASS)
	{
				//start the scheduler - shouldn't return unless there's a problem
		vTaskStartScheduler();

	}

	//if you've wound up here, there is likely an issue with overrunning the freeRTOS heap
	while(1)
	{
	}
}

void Task1(void *argument)
{
  while(1)
  {
	  GreenLed.On();
	  vTaskDelay(105/ portTICK_PERIOD_MS);
	  GreenLed.Off();
	  vTaskDelay(100/ portTICK_PERIOD_MS);
  }
}