/**
 * @brief 硬件初始化
 * @note 该函数应该在task.c中被执行
 */

#include "bsp.h"
#include "handle.h"

void BSP_Init(void) {
    BSP_CAN_Init();
    BSP_DBUS_Init(remoteBuffer);
    BSP_TIM2_Init();
    BSP_IMU_Init();
    BSP_Laser_Init();
    BSP_Beep_Init();
    BSP_LED_Init();
    BSP_User_Power_Init();

    // USART
    // BSP_USART2_Init(9600, USART_IT_RXNE);

    // Judge (USART6)
    BSP_USART6_Init(115200, USART_IT_IDLE);
    BSP_DMA_Init(USART6_Tx, JudgeChannel.sendBuf, Protocol_Buffer_Length);
    BSP_DMA_Init(USART6_Rx, JudgeChannel.receiveBuf, Protocol_Buffer_Length);

    // // Board (UART7)
    // BSP_UART7_Init(115200, USART_IT_IDLE);
    // BSP_DMA_Init(UART7_Tx, UserChannel.sendBuf, Protocol_Buffer_Length);
    // BSP_DMA_Init(UART7_Rx, UserChannel.receiveBuf, Protocol_Buffer_Length);

    //  PS (UART8)
    BSP_UART8_Init(115200, USART_IT_IDLE);
    BSP_DMA_Init(UART8_Tx, HostChannel.sendBuf, Protocol_Buffer_Length);
    BSP_DMA_Init(UART8_Rx, HostChannel.receiveBuf, Protocol_Buffer_Length);

    //微动开关
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}