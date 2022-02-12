
class allocatedParking {


  
  int _park1;
  int _park2;
  int _park3;
  int _park4;
  int gateValue;
  public:
   allocatedParking(int park1, int  park2, int park3, int park4){
    _park1=park1;
    _park2=park2;
    _park3=park3;
    _park4=park4;


    pinMode(_park1,OUTPUT);
    pinMode(_park2,OUTPUT);
    pinMode(_park3,OUTPUT);
    pinMode(_park4,OUTPUT);
    
   }

  void AloctB01(){
      digitalWrite(_park1, HIGH);
      digitalWrite(_park2, LOW);
      digitalWrite(_park3, LOW);
      digitalWrite(_park4, LOW);
      Serial.println("B01");
  }
  void AloctB02(){
      digitalWrite(_park1, LOW);
      digitalWrite(_park2, HIGH);
      digitalWrite(_park3, LOW);
      digitalWrite(_park4, LOW);
      Serial.println("B02");
  }

  void AloctB03(){
      digitalWrite(_park1, LOW);
      digitalWrite(_park2, LOW);
      digitalWrite(_park3, HIGH);
      digitalWrite(_park4, LOW);
      Serial.println("B03");
  }
  void AloctB04(){
      digitalWrite(_park1, LOW);
      digitalWrite(_park2, LOW);
      digitalWrite(_park3, LOW);
      digitalWrite(_park4, HIGH);
      Serial.println("B04");
  }

    void noAvl(){
      digitalWrite(_park1, LOW);
      digitalWrite(_park2, LOW);
      digitalWrite(_park3, LOW);
      digitalWrite(_park4, LOW);
      Serial.println("Parking Full");
  }
  

};
