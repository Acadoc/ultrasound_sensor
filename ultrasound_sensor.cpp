/* ultrasound_sensor.cpp version 1.02 */

#include "ultrasound_sensor.h"

/****************************** variables ************************************/
volatile unsigned long start_time, stop_time;
volatile unsigned short *CurrEchoPin = nullptr;
volatile boolean mesure_started, mesure_ended;
volatile boolean pasif, paselse;

/****************************************************************************/




/********************************** INIT ************************************/
void ultrasound_sensor_init(unsigned short ISR_PIN)
{
	//interrupts();
	DEBUG_PRINT("test1\n");
	delay(3000);
	pinMode(ISR_PIN, INPUT_PULLUP);
	DEBUG_PRINT("test2\n");
	delay(3000);
	*CurrEchoPin = 0;
	attachInterrupt(ISR_PIN, echo_ISR, CHANGE);
	DEBUG_PRINT("test3\n");
	delay(3000);
	//delay(1000);
	start_time = 0 ;
	stop_time = 0 ;
	DEBUG_PRINT("test4\n");
	delay(3000);
	mesure_started = FALSE;
	mesure_ended = TRUE;
	DEBUG_PRINT("ultrasound_sensor init done.\n");
}

/****************************************************************************/

/****************************************************************************/
/******************** ULTRASOUND SENSOR's methods ***************************/
/****************************************************************************/


/*************************** GET_DISTANCE ***********************************/
unsigned int ultrasound_sensor::Get_Distance()
{
	unsigned int mesured_value;

	if( (mesure_started == FALSE) && (mesure_ended == TRUE) )
	{

		CurrEchoPin = &m_EchoPin;
		mesure_started = TRUE;
		mesure_ended = FALSE;

		digitalWrite(m_TrigPin,LOW);
		digitalWrite(m_TrigPin,HIGH);

		delayMicroseconds(10);

		digitalWrite(m_TrigPin,LOW);


		while(mesure_ended == FALSE) /* try to add a limit distance, like 1m or 50cm */
		{
			delay(1);
			DEBUG_PRINT("\nIn the loop, start time : ");
			DEBUG_PRINT(start_time);
			DEBUG_PRINT(", stop time : ");
			DEBUG_PRINT(stop_time);
			DEBUG_PRINT("\t mesure_started : ");
			DEBUG_PRINT(mesure_started);
			DEBUG_PRINT(", mesure_ended time : ");
			DEBUG_PRINT(mesure_ended);
			DEBUG_PRINT(", EchoPin : ");
			DEBUG_PRINT(digitalRead((short)(*CurrEchoPin)));
		}

		mesured_value = (stop_time - start_time) * 17 / 100;

		DEBUG_PRINT("start time: ");
		DEBUG_PRINT(start_time);
		DEBUG_PRINT(", stop time: ");
		DEBUG_PRINT(stop_time);
		DEBUG_PRINT(" mesured: ");
		DEBUG_PRINT(mesured_value);
		DEBUG_PRINT("\n");

		mesure_started = FALSE;

		return mesured_value;
	}
	else
	{
		DEBUG_PRINT("invalid mesure flag set : mesure started = ");
		DEBUG_PRINT(mesure_started);
		DEBUG_PRINT("\tmesure_ended = ");
		DEBUG_PRINT(mesure_ended);
		DEBUG_PRINT("\n");
	}
}
/****************************************************************************/


/***************************** SET_TRIGPIN **********************************/
void ultrasound_sensor::Set_TrigPin(unsigned short pin)
{
	if ((pin >= 0) && (pin <= NB_DIO))
	{
		pinMode(pin,OUTPUT);
		m_TrigPin = pin;
		//pinMode(m_TrigPin,OUTPUT);
		digitalWrite(m_TrigPin,LOW);
		DEBUG_PRINT("TrigPin set up.\n");
	}
	else
	{
		ERROR_CALL("Invalid pin number for TrigPin.")
	}
}
/****************************************************************************/

/***************************** SET_ECHO_PIN *********************************/
void ultrasound_sensor::Set_EchoPin(unsigned short pin)
{
	if ((pin >= 0) && (pin <= NB_DIO))
	{
		pinMode(pin,INPUT_PULLUP);
		m_EchoPin = pin;
		//pinMode(m_EchoPin,INPUT);
		DEBUG_PRINT("EchoPin set up.\n");
	}
	else
	{
		ERROR_CALL("Invalid pin number for EchoPin.")
	}
}
/****************************************************************************/


/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

/****************************** ECHO_ISR ************************************/
void echo_ISR()
{
// don't forget to set any used variable as volatile !
	if(CurrEchoPin == nullptr)
	{
		// do nothing
	}
	else if(digitalRead((short)(*CurrEchoPin)) == HIGH)
	{
		start_time = micros();
		 pasif = TRUE;
	}
	else
	{
		stop_time = micros();
		mesure_ended = TRUE;
		paselse=TRUE;
	}

}
/****************************************************************************/
