#include<reg51.h>
#include<string.h>
#define lcd_port P1						//lcd --> port p1 is defined

//keypad port defined
sbit c1=P2^0;									//c=column; r=row
sbit c2=P2^1;
sbit c3=P2^2;
sbit c4=P2^3;
sbit r1=P2^4;
sbit r2=P2^5;
sbit r3=P2^6;
sbit r4=P2^7;

//lcd_defined
sbit rs=P1^0;									//regiser select pin
sbit rw=P1^1;									//read/write pin
sbit en=P1^2;									//enable pin
sbit buzz=P1^3;							//buzzer pin

char type[4],i=0;							//password total characters
void delay(int t)							//delay defined
{
    int i,j;
    for(i=0;i<t;i++)
    for(j=0;j<1200;j++);
}

void data_en()								//data_function of lcd
{
    rs=1;
    en=1;
    delay(5);
    en=0;
}

void lcd_data(unsigned char ch)					
{
    lcd_port=ch & 0xf0;					//Send upper nibble of _data
    data_en();
    lcd_port=(ch<<4) & 0xf0;	  //Send lower nibble of _data
    data_en();
}

void command_en(void)						//command_function of lcd
{
    rs=0;
    en=1;
    delay(5);
    en=0;
}

void lcd_cmd(unsigned char ch)
{
    lcd_port=ch & 0xf0;				//Send upper nibble of command
    command_en();
    lcd_port=(ch<<4) & 0xf0;	//Send lower nibble of command
    command_en();
}

void lcd_str(char *str)					//string function 
{
    while(*str)
    {
        lcd_data(*str);				 //Call Lcd_data write
        str++;
    }
}

void lcd_init(void)						  	//initialisation of lcd
{
    lcd_cmd(0x02);								//Returns Cursor to home
    lcd_cmd(0x28);								//Selecting 4_bit interface mode
    lcd_cmd(0x0e);								//Display On Cursor On
    lcd_cmd(0x01);								//Clear the display
}
//KEYPAD FUNCTION 
void keypad()
{
    int cursor=0xc0,temp=0;
    lcd_cmd(1);
    lcd_str("fatafat type kal");
    lcd_cmd(0xc0);								//next line of lcd
    i=0;
    while(i<4)
    {
    temp=cursor;
     c1=0;												//first column
     c2=c3=c4=1;
     if(!r1)
     {
        lcd_data('7');
        type[i++]='7';
        cursor++;
        while(!r1);
          }
     
      else if(!r2)
     {
        lcd_data('4');
        type[i++]='4';
        cursor++;
        while(!r2);
        }
     
      else if(!r3)
     {
        lcd_data('1');
        type[i++]='1';
        cursor++;
        while(!r3);
        }
     
      else if(!r4)
     {
        lcd_data('*');
        type[i++]='*';
        cursor++;
        while(!r4);
        }
     
     c2=0;													//second column
     c1=c3=c4=1;
     if(!r1)
     {
        lcd_data('8');
        type[i++]='8';
        cursor++;
        while(!r1);
        }
     
      else if(!r2)
     {
        lcd_data('5');
        type[i++]='5';
        cursor++;
        while(!r2);
        }
     
      else if(!r3)
     {
        lcd_data('2');
        type[i++]='2';
        cursor++;
        while(!r3);
        }
     
      else if(!r4)
     {
        lcd_data('0');
        type[i++]='0';
        cursor++;
        while(!r4);
        }
     
     c3=0;														//third column
     c1=c2=c4=1;
     if(!r1)
     {
        lcd_data('9');
        type[i++]='9';
        cursor++;
        while(!r1);
        }
     
      else if(!r2)
     {
        lcd_data('6');
        type[i++]='6';
        cursor++;
        while(!r2);
        }
     
      else if(!r3)
     {
        lcd_data('3');
        type[i++]='3';
        cursor++;
        while(!r3);
        }
     
      else if(!r4)
     {
        lcd_data('#');
        type[i++]='#';
        cursor++;
        while(!r4);
        }
     
      c4=0;
     c1=c3=c2=1;
     if(!r1)
     {
        lcd_data('P');
        type[i++]='P';
        cursor++;
        while(!r1);
        }
     
      else if(!r2)
     {
        lcd_data('R');
        type[i++]='R';
        cursor++;
        while(!r2);
        }
     
      else if(!r3)
     {
        lcd_data('I');
        type[i++]='I';
        cursor++;
        while(!r3);
        }
     
      else if(!r4)
     {
        lcd_data('T');
        type[i++]='T';
        cursor++;
        while(!r4);
          }
     if(i>0)
     {
         if(temp!=cursor)
         delay(100);
         lcd_cmd(cursor-1);
         lcd_data('*');
     } 
 }      
}

void correct()
{
     lcd_cmd(1);
     lcd_str("haalo");
     lcd_cmd(0xc0);
     lcd_str("manchurian khaie");
     delay(100);
}

void incorrect()
{
    buzz=0;
    lcd_cmd(1);
    lcd_str("khotu che");
    lcd_cmd(0xc0);
    lcd_str("barabar lakh ne");
    delay(100);
    buzz=1;
}

void main()
{
    buzz=1;
    lcd_init();
    lcd_str("MANCUDO'S EFFORTS ");
    lcd_cmd(0xc0);
    lcd_str("=289 LINES CODE ");
    delay(500);
    lcd_cmd(1); 
    lcd_str("AAATLU PAN SELU");
	  lcd_cmd(0xc0);
	  lcd_str(" NOTO PITLA :( ");
    delay(500);
	
    while(1)
    {
            i=0;
            keypad();
            if(strncmp(type,"PRIT",4)==0)			//set p/w
            {
            correct();
            lcd_cmd(1);
							lcd_str("chal andar :) ");
							lcd_cmd(0xc0);
							lcd_str("tane kissi kalu");
              delay(500);
            }
      else 
        {
           lcd_cmd(1);
					 lcd_str("niklo bahar :( ");
					 delay(400);
           incorrect();
           delay(400);
        }
    }
}