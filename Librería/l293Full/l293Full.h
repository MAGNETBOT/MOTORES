/*
  l293Full.h - Librería para controlar el puente H en modo FULL (l293B)
  Creado por Roboteam para el MAGNETBOT, Febrero,9, 2016.
  Librería de código abierto.
*/
#ifndef l293Full_h
#define l293Full_h

#include "Arduino.h"
#include "state.h"

class l293Full
{
  public:
	l293Full(int pin1,int pin2,int pin3,int pin4,int pin5,int pin6);
    void motorsUp();   
    void motorsDown();
    state checkState(state s1);
	void M1_F(int dc);
    void M1_R(int dc);
    void M2_F(int dc);
    void M2_R(int dc);
    void forward(int dc);
    void reverse(int dc);
    void spinRight(int dc);
    void spinLeft(int dc);
    void brakeM1(int dc);
	void brakeM2(int dc);
	void brake(int dc);
  
  private:
    int _logic1=0;
    int _logic2=0;
    int _logic3=0;
    int _logic4=0;
    int _en1=0;
    int _en2=0;
	state _state1= FORWARD;
	state _state2= FORWARD;
};

#endif
