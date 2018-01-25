#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART

int uart0_filestream = -1;
		//Open in non blocking read/write mode
	
struct termios options;
	
	

unsigned char tx_buffer[]={
//5Hz
0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xFA, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x96,0x96,

//Static Hold and Pedestrian
0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00,  
0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x0A, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00,  
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0xE0,

//SBAS
//0xB5, 0x62, 0x06, 0x16, 0x08, 0x00, 0x03, 0x03, 0x01, 0x00, 0x80, 0x01, 0x00, 0x00, 0xAC, 0xC0,

//SBAS2
0xB5, 0x62, 0x06, 0x16, 0x08, 0x00, 0x03, 0x07, 0x03, 0x00, 0x80, 0x01, 0x00, 0x00, 0xB2, 0xE8,

//Baud 115200
0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00,  
0x00, 0x00, 0x00, 0xC2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
0x00, 0x00, 0xEE, 0xBC,

//Save
0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
0x03, 0x1D, 0xAB  
};



int main(){
uart0_filestream = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
if (uart0_filestream == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}
tcgetattr(uart0_filestream, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);
if (uart0_filestream != -1)
	{
		int count = write(uart0_filestream, &tx_buffer[0], 96);		//Filestream, bytes to write, number of bytes to write
		if (count < 0)
		{
			printf("UART TX error\n");
		}
	}

	close(uart0_filestream);
}

