/*

LA PORTA COM3 o COM5 corrisponde a ttyS3 o ttyS5 

sudo chmod 666 /dev/ttyS5
stty -F /dev/ttyS5 115200

poi lancia il programma
*/


#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libs/cap.h"


int main(){

    char *portname = "/dev/ttyS3";

    /*uint8_t datatocrypt[16] = { (uint8_t)0x00, (uint8_t)0x11, (uint8_t)0x22, (uint8_t)0x33, (uint8_t)0x44, (uint8_t)0x55, 
                                (uint8_t)0x66, (uint8_t)0x77, (uint8_t)0x88, (uint8_t)0x99, (uint8_t)0xaa, 
                                (uint8_t)0xbb, (uint8_t)0xcc, (uint8_t)0xdd, (uint8_t)0xee, (uint8_t)0xff};*/

    uint8_t datatocrypt[16] = { (uint8_t)0x8e, (uint8_t)0xa2, (uint8_t)0xb7, (uint8_t)0xca, (uint8_t)0x51, (uint8_t)0x67, 
                                (uint8_t)0x45, (uint8_t)0xbf, (uint8_t)0xea, (uint8_t)0xfc, (uint8_t)0x49, 
                                (uint8_t)0x90, (uint8_t)0x4b, (uint8_t)0x49, (uint8_t)0x60, (uint8_t)0x89};

                                
    uint8_t dataout[16];

    uint8_t key[32] = { (uint8_t)0x00, (uint8_t)0x01, (uint8_t)0x02, (uint8_t)0x03, (uint8_t)0x04, (uint8_t)0x05,
                        (uint8_t)0x06, (uint8_t)0x07, (uint8_t)0x08, (uint8_t)0x09, (uint8_t)0x0a, (uint8_t)0x0b, 
                        (uint8_t)0x0c, (uint8_t)0x0d, (uint8_t)0x0e, (uint8_t)0x0f, (uint8_t)0x10, (uint8_t)0x11, 
                        (uint8_t)0x12, (uint8_t)0x13, (uint8_t)0x14, (uint8_t)0x15, (uint8_t)0x16, (uint8_t)0x17, 
                        (uint8_t)0x18, (uint8_t)0x19, (uint8_t)0x1a, (uint8_t)0x1b, (uint8_t)0x1c, (uint8_t)0x1d, 
                        (uint8_t)0x1e, (uint8_t)0x1f };

    open_communication(portname);


    board_crypt(datatocrypt, 16, dataout, 16, key, 256, 0);

    close_communication();

    

    return 0;
}
