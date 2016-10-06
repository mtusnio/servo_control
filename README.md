# Creator Ci40 - Robot Arm Control
For more information, visit the [Hackster Page](https://www.hackster.io/imgtec/controlling-a-robotic-arm-using-the-creator-ci40-025127)
## Quickstart guide:
### Installing openwrt and LetMeCreate library
[Follow these steps to install openwrt and the LetMeCreate library](https://github.com/francois-berder/LetMeCreate)
Then, to transfer openwrt to the USB:
```
df
```
The USB appears as /dev/sdb[x] (replace x with the number given by the `df` command). If necessary, unplug the USB and run df again to see which device disappears
```
umount /dev/sdb[x]
```
```
sudo mkfs.ext4 /dev/sdb[x]
```
This formats the USB as ext4 format, which is used by the CreatorBoard. Check the USB is empty. If not, re-enter these commands.
```
sudo nautilus
```
This opens a root file explorer. Copy the contents of /path/to/openwrt/bin/pistachio/openwrt-pistachio-marduk-marduk-cc2520-rootfs to the root folder of the USB
```
sync
```
## Adding the programs to the LetMeCreate library

Clone the repository:
```
$ git clone https://github.com/MatthewRFennell/servo_control.git
```
(Note: alternatively, you may download the zip file)

### Controlling the robot with the joystick click on the board

Inside the local folder:
Transfer the main.c file to custom/letmecreate/LetMeCreate/examples/robot_arm/
Transfer the robot_arm.c file to custom/letmecreate/LetMeCreate/src/letmecreate/click/
Transfer the robot_arm.h file to custom/letmecreate/LetMeCreate/include/letmecreate/click/
Open the CMakeLists.txt file found in custom/letmecreate/LetMeCreate/examples/ and append these lines to the bottom:
```
add_executable(letmecreate_test_robot_arm robot_arm/main.c)
target_link_libraries(letmecreate_test_robot_arm letmecreate_click letmecreate_core)
install(TARGETS letmecreate_test_robot_arm RUNTIME DESTINATION bin)
```
Now, to remake the LetMeCreate library:
```
openwrt$ make package/letmecreate/compile V=s
```
```
openwrt $ scp /path/to/openwrt/bin/pistachio/packages/custom/letmecreate_0.1_pistachio.ipk root@PASTE THE IP ADDRESS HERE:~/
```
Then, on the board:
```
opkg install ~/letmecreate_0.1_pistachio.ipk
```
```
/usr/bin/letmecreate_examples/# ./letmecreate_test_robot_arm
```

### Controlling the robot with the joystick click on the 6LoWPAN Clicker
#### Running the server
Inside the clicker/server folder:
Transfer the main.c file to custom/letmecreate/LetMeCreate/examples/robot_arm_server/
Transfer the robot_arm_server.c file to custom/letmecreate/LetMeCreate/src/letmecreate/click/
Transfer the robot_arm_server.h file to custom/letmecreate/LetMeCreate/include/letmecreate/click/
Open the CMakeLists.txt file found in custom/letmecreate/LetMeCreate/examples/ and append these lines to the bottom:
```
add_executable(letmecreate_test_robot_arm_server robot_arm_server/main.c)
target_link_libraries(letmecreate_test_robot_arm_server letmecreate_click letmecreate_core)
install(TARGETS letmecreate_test_robot_arm_server RUNTIME DESTINATION bin)
```
Now, to remake the LetMeCreate library:
```
openwrt$ make package/letmecreate/compile V=s
```
```
openwrt $ scp /path/to/openwrt/bin/pistachio/packages/custom/letmecreate_0.1_pistachio.ipk root@PASTE THE IP ADDRESS HERE:~/
```
Then, on the board, install the server program:
```
opkg install ~/letmecreate_0.1_pistachio.ipk
```
And run the server program:
```
/usr/bin/letmecreate_examples/# ./letmecreate_test_robot_arm_server
```
#### Running the client
A PICkit 3 is used to program the clicker. As such, the MPLAB X IPE and IDE need to be installed using the instructions at the following links:

[Integrated Programming Environment](http://microchip.wikidot.com/ipe:installation)

[Integrated Development Environment](http://microchip.wikidot.com/mplabx:installation)

Now clone the [LetMeCreateIOT library](https://github.com/mtusnio/LetMeCreateIoT/).

Inside LetMeCreateIOT/examples, create a new folder named robot_arm.

Copy the Makefile and main.c files in clicker/client into the LetMeCreateIOT/examples/robot_arm folder

Follow the setup instructions for installation and update at the [LetMeCreateIOT repository](https://github.com/mtusnio/LetMeCreateIoT/)
```
LetMeCreateIOT/examples/robot_arm$ make
```

Plug the PICkit 3 Microchip into the USB port of the computer, and connect the PICkit 3 Microchip to the clicker using the pins on the side with the label “PICkit”. Ensure that the arrow in the PICkit is lined up to the “RST”

In Settings, enable advanced mode. In the Power tab, enable “Power Circuit from Tool”

Select the device model (eg PIC32MX470F512H) and press Apply. The Tool box should now fill

Now click Connect to connect to the clicker

Now browse to the correct folder with the source code in it (LetMeCreateIOT/examples/robot_arm_client). Select the main.hex file

Click Program - the client program will now run until the clicker is erased or reprogrammed.

### Controlling the robot arm using a webapp
Install git and node.js on the board:
```
# Opkg install git
```
```
# Opkg install node
```
```
# Opkg install gcc
```

Clone the repository somewhere on the board:
```
Git clone https://github.com/matthewrfennell/servo_control/
```
```
servo_control/webapp# make
```
```
servo_control/webapp# npm install
```
Run `ifconfig` to find the IP address of the board
```
servo_control/webapp# npm start
```

Now, with another device on the same network, open a web browser to access the webpage:
http://[Ci40 IP Address]:3000

## Links

The web app code is modified from [the Relay Web app project.](https://github.com/hugo-santos-imgtec/ci40_relay_webapp).
The UDP server code is modified from [http://www.tack.ch/unix/network/sockets/udpv6.shtml](http://www.tack.ch/unix/network/sockets/udpv6.shtml)
