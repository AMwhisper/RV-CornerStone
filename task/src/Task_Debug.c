/**
 * @brief 调试任务
 */

#include "main.h"

extern volatile uint32_t ulHighFrequencyTimerTicks;
int                      taskDebug_Sign = 0;

void Task_RTOSState(void *Parameters) {
    while (1) {
        u8 pcWriteBuffer[1000];
        printf("=========================\r\n");
        printf("time:    %d\r\n", ulHighFrequencyTimerTicks);
        if (taskDebug_Sign) {
            printf("\r\nName            Count              Usage\r\n");
            vTaskGetRunTimeStats((char *) &pcWriteBuffer);
            printf("%s\r\n", pcWriteBuffer);
        } else {
            printf("Name         Status   Priority  RemainStackSize   Number\r\n");
            vTaskList((char *) &pcWriteBuffer);
            printf("%s\r\n", pcWriteBuffer);
        }
        taskDebug_Sign = taskDebug_Sign ? 0 : 1;

        printf("=========================\r\n\r\n\r\n");
        vTaskDelay(5000);
    }
    vTaskDelete(NULL);
}

void Task_MagicReceive(void *Parameters) {
    TickType_t LastWakeTime = xTaskGetTickCount();

    Magic_Init_Handle(&magic, 0); // 初始化调试数据的默认值
    while (1) {
        taskENTER_CRITICAL();          // 进入临界段
        Magic_Get_Debug_Value(&magic); // 接收调试数据
        taskEXIT_CRITICAL();           // 退出临界段
        vTaskDelayUntil(&LastWakeTime, 50);
    }
    vTaskDelete(NULL);
}

void Task_MagicSend(void *Parameters) {
    TickType_t LastWakeTime = xTaskGetTickCount();

    while (1) {
        taskENTER_CRITICAL(); // 进入临界段
        printf("Yaw: %f\r\n", EulerAngle.Yaw);
        taskEXIT_CRITICAL(); // 退出临界段
        vTaskDelayUntil(&LastWakeTime, 500);
    }
    vTaskDelete(NULL);
}