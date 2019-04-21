#ifndef __HANDLE_H
#define __HANDLE_H

#include "sys.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "rtos.h"
#include "Driver_Filter.h"
#include "Driver_Magic.h"
#include "Driver_PID.h"
#include "Driver_DBUS.h"
#include "Driver_CAN.h"
#include "Driver_Motor.h"
#include "Driver_Chassis.h"
#include "Driver_Gyroscope.h"
#include "Driver_Ps.h"
#include "mpu6500_driver.h"
#include "Driver_Judge.h"

#ifdef __HANDLE_GLOBALS
#define __HANDLE_EXT
#else
#define __HANDLE_EXT extern
#endif

// TIM
__HANDLE_EXT volatile uint32_t ulHighFrequencyTimerTicks;

// 电机
__HANDLE_EXT Motor_Type Motor_LF, Motor_RF, Motor_RB, Motor_LB;

//云台
__HANDLE_EXT Motor_Type Motor_Yaw, Motor_Pitch;
__HANDLE_EXT PID_Type PID_Cloud_YawAngle, PID_Cloud_YawSpeed, PID_Cloud_PitchAngle, PID_Cloud_PitchSpeed;
__HANDLE_EXT PID_Type PID_Follow_Angle, PID_Follow_Speed;

// 遥控器
__HANDLE_EXT uint8_t remoteBuffer[DBUS_LENGTH + DBUS_BACK_LENGTH];
__HANDLE_EXT DBusData_Type remoteData;

// 陀螺仪
__HANDLE_EXT volatile GyroscopeData_Type Gyroscope_EulerData;

// 无线串口调试
__HANDLE_EXT MagicHandle_Type magic;

// 底盘
__HANDLE_EXT ChassisData_Type ChassisData;
__HANDLE_EXT PID_Type PID_LFCM, PID_LBCM, PID_RBCM, PID_RFCM, PID_YawAngle, PID_YawSpeed, PID_Power;

// Debug陀螺仪用
__HANDLE_EXT int debugA, debugB, debugC, debugD, debugE, debugF, debugG, debugH;

//裁判系统
__HANDLE_EXT Judge_Type Judge;

//功率
__HANDLE_EXT float powerfeed;

// 视觉数据
__HANDLE_EXT PsData_Type PsData;

//发射机构
__HANDLE_EXT Motor_Type Motor_LeftFrict, Motor_RightFrict, Motor_Stir; // 左/右 摩擦轮 拨弹轮 电机
__HANDLE_EXT PID_Type PID_LeftFrictSpeed, PID_RightFrictSpeed;         // 左/右 摩擦轮 PID
__HANDLE_EXT PID_Type PID_StirSpeed, PID_StirAnlge;                    // 拨弹轮 速度/角度 PID

/**
 * @brief 初始化结构体
 * @note 该函数将在所有硬件及任务初始化之前执行
 */
void Handle_Init(void);

#endif