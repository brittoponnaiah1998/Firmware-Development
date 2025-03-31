#include<reg52.h>
#include "lcd.h"
sbit sda=P1^0;
sbit scl=P1^1;
void start();
void write(unsigned char);
unsigned char read();
void stop();
unsigned char sec,min,hour,date,day,yr,mon,ch;
bit c=0;
void main()
{
	start();
	write(0xd0);
	write(0x00);
	write(0x00);
	write(0x20);
	write(0x10);
	write(0x06);
	write(0x18);
	write(0x06);
	write(0x21);
	stop();
	lcd_init();
	cmd(0x80);
	string("TIME:");
	cmd(0xC0);
	string("DATE:");
	while(1)
	{
		unsigned char c,d;
		start();
		write(0xd0);
		write(0x00);
		start();
		write(0xd1);
		read();
		sec=ch;
		sec=sec&0x7f;
		stop();
		start();
		write(0xd0);
		write(0x01);
		start();
		write(0xd1);
		read();
		min=ch;
		min=min&0x7f;
		stop();
		start();
		write(0xd0);
		write(0x02);
		start();
		write(0xd1);
		read();
		hour=ch;
		hour=hour&0x3f;
		stop();
		start();
		write(0xd0);
		write(0x03);
		start();
		write(0xd1);
		read();
		day=ch;
		day=day&0x0f;
		stop();
		start();
		write(0xd0);
		write(0x04);
		start();
		write(0xd1);
		read();
		date=ch;
		date=date&0x03f;
		stop();
		start();
		write(0xd0);
		write(0x05);
		start();
		write(0xd1);
		read();
		mon=ch;
		mon=mon&0x0f;
		stop();
		start();
		write(0xd0);
		write(0x06);
		start();
		write(0xd1);
		read();
		yr=ch;
		yr=yr&0x3f;
		stop();
		
		c=hour&0x0f;
		d=(hour&0xf0)>>4;
		cmd(0x86);
		dat(d|0x30);
		dat(c|0x30);
		dat(':');
		c=min&0x0f;
		d=(min&0xf0)>>4;
		dat(d|0x30);
		dat(c|0x30);
		dat(':');
		c=sec&0x0f;
		d=(sec&0xf0)>>4;
		dat(d|0x30);
		dat(c|0x30);
		
		
		
		c=date&0x0f;
		d=(date&0xf0)>>4;
		cmd(0xc6);
		dat(d|0x30);
		dat(c|0x30);
		dat(':');
		c=mon&0x0f;
		d=(mon&0xf0)>>4;
		dat(d|0x30);
		dat(c|0x30);
		dat(':');
		c=yr&0x0f;
		d=(yr&0xf0)>>4;
		dat(d|0x30);
		dat(c|0x30);
		cmd(0xc6);
	}
}

void write(unsigned char value)
{
	unsigned char c=0x80,d,e;
	d=value;
	for(e=0;e<8;e++)
	{
		sda=d&c;
		scl=1;
		lcd_delay();
		scl=0;
		d=d<<1;
	}
	c=sda;
	scl=1;
	lcd_delay();
	scl=0;
	if(c==1)
	{
		stop();
		while(1);
	}
}

void stop()
{
	scl=1;
	sda=0;
	lcd_delay();
	sda=1;
	scl=0;
  lcd_delay();
}

unsigned char read()
{
	unsigned char a;
	bit m=0;
	for(a=0;a<=7;a++)
	{
		scl=1;
		lcd_delay();
		m=sda;
		scl=0;
		if(m==1)
		{
			ch|=0x01;
		}
		if(a<=6)
		{
			ch=ch<<1;
			lcd_delay();
		}
	}
	return ch;
}

void start()
{
	scl=1;
	sda=1;
	lcd_delay();
	sda=0;
	lcd_delay();
	scl=0;
}