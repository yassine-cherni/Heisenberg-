#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define UART_DEVICE "/dev/ttyUSB0"  // Replace with the actual UART device path
#define BAUD_RATE B9600             // Replace with the desired baud rate

int main() {
    int uartFile;
    struct termios serial;

    // Open UART device
    uartFile = open(UART_DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
    if (uartFile == -1) {
        perror("Error opening UART device");
        exit(EXIT_FAILURE);
    }

    // Configure UART settings
    tcgetattr(uartFile, &serial);
    cfsetospeed(&serial, BAUD_RATE);
    cfsetispeed(&serial, BAUD_RATE);
    serial.c_cflag = BAUD_RATE | CS8 | CREAD | CLOCAL;
    serial.c_iflag = IGNPAR;
    serial.c_oflag = 0;
    serial.c_lflag = 0;
    tcflush(uartFile, TCIFLUSH);
    tcsetattr(uartFile, TCSANOW, &serial);

    // Perform UART read or write operations here

    // Close UART device
    close(uartFile);

    return 0;
}
