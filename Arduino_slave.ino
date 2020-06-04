#include <WorkScheduler.h>
#include <Timer.h>
#include "Step.h"
#include <Servo.h>
Servo myservo;
WorkScheduler *motor1, *motor2, *motor3, *motor4, *motor5;

Step Step1(38,A0,A1); // enState, en, step, dir X
Step Step2(24,26,28); // enState, en, step, dir E0
Step Step3(A8,46,48); // enState, en, step, dir Z 
Step Step4(30,34,36); // enState, en, step, dir E1
Step Step5(A2,A6,A7); // enState, en, step, dir Y 
int  pos;
float angle[4][5] = {
  {0,0,0,0,5},
  {200,300,300,9,10},
  {0,0,-400,-200,15},
  {200,-100,0,500,20},
};
int base=0, first=0, mainH=0, grip=0;
byte endPoint = 0;
void runStep1(){Step1.runStep();}
void runStep2(){Step2.runStep();}
void runStep3(){Step3.runStep();}
void process(){
  endPoint = 0;
  Timer::getInstance()->Update();
  while (endPoint <=3){
  Timer::getInstance()->Update();
  if (Step1.distanceToGo()==0 &&Step2.distanceToGo()==0&& Step3.distanceToGo()==0){
      
      Step1.setLastPos(Step1.targetPos());
      Step1.setTargetPos(round(3200UL*angle[endPoint][0]/360));
      
      Step2.setLastPos(Step2.targetPos());
      Step2.setTargetPos(round(3200UL*angle[endPoint][1]/360));
      
      Step3.setLastPos(Step3.targetPos());
      Step3.setTargetPos(round(3200UL*angle[endPoint][2]/360));
      
      endPoint ++ ; 
  }
  if (Step1.distanceToGo()) motor1->Update(Step1.getVecl());
  if (Step2.distanceToGo()) motor2->Update(Step2.getVecl());
  if (Step3.distanceToGo()) motor3->Update(Step3.getVecl());
  Timer::getInstance()->resetTick();
  }
  Timer::getInstance()->resetTick();
}
void setup()
{
  myservo.attach(4);
  Serial.begin(9600);
  Serial1.begin(9600);
  Timer::getInstance()->initialize();
  Step1.setEnable(0);   
  Step2.setEnable(1);   
  Step3.setEnable(0);   
  motor1 = new WorkScheduler(1000UL,runStep1);
  motor2 = new WorkScheduler(1000UL,runStep2);
  motor3 = new WorkScheduler(1000UL,runStep3);


}
void loop()
{
  Timer::getInstance()->Update();
  /*
*/
  if (Serial1.available()>0){
    String inString = "";
    char c = Serial1.read();
    while (c != '\n'){
      if ((isAscii(c)) || (c==' ')){
        inString+= c;
        //Serial.write(c);
      }
     c = Serial1.read();
    } 
  if (inString[2] == '-') pos = -1* (inString.substring(3, inString.length())).toInt();
  else  pos = (inString.substring(2, inString.length())).toInt();
  if (inString[0] == 'H' ){
      Step3.setLastPos(Step3.targetPos());
      Step3.setTargetPos(round(3200L*pos/360));
  }
  if (inString[0] == 'B' ){
      Step1.setLastPos(Step1.targetPos());
      Step1.setTargetPos(round(3200L*pos/360));
  }
  if (inString[0] == 'F' ){
      Step2.setLastPos(Step2.targetPos());
      Step2.setTargetPos(round(3200L*pos/360));
  }
  if (inString[0] == 'G' ){
      if(pos==0) myservo.write(0);
      else myservo.write(150);
  }
  if (inString[0] =='A') {
      if (pos==1) process();   
  }
  Serial.println(pos);
  }
  while (Step1.distanceToGo())
  {
    Timer::getInstance()->Update();
    motor1->Update(Step1.getVecl());
    Timer::getInstance()->resetTick();
  }
  while (Step2.distanceToGo())
  {
    Timer::getInstance()->Update();
    motor2->Update(Step2.getVecl());
    Timer::getInstance()->resetTick();
  }
  while (Step3.distanceToGo())
  {
    Timer::getInstance()->Update();
    motor3->Update(Step3.getVecl());
    Timer::getInstance()->resetTick();
  }
  
  Timer::getInstance()->resetTick();
}
