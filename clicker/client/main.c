#include <stdio.h>
#include <contiki.h>
#include <contiki-net.h>
#include <sys/clock.h>
#include "letmecreate/core/i2c.h"
#include "letmecreate/core/network.h"
#include "letmecreate/click/joystick.h"
#include "letmecreate/core/common.h"
#include "button-sensor.h"
#include <lib/sensors.h>
#include <sys/etimer.h>

#define SERVER_IP_ADDR "fe80::e05d:1ff:fe47:dfd8"
#define SERVER_PORT 3000
#define CLIENT_PORT 3001
#define BUFFER_SIZE 64

PROCESS(main_process, "Main process");
AUTOSTART_PROCESSES(&main_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data){
    PROCESS_BEGIN();{
        static struct uip_udp_conn * conn;
        static char buffer[BUFFER_SIZE];
        conn = udp_new_connection(CLIENT_PORT, SERVER_PORT, SERVER_IP_ADDR);
        while(1){
            static int8_t x, y;
            i2c_init();
            joystick_click_get_x(&x);
            joystick_click_get_y(&y);
            static int old_value = 0;
            if(old_value != button_sensor.value(0)){
                old_value = button_sensor.value(0);
                sprintf(buffer, "%i,%i,1     ", ((70 * x) / 98) + 90, ((45 * y) / 98) + 45);
                udp_packet_send(conn, buffer, strlen(buffer));
                PROCESS_WAIT_UDP_SENT();
            }
            else{
                sprintf(buffer, "%i,%i,0     ", ((70 * x) / 98) + 90, ((45 * y) / 98) + 45);
                udp_packet_send(conn, buffer, strlen(buffer));
                PROCESS_WAIT_UDP_SENT();
            }
        }
}
PROCESS_END();
}
