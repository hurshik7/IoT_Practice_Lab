#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

const int FndSelectPin[6] = {4, 17, 18, 27, 22, 23};
const int FndPin[8] = {6, 12, 13, 16, 19, 20, 26, 21};
const int FndFont[6] = {0x76, 0x79, 0x38, 0x38,  0x3F, 0x08};


void Init()
{
		int i;
		if(wiringPiSetupGpio() == -1)
		{
				printf("WiringPiSetupGpio() error\n");
				exit(-1);
		}

		for(i=0; i<6; i++){
				pinMode(FndSelectPin[i], OUTPUT);
				digitalWrite(FndSelectPin[i], HIGH);
		}

		for(i=0; i<8; i++) {
				pinMode(FndPin[i], OUTPUT);
				digitalWrite(FndPin[i], LOW);
		}
}

void FndSelect(int position)
{
		int i;
		for(i=0; i<6; i++)
		{
				if(i==position)
						digitalWrite(FndSelectPin[i], LOW);
		}
}

void FndDisplay(int position, int num)
{
		int i,j;
		int flag = 0;
		int shift = 0x01;

		FndSelect(position);
		for(i=0; i<8; i++)
		{
				flag = (FndFont[num] & shift);
				digitalWrite(FndPin[i], flag);
				shift <<= 1;
		}
}

void DisplayStart(int position)
{
		int i;
		int data[6] = {0, 1, 2, 3, 4, 5};
		for(i=0; i<6; i++)
		{
			FndDisplay(position, data[i]);
			delay(500);
		}
}

int main()
{
		int i, pos;
		Init();
		while(1)
		{
			for( i=0; i<6; i++){
				DisplayStart(i);
				delay(500);
			}
		}
		return 0;
}
