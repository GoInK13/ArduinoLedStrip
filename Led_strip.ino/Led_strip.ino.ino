/*
   20DF9E61 = Ratio
   20DF8976 = AD
*/

#include <IRremote.h>
#include "define.h"
#include <EEPROM.h>

//Uncomment the next to enable USB debug
//#define DBG
//Next is removed, bevause LED1_R doesn't work with IR_Receiver…
//#define IR_RECV

//Const
//const int pwmStepSize = 50;		//Choose number of step for PWM brightness.
//int pwmStep[pwmStepSize]; //Old value : = {0,1,2,5,8,11,15,20,26,33,41,51,64,80,100,125,160,200,255};
const int pwmStepSize = 37;    //Number of step for PWM brightness.
int pwmStep[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13, 15, 17, 19, 22, 25, 28, 32, 36, 40, 45, 51, 57, 64, 72, 81, 91, 102, 114, 128, 143, 161, 180, 202, 226, 255};

//Current settings
int pwmIndexR = 0, pwmIndexG = 0, pwmIndexB = 0;		//Current PWM settings
int cntTransition = 0;	//Count transition for fade and jump.
int stateSet = 0;	//Number of settings currently setting. 0 : settings currently not enabled
int mode = 0; //0:color fixed. 1:RGB fading. 2:RGB jumping. 3:Night = Slowly turn OFF, then ON after Xhours

//Saved in EEPROM. To update eeprom after values have changed, you need to click the setting button until going to set 0.
int set0_R, set0_G, set0_B;	//Mode 0 : fix color
int set1_speed;	//Speed transition in ms. Fade
int set2_speed;	//Speed transition in ms. Jump
//Color before night and after. delayNight is in 30min + 5h. ie:2blinks=6h
int set3_colorBeforeR, set3_colorBeforeG, set3_colorBeforeB, set3_colorAfterR, set3_colorAfterG, set3_colorAfterB, set3_delayNight;

unsigned long mode3_nightStarting;	//millis() start when entering in this mode

unsigned int oldPot=0;	//Save the old value of POT, before update it

//Next two lines are used for IR receiver. I added a "2" because I had some compilation troubble with the lib IRremote.h.
//I also changed "TKD2" in IRremoteTools.cpp with "12"

#ifdef IR_RECV
IRrecv irrecv2(IR_RECV_PIN);
decode_results results2;
#endif

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
  if (EEPROM.read(101) != 1 || (digitalRead(BUT_MODE) == 1 && digitalRead(BUT_SET) == 1)) {	//Two buttons pressed on boot = RESET settings
    mode = 0;
    set0_R = pwmStepSize - 1;
    set0_G = pwmStepSize - 1;
    set0_B = pwmStepSize - 1;
    set1_speed = 100;
    set2_speed = 100;
    set3_colorBeforeR = pwmStepSize - 1;
    set3_colorBeforeG = pwmStepSize - 1;
    set3_colorBeforeB = pwmStepSize - 1;
    set3_colorAfterR = pwmStepSize - 1;
    set3_colorAfterG = pwmStepSize - 1;
    set3_colorAfterB = pwmStepSize - 1;
    set3_delayNight = 4;
    EepromUpdateAll();	//Save all
  } else {
    mode = EEPROM.read(100);
    //Mode 0
    set0_R = EEPROM.read(1);
    set0_G = EEPROM.read(2);
    set0_B = EEPROM.read(3);
    //Mode 1
    set1_speed = EEPROM.read(10);
    //Mode 2
    set2_speed = EEPROM.read(20);
    //Mode 3
    set3_colorBeforeR = EEPROM.read(30);
    set3_colorBeforeG = EEPROM.read(31);
    set3_colorBeforeB = EEPROM.read(32);
    set3_colorAfterR = EEPROM.read(33);
    set3_colorAfterG = EEPROM.read(34);
    set3_colorAfterB = EEPROM.read(35);
    set3_delayNight = EEPROM.read(36);
  }
  /*
    //Update pwmStep using pwm exponential led fading method. Thanks to diarmuidie : https://diarmuid.ie/blog/pwm-exponential-led-fading-on-arduino-or-other-platforms/
    float R = ((pwmStepSize-1) * log10(2))/(log10(255));
    for (int interval = 0; interval < pwmStepSize; interval++) {
  	// Calculate the required PWM value for this interval step
  	pwmStep[interval]=pow(2, (interval / R)) - 1;
    }
  */

#ifdef IR_RECV
  irrecv2.enableIRIn(); // Start the receiver
#endif
#ifdef DBG
  Serial.begin(115200);
  Serial.print("Enabled IRin.! pwmStep=");
  Serial.println(pwmStepSize);
#endif
  delay(100);		//Slow booting delay to see the BUILTIN LED blink
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

#ifdef IR_RECV
  if (irrecv2.decode(&results2)) {	//IR decoded
    digitalWrite(LED_BUILTIN, HIGH);
#ifdef DBG
    Serial.print(pwmIndexR);
    Serial.print(". VAL=");
    Serial.print(results2.value, HEX);
#endif
    if (results2.value == IR_LG_BLUE) {	//Increase power of blue
      if (pwmIndexB < pwmStepSize - 1)
        pwmIndexB++;
    } else if (results2.value == IR_LG_RED) {
      if (pwmIndexR < pwmStepSize - 1)
        pwmIndexR++;
    } else if (results2.value == IR_LG_GREEN) {
      if (pwmIndexG < pwmStepSize - 1)
        pwmIndexG++;
    }
    analogWrite(LED0_R, pwmStep[pwmIndexR]);
    analogWrite(LED0_G, pwmStep[pwmIndexG]);
    analogWrite(LED0_B, pwmStep[pwmIndexB]);
    analogWrite(LED1_R, pwmStep[pwmIndexR]);
    analogWrite(LED1_G, pwmStep[pwmIndexG]);
    analogWrite(LED1_B, pwmStep[pwmIndexB]);
    irrecv2.resume(); // Receive the next value
  }
#endif
  if (digitalRead(BUT_MODE) == 1) {	//Transition button mode
    while (digitalRead(BUT_MODE) == 1);  //Wait releasing button
    Blink(mode + 1);
    stateSet = 0;
    pwmIndexR = 0;
    pwmIndexG = 0;
    pwmIndexB = 0;
    cntTransition = 0;
    if (mode == 3) {	//Mode night
      mode3_nightStarting = millis();
    }
    if (mode == 0) {
      EepromUpdateAll();  //Save all
    }
  }
  if (digitalRead(BUT_SET) == 1) {	//Transition button mode
    ShowSettings(stateSet + 1);
    oldPot=analogRead(POT);
    while (digitalRead(BUT_SET) == 1);	//Wait releasing button
  }
  if (stateSet != 0) {
    SetSettings();
  } else {
    UpdateLED(mode);
  }
  LightLED();

#ifdef DBG
  Serial.println();
  Serial.print("Mode=");
  Serial.print(mode);
  Serial.print(", set=");
  Serial.print(stateSet);
  Serial.print(",R=");
  Serial.print(pwmIndexR);
  Serial.print(",G=");
  Serial.print(pwmIndexG);
  Serial.print(",B=");
  Serial.print(pwmIndexB);
#endif
}

//-----------FUNCTIONS-----------

/*
	UpdateLED from mode
*/
void UpdateLED(int _mode) {
  if (_mode == 0) {		//Fix
    pwmIndexR = set0_R;
    pwmIndexG = set0_G;
    pwmIndexB = set0_B;
  } else if (_mode == 1) {
    cntTransition = cntTransition >= 6 * pwmStepSize ? 0 : cntTransition + 1;
    /*
      0    0    0    OFF        ---
      0    0    1    Blue       470
      0    1    1    Turquoise  510     Représentant les couleurs selon leur longueur
      0    1    0    Green      540     d'onde, de la plus faible à la plus grande
      1    1    0    Yellow     575
      1    0    0    Red        650
      1    0    1    Pink       400
      1    1    1    White      ---
    */
    if (cntTransition <= 1 * pwmStepSize) {
      pwmIndexR = pwmIndexR == 0 ? 0 : pwmIndexR - 1;
    } else if (cntTransition <= 2 * pwmStepSize) {
      pwmIndexG = pwmIndexG >= pwmStepSize - 1 ? pwmStepSize - 1 : pwmIndexG + 1;
    } else if (cntTransition <= 3 * pwmStepSize) {
      pwmIndexB = pwmIndexB == 0 ? 0 : pwmIndexB - 1;
    } else if (cntTransition <= 4 * pwmStepSize) {
      pwmIndexR = pwmIndexR >= pwmStepSize - 1 ? pwmStepSize - 1 : pwmIndexR + 1;
    } else if (cntTransition <= 5 * pwmStepSize) {
      pwmIndexG = pwmIndexG == 0 ? 0 : pwmIndexG - 1;
    } else if (cntTransition <= 6 * pwmStepSize) {
      pwmIndexB = pwmIndexB >= pwmStepSize - 1 ? pwmStepSize - 1 : pwmIndexB + 1;
    }
    DelayInter(set1_speed);
  } else if (_mode == 2) { //Jump
    cntTransition = cntTransition >= 6 ? 1 : cntTransition + 1;
    /*
      R    G    B
      0    0    1    Blue       470		001	1
      0    1    1    Turquoise  510     010	2
      0    1    0    Green      540     011	3
      1    1    0    Yellow     575		100	4
      1    0    0    Red        650		101	5
      1    0    1    Pink       400		110	6
    */
    if (cntTransition == 1 || cntTransition == 2 || cntTransition == 6) {
      pwmIndexB = pwmStepSize-1;
    } else {
      pwmIndexB = 0;
    }
    if (cntTransition == 2 || cntTransition == 3 || cntTransition == 4) {
      pwmIndexG = pwmStepSize-1;
    } else {
      pwmIndexG = 0;
    }
    if (cntTransition == 4 || cntTransition == 5 || cntTransition == 6) {
      pwmIndexR = pwmStepSize-1;
    } else {
      pwmIndexR = 0;
    }
    DelayInter(set2_speed);
  } else if (_mode == 3) {	//Night
    if (millis() - mode3_nightStarting < 1800000) { //30 first minutes
      static unsigned long temp_powerNight;
      temp_powerNight = (millis() - mode3_nightStarting) * pwmStepSize / 1800000;
      pwmIndexR = set3_colorBeforeR * (pwmStepSize - temp_powerNight) / pwmStepSize;
      pwmIndexG = set3_colorBeforeG * (pwmStepSize - temp_powerNight) / pwmStepSize;
      pwmIndexB = set3_colorBeforeB * (pwmStepSize - temp_powerNight) / pwmStepSize;
    } else if (millis() - mode3_nightStarting < 21600000 + set3_delayNight * 1800000) { //During night
      pwmIndexR = 0;
      pwmIndexG = 0;
      pwmIndexB = 0;
    } else {
      static unsigned long temp_powerNight;
      temp_powerNight = (millis() - mode3_nightStarting - 0 - set3_delayNight * 30000) * pwmStepSize / 30000;
      temp_powerNight = (millis() - mode3_nightStarting - 21600000 - set3_delayNight * 1800000) * pwmStepSize / 1800000;
      if (temp_powerNight < pwmStepSize) {
        pwmIndexR = set3_colorAfterR * temp_powerNight / pwmStepSize;
        pwmIndexG = set3_colorAfterG * temp_powerNight / pwmStepSize;
        pwmIndexB = set3_colorAfterB * temp_powerNight / pwmStepSize;
      } else {
        pwmIndexR = set3_colorAfterR;
        pwmIndexG = set3_colorAfterG;
        pwmIndexB = set3_colorAfterB;
      }
    }
  }
}

/*
	Light LED using global pwm_index
*/
void LightLED() {
  analogWrite(LED0_R, pwmStep[pwmIndexR]);
  analogWrite(LED0_G, pwmStep[pwmIndexG]);
  analogWrite(LED0_B, pwmStep[pwmIndexB]);
  analogWrite(LED1_R, pwmStep[pwmIndexR]);
  analogWrite(LED1_G, pwmStep[pwmIndexG]);
  analogWrite(LED1_B, pwmStep[pwmIndexB]);
}
/*
	Update variables settings in current mode and settings. Use Analog
*/
void SetSettings() {
  int i;
  if (mode == 0) {
    if (stateSet == 1) {		//All
      TurnAllLED_Pot(analogRead(POT), &pwmIndexR, &pwmIndexG, &pwmIndexB);
    }
  } else if (mode == 1) {
    if (stateSet == 1) {
      cntTransition = cntTransition >= 6 * pwmStepSize ? 0 : cntTransition + 1;
      if (cntTransition <= 1 * pwmStepSize) {
        pwmIndexR = pwmIndexR == 0 ? 0 : pwmIndexR - 1;
      } else if (cntTransition <= 2 * pwmStepSize) {
        pwmIndexG++;
      } else if (cntTransition <= 3 * pwmStepSize) {
        pwmIndexB = pwmIndexB == 0 ? 0 : pwmIndexB - 1;
      } else if (cntTransition <= 4 * pwmStepSize) {
        pwmIndexR++;
      } else if (cntTransition <= 5 * pwmStepSize) {
        pwmIndexG = pwmIndexG == 0 ? 0 : pwmIndexG - 1;
      } else if (cntTransition <= 6 * pwmStepSize) {
        pwmIndexB++;
      }
      DelayInter(analogRead(POT) < 4 ? 1 : analogRead(POT) / 4);
    }
  } else if (mode == 2) {
    if (stateSet == 1) {
      cntTransition = cntTransition >= 6 ? 1 : cntTransition + 1;
      if (cntTransition == 1 || cntTransition == 2 || cntTransition == 6) {
        pwmIndexB = pwmStepSize;
      } else {
        pwmIndexB = 0;
      }
      if (cntTransition == 2 || cntTransition == 3 || cntTransition == 4) {
        pwmIndexG = pwmStepSize;
      } else {
        pwmIndexG = 0;
      }
      if (cntTransition == 4 || cntTransition == 5 || cntTransition == 6) {
        pwmIndexR = pwmStepSize;
      } else {
        pwmIndexR = 0;
      }
      DelayInter(analogRead(POT) * 3);
    }
  } else if (mode == 3) {
    if (stateSet == 1) {	//		set3_colorBefore
      if (oldPot/5!=analogRead(POT)/5) {    // /5 : avoid low oscillations
        oldPot=-1;  //Set impossible value to oldPot. Avoid oldPot==analogRead(POT)
        TurnAllLED_Pot(analogRead(POT), &pwmIndexR, &pwmIndexG, &pwmIndexB);
      } else {
        pwmIndexR=set3_colorBeforeR;
        pwmIndexG=set3_colorBeforeG;
        pwmIndexB=set3_colorBeforeB;
      }
    } else if (stateSet == 2) {		//set3_colorAfter
      if (oldPot/5!=analogRead(POT)/5) {
        oldPot=-1;  //Set impossible value to oldPot. Avoid oldPot==analogRead(POT)
        TurnAllLED_Pot(analogRead(POT), &pwmIndexR, &pwmIndexG, &pwmIndexB);
      } else {
        pwmIndexR=set3_colorAfterR;
        pwmIndexG=set3_colorAfterG;
        pwmIndexB=set3_colorAfterB;
      }
    } else if (stateSet == 3) {		//set3_delayNight;
      static int temp_delayNight = 0;
      pwmIndexR=0;
      pwmIndexG=0;
      pwmIndexB=0;
      if (oldPot/5==analogRead(POT)/5) {
        temp_delayNight=set3_delayNight;
      } else if (temp_delayNight != analogRead(POT) / 80) {
        oldPot=-1;  //Set impossible value to oldPot. Avoid oldPot==analogRead(POT)
        temp_delayNight = analogRead(POT) / 80;
//        DelayInter(100);
        TurnLED(TURN_RED);
        DelayInter(200);
        TurnLED(TURN_OFF);
        DelayInter(400);
      }
      TurnLED(TURN_OFF);
      delay(100);
      for (int i = 0; i < temp_delayNight; i += 1) {
        TurnLED(TURN_WHITE);
        DelayInter(250);
        if (temp_delayNight != analogRead(POT) / 80 || digitalRead(BUT_SET) == 1) return;
        TurnLED(TURN_OFF);
        DelayInter(250);
        if (temp_delayNight != analogRead(POT) / 80 || digitalRead(BUT_SET) == 1) return;
      }
      for (int i = 0; i < 20; i += 1) {
        if (temp_delayNight == analogRead(POT) / 80 && digitalRead(BUT_SET) == 0 && digitalRead(BUT_MODE) == 0) DelayInter(50);
        else return;
      }
    }
  }
}

/*
	ShowSettings shows the current settings that you can set using the analog
*/
void ShowSettings(int _settings) {
  int i;
  if (mode == 0) {
    stateSet = (_settings <= 1) ? _settings : 0;
    if (stateSet == 0) {    //Save when return settings to 0
      set0_R = pwmIndexR;
      set0_G = pwmIndexG;
      set0_B = pwmIndexB;
    }
    if (stateSet == 1) {		//All
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
    }
  } else if (mode == 1) {
    stateSet = (_settings <= 1) ? _settings : 0;
    if (stateSet == 0) {
      set1_speed = analogRead(POT) < 4 ? 1 : analogRead(POT) / 4;
    }
    if (stateSet == 1) {
      TurnLED(TURN_OFF);
      delay(150);
      for (i = 0; i < pwmStepSize; i += 1) {
        analogWrite(LED0_R, pwmStep[i]);
        analogWrite(LED0_G, pwmStep[i]);
        analogWrite(LED0_B, pwmStep[i]);
        analogWrite(LED1_R, pwmStep[i]);
        analogWrite(LED1_G, pwmStep[i]);
        analogWrite(LED1_B, pwmStep[i]);
        delay(500 / pwmStepSize);
      }
      for (i = pwmStepSize - 1; i >= 0; i -= 1) {
        analogWrite(LED0_R, pwmStep[i]);
        analogWrite(LED0_G, pwmStep[i]);
        analogWrite(LED0_B, pwmStep[i]);
        analogWrite(LED1_R, pwmStep[i]);
        analogWrite(LED1_G, pwmStep[i]);
        analogWrite(LED1_B, pwmStep[i]);
        delay(500 / pwmStepSize);
      }
      delay(300);
    }
  } else if (mode == 2) {
    stateSet = (_settings <= 1) ? _settings : 0;
    if (stateSet == 0) {
      set2_speed = analogRead(POT) * 3;
    } else if (stateSet == 1) {
      TurnLED(TURN_OFF);
      delay(100);
      for (i = 0; i < 7; i += 1) {
        TurnLED(i);
        delay(50);
        TurnLED(TURN_OFF);
        delay(50);
      }
      delay(300);
    }
  } else if (mode == 3) {
    stateSet = (_settings <= 3) ? _settings : 0;
    if (stateSet == 0) {
      //Save set3_delayNight if it has changed
      if (oldPot != analogRead(POT)) {
        set3_delayNight = analogRead(POT) / 80;
      }
      mode3_nightStarting = millis();
    } else if (stateSet == 1) {	//		set3_colorBefore
      TurnLED(TURN_YELLOW);
      delay(150);
      for (i = pwmStepSize; i >= 0 ; i -= 1) {
        analogWrite(LED0_R, pwmStep[i]);
        analogWrite(LED0_G, pwmStep[i]);
        analogWrite(LED1_R, pwmStep[i]);
        analogWrite(LED1_G, pwmStep[i]);
        delay(500 / pwmStepSize);
      }
      TurnLED(TURN_OFF);
      delay(300);
    } else if (stateSet == 2) {		//set3_colorAfter
      //Save set3_colorBefore if it has changed
      if (oldPot != analogRead(POT)) {
        set3_colorBeforeR = pwmIndexR;
        set3_colorBeforeG = pwmIndexG;
        set3_colorBeforeB = pwmIndexB;
      }
      TurnLED(TURN_OFF);
      delay(150);
      for (i = 0; i < pwmStepSize; i += 1) {
        analogWrite(LED0_B, pwmStep[i]);
        analogWrite(LED0_G, pwmStep[i]);
        analogWrite(LED1_B, pwmStep[i]);
        analogWrite(LED1_G, pwmStep[i]);
        delay(500 / pwmStepSize);
      }
      TurnLED(TURN_OFF);
      delay(300);
    } else if (stateSet == 3) {		//set3_delayNight;
      if (oldPot != analogRead(POT)) {
        set3_colorAfterR = pwmIndexR;
        set3_colorAfterG = pwmIndexG;
        set3_colorAfterB = pwmIndexB;
      }
      TurnLED(TURN_YELLOW);
      delay(150);
      for (i = pwmStepSize; i >= 0 ; i -= 1) {
        analogWrite(LED0_R, pwmStep[i]);
        analogWrite(LED0_G, pwmStep[i]);
        analogWrite(LED1_R, pwmStep[i]);
        analogWrite(LED1_G, pwmStep[i]);
        delay(250 / pwmStepSize);
      }
      TurnLED(TURN_OFF);
      delay(50);
      TurnLED(TURN_WHITE);
      delay(50);
      TurnLED(TURN_OFF);
      delay(50);
      TurnLED(TURN_WHITE);
      delay(50);
      TurnLED(TURN_OFF);
      delay(150);
      for (i = 0; i < pwmStepSize; i += 1) {
        analogWrite(LED0_B, pwmStep[i]);
        analogWrite(LED0_G, pwmStep[i]);
        analogWrite(LED1_B, pwmStep[i]);
        analogWrite(LED1_G, pwmStep[i]);
        delay(500 / pwmStepSize);
      }
      delay(150);
    }
  }
  if (stateSet == 0) {		//Anim leaving settings
    for (i = pwmStepSize - 1; i >= 0; i -= 1) {
      analogWrite(LED0_R, pwmStep[i]);
      analogWrite(LED0_G, pwmStep[i]);
      analogWrite(LED0_B, pwmStep[i]);
      analogWrite(LED1_R, pwmStep[i]);
      analogWrite(LED1_G, pwmStep[i]);
      analogWrite(LED1_B, pwmStep[i]);
      delay(500 / pwmStepSize);
    }
  }
}

/*
	Blink LED to know the mode
*/
void Blink(int _mode) {
  mode = (_mode < 4) ? _mode : 0;
  int i;
  TurnLED(TURN_OFF);
  DelayInter(200);
  for (i = 0; i < mode + 1; i += 1) {
    TurnLED(TURN_WHITE);
    DelayInter(400);
    TurnLED(TURN_OFF);
    DelayInter(400);
  }
  DelayInter(400);
}

/*
	Turn all LED ON or OFF.
	_state : 001:Red, 010:Green, 100:Blue
	IE : 0=Off, 1=Red, 2=Blue, 3=Pink, 4=Green, 5=Yellow, 6=Turquoise, 7=White
*/
void TurnLED(int _state) {
  analogWrite(LED0_R, pwmStep[(_state & 1) == 0 ? 0 : pwmStepSize - 1]);
  analogWrite(LED0_G, pwmStep[(_state & 2) == 0 ? 0 : pwmStepSize - 1]);
  analogWrite(LED0_B, pwmStep[(_state & 4) == 0 ? 0 : pwmStepSize - 1]);
  analogWrite(LED1_R, pwmStep[(_state & 1) == 0 ? 0 : pwmStepSize - 1]);
  analogWrite(LED1_G, pwmStep[(_state & 2) == 0 ? 0 : pwmStepSize - 1]);
  analogWrite(LED1_B, pwmStep[(_state & 4) == 0 ? 0 : pwmStepSize - 1]);
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
  if (_pot != 0 && _pot <= 146)              //B : Increasing blue
  {
    *_ptR = 0;        // *1.75 pour ramener 146 à 255(.5)
    *_ptG = 0;        //Le int prends la valeur entière
    *_ptB = int(_pot * 1.75);  //Tension modifié sur l'anode bleu
  }
  else if (_pot > 146 && _pot <= 292) { //BC=B+↑G    Turquoise. Blue+Increasing green
    *_ptR = 0;
    *_ptG = int((_pot - 146) * 1.75); //G¡
    *_ptB = 255;
  }
  else if (_pot > 292 && _pot <= 438) { //G+↓B   Green+Decreasing blue
    *_ptR = 0;
    *_ptG = 255;
    *_ptB = 255 - int((_pot - 292) * 1.75); //B! reduce blue
  }
  else if (_pot > 438 && _pot <= 584) { //Y=G+↑R    Yellow
    *_ptR = int((_pot - 438) * 1.75); //R↑
    *_ptG = 255;
    *_ptB = 0;
  }
  else if (_pot > 584 && _pot <= 730) { //R+↓G  : Rouge
    *_ptR = 255;
    *_ptG = 255 - int((_pot - 584) * 1.75); //G!
    *_ptB = 0;
  }
  else if (_pot > 730 && _pot <= 876) { //P   Pink
    *_ptR = 255;
    *_ptG = 0;
    *_ptB = int((_pot - 730) * 1.75); //B¡
  }
  else if (_pot > 876 && _pot <= 1022) { //W        White
    *_ptR = 255;
    *_ptG = int((_pot - 876) * 1.75); //G¡
    *_ptB = 255;
  } else {
    *_ptR = 255;
    *_ptG = 255;
    *_ptB = 255;
  }
  //Transform 0→255 to 0→pwmStepSize
  *_ptR = *_ptR * pwmStepSize / 256;
  *_ptG = *_ptG * pwmStepSize / 256;
  *_ptB = *_ptB * pwmStepSize / 256;
}

/*
	Fade LED R→G→B. Use POT as speed and return if settings is clicked.
*/
void FadeLED() {
  int i;
  for (i = 0; i < pwmStepSize; i += 1) {
    analogWrite(LED0_B, pwmStep[i]);
    analogWrite(LED1_B, pwmStep[i]);
    DelayInter(analogRead(POT) < 4 ? 1 : analogRead(POT) / 4);
    if (digitalRead(BUT_SET) == 1) return;
  }
  for (i = pwmStepSize - 1; i >= 0; i -= 1) {
    analogWrite(LED0_G, pwmStep[i]);
    analogWrite(LED1_G, pwmStep[i]);
    DelayInter(analogRead(POT) < 4 ? 1 : analogRead(POT) / 4);
    if (digitalRead(BUT_SET) == 1) return;
  }
  for (i = 0; i < pwmStepSize; i += 1) {
    analogWrite(LED0_R, pwmStep[i]);
    analogWrite(LED1_R, pwmStep[i]);
    DelayInter(analogRead(POT) < 4 ? 1 : analogRead(POT) / 4);
    if (digitalRead(BUT_SET) == 1) return;
  }
  for (i = pwmStepSize - 1; i >= 0; i -= 1) {
    analogWrite(LED0_B, pwmStep[i]);
    analogWrite(LED1_B, pwmStep[i]);
    DelayInter(analogRead(POT) < 4 ? 1 : analogRead(POT) / 4);
    if (digitalRead(BUT_SET) == 1) return;
  }
  for (i = 0; i < pwmStepSize; i += 1) {
    analogWrite(LED0_G, pwmStep[i]);
    analogWrite(LED1_G, pwmStep[i]);
    DelayInter(analogRead(POT) < 4 ? 1 : analogRead(POT) / 4);
    if (digitalRead(BUT_SET) == 1) return;
  }
  for (i = pwmStepSize - 1; i >= 0; i -= 1) {
    analogWrite(LED0_R, pwmStep[i]);
    analogWrite(LED1_R, pwmStep[i]);
    DelayInter(analogRead(POT) < 4 ? 1 : analogRead(POT) / 4);
    if (digitalRead(BUT_SET) == 1) return;
  }
  /*
  	for(int c=0; c<255; c++) {
  		analogWrite(6,c);
  		delay(analogRead(POT)<4?1:analogRead(POT)/4);
  		if(digitalRead(BUT_SET)==1) return;
  	}
  	for(int c=255; c>0; c--) {
  		analogWrite(5,c);
  		delay(analogRead(POT)<4?1:analogRead(POT)/4);
  		if(digitalRead(BUT_SET)==1) return;
  	}
  	for(int c=0; c<255; c++) {
  		analogWrite(9,c);
  		delay(analogRead(POT)<4?1:analogRead(POT)/4);
  		if(digitalRead(BUT_SET)==1) return;
  	}
  	for(int c=255; c>0; c--) {
  		analogWrite(6,c);
  		delay(analogRead(POT)<4?1:analogRead(POT)/4);
  		if(digitalRead(BUT_SET)==1) return;
  	}
  	for(int c=0; c<255; c++) {
  		analogWrite(5,c);
  		delay(analogRead(POT)<4?1:analogRead(POT)/4);
  		if(digitalRead(BUT_SET)==1) return;
  	}
  	for(int c=255; c>0; c--) {
  		analogWrite(9,c);
  		delay(analogRead(POT)<4?1:analogRead(POT)/4);
  		if(digitalRead(BUT_SET)==1) return;
  	}
  */
}

/*
  delay in ms
*/
void DelayInter(unsigned int delay_ms) {
  unsigned int i;
  unsigned int delay_modif = delay_ms / 5;
  if (delay_ms < 5) delay_modif = 1;
  for (i = 0; i < delay_modif; i += 1) {
    delay(5);
    if (digitalRead(BUT_MODE) == 1 || digitalRead(BUT_SET) == 1)
      return;
  }
}

/*
	Update EEPROM from currents values set. (Limites to 100k writes!!!)
*/
void EepromUpdateAll() {
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
