/* ultrasound_sensor.h version 1.00 */

#ifndef ultrasound_sensor_h
	#define ultrasound_sensor_h

	#ifndef ressources_h
		#include "ressources.h"
	#endif

	#ifndef Arduino_h
		#include <Arduino.h>
	#endif

	/************************************* variables extern ******************************/
	extern volatile boolean mesure_started, mesure_ended;
	extern volatile unsigned long start_time, stop_time;

	/*************************************************************************************/


	/************************************* functions extern ******************************/
	extern void echo_ISR();
	extern void ultrasound_sensor_init(unsigned short ISR_PIN);


	/*************************************************************************************/


	class ultrasound_sensor
	{
		/* attributes */
		private:
		
		unsigned short m_TrigPin, m_EchoPin;

		/* methodes */
		public:
			
		unsigned int Get_Distance();
		void Set_TrigPin(unsigned short pin);
		void Set_EchoPin(unsigned short pin);
	};
#endif
