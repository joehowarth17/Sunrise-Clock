#include <stdio.h>
#include <stdint.h>

//void shiftOut(uint16_t value, uint16_t latchPin[], uint16_t dataPin[], uint16_t clockPin[]) {
//	latchPin[0] = 0;
//	for (int i = 0; i < 16; i++) {
//		clockPin[0] = 1;
//		dataPin[0] = ((value >> (15 - i)) && 0x01);
//		clockPin[0] = 0;
//	
//	}
//
//
//}
void shift(uint16_t value, char pin) {
	for (int i = 0; i < 16; i++) {
		pin = ((value >> 15 - i) & 0x1);
		printf("%d ", pin);

	}
}
void printArray(char string[]) {
	
	printf("%c", string);



}

int main() {
	/*uint16_t latch[1] = { 0 };
	uint16_t data[1] = {0};
	uint16_t clock[1] = {0};
	uint16_t data = 256;

	shiftOut(data, latch, data, clock);
	return 0;*/
	/*char a= 0;
	uint16_t value = 0xFE09;
	shift(value, a);*/
	
	char a[] = { '9','\0' };
	char *b;
	char value = "abcdefg";
	char *valuePtr = value;
	b = &a[0];
	//printf("%c",*b);
	//printArray(value);
	for (int i = 0; i < 2; i++) {
		printf("%c", *(valuePtr + i));
	}


	return 0;
}