#include "click/robot_arm_server.h"

#define ROBOT_ARM_ADDRESS       (0x40)
#define LED_ON_LOW              (0x06)
#define LED_ON_HIGH             (0x07)

/* Used for movement of the servo */
#define LED_OFF_LOW             (0x08)
#define LED_OFF_HIGH            (0x09)

#define MODE_REGISTER           (0x00)
#define PRESCALE_REGISTER       (0xfe)
#define RESTART                 (0x81)

void server_switch_close_claws(void){
    usleep(10000);
    server_move_servo(100, CLAWS);
    usleep(10000);
}

void server_switch_open_claws(void){
    usleep(10000);
    server_move_servo(0, CLAWS);
    usleep(10000);
}

int server_robot_arm_init(void){
    i2c_init();
    i2c_select_bus(ROBOT_ARM);

    uint8_t buffer[2];
    buffer[0] = MODE_REGISTER;
    buffer[1] = 0x11;
    i2c_write(ROBOT_ARM_ADDRESS, buffer, sizeof(buffer));
        
    buffer[0] = PRESCALE_REGISTER;
    buffer[1] = 121;
    i2c_write(ROBOT_ARM_ADDRESS, buffer, sizeof(buffer));
        
    buffer[0] = MODE_REGISTER;
    buffer[1] = 0x01;
    i2c_write(ROBOT_ARM_ADDRESS, buffer, sizeof(buffer));
        
    buffer[0] = MODE_REGISTER;
    buffer[1] = RESTART;
    i2c_write(ROBOT_ARM_ADDRESS, buffer, sizeof(buffer));

    return 0;
}

int server_move_servo(float angle, uint8_t channel){
    /* Converts the angle entered by the user into the range of register values that can be written to the servo */
    uint16_t rotationValue = (uint16_t) ((angle / 180.f) * (MAX_ROTATION - MIN_ROTATION) + MIN_ROTATION);
    uint8_t buffer[2] = {0};
    
    /* Each channel has 4 registers, hence addressing the register of the 1st channel + 4 will access the equivalent register of the 2nd channel */
    buffer[0] = LED_ON_LOW + (4 * channel);
    buffer[1] = 0x00;
    i2c_write(ROBOT_ARM_ADDRESS, buffer, sizeof(buffer));
    buffer[0] = LED_ON_HIGH + (4 * channel);
    buffer[1] = 0x00;
    i2c_write(ROBOT_ARM_ADDRESS, buffer, sizeof(buffer));
        
    /* The registers are 8 bits while the data to be written is 16 bits, hence 2 write transactions are needed */
    buffer[0] = LED_OFF_LOW + (4 * channel);
    buffer[1] = rotationValue;
    i2c_write(ROBOT_ARM_ADDRESS, buffer, sizeof(buffer));
    buffer[0] = LED_OFF_HIGH + (4 * channel);
    buffer[1] = (rotationValue >> 8);
    i2c_write(ROBOT_ARM_ADDRESS, buffer, sizeof(buffer));
     
    return 0;
}
