#include<reg51.h>
sbit clk=P1^0;
sbit Din=P1^1;//MOSI
sbit Dout=P1^2;//MISO
sbit cs=P1^3;

float read_adc_val(char chNo)
{
	signed char i;
	unsigned int digitalcode=0;
	float analogreadval=0;

	clk=Din=Dout=cs=1;//initial status of port pins
	cs=0;//To initiate the communication
	clk=0;clk=1;//start bit
	clk=0;clk=1;//single ended communication
	Din=0;
	clk=0;clk=1;//D2 bit
	Din=(chNo>>1)&1;
	clk=0;clk=1;//D1 bit
	Din=(chNo>>0)&1;
	clk=0;clk=1;//D0 bit
	clk=0;clk=1;//clocking for sample and hold
	clk=0;clk=1;//null bit
	for(i=11;i>=0;i--)
	{
		clk=0;
		if(Dout==1)
			digitalcode|=1<<i;
		clk=1;
	}
	cs=1;//stop the SPI communication
	analogreadval=(digitalcode*5.0)/4096;
	return(analogreadval);	
}
