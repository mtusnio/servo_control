#include "letmecreate/click/robot_arm.h"

int main(void){
    i2c_init();
    robot_arm_init();
    /* The two switches on the board are used to open and close the claws of the robotic arm */
    switches_init();
    while(1){
        /* x and y correspond to the x and y co-ordinates of the joystick click */
        int8_t x, y;
        /* x_angle and y_angle are the angles to rotate the servos to. */
        float x_angle, y_angle;
        
        i2c_select_bus(JOYSTICK);
        if(joystick_click_get_position(&x, &y) == -1)
            return -1;
        x_angle = convert_to_angle(x, LEFT_RIGHT);
        y_angle = convert_to_angle(y, FORWARD_BACKWARD);
        
        i2c_select_bus(ROBOT_ARM);
        move_servo(x_angle, LEFT_RIGHT);
        usleep(10000);
        move_servo(y_angle, FORWARD_BACKWARD);
        usleep(10000);
        
        printf("x:%d    y:%d\n", (int) x_angle, (int) y_angle);
    }
    return 0;
}
