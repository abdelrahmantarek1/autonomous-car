#include "main.h"

int main(void)
{
	uint8_t dist=0;
	//State variable used to control the LCD display value

	uint16_t state = 0;

	uint8_t rightDistance=0;

	uint8_t leftDistance=0;

	uint8_t safeDistance = 10;

	uint8_t reading=0;
	Motor_Initialize();
	LCD_Initialize();
	Motor_Initialize();
	ServoMotor_Initialize();
	SetupUltrasonic();
	sei();                  // Enabling Global interrupt
    while (1) 
    {
		/*LCD_Write_String((uint8_t*)"Direction is ");
		Motor_ON(clockwise,enable1);
		Motor_ON(clockwise,enable2);
		if(clockwise){
			LCD_Write_Command(ROW1_FIRST_CELL);
			LCD_Write_String((uint8_t*)" clockwise");	
		}
		else if(anticlockwise){
			LCD_Write_Command(ROW1_FIRST_CELL);
			LCD_Write_String((uint8_t*)"anticlockwise");
		}
		_delay_ms(1000);*/
		/*ServoMotor_Rotate(5);_delay_ms(500);
		ServoMotor_Rotate(6);_delay_ms(500);
		ServoMotor_Rotate(7);_delay_ms(500);
		ServoMotor_Rotate(8);_delay_ms(500);
		ServoMotor_Rotate(9);_delay_ms(500);
		ServoMotor_Rotate(10);_delay_ms(500);*/
		LCD_Write_String((uint8_t*)"Distance is");
		SendTrigger();
		dist=ReceiveEcho();
		_delay_ms(100);  
		LCD_Write_Command(ROW1_FIRST_CELL);
		LCD_Write_Number(dist); 
		_delay_ms(2000); 
		LCD_Clear(); 
		LCD_Write_String((uint8_t*)"Done");
		LCD_Clear(); 
		/*
		  if(reading > safeDistance)
		  {
			  forward();

			  lcdPrint();
		  }
		  else if(reading == safeDistance)
		  {
			  stop();

			  checkSurroundings();
		  }*/
    }
//Movement functions

//Car's forward movement function

void forward()
{
	Motor_ON(clockwise,enable1);
	
	Motor_ON(clockwise,enable2);

	state = 1;
}

//Car's backward movement function

void backward()
{
	Motor_ON(anticlockwise,enable1);
	
	Motor_ON(anticlockwise,enable2);

	state = 2;
}

//Car's right movement function

void right()
{
	Motor_ON(clockwise,enable1);
	
	Motor_OFF(enable2);

	state = 3;
}

//Car's left movement function

void left()
{
	Motor_ON(clockwise,enable2);
	Motor_OFF(enable1);

	state = 4;
}

//Trial Functions for right and left
//Car's no movement function

void stop()
{
	Motor_OFF(enable1);

	Motor_OFF(enable2);

	state = 0;
}

// LCD printing function

void lcdPrint()
{
	if(state == 0)
	{
		LCD_Write_String((uint8_t*)"No Movement");
	}
	else if(state == 1)
	{
		LCD_Write_String((uint8_t*)"Moving Forward");
	}
	else if(state == 2)
	{
		LCD_Write_String((uint8_t*)"Moving Backward");
	}
	else if(state == 3)
	{
		LCD_Write_String((uint8_t*)"Moving Right");
	}
	else
	{
		LCD_Write_String((uint8_t*)"Moving Left");
	}
}

//Function to check surroundings

void checkSurroundings()
{
	//Move Servo right

	_delay_ms(15);

	rightDistance = reading;

	//Move Servo left

	_delay_ms(15);

	leftDistance = reading;

	if(rightDistance > safeDistance && leftDistance > safeDistance)
	{
		if(rightDistance > leftDistance)
		{
			right();
			lcdPrint();

			_delay_ms(10);

			stop();
			lcdPrint();

			forward();
			lcdPrint();
		}
		else
		{
			left();
			lcdPrint();

			_delay_ms(10);

			stop();
			lcdPrint();

			forward();
			lcdPrint();
		}
	}
	else
	{
		backward();

		_delay_ms(10);

		checkSurroundings();
	}
}


}