#include <l293Full.h>
#define LOGIC1  31
#define LOGIC2  11
#define LOGIC3  39
#define LOGIC4  10
#define ENABLE1 33
#define ENABLE2 37

l293Full myMotor(LOGIC1,LOGIC2,LOGIC3,LOGIC4,ENABLE1,ENABLE2);
int DC=255;
int flag=1;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
 if(flag==1){
  myMotor.motorsUp();
  delay(3000);
  myMotor.reverse(DC);
  delay(3000);
  myMotor.forward(DC);
  delay(3000);
  myMotor.brake(DC);
  flag=0;
 }
 DC=255;
}
