
class selectGate {


  
  int _gate1;
  int _gate2;
  int gate1read;
  int gate2read;
  int gateValue;

  public: 
  selectGate(int gate1, int gate2) {
    _gate1=gate1;
    _gate2=gate2;

    
    pinMode(_gate1, INPUT);
    pinMode(_gate2, INPUT);
  }


  int activegate(){

    int gate1read = digitalRead(_gate1);
    int gate2read = digitalRead(_gate2);
    if (gate1read == 1)
    {
      gateValue = 1;
    }

    else if (gate2read == 1)
    {
      gateValue = 2;
    }

    else
    {
      gateValue = 0;
    }

    
    return gateValue;
  }
  

};
