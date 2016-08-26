#define _BSD_SOURCE
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "click/robot_arm.h"
#include "core/common.h"

int main(int argc, char ** argv)
{
	char *cmd = NULL;
	if (argc < 2) {
		fprintf(stderr, "Not enough arguments.\n");
		return -1;
	}

	cmd = argv[1];
	
	i2c_init();
	robot_arm_init();
	
	int x, y, claw;
	bool claw_open = false;
	
	if(sscanf(cmd, "%d,%d,%d", &x, &y, &claw) < 0)
		return -1;
		
	if(claw == 0)
		claw_open = false;
	else if(claw == 1)
		claw_open = true;
	else
		return -1;
	
	i2c_select_bus(ROBOT_ARM);
	move_servo(x, LEFT_RIGHT);
	usleep(10000);
	move_servo(y, FORWARD_BACKWARD);
	usleep(10000);
	if(claw_open == false)
		switch_close_claws();
	else
		switch_open_claws();

	return 0;
}
