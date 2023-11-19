#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include "core_cm4.h"

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
    while(1)
    {

    }
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler_C(unsigned long * hardfault_args, unsigned int lr_value)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  unsigned long stacked_r0;
  unsigned long stacked_r1;
  unsigned long stacked_r2;
  unsigned long stacked_r3;
  unsigned long stacked_r12;
  unsigned long stacked_lr;
  unsigned long stacked_pc;
  unsigned long stacked_psr;
  unsigned long cfsr;
  unsigned long bus_fault_address;
  unsigned long memmanage_fault_address;

  bus_fault_address       = SCB->BFAR;
  memmanage_fault_address = SCB->MMFAR;
  cfsr                    = SCB->CFSR;

  stacked_r0  = ((unsigned long) hardfault_args[0]);
  stacked_r1  = ((unsigned long) hardfault_args[1]);
  stacked_r2  = ((unsigned long) hardfault_args[2]);
  stacked_r3  = ((unsigned long) hardfault_args[3]);
  stacked_r12 = ((unsigned long) hardfault_args[4]);
  stacked_lr  = ((unsigned long) hardfault_args[5]);
  stacked_pc  = ((unsigned long) hardfault_args[6]);
  stacked_psr = ((unsigned long) hardfault_args[7]);
}

// HardFault handler wrapper in assembly language.
// It extracts the location of stack frame and passes it to the handler written
// in C as a pointer. We also extract the LR value as second parameter.
void HardFault_Handler(void) __attribute__((naked));
void HardFault_Handler(void) {
    __asm__(
        "TST LR, #4\n"
        "ITE EQ\n"
        "MRSEQ R0, MSP\n"
        "MRSNE R0, PSP\n"
        "MOV R1, LR\n"
        "B HardFault_Handler_C\n"
    );
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//    LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_0);
//}


void MemManage_Handler(void)
{
    //Check the MMFAR register to get more information about the fault
    while(1)
    {

    }
    return;
}

void BusFault_Handler(void)
{
    //Check the CFSR register to get more information about the fault
    while(1)
    {

    }
    return;
}

void UsageFault_Handler(void)
{
    //Check the CFSR register to get more information about the fault

    while(1)
    {

    }

    return;
}