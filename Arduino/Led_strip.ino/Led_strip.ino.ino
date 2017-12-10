/*
 * 20DF9E61 = Ratio
 * 20DF8976 = AD
 */

#include <IRremote.h>
#include "define.h"

//Uncomment the next to enable USB debug
//#define DBG

//Const
const int pwm_step[] = {0,1,2,5,8,11,15,20,26,33,41,51,64,80,100,125,160,200,255};
int pwm_step_size;

//Current settings
int pwm_index_R=0, pwm_index_G=0, pwm_index_B=0;
int state_but_mode, state_but_set;	//Status of buttons
int state_set=0;	//Number of settings currently setting. 0 : settings currently not enabled

//Saved in EEPROM. To update eeprom after values have changed, you need to change mode.
int mode=0; //0:color fixed. 1:RGB fading. 2:RGB jumping. 3:Night = Slowly turn OFF, then ON after Xhours
int set0_R, set0_G, set0_B;
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
	//Save number of values in pwm_step
	pwm_step_size=sizeof(pwm_step)/sizeof(int);
  #ifdef DBG
	Serial.begin(9600);
	Serial.print("Enabled IRin.! pwm_step=");
	Serial.println(pwm_step_size);
  #endif
	irrecv2.enableIRIn(); // Start the receiver
	delay(100);		//Slow booting delay to see the BUILTIN LED blink
	digitalWrite(LED_BUILTIN, LOW);
	
	//Init values from EEPROM
	if(EEPROM.read(101)!=1 || (digitalRead(BUT_MODE)==1 && digitalRead(BUT_SET)==1)) {	//Two buttons pressed on boot = RESET settings
		mode=0;
		set0_R=pwm_step_size-1;
		set0_G=pwm_step_size-1;
		set0_B=pwm_step_size-1;
		set1_speed=100;
		set2_speed=100;
		set3_colorBeforeR=pwm_step_size-1;
		set3_colorBeforeG=pwm_step_size-1;
		set3_colorBeforeB=pwm_step_size-1;
		set3_colorAfterR=pwm_step_size-1;
		set3_colorAfterG=pwm_step_size-1;
		set3_colorAfterB=pwm_step_size-1;
		set3_delayNight=4;
		EepromUpdateAll();	//Save all
	}
	state_but_mode=digitalRead(BUT_MODE);
	state_but_set =digitalRead(BUT_SET);
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
			if(pwm_index_B<pwm_step_size-1)
				pwm_index_B++;
		} else if(results2.value==IR_LG_RED){
			if(pwm_index_R<pwm_step_size-1)
				pwm_index_R++;
		} else if(results2.value==IR_LG_GREEN){
			if(pwm_index_G<pwm_step_size-1)
				pwm_index_G++;
		}
		analogWrite(LED0_R,pwm_step[pwm_index_R]);
		analogWrite(LED0_G,pwm_step[pwm_index_G]);
		analogWrite(LED0_B,pwm_step[pwm_index_B]);
		irrecv2.resume(); // Receive the next value
	}
	if (digitalRead(BUT_MODE)!=state_but_mode) {	//Transition button mode
		state_but_mode=digitalRead(BUT_MODE);
		if (state_but_mode==1) {		//Clicked!!
			Blink(mode+1);
			state_set=0;
		}
		while(digitalRead(BUT_MODE)==1);	//Wait releasing button
	}
	if (digitalRead(BUT_SET)!=state_but_set) {	//Transition button mode
		state_but_set=digitalRead(BUT_set);
		if (state_but_set==1) {		//Clicked!!
			ShowSettings(state_set+1);
		}
		while(digitalRead(BUT_SET)==1);	//Wait releasing button
	}
	UpdateLED();
	LightLED();
}

//-----------FUNCTIONS-----------

/*
	UpdateLED from mode
*/
void UpdateLED(int _mode){
	if (_mode==0) {		//Fix
		pwm_index_R=set0_R;
		pwm_index_G=set0_G;
		pwm_index_B=set0_B;
	} else if (_mode==1) {
		pwm_index_R
	}
}

/*
	Light LED using global pwm_index
*/
void LightLED(){
	analogWrite(LED0_R,pwm_index_R);
	analogWrite(LED0_G,pwm_index_G);
	analogWrite(LED0_B,pwm_index_B);
}
/*
	Update variables settings in current mode and settings. Use Analog
*/
void SetSettings(){
	int i;
	if (mode==0) {
		if (state_set==1) {		//R
			TurnAllLED_Pot(analogRead(POT), &set0_R, &set0_G, &set0_B);
		} else if (state_set==2) {		//G
			set0_R=analogRead(POT)/pwm_step_size;
		} else if (state_set==3) {		//B
			set0_G=analogRead(POT)/pwm_step_size;
		} else if (state_set==4) {
			set0_B=analogRead(POT)/pwm_step_size;
		}
	} else if (mode==1) {
		if (state_set==1) {
			while(digitalRead(BUT_SET)==0){
				TurnLED(TURN_OFF);
				for(int c=0; c<255; c++) {
					analogWrite(LED0_R,c);
					delay(analogRead(POT));
					if(digitalRead(BUT_SET)==1) return;
				}
				FadeLED();
			}
			set1_speed=analogRead(POT);
			state_set=0;
		}
	} else if (mode==2) {
		if (state_set==1) {
		}
	} else if (mode==3) {
		if (state_set==1) {	//		set3_colorBeforeR
		} else if (state_set==2) {		//set3_colorBeforeG
		} else if (state_set==3) {		//set3_colorBeforeB
		} else if (state_set==4) {		//set3_colorAfterR
		} else if (state_set==5) {		//set3_colorAfterG
		} else if (state_set==6) {		//set3_colorAfterB
		} else if (state_set==7) {		//set3_delayNight;
		}
	}
}

/*
	ShowSettings shows the current settings that you can set using the analog
*/
void ShowSettings(int _settings){
	int i;
	if (mode==0) {
		state_set=(_settings<=1)?_settings:0;
		if (state_set==1) {		//All
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
		} else if (state_set==2) {		//R
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (state_set==3) {		//G
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_GREEN);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (state_set==4) {		//B
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_BLUE);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		}
	} else if (mode==1) {
		state_set=(_settings<=1)?_settings:0;
		if (state_set==1) {
			TurnLED(TURN_OFF);
			delay(150);
			for (i = 0; i < pwm_step_size; i += 1) {
				analogWrite(LED0_R,pwm_step[i]);
				analogWrite(LED0_G,pwm_step[i]);
				analogWrite(LED0_B,pwm_step[i]);
				delay(500/pwm_step_size);
			}
			for (i = pwm_step_size-1; i >= 0; i -= 1) {
				analogWrite(LED0_R,pwm_step[i]);
				analogWrite(LED0_G,pwm_step[i]);
				analogWrite(LED0_B,pwm_step[i]);
				delay(500/pwm_step_size);
			}
			delay(300);
		}
	} else if (mode==2) {
		state_set=(_settings<=1)?_settings:0;
		if (state_set==1) {
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		}
	} else if (mode==3) {
		state_set=(_settings<=7)?_settings:0;
		if (state_set==1) {	//		set3_colorBeforeR
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (state_set==2) {		//set3_colorBeforeG
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_GREEN);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (state_set==3) {		//set3_colorBeforeB
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_BLUE);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (state_set==4) {		//set3_colorAfterR
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_RED);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (state_set==5) {		//set3_colorAfterG
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_GREEN);
			delay(300);
			TurnLED(TURN_GREEN);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (state_set==6) {		//set3_colorAfterB
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_BLUE);
			delay(300);
			TurnLED(TURN_BLUE);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		} else if (state_set==7) {		//set3_delayNight;
			TurnLED(TURN_OFF);
			delay(150);
			TurnLED(TURN_WHITE);
			delay(300);
			TurnLED(TURN_OFF);
			delay(300);
		}
	}
	if (state_set==0) {		//Anim leaving settings
		for (i = pwm_step_size-1; i >= 0; i -= 1) {
			analogWrite(LED0_R,pwm_step[i]);
			analogWrite(LED0_G,pwm_step[i]);
			analogWrite(LED0_B,pwm_step[i]);
			delay(500/pwm_step_size);
		}
	}
}

/*
	Blink LED to knwo the mode
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
	analogWrite(LED0_R,pwm_step[(_state&1)==0?0:pwm_step_size-1]);
	analogWrite(LED0_G,pwm_step[(_state&2)==0?0:pwm_step_size-1]);
	analogWrite(LED0_B,pwm_step[(_state&4)==0?0:pwm_step_size-1]);
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
    _ptR=0;          // *1.75 pour ramener 146 à 255(.5)
    _ptG=0;          //Le int prends la valeur entière
    _ptB=int(_pot*1.75);      //Tension modifié sur l'anode bleu
  }
  else if(_pot>146 && _pot<=292) {    //BC=B+↑G    Turquoise. Blue+Increasing green
    _ptR=0;
    _ptG=int((_pot-146)*1.75));      //G¡
    _ptB=255;
  }
  else if(_pot>292 && _pot<=438) {    //G+↓B   Green+Decreasing blue
    _ptR=0;
    _ptG=255;
    _ptB=255-int((_pot-292)*1.75));      //B! reduce blue
  }
  else if(_pot>438 && _pot<=584) {    //Y=G+↑R    Yellow
    _ptR=int((_pot-438)*1.75));      //R↑
    _ptG=255;
    _ptB=0;
  }
  else if(_pot>584 && _pot<=730) {   //R+↓G  : Rouge
    _ptR=255;
    _ptG=255-int((_pot-584)*1.75));      //G!
    _ptB=0;
  }
  else if(_pot>730 && _pot<=876) {   //P   Pink
    _ptR=255;
    _ptG=0;
    _ptB=int((_pot-730)*1.75));      //B¡
  }
  else if(_pot>876 && _pot<=1022) {    //W        White
    _ptR=255;
    _ptG=int((_pot-876)*1.75));      //G¡
    _ptB=255;
  }
  //Transform 0→255 to 0→pwm_step_size
  _ptR*pwm_step_size/256;
  _ptG*pwm_step_size/256;
  _ptB*pwm_step_size/256;
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
