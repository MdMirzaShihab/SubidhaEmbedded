

class LEDsignal {


  
  int _red;
  int _green;
  int _blue;

  public: 
  LEDsignal(int red, int green, int blue) {
    _red=red;
    _green=green;
    _blue=blue;

    
    pinMode(_red, OUTPUT);
    pinMode(_green, OUTPUT);
    pinMode(_blue, OUTPUT);
  }


    
    
    void redOn(){
      digitalWrite(_red, HIGH);
      digitalWrite(_green, LOW);
      digitalWrite(_blue, LOW);
     
    }

//    void greenOn(){
//      digitalWrite(_red, LOW);
//      digitalWrite(_green, HIGH);
//      digitalWrite(_blue, LOW);
//      
//
//     
//    }

    void blueOn(){
      digitalWrite(_red, LOW);
      digitalWrite(_green, LOW);
      digitalWrite(_blue, HIGH);
    }


    void off(){
      digitalWrite(_red, LOW);
      digitalWrite(_green, LOW);
      digitalWrite(_blue, LOW);
    }

};
