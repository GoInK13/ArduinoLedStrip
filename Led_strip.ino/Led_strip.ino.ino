/*
 * 20DF9E61 = Ratio
 * 20DF8976 = AD
 */

#include <IRremote.h>
#include "define.h"
#include <EEPROM.h>

//Uncomment the next to enable USB debug
//#define DBG

//Const
const int pwmStepSize = 50;		//Choose number of step for PWM brightness.
int pwmStep[pwmStepSize];	//Old value : = {0,1,2,5,8,11,15,20,26,33,41,51,64,80,100,125,160,200,255};

//Current settings
int pwmIndexR=0, pwmIndexG=0, pwmIndexB=0;		//Current PWM settings
int stateButMode, stateButSet;	//Status of buttons
int stateSet=0;	//Number of settings currently setting. 0 : settings currently not enabled
int mode=0; //0:color fixed. 1:RGB fading. 2:RGB jumping. 3:Night = Slowly turn OFF, then ON after Xhours

//Saved in EEPROM. To update eeprom after values have changed, you need to click the setting button until going to set 0.
int set0_R, set0_G, set0_B;	//Mode 0 : fix color
int set1_speed;	//Speed transition in ms
int set2_speed;	//Speed transition in ms
//Color before night and after. delayNight is in 30min + 5h. ie:2blinks=6h
int set3_colorBeforeR,set3_colorBeforeG,set3_colorBeforeB,set3_colorAfterR,set3_colorAfterG,set3_colorAfterB, set3_delayNight;

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
	//Save number of values in pwmStep
	
	//Init values from EEPROM
	if(EEPROM.read(101)!=1 || (digitalRead(BUT_MODE)==1 && digitalRead(BUT_SET)==1)) {	//Two buttons pressed on boot = RESET settings
		mode=0;
		set0_R=pwmStepSize-1;
		set0_G=pwmStepSize-1;
		set0_B=pwmStepSize-1;
		set1_speed=100;
		set2_speed=100;
		set3_colorBeforeR=pwmStepSize-1;
		set3_colorBeforeG=pwmStepSize-1;
		set3_colorBeforeB=pwmStepSize-1;
		set3_colorAfterR=pwmStepSize-1;
		set3_colorAfterG=pwmStepSize-1;
		set3_colorAfterB=pwmStepSize-1;
		set3_delayNight=4;
		EepromUpdateAll();	//Save all
	} else {
		mode=EEPROM.read(100);
		//Mode 0
		set0_R=EEPROM.read(1);
		set0_G=EEPROM.read(2);
		set0_B=EEPROM.read(3);
		//Mode 1
		set1_speed=EEPROM.read(10);
		//Mode 2
		set2_speed=EEPROM.read(20);
		//Mode 3
		set3_colorBeforeR=EEPROM.read(30);
		set3_colorBeforeG=EEPROM.read(31);
		set3_colorBeforeB=EEPROM.read(32);
		set3_colorAfterR=EEPROM.read(33);
		set3_colorAfterG=EEPROM.read(34);
		set3_colorAfterB=EEPROM.read(35);
		set3_delayNight=EEPROM.read(36);
	}
	stateButMode=digitalRead(BUT_MODE);
	stateButSet =digitalRead(BUT_SET);
	
	//Update pwmStep using pwm exponential led fading method. Thanks to diarmuidie : https://diarmuid.ie/blog/pwm-exponential-led-fading-on-arduino-or-other-platforms/
	float R = ((pwmStepSize-1) * log10(2))/(log10(255));
	for (int interval = 0; interval < pwmStepSize; interval++) {
		// Calculate the required PWM value for this interval step
		pwmStep[interval]=pow(2, (interval / R)) - 1;
	}
	
	irrecv2.enableIRIn(); // Start the receiver
	#ifdef DBG
		Serial.begin(9600);
		Serial.print("Enabled IRin.! pwmStep=");
		Serial.println(pwmStepSize);
	#endif
	delay(100);		//Slow booting delay to see the BUILTIN LED blink
	digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
	if (irrecv2.decode(&results2)) {	//IR decoded
		digitalWrite(LED_BUILTIN, HIGH);
#ifdef DBG
		Serial.print(pwmIndexR);
		Serial.print(". VAL=");
		Serial.print(results2.value, HEX);
#endif
		if(results2.value==IR_LG_BLUE){	//Increase power of blue
			if(pwmIndexB<pwmStepSize-1)
				pwmIndexB++;
		} else if(results2.value==IR_LG_RED){
			if(pwmIndexR<pwmStepSize-1)
				pwmIndexR++;
		} else if(results2.value==IR_LG_GREEN){
			if(pwmIndexG<pwmStepSize-1)
				pwmIndexG++;
		}
    analogWrite(LED0_R,pwmStep[pwmIndexR]);
    analogWrite(LED0_G,pwmStep[pwmIndexG]);
    analogWrite(LED0_B,pwmStep[pwmIndexB]);
    analogWrite(LED1_R,pwmStep[pwmIndexR]);
    analogWrite(LED1_G,pwmStep[pwmIndexG]);
    analogWrite(LED1_B,pwmStep[pwmIndexB]);
		irrecv2.resume(); // Receive the next value
	}
	if (digitalRead(BUT_MODE)!=stateButMode) {	//Transition button mode
		stateButMode=digitalRead(BUT_MODE);
		if (stateButMode==1) {		//Clicked!!
			Blink(mode+1);
			stateSet=0;
		}
		while(digitalRead(BUT_MODE)==1);	//Wait releasing button
	}
	if (digitalRead(BUT_SET)!=stateButSet) {	//Transition button mode
		stateButSet=digitalRead(BUT_SET);
		if (stateButSet==1) {		//Clicked!!
			ShowSettings(stateSet+1);
			if (stateSet==0) {
				EepromUpdateAll();	//Save all
			}
		}
		while(digitalRead(BUT_SET)==1);	//Wait releasing button
	}
  if(stateSet!=0) {
    SetSettings();
  }
	UpdateLED(mode);
	LightLED();
}

//-----------FUNCTIONS-----------

/*
	UpdateLED from mode
*/
void UpdateLED(int _mode){
	if (_mode==0) {		//Fix
		pwmIndexR=set0_R;
		pwmIndexG=set0_G;
		pwmIndexB=set0_B;
	} else if (_mode==1) {
		pwmIndexR=(pwmIndexR>=pwmStepSize?0:pwmIndexR+1);
		pwmIndexG=(pwmIndexG>=pwmStepSize?0:pwmIndexG+1);
		pwmIndexB=(pwmIndexB>=pwmStepSize?0:pwmIndexB+1);
	}
}

/*
	Light LED using global pwm_index
*/
void LightLED(){
  analogWrite(LED0_R,pwmIndexR);
  analogWrite(LED0_G,pwmIndexG);
  analogWrite(LED0_B,pwmIndexB);
  analogWrite(LED1_R,pwmIndexR);
  analogWrite(LED1_G,pwmIndexG);
  analogWrite(LED1_B,pwmIndexB);
}
/*
	Update variables settings in current mode and settings. Use Analog
*/
void SetSettings(){
	int i;
	if (mode==0) {
		if (stateSet==1) {		//R
			TurnAllLED_Pot(analogRead(POT), &set0_R, &set0_G, &set0_B);
		} else if (stateSet==2) {		//G
			set0_R=analogRead(POT)/pwmStepSize;
		} else if (stateSet==3) {		//B
			set0_G=analogRead(POT)/pwmStepSize;
		} else if (stateSet==4) {
			set0_B=analogRead(POT)/pwmStepSize;
		}
	} else if (mode==1) {
		if (stateSet==1) {
			while(digitalRead(BUT_SET)==0){
				TurnLED(TURN_OFF);
				for(int c=0; c<255; c++) {
          analogWrite(LED0_R,c);
          analogWrite(LED1_R,c);
					delay(analogRead(POT));
					if(digitalRead(BUT_SET)==1) return;
				}
				FadeLED();
			}
			set1_speed=analogRead(POT);
			stateSet=0;
		}
	} else if (mode==2) {
		if (stateSet==1) {
		}
	} else if (mode==3) {
		if (stateSet==1) {	//		set3_colorBeforeR
		} else if (stateSet==2) {		//set3_colorBeforeG
		} else if (stateSet==3) {		//set3_colorBeforeB
		} else if (stateSet==4) {		//set3_colorAfterR
		} else if (stateSet==5) {		//set3_colorAfterG
		} else if (stateSet==6) {		//set3_colorAfterB
		} else if (stateSet==7) {		//set3_delayNight;
		}
	}
}

/*
	ShowSettings shows the current settings that you can set using the analog
*/
void ShowSettings(int _settings){
	int i;
	if (mode==0) {
		stateSet=(_settings<=1)?_settings:0;
		if (stateSet==1) {		//All
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_GREEN);
			delay(300);
			TurnLED(TURN_BLUE);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (stateSet==2) {		//R
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (stateSet==3) {		//G
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_GREEN);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (stateSet==4) {		//B
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_BLUE);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		}
	} else if (mode==1) {
		stateSet=(_settings<=1)?_settings:0;
		if (stateSet==1) {
			TurnLED(TURN_OFF);
			delay(150);
			for (i = 0; i < pwmStepSize; i += 1) {
        analogWrite(LED0_R,pwmStep[i]);
        analogWrite(LED0_G,pwmStep[i]);
        analogWrite(LED0_B,pwmStep[i]);
        analogWrite(LED1_R,pwmStep[i]);
        analogWrite(LED1_G,pwmStep[i]);
        analogWrite(LED1_B,pwmStep[i]);
				delay(500/pwmStepSize);
			}
			for (i = pwmStepSize-1; i >= 0; i -= 1) {
        analogWrite(LED0_R,pwmStep[i]);
        analogWrite(LED0_G,pwmStep[i]);
        analogWrite(LED0_B,pwmStep[i]);
        analogWrite(LED1_R,pwmStep[i]);
        analogWrite(LED1_G,pwmStep[i]);
        analogWrite(LED1_B,pwmStep[i]);
				delay(500/pwmStepSize);
			}
			delay(300);
		}
	} else if (mode==2) {
		stateSet=(_settings<=1)?_settings:0;
		if (stateSet==1) {
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		}
	} else if (mode==3) {
		stateSet=(_settings<=7)?_settings:0;
		if (stateSet==1) {	//		set3_colorBeforeR
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (stateSet==2) {		//set3_colorBeforeG
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_GREEN);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (stateSet==3) {		//set3_colorBeforeB
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_BLUE);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (stateSet==4) {		//set3_colorAfterR
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (stateSet==5) {		//set3_colorAfterG
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_GREEN);
			delay(300);
			TurnLED(TURN_GREEN);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (stateSet==6) {		//set3_colorAfterB
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_BLUE);
			delay(300);
			TurnLED(TURN_BLUE);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (stateSet==7) {		//set3_delayNight;
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_WHITE);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		}
	}
	if (stateSet==0) {		//Anim leaving settings
		for (i = pwmStepSize-1; i >= 0; i -= 1) {
      analogWrite(LED0_R,pwmStep[i]);
      analogWrite(LED0_G,pwmStep[i]);
      analogWrite(LED0_B,pwmStep[i]);
      analogWrite(LED1_R,pwmStep[i]);
      analogWrite(LED1_G,pwmStep[i]);
      analogWrite(LED1_B,pwmStep[i]);
			delay(500/pwmStepSize);
		}
	}
}

/*
	Blink LED to know the mode
*/
void Blink(int _mode){
	mode=(_mode<4)?_mode:0;
	int i;
	TurnLED(TURN_OFF);
	delay(200);
	for (i = 0; i < mode+1; i += 1) {
		TurnLED(TURN_WHITE);
		delay(400);
		TurnLED(TURN_OFF);
		delay(400);
	}
	delay(400);
}

/*
	Turn all LED ON or OFF.
	_state : 001:Red, 010:Green, 100:Blue
	IE : 0=Off, 1=Red, 2=Blue, 3=Pink, 4=Green, 5=Yellow, 6=Turquoise, 7=White
*/
void TurnLED(int _state){
  analogWrite(LED0_R,pwmStep[(_state&1)==0?0:pwmStepSize-1]);
  analogWrite(LED0_G,pwmStep[(_state&2)==0?0:pwmStepSize-1]);
  analogWrite(LED0_B,pwmStep[(_state&4)==0?0:pwmStepSize-1]);
  analogWrite(LED1_R,pwmStep[(_state&1)==0?0:pwmStepSize-1]);
  analogWrite(LED1_G,pwmStep[(_state&2)==0?0:pwmStepSize-1]);
  analogWrite(LED1_B,pwmStep[(_state&4)==0?0:pwmStepSize-1]);
}

/*
	Change color using the analog
	R    G    B    Couleur    Longueur d'onde (nm)
	0    0    0    OFF        ---
	0    0    1    Blue       470
	0    1    1    Turquoise  510     Représentant les couleurs selon leur longueur
	0    1    0    Green      540     d'onde, de la plus faible à la plus grande
	1    1    0    Yellow     575
	1    0    0    Red        650
	1    0    1    Pink       400
	1    1    1    White      ---
*/
void TurnAllLED_Pot(int _pot, int* _ptR, int* _ptG, int* _ptB) {
  if(_pot !=0 && _pot<=146)                  //B : Increasing blue
  {
    *_ptR=0;          // *1.75 pour ramener 146 à 255(.5)
    *_ptG=0;          //Le int prends la valeur entière
    *_ptB=int(_pot*1.75);      //Tension modifié sur l'anode bleu
  }
  else if(_pot>146 && _pot<=292) {    //BC=B+↑G    Turquoise. Blue+Increasing green
    *_ptR=0;
    *_ptG=int((_pot-146)*1.75);      //G¡
    *_ptB=255;
  }
  else if(_pot>292 && _pot<=438) {    //G+↓B   Green+Decreasing blue
    *_ptR=0;
    *_ptG=255;
    *_ptB=255-int((_pot-292)*1.75);      //B! reduce blue
  }
  else if(_pot>438 && _pot<=584) {    //Y=G+↑R    Yellow
    *_ptR=int((_pot-438)*1.75);      //R↑
    *_ptG=255;
    *_ptB=0;
  }
  else if(_pot>584 && _pot<=730) {   //R+↓G  : Rouge
    *_ptR=255;
    *_ptG=255-int((_pot-584)*1.75);      //G!
    *_ptB=0;
  }
  else if(_pot>730 && _pot<=876) {   //P   Pink
    *_ptR=255;
    *_ptG=0;
    *_ptB=int((_pot-730)*1.75);      //B¡
  }
  else if(_pot>876 && _pot<=1022) {    //W        White
    *_ptR=255;
    *_ptG=int((_pot-876)*1.75);      //G¡
    *_ptB=255;
  }
  //Transform 0→255 to 0→pwmStepSize
  *_ptR*pwmStepSize/256;
  *_ptG*pwmStepSize/256;
  *_ptB*pwmStepSize/256;
}

/*
	Fade LED R→G→B. Use POT as speed and return if settings is clicked.
*/
void FadeLED(){
	for(int c=0; c<255; c++) {
		analogWrite(6,c);
		delay(analogRead(POT));
		if(digitalRead(BUT_SET)==1) return;
	}
	for(int c=255; c>0; c--) {
		analogWrite(5,c);
		delay(analogRead(POT));
		if(digitalRead(BUT_SET)==1) return;
	}
	for(int c=0; c<255; c++) {
		analogWrite(9,c);
		delay(analogRead(POT));
		if(digitalRead(BUT_SET)==1) return;
	}
	for(int c=255; c>0; c--) {
		analogWrite(6,c);
		delay(analogRead(POT));
		if(digitalRead(BUT_SET)==1) return;
	}
	for(int c=0; c<255; c++) {
		analogWrite(5,c);
		delay(analogRead(POT));
		if(digitalRead(BUT_SET)==1) return;
	}
	for(int c=255; c>0; c--) {
		analogWrite(9,c);
		delay(analogRead(POT));
		if(digitalRead(BUT_SET)==1) return;
	}
}

/*
	Update EEPROM from currents values set. (Limites to 100k writes!!!)
*/
void EepromUpdateAll(){
	EEPROM.update(100, mode);
	EEPROM.update(101, 1);	//Set to 1 : says it's programmed
	//Mode 0
	EEPROM.update(1, set0_R);
	EEPROM.update(2, set0_G);
	EEPROM.update(3, set0_B);
	//Mode 1
	EEPROM.update(10, set1_speed);
	//Mode 2
	EEPROM.update(20, set2_speed);
	//Mode 3
	EEPROM.update(30, set3_colorBeforeR);
	EEPROM.update(31, set3_colorBeforeG);
	EEPROM.update(32, set3_colorBeforeB);
	EEPROM.update(33, set3_colorAfterR);
	EEPROM.update(34, set3_colorAfterG);
	EEPROM.update(35, set3_colorAfterB);
	EEPROM.update(36, set3_delayNight);
}
