#ifndef __LETMECREATE_CLICK_ROBOT_ARM_H__
#define __LETMECREATE_CLICK_ROBOT_ARM_H__

#define MIN_ROTATION                  (111)
#define MAX_ROTATION                  (502)

#define LEFT_RIGHT                    0
#define FORWARD_BACKWARD              4
#define UP_DOWN                       8
#define CLAWS                         12

#define ROBOT_ARM                     MIKROBUS_1

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "letmecreate/letmecreate.h"

/* Initialises writing to i2c and writes to the mode and prescale registers to allow for servo movement */
int server_robot_arm_init(void);

/* Converts the entered angle into the values to be written to the registers and writes to the registers */
int server_move_servo(float angle, uint8_t channel);

/* Run when the switches on the board are pressed */
void server_switch_close_claws(void);
void server_switch_open_claws(void);

#endif
