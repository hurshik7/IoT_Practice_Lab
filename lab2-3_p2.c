#include<stdlib.h>
#include<stdio.h>
#include<wiringPi.h>

const int LedRed[8] = {4, 17, 18, 27, 22, 23, 24, 25};
const int Keypad[8] = {16, 19, 20, 26};

int KeypadRead()
{
		int i;
		int keypadnum = -1;
		for(i=0; i<8; i++)
		{
				if(!digitalRead(Keypad[i]))
				{
						keypadnum = i;
						break;
				}
		}
		return keypadnum;
}

void LedControl(int keypadnum)
{
		int i;
		for(i=0; i<8; i++)
		{
				if(i==keypadnum)
						digitalWrite(LedRed[i], HIGH);
				else
						digitalWrite(LedRed[i], LOW);
		}
}

int main(void)
{
		int i, keypadnum = -1;
		int isRun = 0;
		if(wiringPiSetupGpio() == -1)
				return 1;

		for(i=0; i<8; i++)
		{
				pinMode(LedRed[i], OUTPUT);
				digitalWrite(LedRed[i], LOW);
		}

		for(i=0; i<8; i++)
				pinMode(Keypad[i], INPUT);

		while(1)
		{
				keypadnum = KeypadRead();
				if(keypadnum == 0)
				{
						isRun = 1;
						while(isRun)
						{		
							for(i=0; i<8; i++) {
								LedControl(i);
								delay(500);

								keypadnum = KeypadRead();
								if(keypadnum == 2)
								{
										for(i=0; i<8; i++)
											digitalWrite(LedRed[i], LOW);
										isRun = 0;
										//break;
								}
								else if(keypadnum == 3)
								{
										for(i=0; i<8; i++)
											digitalWrite(LedRed[i], LOW);
										printf("Exit program\n");
										exit(100);
								}
							}
						}
				}
				else if(keypadnum == 1)
				{
						isRun = 1;
						while(isRun)
						{		
							for(i=7; i>=0; i--)
							{
								LedControl(i);
								delay(500);

								keypadnum = KeypadRead();
								if(keypadnum == 2)
								{
										for(i=0; i<8; i++)
											digitalWrite(LedRed[i], LOW);
										isRun = 0;
										break;
								}
								else if(keypadnum == 3)
								{
										for(i=0; i<8; i++)
											digitalWrite(LedRed[i], LOW);
										printf("Exit program\n");
										exit(100);
								}
							}
						}
				}
		}
		return 0;
}
