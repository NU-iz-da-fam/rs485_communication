// test_board_485
// rs485_professional
// C library headers
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

void communication_checking()
{
    fstream MyReadFile;
    int serial_port = open ("/dev/ttyUSB0", O_RDWR);

    // Check the error connection
    if (serial_port < 0) {
        printf("Error\n");
    }
    if (serial_port > 0) {
        printf("Connect succesfully\n");
    }
    // Struct Communication
    struct termios config485;
    if(tcgetattr(serial_port, &config485) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
    config485.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    config485.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    config485.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
    config485.c_cflag |= CS8; // 8 bits per byte (most common)
    config485.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    config485.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    config485.c_lflag &= ~ICANON;
    config485.c_lflag &= ~ECHO; // Disable echo
    config485.c_lflag &= ~ECHOE; // Disable erasure
    config485.c_lflag &= ~ECHONL; // Disable new-line echo
    config485.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    config485.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    config485.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    config485.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    config485.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // config485.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // config485.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    config485.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    config485.c_cc[VMIN] = 0;
    // Set in/out baud rate to be 9600
    cfsetispeed(&config485, B9600);
    cfsetospeed(&config485, B9600);
    // Save and check config error
    if (tcsetattr(serial_port, TCSANOW, &config485) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    } else
    {
        printf("Save config succesfully\n");
    }
}

// read command list for details
void testing_command()
{
    // WRITE TO SERIAL PORT
    write(serial_port,"SC01#\n", sizeof("SW01#\n"));
    sleep(1);

    // READ BACK
    char read_buf [256];
    int n = read(serial_port, &read_buf, sizeof(read_buf));
    cout << read_buf << std::endl;
    sleep(1);

    // Send DOWN signal if necessary
    //write(serial_port,"SW010#", sizeof("SO050#"));
    
    // WRITE TO SERIAL PORT
    write(serial_port,"SW021#\n", sizeof("SO041#\n"));
    sleep(1);

    // Send DOWN signal if necessary
    //write(serial_port,"SW011#", sizeof("SO040#"));
    

    // WRITE TO SERIAL PORT
    write(serial_port,"SW031#\n", sizeof("SO031#\n"));
    sleep(1);
    
    // Send DOWN signal if necessary
    //write(serial_port,"SW011#", sizeof("SO030#"));


    close(serial_port);
}


int main()
{
    communication_checking();
    testing_command();

    return 0;
}