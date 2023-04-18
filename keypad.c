#include<reg51.h>
#include"glcd.h"
#include"delay.h"
sbit r0=P1^0;
sbit r1=P1^1;
sbit r2=P1^2;
sbit r3=P1^3;
sbit c0=P1^4;
sbit c1=P1^5;
sbit c2=P1^6;
sbit c3=P1^7;
char row_val,col_val;
char code Key_Val[4][4]={ '1','2','3',':',
													'4','5','6','/',
													'7','8','9',':',
													'*','0','#','/'};
void Row_Init(void)
{
	r0=r1=r2=r3=0;
}
/*bit IsKeyPress(void)
{
	return(c0&c1&c2&c3);
}*/
char KeyValue(void)
{
	Row_Init();
	while((c0&&c1&&c2&&c3));//waiting for key Pressing

	r0=0;r1=r2=r3=1;
	if(!(c0&&c1&&c2&&c3))
	{
		row_val=0;	
		goto col_check;			
	}
	r1=0;r0=r2=r3=1;
	if(!(c0&&c1&&c2&&c3))
	{
		row_val=1;	
		goto col_check;		
	}
	r2=0;r0=r1=r3=1;
	if(!(c0&&c1&&c2&&c3))
	{
		row_val=2;	
		goto col_check;		
	}
	r3=0;r0=r1=r2=1;
	if(!(c0&&c1&&c2&&c3))
		row_val=3;	
		
col_check:
	if(c0==0)
		col_val=0;
	else if(c1==0)
		col_val=1;
	else if(c2==0)
		col_val=2;
	else	
		col_val=3;
	while(!(c0&&c1&&c2&&c3));//waiting for key release
	delay_ms(500);
	return(Key_Val[row_val][col_val]);
}

unsigned char * Key_str(void)
{
	unsigned char a[10],i=0,ch=6;
	do
	{
		a[i]=KeyValue();
		glcd_char_left(0xb9,0x40+(ch*i),a[i]);
		if(a[i]=='*')
			i--;		
	}while(a[i++]!='#');
	a[i]='\0';
	return a;
}


void Key_pad_display(void)
{
	unsigned char i,j,k=8;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			glcd_char_right(0xb8+i,0x40+(k*j),Key_Val[i][j]);
		}
	}
}
char code day[7][5]={"1.Sun","2.Mon","3.Tue","4.Wed","5.Thu","6.Fri","7.Sat"};
void Key_pad_display1(void)
{
	unsigned char i,j,k=8;
	for(i=0;i<7;i++)
	{
		for(j=0;j<5;j++)
		{
			glcd_char_right(0xb8+i,0x40+(k*j),day[i][j]);
		}
	}
}
