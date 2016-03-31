/*
  l293Full.cpp - Librería para controlar el puente H en modo FULL (l293B)
  Creado por Roboteam para el MAGNETBOT, Febrero,9, 2016.
  Librería de código abierto.
*/

#include "Arduino.h"
#include "l293Full.h"
#include "state.h"


l293Full::l293Full(int pin1,int pin2,int pin3,int pin4,int pin5,int pin6)
{
  pinMode(pin1, OUTPUT);
  _logic1 = pin1;
  pinMode(pin2, OUTPUT);
  _logic2 = pin2;
   pinMode(pin3, OUTPUT);
  _logic3 = pin3;
   pinMode(pin4, OUTPUT);
  _logic4 = pin4;
   pinMode(pin5, OUTPUT);
  _en1 = pin5;
   pinMode(pin6, OUTPUT);
  _en2 = pin6;
  duty_cycle=255;
  duty_cycle2=255;
  dutyMax1=255;
  dutyMax2=255;
  step=4;
  wait=2;
 
}

void l293Full::motorsUp(){
  digitalWrite(_en1,HIGH);
  digitalWrite(_en2,HIGH);
}

void l293Full::motorsDown(){
  digitalWrite(_en1,LOW);
  digitalWrite(_en2,LOW);
}


void l293Full::M1_F(int dc){
	int DutyCycle=dc;
	digitalWrite(_logic1,LOW);
	if (DutyCycle >=dutyMax1-step){
		analogWrite(_logic2,dutyMax1);
		duty_cycle=dutyMax1;
	}
	else{
		analogWrite(_logic2,DutyCycle);
		delay(wait);
		M1_F(dc+step);
	}
	_state1= FORWARD;
}

void l293Full::M2_F(int dc){
	int DutyCycle=dc;
	digitalWrite(_logic3,LOW);
	if (DutyCycle >=dutyMax2-step){
		analogWrite(_logic4,dutyMax2);
		duty_cycle2=dutyMax2;
	}
	else{
		analogWrite(_logic4,DutyCycle);
		delay(wait);
		M2_F(dc+step);
	}
	_state2= FORWARD;
}

void l293Full::M1_R(int dc){
   int DutyCycle=255-dc;
   int CMax=255-dutyMax1;
   digitalWrite(_logic1,HIGH);
   if (DutyCycle <= CMax+step){
		analogWrite(_logic2,CMax);
		duty_cycle=dutyMax1;
	}
	else{
		analogWrite(_logic2,DutyCycle);
		delay(wait);
		M1_R(dc+step);
	}
	_state1= REVERSE;
}

void l293Full::M2_R(int dc){
	int DutyCycle=255-dc;;
	int CMax=255-dutyMax2;
	digitalWrite(_logic3,HIGH);
	if (DutyCycle <=CMax+step){
		analogWrite(_logic4,CMax);
		duty_cycle2=dutyMax2;
	}
	else{
		analogWrite(_logic4,DutyCycle);
		delay(wait);
		M2_R(dc+step);
	}
   _state2= REVERSE;
}

void l293Full::forward(int dc){
	if(_state1==REVERSE || _state2==REVERSE){
		brake(dc);
	}
	delay(wait);
	_state1= FORWARD;
	_state2= FORWARD;
	int DutyCycle=dc;
	bool flagOne=false;
	bool flagTwo=false;
	digitalWrite(_logic1,LOW);
	digitalWrite(_logic3,LOW);
	if (DutyCycle >=dutyMax2-step){
		analogWrite(_logic4,dutyMax2);
		duty_cycle2=dutyMax2;
		flagTwo=true;
	}
	if (DutyCycle >=dutyMax1-step){
		analogWrite(_logic2,dutyMax1);
		duty_cycle=dutyMax1;
		flagOne=true;
	}
	if(!flagTwo){analogWrite(_logic4,DutyCycle);}
	if(!flagOne){analogWrite(_logic2,DutyCycle);}
	if(!flagOne || !flagTwo){
		delay(wait);
		forward(dc+step);
	}
}


void l293Full::reverse(int dc){
   if(_state1==FORWARD || _state2==FORWARD){
		brake(dc);
	}
	delay(wait);
	_state1= REVERSE;
	_state2= REVERSE;
	int DutyCycle=255-dc;;
	int CMax=255-dutyMax1;
	int CMax2=255-dutyMax2;
	bool flagOne=false;
	bool flagTwo=false;
	digitalWrite(_logic1,HIGH);
	digitalWrite(_logic3,HIGH);
	if (DutyCycle<=CMax2+step){
		analogWrite(_logic4,CMax2);
		duty_cycle2=dutyMax2;
		flagTwo=true;
	}
	if (DutyCycle<=CMax+step){
		analogWrite(_logic2,CMax);
		duty_cycle=dutyMax1;
		flagOne=true;
	}
	if(!flagOne){analogWrite(_logic2,DutyCycle);}
	if(!flagTwo){analogWrite(_logic4,DutyCycle);}
	
	if(!flagOne || !flagTwo){
		delay(wait);
		reverse(dc+step);
	}
}


void l293Full::spinRight (int dc){
     if(_state1==REVERSE || _state2== FORWARD){
	   brake(dc);
	} 
	delay(wait);
	_state1= FORWARD;
	_state2= REVERSE;
	int DutyCycle=dc;
	int DutyCycle2=255-dc;;
	int CMax=255-dutyMax2;
	bool flagOne=false;
	bool flagTwo=false;
	digitalWrite(_logic1,LOW);
	digitalWrite(_logic3,HIGH);
	if (DutyCycle>=dutyMax1-step){
		analogWrite(_logic2,dutyMax1);
		duty_cycle=dutyMax1;
		flagOne=true;
	}
	if (DutyCycle2<=CMax+step){
		analogWrite(_logic4,CMax);
		duty_cycle2=dutyMax2;
		flagTwo=true;
	}
	if(!flagOne){analogWrite(_logic2,DutyCycle);}
	if(!flagTwo){analogWrite(_logic4,DutyCycle2);}
	
	if(!flagOne || !flagTwo){
		delay(wait);
		spinRight(dc+step);
	}
}


void l293Full::spinLeft(int dc){
    if(_state1==FORWARD || _state2== REVERSE){
	   brake(dc);
	} 
	delay(wait);
	_state1= REVERSE;
	_state2= FORWARD;
	int DutyCycle=255-dc;
	int DutyCycle2=dc;
	int CMax=255-dutyMax1;
	bool flagOne=false;
	bool flagTwo=false;
	digitalWrite(_logic1,HIGH);
	digitalWrite(_logic3,LOW);
	if (DutyCycle<=CMax+step){
		analogWrite(_logic2,CMax);
		duty_cycle=dutyMax1;
		flagOne=true;
	}
	if (DutyCycle2>=dutyMax2-step){
		analogWrite(_logic4,dutyMax2);
		duty_cycle2=dutyMax2;
		flagTwo=true;
	}
	if(!flagOne){analogWrite(_logic2,DutyCycle);}
	if(!flagTwo){analogWrite(_logic4,DutyCycle2);}
	
	if(!flagOne || !flagTwo){
		delay(wait);
		spinLeft(dc+step);
	}
}

void l293Full::brakeM1(int dc){
	
	if(_state1==FORWARD){
		int DutyCycle=dc;
		if (DutyCycle <=step){
			analogWrite(_logic2,0);
			duty_cycle=0;
		}
		else{
			analogWrite(_logic2,DutyCycle);
			delay(wait);
			brakeM1(dc-step);
		}
	}
	else{
		int DutyCycle= 255-dc;
		if (DutyCycle >=255-step){
			analogWrite(_logic2,255);
			duty_cycle=0;
		}
		else{
			analogWrite(_logic2,DutyCycle);
			delay(wait);
			brakeM1(dc-step);
		}
	}
}

void l293Full::brakeM2(int dc){
	
	if(_state2==FORWARD){
		int DutyCycle=dc;
		if (DutyCycle <=step){
			analogWrite(_logic4,0);
			duty_cycle2=0;
		}
		else{
			analogWrite(_logic4,DutyCycle);
			delay(wait);
			brakeM2(dc-step);
		}
	}
	else{
		int DutyCycle= 255-dc;
		if (DutyCycle >=255-step){
			analogWrite(_logic4,255);
			duty_cycle2=0;
		}
		else{
			analogWrite(_logic4,DutyCycle);
			delay(wait);
			brakeM2(dc-step);
		}
	}
}

void l293Full::brake(int dc){
	
	if(_state1==FORWARD && _state2==FORWARD){
		int DutyCycle=dc;
		if (DutyCycle <=step){
			analogWrite(_logic2,0);
			analogWrite(_logic4,0);
			duty_cycle=0;
			duty_cycle2=0;
		}
		else{
			analogWrite(_logic2,DutyCycle);
			analogWrite(_logic4,DutyCycle);
			delay(wait);
			brake(dc-step);
		}
	}
	else if(_state1==REVERSE && _state2==REVERSE){
		int DutyCycle= 255-dc;
		if (DutyCycle >=255-step){
			analogWrite(_logic2,255);
			analogWrite(_logic4,255);
			duty_cycle=0;
			duty_cycle2=0;
		}
		else{
			analogWrite(_logic2,DutyCycle);
			analogWrite(_logic4,DutyCycle);
			delay(wait);
			brake(dc-step);
		}
	}
	else if(_state1==REVERSE && _state2==FORWARD){
		int DutyCycle= 255-dc;
		int DutyCycle2=dc;
		if (DutyCycle >=255-step || DutyCycle2 <=step){
			analogWrite(_logic2,255);
			analogWrite(_logic4,0);
			duty_cycle2=0;
			duty_cycle=0;
		}
		else{
			analogWrite(_logic2,DutyCycle);
			analogWrite(_logic4,DutyCycle2);
			delay(wait);
			brake(dc-step);
		}
	}	
	else if(_state1==FORWARD && _state2==REVERSE){
		int DutyCycle=dc;
		int DutyCycle2= 255-dc;
		if (DutyCycle2 >=255-step || DutyCycle <=step){
			analogWrite(_logic4,255);
			analogWrite(_logic2,0);
			duty_cycle2=0;
			duty_cycle=0;
		}
		else{
			analogWrite(_logic2,DutyCycle);
			analogWrite(_logic4,DutyCycle2);
			delay(wait);
			brake(dc-step);
		}
	}
}