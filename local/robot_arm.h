#ifndef __LETMECREATE_CLICK_ROBOT_ARM_H__
#define __LETMECREATE_CLICK_ROBOT_ARM_H__

#define MIN_ROTATION                  (111)
#define MAX_ROTATION                  (502)

#define LEFT_RIGHT                    0
#define FORWARD_BACKWARD              4
#define UP_DOWN                       8
#define CLAWS                         12

#define ROBOT_ARM                     MIKROBUS_1
#define JOYSTICK                      MIKROBUS_2

#include <stdio.h>
#include <unistd.h>
#include "letmecreate/letmecreate.h"

/* Initialises writing to i2c and writes to the mode and prescale registers to allow for servo movement */
int robot_arm_init(void);

/* Initialises the switches on the board */
int switches_init(void);

/* converts the entered angle into the values to be written to the registers and writes to the registers */
int move_servo(float angle, uint8_t channel);

/* Run when the switches on the board are pressed */
void switch_close_claws(void);
void switch_open_claws(void);

/* Converts the value reported from the joystick to be in degrees */
float convert_to_angle(int x, uint8_t servo);

#endif
