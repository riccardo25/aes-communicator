/*
    COMUNICATOR for AES Protocol
    Written by: Riccardo Fontanini
    Start date: 30/8/2018
    Note: Implementation for comunicate with Atlys board

     R O T A S
     O P E R A
     T E N E T
     A R E P O
     S A T O R

*/

#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef CAP_H
#define CAP_H

    /* GLOBAL VARIABLES */

    #ifndef Nb
        #define Nb 4
    #endif

    extern int fd;

    /* FUNCTIONS */

    // Open the communication
    int open_communication(char *portname);

    // Communicate with board  to crypt data
    int board_crypt(uint8_t *in, unsigned int len_in, uint8_t *out, unsigned int len_out, uint8_t key[32], unsigned int key_bits, unsigned int enc);

    // Close communication
    void close_communication();

    int set_interface_attribs (int fd, int speed, int parity);

    void set_blocking (int fd, int should_block);

#endif