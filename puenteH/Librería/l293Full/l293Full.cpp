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
}

void l293Full::motorsUp(){
  digitalWrite(_en1,HIGH);
  digitalWrite(_en2,HIGH);
}

void l293Full::motorsDown(){
  digitalWrite(_en1,LOW);
  digitalWrite(_en2,LOW);
}

state l293Full::checkState(state s1){
	return s1;
}

void l293Full::M1_F(int dc){
   int DutyCycle=dc;
   digitalWrite(_logic1,LOW);
   analogWrite(_logic2,DutyCycle);
   
	if (DutyCycle >=253){
		analogWrite(_logic2,255);
		duty_cycle=255;
	}
	else{
		analogWrite(_logic2,DutyCycle);
		delay(2);
		M1_F(DutyCycle+2);
	}
	_state1= FORWARD;
}

void l293Full::M2_F(int dc){
   int DutyCycle=dc;
   digitalWrite(_logic3,LOW);
   analogWrite(_logic4,DutyCycle);
	if (DutyCycle >=253){
		analogWrite(_logic4,255);
		duty_cycle=255;
	}
	else{
		analogWrite(_logic4,DutyCycle);
		delay(2);
		M2_F(DutyCycle+2);
	}
   _state2= FORWARD;
}

void l293Full::M1_R(int dc){
   int DutyCycle=255-dc;
   digitalWrite(_logic1,HIGH);
   analogWrite(_logic2,DutyCycle);
   
	if (DutyCycle <=2){
		analogWrite(_logic2,0);
		duty_cycle=255;
	}
	else{
		analogWrite(_logic2,DutyCycle);
		delay(2);
		M1_R(DutyCycle-2);
	}
   _state1= REVERSE;
}

void l293Full::M2_R(int dc){
   int DutyCycle=255-dc;;
   digitalWrite(_logic3,HIGH);
   analogWrite(_logic4,DutyCycle);
   
	if (DutyCycle <=2){
		analogWrite(_logic4,0);
		duty_cycle=255;
	}
	else{
		analogWrite(_logic4,DutyCycle);
		delay(2);
		M2_R(DutyCycle-2);
	}
   _state2= REVERSE;
}

void l293Full::forward(int dc){
   if(_state1==REVERSE || _state2== REVERSE){
	   brakeM1(dc);
	   brakeM2(dc);
   }
   delay(10);
   M1_F(dc);
   M2_F(dc); 
}


void l293Full::reverse(int dc){
    if(_state1==FORWARD || _state2== FORWARD){
	   brakeM1(dc);
	   brakeM2(dc);
   }
   delay(10);
   M1_R(dc);
   M2_R(dc); 
}


void l293Full::spinRight (int dc){
     if(_state1==REVERSE || _state2== FORWARD){
	   brakeM1(dc);
	   brakeM2(dc);
   } 
   delay(10);
   M1_F(dc);
   M2_R(dc); 
}


void l293Full::spinLeft(int dc){
    if(_state1==FORWARD|| _state2== REVERSE){
	   brakeM1(dc);
	   brakeM2(dc);
   } 
   delay(10);
   M1_R(dc);
   M2_F(dc); 
}


void l293Full::brakeM1(int dc){
	
	if(_state1==FORWARD){
		int DutyCycle=dc;
		if (DutyCycle <=2){
			analogWrite(_logic2,0);
			duty_cycle=0;
		}
		else{
			analogWrite(_logic2,DutyCycle);
			delay(2);
			brakeM1(DutyCycle-2);
		}
	}
	else{
		int DutyCycle= 255-dc;
		if (DutyCycle >=253){
			analogWrite(_logic2,255);
			duty_cycle=0;
		}
		else{
			analogWrite(_logic2,DutyCycle);
			delay(2);
			brakeM1(DutyCycle+2);
		}
	}
}

void l293Full::brakeM2(int dc){
	
	if(_state2==FORWARD){
		int DutyCycle=dc;
		if (DutyCycle <=2){
			analogWrite(_logic4,0);
			duty_cycle=0;
		}
		else{
			analogWrite(_logic4,DutyCycle);
			delay(2);
			brakeM2(DutyCycle-2);
		}
	}
	else{
		int DutyCycle= 255-DutyCycle;
		if (DutyCycle >=253){
			analogWrite(_logic4,255);
			duty_cycle=0;
		}
		else{
			analogWrite(_logic4,DutyCycle);
			delay(2);
			brakeM2(DutyCycle+2);
		}
	}
}

void l293Full::brake(int dc){
		brakeM1(dc);
		brakeM2(dc);
}
	