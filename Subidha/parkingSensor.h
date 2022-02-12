

class parkingSensor {


  
  int _trig;
  int _echo;
  int _traveltime;
  int _traveldistance;
  int _lastdistance;
  int _parkingFlag;
  int _gate1distance;
  int _gate2distance;

  public:
   parkingSensor(int trig, int  echo, int gate1distance, int gate2distance){
    _trig=trig;
    _echo=echo;
    _gate1distance=gate1distance;
    _gate2distance=gate2distance;


    pinMode(_trig,OUTPUT);
    pinMode(_echo,INPUT);
    
   }


   void activeSonar() {
    digitalWrite (_trig,LOW);
    delayMicroseconds(10);
    digitalWrite (_trig,HIGH);
    delayMicroseconds(10);
    digitalWrite (_trig,LOW);
    _traveltime=pulseIn(_echo,HIGH);

    delay(25);

   _traveldistance = ((_traveltime/2)* 0.0343)/15;    
         
   }



//   int isEmepty(){

//        if (_traveldistance==1){
//      Serial.print(_traveldistance);
//      Serial.println("  Emepty"); 
      
//    }
//  return _traveldistance;
//   }




   


 bool isFull(){
 
  return !_traveldistance;
 }
   
int g1distance(){
  return _gate1distance;
}

int g2distance(){
  return _gate2distance;
}

int g1makeInactive(){
   _gate1distance += 1000;
   return _gate1distance;
}

int g2makeInactive(){
   _gate2distance += 1000;
   return _gate2distance;
}



int g1makeActive(){
   _gate1distance -= 1000;
   return _gate1distance;
}

int g2makeActive(){
   _gate2distance -= 1000;
   return _gate2distance;
}

 
};
