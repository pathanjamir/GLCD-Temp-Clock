							/* ds1307.c */
#include "types.h"
#include "i2c.h"

u8 AsciiToHexBCD(u8 t1,u8 t2)
{
  return (((t1&0x0f)<<4)|(t2&0x0f));
}

u8 HexBCDtoAsciiUNibble(u8 bcdVal)
{
  return ((bcdVal>>4)+48);        
}

u8 HexBCDtoAsciiLNibble(u8 bcdVal)
{
  return ((bcdVal&0x0f)+48);        
}

u8 Dec2HexBCD(u8 val)
{
  return (((val/10)<<4)|(val%10)); 
}

u8 HexBCD2Dec(u8 val)
{
  return (((val/16)*10)+(val%16));
}

void setTime(u8 *time /*13:45:50*/)
{
  u8 hrs,mins,secs;
  hrs=AsciiToHexBCD(time[0],time[1]);
  mins=AsciiToHexBCD(time[3],time[4]);
  secs=AsciiToHexBCD(time[6],time[7]);
  i2cByteWrite(0xd0,0x02,hrs);
  i2cByteWrite(0xd0,0x01,mins);
  i2cByteWrite(0xd0,0x00,secs);
}

u8 * getTime(void)
{
   static u8 time[9]="00:00:00";
   u8 hrs,mins,secs;
  
   hrs=i2cRandomRead(0xd0,0x02);  
   mins=i2cRandomRead(0xd0,0x01);
   secs=i2cRandomRead(0xd0,0x00);
  
   time[0]=HexBCDtoAsciiUNibble(hrs);
   time[1]=HexBCDtoAsciiLNibble(hrs);
   time[3]=HexBCDtoAsciiUNibble(mins);
   time[4]=HexBCDtoAsciiLNibble(mins);
   time[6]=HexBCDtoAsciiUNibble(secs);
   time[7]=HexBCDtoAsciiLNibble(secs);

   return time;
}

/*void setHrs(u8 hrs)
{
  u8 t;
  t=Dec2HexBCD(hrs);
  i2cByteWrite(0xD0,0x02,t);
}

void setMins(u8 mins)
{
  u8 t;
  t=Dec2HexBCD(mins);
  i2cByteWrite(0xD0,0x01,t);
}

void setSecs(u8 secs)
{
  u8 t;
  t=Dec2HexBCD(secs);
  i2cByteWrite(0xD0,0x00,t);
}

u8 getHrs()
{
  u8 t;
  t=i2cRandomRead(0xD0,0x02);
  t=HexBCD2Dec(t);
  return t;
}

u8 getMins()
{
  u8 t;
  t=i2cRandomRead(0xD0,0x01);
  t=HexBCD2Dec(t);
  return t;
}

u8 getSecs()
{
  u8 t;
  t=i2cRandomRead(0xD0,0x00);
  t=HexBCD2Dec(t);
  return t;
}*/
void setCalendar(u8 *date)
{
  u8 day,month,year;
  day=AsciiToHexBCD(date[0],date[1]);
  month=AsciiToHexBCD(date[3],date[4]);
  year=AsciiToHexBCD(date[6],date[7]);
  i2cByteWrite(0xd0,0x04,day);
  i2cByteWrite(0xd0,0x05,month);
  i2cByteWrite(0xd0,0x06,year);
}
u8 *getCalendar() 
{
   static u8 date[9]="00:00:00";
   u8 day,month,year;
  
   day=i2cRandomRead(0xd0,0x04);  
   month=i2cRandomRead(0xd0,0x05);
   year=i2cRandomRead(0xd0,0x06);
  
   date[0]=HexBCDtoAsciiUNibble(day);
   date[1]=HexBCDtoAsciiLNibble(day);
   date[3]=HexBCDtoAsciiUNibble(month);
   date[4]=HexBCDtoAsciiLNibble(month);
   date[6]=HexBCDtoAsciiUNibble(year);
   date[7]=HexBCDtoAsciiLNibble(year);

   return date;
}
/*void setDate(u8 day)
{
  u8 d;
  d=Dec2HexBCD(day);
  i2cByteWrite(0xD0,0x04,d);
}

void setMonth(u8 month)
{
  u8 d;
  d=Dec2HexBCD(month);
  i2cByteWrite(0xD0,0x05,d);
}

void setYear(u8 year)
{
  u8 d;
  d=Dec2HexBCD(year);
  i2cByteWrite(0xD0,0x06,d);
}
u8 getDate()
{
  u8 d;
  d=i2cRandomRead(0xD0,0x04);
  d=HexBCD2Dec(d);
  return d;
}

u8 getMonth()
{
  u8 d;
  d=i2cRandomRead(0xD0,0x05);
  d=HexBCD2Dec(d);
  return d;
}

u8 getYear()
{
  u8 d;
  d=i2cRandomRead(0xD0,0x06);
  d=HexBCD2Dec(d);
  return d;
}*/
u16 getDay(void)
{
	return i2cRandomRead(0xd0,0x03);
}

void setDay(char ch)
{
	i2cByteWrite(0xd0,0x03,ch);
}