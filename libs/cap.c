#include "cap.h"

int fd;

/*FUNCTIONS*/

/* COMUNICATION OPEN */
//open communication with board
int open_communication(char *portname)
{
    fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);

    if (fd < 0)
    {
        fprintf(stderr, "Communication error, not possible open file!\n");
        return -1;
    }

    set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (fd, 0);                   // set no blocking

    return 0;
}


/*ENCRYPT*/
//return -1 bed params
//if len not multiple of 4*Nb, zeros will be added at the end
//len_in coud what you want, but len_outmust be multiple of Nb*4 and >= len_in
int board_crypt(uint8_t *in, unsigned int len_in, uint8_t *out, unsigned int len_out, uint8_t key[32], unsigned int key_bits, unsigned int enc){

    //control parameters
    if(len_in == 0 || (key_bits != 128 && key_bits != 192 && key_bits != 256 ) || len_out < len_in || len_out % 4*Nb != 0)
        return -1;

    if(fd < 0) {
        fprintf(stderr, "Communication error, file not opened!\n");
        return -1;
    }

    //seed the random
    srand(time(NULL));

    //get the number of elements in the tail of input buffer (add 0)
    unsigned int tail = len_in % (4*Nb);
    unsigned int N = len_in / (4*Nb);//number of iterations
    
    if(tail != 0)//one more iteration
        N++;

    uint8_t *output;
    uint8_t newin[ 4 * Nb];
    uint8_t    towrite[51];

    for (int i = 0; i < N; i++){
        //transpose and full tail with 0
        for(int c = 0; c < Nb*4 ; c++){
            if( i != N-1 || tail == 0 || c < tail)
                *(newin + Nb * (c % 4) + (int) (c / 4)) = *(in + i * 4 * Nb + c);
            else 
                *(newin + Nb * (c % 4) + (int) (c / 4)) = 0;
        }

        output = out + i * 4 * Nb;

        if(enc == 1)
            towrite[0] = (uint8_t) 0x01;
        else
            towrite[0] = (uint8_t) 0x02;

        towrite[1] = (uint8_t) rand() % 0xFF; //random number 0 to FF -256

        if(key_bits == 128)
            towrite[2] = (uint8_t) 0x00;
        else if(key_bits == 192)
            towrite[2] = (uint8_t) 0x01;
        else
            towrite[2] = (uint8_t) 0x02;

        for (int word = 7; word >= 0; word--)
             for (int b = 0; b < 4; b++)
                towrite[3 + ((7 - word) * 4) + b] = key[ word * 4 + b ];
        

        for (int p = 0; p < Nb*4; p++){
            towrite[35+p] =  (uint8_t) in[p];
        }

        fprintf(stderr, "Send: ");

        for (int p = 0; p < 51; p++){
            fprintf(stderr, "%02x", towrite[p]);
        }
        fprintf(stderr, "\n");

        write (fd, towrite, 51);

        uint8_t buf [100];
        int recived = read (fd, buf, sizeof buf);

        fprintf(stderr, "Recived data: %d\n", recived);

        if(recived > 0) {
            fprintf(stderr, "Recived: ");
            for ( int i = 0; i < recived; i++ )
            {
                
                fprintf(stderr, "%02x", buf[i]);
            }
            fprintf(stderr, "\n");
        }

        for (int p = 0; p < 16 && 2 + p < recived; p++){
            out[ (N - 1) * 16 + p ] = buf[ 2 + p];
        }


    }

    return 0;
}




void close_communication() {
    
    if(fd > 0) {
        close(fd);
    }
}



int set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
            fprintf(stderr, "error %d from tcgetattr\n", errno);
            return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= /*~*/(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
            fprintf(stderr, "error %d from tcsetattr", errno);
            return -1;
        }
        return 0;
}

void set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
            fprintf(stderr, "error %d from tggetattr", errno);
            return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
            fprintf(stderr, "error %d setting term attributes", errno);
                
}
