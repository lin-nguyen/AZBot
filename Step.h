#include <Arduino.h>

class Step{
public: 
  Step(byte enPin, byte stepPin, byte dirPin);
  void moveTo(unsigned long pos);
   long targetPos();
   long currentPos();
   long lastPos();
  //void (*func)();
  void runStep();
  bool setDir(int State);
  bool setEnable(int State);
  bool getDir();
  bool getEnable();
  bool setTargetPos(long Pos);
  bool setLastPos(long Pos);
  long distanceToGo();
  long getVecl();
private: 
  long _lastPos; 
  long _targetPos;
  long _currentPos;
  int _enPin ; int _stepPin; int _dirPin; 
  int _enState; int _dirState;
};
