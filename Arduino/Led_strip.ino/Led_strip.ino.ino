/*
 * 20DF9E61 = Ratio
 * 20DF8976 = AD
 */

#include <IRremote.h>
//
#define IR_LG_RATIO	0x20DF9E61
#define IR_LG_AD		 0x20DF8976
#define IR_LG_TEXT	 0x20DF04FB
#define IR_LG_TOPT	 0x20DF847B
#define IR_LG_SUBTITLE 0x20DF9C63
#define IR_LG_STOP	 0x20DF8D72
#define IR_LG_PLAY	 0x20DF0DF2
#define IR_LG_PAUSE	0x20DF5DA2
#define IR_LG_PREV	 0x20DFF10E
#define IR_LG_NEXT	 0x20DF718E
#define IR_LG_SIMPLX 0x20DF7E81
#define IR_LG_RED		0x20DF4EB1
#define IR_LG_GREEN	0x20DF8E71
#define IR_LG_BLUE	 0x20DF8679
#define IR_LG_YELL	 0x20DFC639
//IR Receiver
#define IR_RECV_PIN 12
//LEDs
#define LEDWS_Din 4
#define LED0_R    10
#define LED0_G    9
#define LED0_B    11
#define LED1_R    3
#define LED1_G    5
#define LED1_B    6
//#define LED_BUILTIN 13  //Good reception IR
//Buttons
#define POT   A0   //Analog
#define BUTTON0   15
#define BUTTON1   16

//#define DBG 1

//int pwm_step[] = {0,5,10,15,20,25,35,45,55,66,80,100,130,190,255};
int pwm_step[] = {0,1,2,5,8,11,15,20,26,33,41,51,64,80,100,125,160,200,255};
int pwm_step_size;
int pwm_index_0R=0, pwm_index_0G=0, pwm_index_0B=0;
int pwm_index_1R=0, pwm_index_1G=0, pwm_index_1B=0;

//Next two lines are used for IR receiver. I added a "2" because I had some compilation troubble with the lib IRremote.h.
//I also changed "TKD2" in IRremoteTools.cpp with "12"
IRrecv irrecv2(IR_RECV_PIN);
decode_results results2;

void setup()
{
	//Define all output
	//Internal LED used to see good IR reception
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(LED0_R, OUTPUT);
	pinMode(LED0_G, OUTPUT);
	pinMode(LED0_B, OUTPUT);
	pinMode(LED1_R, OUTPUT);
	pinMode(LED1_G, OUTPUT);
	pinMode(LED1_B, OUTPUT);
	pinMode(LEDWS_Din, OUTPUT);
	//Set all LED to LOW
	digitalWrite(LED_BUILTIN, HIGH);
	digitalWrite(LED0_R, LOW);
	digitalWrite(LED0_G, LOW);
	digitalWrite(LED0_B, LOW);
	digitalWrite(LED1_R, LOW);
	digitalWrite(LED1_G, LOW);
	digitalWrite(LED1_B, LOW);
	digitalWrite(LEDWS_Din, LOW);
	//Inputs : Push button and analog
	pinMode(BUTTON0, INPUT);
	pinMode(BUTTON1, INPUT);
	//Pot doesn't need to be initialized, because it's an analog
	pwm_step_size=sizeof(pwm_step)/sizeof(int);
  #ifdef DBG
	Serial.begin(9600);
	Serial.print("Enabled IRin.! pwm_step=");
	Serial.println(pwm_step_size);
  #endif
	irrecv2.enableIRIn(); // Start the receiver
	delay(100);		//Slow booting delay to see the BUILTIN LED blink
	digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
	if (irrecv2.decode(&results2)) {	//IR decoded
		digitalWrite(LED_BUILTIN, HIGH);
#ifdef DBG
		Serial.print(pwm_index);
		Serial.print(". VAL=");
		Serial.print(results2.value, HEX);
#endif
		if(results2.value==IR_LG_BLUE){	//Increase power of blue
			if(pwm_index_0B<pwm_step_size-1)
				pwm_index_0B++;
		} else if(results2.value==IR_LG_RED){
			if(pwm_index_0R<pwm_step_size-1)
				pwm_index_0R++;
		} else if(results2.value==IR_LG_GREEN){
			if(pwm_index_0G<pwm_step_size-1)
				pwm_index_0G++;
		}
		analogWrite(LED0_R,pwm_step[pwm_index_0R]);
		analogWrite(LED0_G,pwm_step[pwm_index_0G]);
		analogWrite(LED0_B,pwm_step[pwm_index_0B]);
		irrecv2.resume(); // Receive the next value
	}
}
