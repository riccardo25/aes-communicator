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

    char *portname = "/dev/ttyS4";


    /* 128 bit
    uint8_t datatocrypt[32] = { (uint8_t)0x00, (uint8_t)0x11, (uint8_t)0x22, (uint8_t)0x33, (uint8_t)0x44, (uint8_t)0x55, 
                                (uint8_t)0x66, (uint8_t)0x77, (uint8_t)0x88, (uint8_t)0x99, (uint8_t)0xaa, 
                                (uint8_t)0xbb, (uint8_t)0xcc, (uint8_t)0xdd, (uint8_t)0xee, (uint8_t)0xff,
                                (uint8_t)0x69, (uint8_t)0xc4, (uint8_t)0xe0, (uint8_t)0xd8, (uint8_t)0x6a, 
                                (uint8_t)0x7b, (uint8_t)0x04, (uint8_t)0x30, (uint8_t)0xd8, (uint8_t)0xcd, 
                                (uint8_t)0xb7, (uint8_t)0x80, (uint8_t)0x70, (uint8_t)0xb4, (uint8_t)0xc5, (uint8_t)0x5a};                       
    */
    
    
    /*192 bit
    uint8_t datatocrypt[32] = { (uint8_t)0x00, (uint8_t)0x11, (uint8_t)0x22, (uint8_t)0x33, (uint8_t)0x44, (uint8_t)0x55, 
                                (uint8_t)0x66, (uint8_t)0x77, (uint8_t)0x88, (uint8_t)0x99, (uint8_t)0xaa, 
                                (uint8_t)0xbb, (uint8_t)0xcc, (uint8_t)0xdd, (uint8_t)0xee, (uint8_t)0xff,
                                (uint8_t)0xdd, (uint8_t)0xa9, (uint8_t)0x7c, (uint8_t)0xa4, (uint8_t)0x86,
                                (uint8_t)0x4c, (uint8_t)0xdf, (uint8_t)0xe0, (uint8_t)0x6e, (uint8_t)0xaf, 
                                (uint8_t)0x70, (uint8_t)0xa0, (uint8_t)0xec, (uint8_t)0x0d, (uint8_t)0x71, (uint8_t)0x91};
    
    */


   /*256 bit*/
    uint8_t datatocrypt[32] = { (uint8_t)0x00, (uint8_t)0x11, (uint8_t)0x22, (uint8_t)0x33, (uint8_t)0x44, (uint8_t)0x55, 
                                (uint8_t)0x66, (uint8_t)0x77, (uint8_t)0x88, (uint8_t)0x99, (uint8_t)0xaa, 
                                (uint8_t)0xbb, (uint8_t)0xcc, (uint8_t)0xdd, (uint8_t)0xee, (uint8_t)0xff,
                                (uint8_t)0x8e, (uint8_t)0xa2, (uint8_t)0xb7, (uint8_t)0xca, (uint8_t)0x51, 
                                (uint8_t)0x67, (uint8_t)0x45, (uint8_t)0xbf, (uint8_t)0xea, (uint8_t)0xfc, 
                                (uint8_t)0x49, (uint8_t)0x90, (uint8_t)0x4b, (uint8_t)0x49, (uint8_t)0x60, (uint8_t)0x89};
    
    
    
    uint8_t dataout[32];
    uint8_t key[32] = { (uint8_t)0x00, (uint8_t)0x01, (uint8_t)0x02, (uint8_t)0x03, (uint8_t)0x04, (uint8_t)0x05,
                        (uint8_t)0x06, (uint8_t)0x07, (uint8_t)0x08, (uint8_t)0x09, (uint8_t)0x0a, (uint8_t)0x0b, 
                        (uint8_t)0x0c, (uint8_t)0x0d, (uint8_t)0x0e, (uint8_t)0x0f, (uint8_t)0x10, (uint8_t)0x11, 
                        (uint8_t)0x12, (uint8_t)0x13, (uint8_t)0x14, (uint8_t)0x15, (uint8_t)0x16, (uint8_t)0x17, 
                        (uint8_t)0x18, (uint8_t)0x19, (uint8_t)0x1a, (uint8_t)0x1b, (uint8_t)0x1c, (uint8_t)0x1d, 
                        (uint8_t)0x1e, (uint8_t)0x1f };


    open_communication(portname);

    board_crypt(datatocrypt, 32, dataout, 32, key, 256, 1, 0);

    close_communication();


    fprintf(stderr, "DATA CRYPTED: ");
    for ( int i = 0; i < 32; i++ )
    {

        if(i%16 == 0)
            fprintf(stderr, "\n");  
        fprintf(stderr, "%02x", dataout[i]);
        
    }
    fprintf(stderr, "\n");
    

    return 0;
}
