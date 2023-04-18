#include <reg51.h> 
#include "glcd.h"  	 
#include "ds1307.h" 
#include "i2c.h"
#include "delay.h"
#include "mcp3204.h"
#include "keypad.h"
void ext_int0() interrupt 0
{
unsigned char ch;
	while(1)
	{
		glcd_clr(0);
		glcd_str(0xb8,0x40,"***MENU***");
		glcd_str(0xb9,0x40,"1.Time");
		glcd_str(0xba,0x40,"2.Date");
		glcd_str(0xbb,0x40,"3.Day");
		glcd_str(0xbc,0x40,"4.Exit");
		Key_pad_display();

		switch(KeyValue())
		{	
			case '1':
					glcd_clr(0);
					glcd_str(0xb8,0x40,"HH:MM:SS");
					Key_pad_display();
					glcd_str(0xbe,0x40,"*:Back");
					glcd_str(0xbf,0x40,"#:Enter");
					setTime(Key_str());
					glcd_clr(0);
					break;
			case '2':
					glcd_clr(0);
					glcd_str(0xb8,0x40,"DD/MM/YY");
					Key_pad_display();
					glcd_str(0xbe,0x40,"*:Back");
					glcd_str(0xbf,0x40,"#:Enter");
					setCalendar(Key_str());
					glcd_clr(0);
					break;
			case '3':
					glcd_clr(0);
					glcd_str(0xb8,0x40,"Day(1-7)");
					Key_pad_display1();
					glcd_str(0xbf,0x40,"#:Enter");
					ch=KeyValue();
					glcd_char_left(0xb9,0x40,ch);
					KeyValue();
					setDate(ch);
					break;
			case '4':
					glcd_clr(0);
					return;
		}
	}
}	

/* main program */
void main() 
{
	u8 i,j,k=8,temp;
	char code ch[7][3]={"sun","mon","tue","wed","thu","fri","sat"};
  /* Initilize the lcd */
		glcd_init();
		glcd_clr(0);
  /*set the time and Date only once */
		while(1)
		{		
			/* Display "time" on first line*/
				write_cmd(0xc0);
				glcd_str(0xb8,0x40,"TIME: ");
				write_cmd(0xc0);
				glcd_str(0xb9,0x40,getTime());
			
			/* Display "day" on third line*/	
				//glcd_str(0xba,0x40,"Day:");
				write_cmd(0xc0);
				j=getDay();
				for(i=0;i<3;i++)
					glcd_char_left(0xba,0x40+(i*k),ch[j-1][i]);
			
			/* Display "date" on fifth line*/
				write_cmd(0xc0);
				glcd_str(0xbc,0x40,"DATE: ");
				write_cmd(0xc0);
				glcd_str(0xbd,0x40,getCalendar());
			
			/* Display "date" on fifth line*/
			glcd_str(0xbe,0x40,"TEMP:");	
			temp=read_adc_val(0)*100;// Reading LM35 temp through ADC (0)channel 0,and displaying on GLCD
			glcd_int(temp);
			glcd_str(0xbf,0x55," C");
		}
		while(1);
}