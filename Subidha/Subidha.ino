
#include "parkingSensor.h"
#include "LEDsignal.h"
#include "selectGate.h"
#include "allocatedParking.h"
#include "servoGate.h"



int closestPark;
int gateNo;
int parkingNo;
int SentToDisplay=A1;
int parkVal;




parkingSensor Parking1(2, 3, 1,4);
parkingSensor Parking2(4, 5, 2,3);
parkingSensor Parking3(6, 7, 3,2);
parkingSensor Parking4(8, 9, 4,1);
LEDsignal Park1(22,23,24);
LEDsignal Park2(25,26,27);
LEDsignal Park3(28,29,30);
LEDsignal Park4(31,32,33);
selectGate gate(12,11);
servoGate gateMain(15);
servoGate gateB01(0);
servoGate gateB02(4);
servoGate gateB03(8);
servoGate gateB04(12);  

allocatedParking parkNo(36,37,38,39);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(SentToDisplay, OUTPUT);
  
  pwm.begin();
  
  pwm.setPWMFreq(60);

}

void loop() {

  Serial.println("Please enter gate number: ");


  gateNo= gate.activegate();
  

  Serial.println(gateNo);
if (gateNo==0){
//  return gateNo;
}

  else if (gateNo==1){
    
      Parking1.activeSonar();
  if(Parking1.isFull()){
    if (Parking1.g1distance()<1000){
      Parking1.g1makeInactive();
    }
      
//    Serial.print("parking1 distance ");
//    Serial.println(Parking1.g1distance());
//    Park1.redOn();
  }
  else{
      if (Parking1.g1distance()>999){
       Parking1.g1makeActive(); 
    }
//    Serial.print("parking1 distance ");
//    Serial.println(Parking1.g1distance());
//    Park1.blueOn();

  }
//  delay(1000);
  Parking2.activeSonar();
    if(Parking2.isFull()){
      if (Parking2.g1distance()<1000){
      Parking2.g1makeInactive();
    }
      
//    Serial.print("parking2 distance ");
//    Serial.println(Parking2.g1distance());
//    Park2.redOn();
    
  }
  else{
      if (Parking2.g1distance()>999){
       Parking2.g1makeActive(); 
    }
//    Serial.print("parking2 distance ");
//    Serial.println(Parking2.g1distance());
//    Park2.blueOn();

  }
//  delay(1000);
  Parking3.activeSonar();
    if(Parking3.isFull()){
      if (Parking3.g1distance()<1000){
      Parking3.g1makeInactive();
    }
      
//    Serial.print("parking3 distance ");
//    Serial.println(Parking3.g1distance());
//    Park3.redOn();
  }
  else{
    if (Parking3.g1distance()>999){
       Parking3.g1makeActive(); 
    }
//    Serial.print("parking3 distance ");
//    Serial.println(Parking3.g1distance());
//    Park3.blueOn();

  }
//  delay(1000);

  Parking4.activeSonar();
    if(Parking4.isFull()){
      if (Parking4.g1distance()<1000){
      Parking4.g1makeInactive();
    }
      
//    Serial.print("parking4 distance ");
//    Serial.println(Parking4.g1distance());
//    Park4.redOn();
  }
  else{
    if (Parking4.g1distance()>999){
       Parking4.g1makeActive(); 
    }
//    Serial.print("parking4 distance ");
//    Serial.println(Parking4.g1distance());
//    Park4.blueOn();

  }
//  delay(1000);


  if (Parking1.g1distance()<1000 || Parking2.g1distance()<1000 || Parking3.g1distance()<1000 || Parking4.g1distance()<1000) {
    int closestPark = min(min(Parking1.g1distance(), Parking2.g1distance()), min(Parking3.g1distance(), Parking4.g1distance()));
 
    
    switch (closestPark){
      case 1: 
      parkNo.AloctB01();


        Park1.redOn();
        gateMain.Open();

        delay(5000);

        gateMain.Close();
        delay(5000);
        gateB01.Open();
        delay(5000);

        gateB01.Close();
        Park1.off();
        

        
    break;
   
    case 2: 
       parkNo.AloctB02();


        Park2.redOn();
        gateMain.Open();

        delay(5000);

        gateMain.Close();
        delay(5000);
        gateB02.Open();
        delay(5000);

        gateB02.Close();
        Park2.off();
    break;
    case 3:
      parkNo.AloctB03();


        Park3.redOn();
        gateMain.Open();

        delay(5000);

        gateMain.Close();
        delay(5000);
        gateB03.Open();
        delay(5000);

        gateB03.Close();
        Park3.off();
    break;
    case 4: 
      parkNo.AloctB04();


        Park4.redOn();
        gateMain.Open();

        delay(5000);

        gateMain.Close();
        delay(5000);
        gateB04.Open();
        delay(5000);

        gateB04.Close();
        Park4.off();
    break;


    
    }
  }
    
//   else{
//      parkNo.noAvl();
//    }
 //   Serial.print("Parking is B0");
//    Serial.println(parkVal);
//    delay (2000);
  }



  
  










  
  else if (gateNo==2){
   Parking1.activeSonar();
  if(Parking1.isFull()){
    if (Parking1.g2distance()<1000){
      Parking1.g2makeInactive();
    }
      
//    Serial.print("parking1 distance ");
//    Serial.println(Parking1.g2distance());
    Park1.redOn();
  }
  else{
      if (Parking1.g2distance()>999){
       Parking1.g2makeActive(); 
    }
//    Serial.print("parking1 distance ");
//    Serial.println(Parking1.g2distance());
    Park1.blueOn();

  }
//  delay(1000);
  Parking2.activeSonar();
    if(Parking2.isFull()){
      if (Parking2.g2distance()<1000){
      Parking2.g2makeInactive();
    }
      
//    Serial.print("parking2 distance ");
//    Serial.println(Parking2.g2distance());
    Park2.redOn();
    
  }
  else{
      if (Parking2.g2distance()>999){
       Parking2.g2makeActive(); 
    }
//    Serial.print("parking2 distance ");
//    Serial.println(Parking2.g2distance());
    Park2.blueOn();

  }
//  delay(1000);
  Parking3.activeSonar();
    if(Parking3.isFull()){
      if (Parking3.g2distance()<1000){
      Parking3.g2makeInactive();
    }
      
//    Serial.print("parking3 distance ");
//    Serial.println(Parking3.g2distance());
    Park3.redOn();
  }
  else{
    if (Parking3.g2distance()>999){
       Parking3.g2makeActive(); 
    }
//    Serial.print("parking3 distance ");
//    Serial.println(Parking3.g2distance());
    Park3.blueOn();

  }
//  delay(1000);

  Parking4.activeSonar();
    if(Parking4.isFull()){
      if (Parking4.g2distance()<1000){
      Parking4.g2makeInactive();
    }
      
//    Serial.print("parking4 distance ");
//    Serial.println(Parking4.g2distance());
//    Park4.redOn();
  }
  else{
    if (Parking4.g2distance()>999){
       Parking4.g2makeActive(); 
    }
//    Serial.print("parking4 distance ");
//    Serial.println(Parking4.g2distance());
//    Park4.blueOn();

  }
//  delay(1000);



  if (Parking1.g2distance()<1000 || Parking2.g2distance()<1000 || Parking3.g2distance()<1000 || Parking4.g2distance()<1000) {
    int closestPark = min(min(Parking1.g2distance(), Parking2.g2distance()), min(Parking3.g2distance(), Parking4.g2distance()));

    
    
    switch (closestPark){
      case 4:
    
      parkNo.AloctB01();


        Park1.redOn();
        gateMain.Open();

        delay(1000);

        gateMain.Close();
        delay(500);
        gateB01.Open();
        delay(500);

        gateB01.Close();
        Park1.off();
   break;
    case 3:
      parkNo.AloctB02();


        Park2.redOn();
        gateMain.Open();

        delay(5000);

        gateMain.Close();
        delay(5000);
        gateB02.Open();
        delay(5000);

        gateB02.Close();
        Park2.off();
    break;
    case 2:
      parkNo.AloctB03();


        Park3.redOn();
        gateMain.Open();

        delay(5000);

        gateMain.Close();
        delay(5000);
        gateB03.Open();
        delay(5000);

        gateB03.Close();
        Park3.off();
    break;
    case 1:
      parkNo.AloctB04();


        Park4.redOn();
        gateMain.Open();

        delay(5000);

        gateMain.Close();
        delay(5000);
        gateB04.Open();
        delay(5000);

        gateB04.Close();
        Park4.off();
    break;

    
 

  }


  }
//    else{
//      parkNo.noAvl();
//    }
//  delay (2000);
  }
//      Serial.println(parkVal);
  // put your main code here, to run repeatedly:
//Serial.parseInt();

}
