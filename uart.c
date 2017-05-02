
long ar[10];
const int k = 3;
const char l = 3;
const char *str = "erwin";


void init() {

	char *uart_p = (char *)0xff80;
	*(uart_p + 1) = 0x00;
	*(uart_p + 3) = 0x80;
	*(uart_p + 0) = 0x32;
	*(uart_p + 1) = 0x00;
	*(uart_p + 3) = 0x03;
	/* *(uart_p + 4) = 0x0B;  // IRQs enabled, RTS/DSR set  */

}