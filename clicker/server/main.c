// Code adapted from http://www.tack.ch/unix/network/sockets/udpv6.shtml

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#include "letmecreate/click/robot_arm_server.h"

#define MAXBUF 65536

int main(){
    server_robot_arm_init();
    
    bool claw_open = false;
    int claw = 0;
    
    while(1){
        int sock;
        int status;
        struct sockaddr_in6 sin6;
        int sin6len;
        char buffer[MAXBUF];

        sock = socket(PF_INET6, SOCK_DGRAM,0);
        sin6len = sizeof(struct sockaddr_in6);
        memset(&sin6, 0, sin6len);

        sin6.sin6_port = htons(3000);
        sin6.sin6_family = AF_INET6;
        sin6.sin6_addr = in6addr_any;

        status = bind(sock, (struct sockaddr *)&sin6, sin6len);
        if(-1 == status)
            perror("bind"), exit(1);

        status = getsockname(sock, (struct sockaddr *)&sin6, &sin6len);
        status = recvfrom(sock, buffer, MAXBUF, 0, (struct sockaddr *)&sin6, &sin6len);
        
        int x, y;
        x = y = 0;
    
        if(sscanf(buffer, "%d,%d,%d", &x, &y, &claw) < 0)
            return -1;

        if(claw == 1 && claw_open != false){
            server_switch_close_claws();
            claw_open = false;
        }
        else if(claw == 0 && claw_open != true){
            server_switch_open_claws();
            claw_open = true;
        }
    
        if(claw_open == true)
            printf("%d     %d	open\n", x, y);
        else
            printf("%d     %d	closed\n", x, y);

        server_move_servo(x, LEFT_RIGHT);
        usleep(10000);
        server_move_servo(y, FORWARD_BACKWARD);
        usleep(10000);
    
        shutdown(sock, 2);
        close(sock);
    }
    return 0;
}
