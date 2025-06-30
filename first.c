#include "FreeRTOS.h"
#include "task.h"

void task1(void *); //declaration
void task2(void *); 

int main()
{
	PINSEL0=0;
	IO0DIR=0xc;
	xTaskCreate(task1,"t1",90,NULL,0,NULL);
	xTaskCreate(task2,"t2",90,NULL,0,NULL);
	vTaskStartScheduler();
	while(1);
}
	

void task1(void *a)
{
	int i;
while(1)
{
	IO0SET=0x4;//p0.2
	for(i=0;i<=100000;i++);
	
	IO0CLR=0x4;
	for(i=0;i<=100000;i++);
}
}
void task2(void *a)
{
	int i;
while(1)
{
	IO0SET=0x8;//p0.3
	for(i=0;i<=100000;i++);
	
	IO0CLR=0x8;
	for(i=0;i<=100000;i++);
	
}
}
