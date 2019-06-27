#ifndef __DRIVER_PROTOCOL_H
#define __DRIVER_PROTOCOL_H

#include "stm32f4xx.h"

#define Protocol_Buffer_Length 1000

#define Protocol_Data_Id_Client 0xD180
#define Protocol_Data_Id_Robot 0x0201 : case 0x0202 : case 0x0203 : case 0x0204 : case 0x0205 : case 0x0206 : case 0x0207

#define Protocol_Pack_Length_0001 3
#define Protocol_Pack_Length_0002 1
#define Protocol_Pack_Length_0003 2
#define Protocol_Pack_Length_0101 4
#define Protocol_Pack_Length_0102 3
#define Protocol_Pack_Length_0103 2
#define Protocol_Pack_Length_0201 15
#define Protocol_Pack_Length_0202 14
#define Protocol_Pack_Length_0203 16
#define Protocol_Pack_Length_0204 1
#define Protocol_Pack_Length_0205 3
#define Protocol_Pack_Length_0206 1
#define Protocol_Pack_Length_0207 6
#define Protocol_Pack_Length_0301_Header 6
#define Protocol_Pack_Length_0301_Client 13
#define Protocol_Pack_Length_0301_Robot 112
#define Protocol_Pack_Length_0401 9

#define PROTOCOL_HEADER 0xA5
#define PROTOCOL_HEADER_SIZE 5
#define PROTOCOL_CMD_SIZE 2
#define PROTOCOL_CRC16_SIZE 2
#define PROTOCOL_HEADER_CRC_LEN (PROTOCOL_HEADER_SIZE + PROTOCOL_CRC16_SIZE)
#define PROTOCOL_HEADER_CRC_CMDID_LEN (PROTOCOL_HEADER_SIZE + PROTOCOL_CRC16_SIZE + PROTOCOL_CMD_SIZE)
#define PROTOCOL_HEADER_CMDID_LEN (PROTOCOL_HEADER_SIZE + PROTOCOL_CMD_SIZE)

typedef union {
    uint8_t U[4];
    float   F;
    int     I;
} format_trans_t;

typedef struct {
    union {
        struct {
            uint8_t  robot_id;
            uint8_t  robot_level;
            uint16_t remain_HP;
            uint16_t max_HP;
            uint16_t shooter_heat0_cooling_rate;
            uint16_t shooter_heat0_cooling_limit;
            uint16_t shooter_heat1_cooling_rate;
            uint16_t shooter_heat1_cooling_limit;
            uint8_t  mains_power_gimbal_output : 1;
            uint8_t  mains_power_chassis_output : 1;
            uint8_t  mains_power_shooter_output : 1;
        };
        struct {
            uint8_t data[Protocol_Pack_Length_0201];
        };
    };
} ext_game_robot_state_t;

typedef struct {
    union {
        struct {
            uint16_t chassis_volt;
            uint16_t chassis_current;
            float    chassis_power;
            uint16_t chassis_power_buffer;
            uint16_t shooter_heat0;
            uint16_t shooter_heat1;
        };
        struct {
            uint8_t data[Protocol_Pack_Length_0202];
        };
    };
} ext_power_heat_data_t;

typedef struct {
    union {
        struct {
            uint8_t energy_point;
            uint8_t attack_time;
        };
        struct {
            uint8_t data[Protocol_Pack_Length_0205];
        };
    };
} aerial_robot_energy_t;

typedef struct {
    union {
        struct {
            uint8_t armor_id : 4;
            uint8_t hurt_type : 4;
        };
        struct {
            uint8_t data[Protocol_Pack_Length_0206];
        };
    };
} ext_robot_hurt_t;

typedef struct {
    union {
        struct {
            uint8_t bullet_type;
            uint8_t bullet_freq;
            float   bullet_speed;
        };
        struct {
            uint8_t data[Protocol_Pack_Length_0207];
        };
    };
} ext_shoot_data_t;

typedef struct {
    union {
        struct {
            float   yaw_angle_diff;
            float   pitch_angle_diff;
            uint8_t biu_biu_state;
        };
        struct {
            uint8_t data[Protocol_Pack_Length_0401];
        };
    };
} ext_gimal_aim_data_t;

typedef struct {
    union {
        struct {
            uint16_t data_cmd_id;
            uint16_t send_id;
            uint16_t receiver_id;
        };
        struct {
            uint8_t data[Protocol_Pack_Length_0301_Header];
        };
    };
} interactive_header_data_t;

typedef struct {
    union {
        struct {
            float   data1;
            float   data2;
            float   data3;
            uint8_t masks;
        };
        struct {
            uint8_t data[Protocol_Pack_Length_0301_Client];
        };
    };
} client_custom_data_t;

typedef struct {
    uint8_t data[Protocol_Pack_Length_0401];
} vision_interactive_data_t;

typedef struct {
    union {
        struct {
            format_trans_t transformer[Protocol_Pack_Length_0301_Robot / sizeof(float)];
        };
        struct {
            uint8_t data[Protocol_Pack_Length_0301_Robot];
        };
    };
    uint16_t length;
} robot_interactive_data_t;

typedef struct {
    uint8_t  sof;
    uint16_t data_length;
    uint8_t  seq;
    uint8_t  crc8;
} frame_header_t;

typedef enum {
    STEP_HEADER_SOF  = 0,
    STEP_LENGTH_LOW  = 1,
    STEP_LENGTH_HIGH = 2,
    STEP_FRAME_SEQ   = 3,
    STEP_HEADER_CRC8 = 4,
    STEP_DATA_CRC16  = 5,
} unpack_step_e;

typedef struct {
    uint8_t                   buf[Protocol_Buffer_Length];
    uint8_t                   packet[Protocol_Buffer_Length];
    uint8_t                   interact[Protocol_Buffer_Length];
    unpack_step_e             step;
    uint16_t                  index;
    uint16_t                  dataLength;
    uint16_t                  seq;
    uint16_t                  id;
    uint64_t                  lost;
    uint64_t                  received;
    ext_game_robot_state_t    robotState;
    ext_power_heat_data_t     powerHeatData;
    aerial_robot_energy_t     aerialRobotEnergy;
    ext_robot_hurt_t          robotHurt;
    ext_shoot_data_t          shootData;
    ext_gimal_aim_data_t      gimbalAimData;
    interactive_header_data_t interactiveHeaderData;
    client_custom_data_t      clientCustomData;
    vision_interactive_data_t visionInteractiveData;
    robot_interactive_data_t  robotInteractiveData[8];
} Protocol_Type;

unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength, unsigned char ucCRC8);
unsigned int  Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
void          Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
uint16_t      Get_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength, uint16_t wCRC);
uint32_t      Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
void          Append_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);

void Protocol_Init(Protocol_Type *Protocol);
void Protocol_Update(Protocol_Type *Protocol);
void Protocol_Unpack(Protocol_Type *Protocol, uint8_t byte);
void Protocol_Load(Protocol_Type *Protocol);
void Protocol_Pack(Protocol_Type *Protocol);

#endif
