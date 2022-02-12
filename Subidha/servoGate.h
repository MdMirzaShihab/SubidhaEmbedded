#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  90 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)


uint8_t servonum = 0;

 class servoGate {


int _motor;

   public: 
  servoGate(int motor) {
    _motor = motor;
  }

  void Open(){
        pwm.setPWM(_motor, 0, 145 );

  }

    void Close(){
        pwm.setPWM(_motor, 0, 375 );
  }
 };
