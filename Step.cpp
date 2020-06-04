
#include "Step.h"
#include "Arduino.h"
Step::Step(byte enPin, byte stepPin, byte dirPin){
    pinMode(enPin, OUTPUT); 
    _enPin = enPin; 
    pinMode(stepPin, OUTPUT);
    _stepPin = stepPin;
    pinMode(dirPin, OUTPUT);
    _dirPin = dirPin;  
    _currentPos = 0;
    _targetPos = 0;
    _lastPos = 0;
}

 long Step::targetPos(){
    return _targetPos;
}
 long Step::currentPos(){
    return _currentPos;
}
void Step::runStep(){
    
    if(_dirState==1 )_lastPos++;
    else _lastPos--;
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_stepPin, LOW);
}
bool Step::setDir(int State){
    _dirState = State;
    digitalWrite(_dirPin, State);
    return true;
}
bool Step::setEnable(int State){
    this->_enState = State;
    digitalWrite(this->_enPin, State);
    return true;
}
bool Step::getDir(){
    return _dirState;
}
bool Step::getEnable(){
    return _enState;
}
bool Step::setTargetPos(long Pos){
    
    _targetPos = Pos;
    Serial.print(_lastPos);
    Serial.print(" ");
    Serial.println(_targetPos);
    if(_targetPos > _lastPos ) {
        _dirState = 1;
        //Serial.println("ok");
    }
    else {
        //Serial.println("no");
        _dirState =0;
    }
    digitalWrite(_dirPin, _dirState);
    return true;
}
bool Step::setLastPos(long Pos){
    _lastPos = Pos;
}
long Step::distanceToGo(){
    
    return (_targetPos - _lastPos>0)? _targetPos - _lastPos : _lastPos - _targetPos;
}
long Step::getVecl(){
    int distance = (_targetPos - _lastPos>0)? _targetPos - _lastPos : _lastPos - _targetPos;
    if(distanceToGo() > distance/2)
        return map(distanceToGo(), distance,0,  1500UL, 100UL);
    else 
        return map(distanceToGo(), distance,0,  100UL, 1500UL);
}
long Step::lastPos(){
    return _lastPos;
}
