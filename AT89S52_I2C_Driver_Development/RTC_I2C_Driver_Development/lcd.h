#define Data P2
sbit rs=P3^0;
sbit en=P3^1;
void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void string(unsigned char *s);
void lcd_delay();
 void lcd_init()
{
    cmd(0x38);
    cmd(0x0E);
    cmd(0x01);
    cmd(0x06);
    cmd(0x0c);
    cmd(0x80);
}
void cmd(unsigned char a)
{
    Data=a;
    rs=0;
    en=1;
    lcd_delay();
    en=0;
}
void dat(unsigned char b)
{
    Data=b;
    rs=1;
    en=1;
    lcd_delay();
    en=0;
}
void string(unsigned char *s)
{
    while(*s) {
        dat(*s++);
    }
}
void lcd_delay()
{
    unsigned int lcd_delay;
    for(lcd_delay=0;lcd_delay<=200;lcd_delay++);
}


