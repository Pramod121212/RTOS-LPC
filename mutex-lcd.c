#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
SemaphoreHandle_t m;

void cmd(char a);
void data(char a);
void lcd1(void *a);
void lcd2(void *a);
void display(const char *);
int main()
{
	m=xSemaphoreCreateMutex();
	PINSEL0=0;
	PINSEL1=0;
	IO0DIR=0X3FF<<2;
	cmd(0x38);
	cmd(0x0F);
	cmd(0x01);
	xTaskCreate(lcd1,"Welcome",90,NULL,0,NULL);
	xTaskCreate(lcd2,"hello",90,NULL,0,NULL);
	vTaskStartScheduler();
	while(1);
}

void cmd(char a)
{
	int i;
	IO0CLR=0x3ff<<2;
	IO0SET=a<<4;
	IO0SET=1<<3;
	for(i=0;i<=100000;i++);
	IO0CLR=1<<3;
}

void data(char a)
{
	int i;
	IO0CLR=0x3ff<<2;
	IO0SET=a<<4|1<<2;
	IO0SET=1<<3;
	for(i=0;i<=100000;i++);
	IO0CLR=1<<3;
}
void display(const char *p)
{
	while(*p)
	{
		data(*p);
		p++;
	}
}
void lcd1(void *a)
{
	while(1)
	{
		if(xSemaphoreTake(m,1000))
		{
		cmd(0x80);
		display("Welcome");
		xSemaphoreGive(m);
		vTaskDelay(200);
		}
	}
}

void lcd2(void *a)
{

	while(1)
	{
		
		if(xSemaphoreTake(m,1000))
		{
		cmd(0xC0);
		display("Hello");
		xSemaphoreGive(m);
		vTaskDelay(200);
		}
		
		
	}
}
