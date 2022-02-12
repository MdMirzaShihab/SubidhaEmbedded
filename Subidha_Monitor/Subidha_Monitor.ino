/* Display Subsystem for Smart Parking System Subidha */

#include <SPFD5408_Adafruit_GFX.h>     // Core graphics library
#include <SPFD5408_Adafruit_tftLCD.h>  // Hardware-specific library
#include <SPFD5408_TouchScreen.h>      // Touch Screen Library




#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif


#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin


// Calibrate values
#define TS_MINX 125
#define TS_MINY 85
#define TS_MAXX 965
#define TS_MAXY 905

// Presser optimizing
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional 
#define LCD_RESET A4

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Assigned human-readable names to some common 16-bit color values:
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define White           0xFFFF      /* 255, 255, 255 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


int readParking;
int g1out = A5;       // To communicate with core
int g2out = 8;       // To communicate with core
int park1 = 10;      // To communicate with core
int park2 = 11;       // To communicate with core
int park3 = 12;       // To communicate with core
int park4 = 13;       // To communicate with core
String parkNo;        // Variable to set allocated value on ClosestGate() function






void setup(void) {

  Serial.begin(9600);
  
  tft.reset();                         //Shield launching
  tft.begin(0x9341);                 
  tft.setRotation(1);                  //Rotation 0-3

                             //button parking gate2

  homepage(); 


  
}



void loop()
{



  TSPoint p = ts.getPoint();       //checking if the user touched the screen

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) { //p.z means the pressure value so if the touch wants to be detected
                                               // it pressure should be in this range (it's enough)

    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());    //x and y positions of the touch so the program know the postion where the user has pressed
    
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());;

    

    if(p.y > 80 && p.y < 135 && p.x >70 && p.x <120){   //This concerns the red rectangle we draw before if the "y" position is between (20-100) and "x" position is between (40-120)
        tft.fillScreen(Black);

        


      

        //delay(5000);
        digitalWrite(g1out, HIGH);
        digitalWrite(g2out, LOW);

//        delay(5000);

        park();
        
        if (ClosestGate()=="Full"){
          parkFull();
          delay (2500);
          parkNotiF();
          serial();

        }
        else
        {
          parkSpot();
          delay (2500);
          parkNoti();
          serial();
        }
        
        waitOneTouch();
        homepage();
        

    }

     else if(p.x > 70 && p.x < 120 && p.y >150 && p.y <205){






      
        
        digitalWrite(g1out, LOW);
        digitalWrite(g2out, HIGH);

      
        
//        delay(5000);
        park();
        
        if (ClosestGate()=="Full"){
          parkFull();
          delay (2500);
          parkNotiF();
          serial();
        }
        else
        {
          parkSpot();
          delay (2500);
          parkNoti();
          serial();
        }
        waitOneTouch();
        homepage();
        
        
    }
  }



}

void homepage() {

 
  digitalWrite(g1out, LOW);
  digitalWrite(g2out, LOW);
  
  tft.fillScreen(Black);
  tft.drawRect(0, 0, 320, 240, DarkCyan);            // border
  tft.drawRect(2, 2, 316, 236, Olive);               // border
  tft.drawRect(4, 4, 312, 232, DarkCyan);            // border

  
  tft.setCursor(100,15);                      //Welcome text
  tft.setTextColor(LightGrey);                //Welcome text
  tft.setTextSize(2);                         //Welcome text
  tft.print("Welcome to");                    //Welcome text
  tft.setCursor(50,35);                       //Welcome text
  tft.setTextColor(Magenta);                  //Welcome text
  tft.setTextSize(3);                         //Welcome text
  tft.print("Subidha");                       //Welcome text
  tft.setCursor(180,50);                      //Welcome text
  tft.setTextColor(Magenta);                  //Welcome text
  tft.setTextSize(1);                         //Welcome text
  tft.print("Parking soluion");               //Welcome text

  
  tft.fillRect(20,80,280,140,DarkGrey);     //bottom part
  tft.fillRect(25,85,270,130,Navy);         //bottom part

  
  tft.setCursor(90,100);                       //parking box text
  tft.setTextColor(GreenYellow);               //parking box text
  tft.setTextSize(1);                          //parking box text
  tft.print("Please Select The Gate");         //parking box text
  tft.setCursor(110,115);                      //parking box text
  tft.setTextColor(GreenYellow);               //parking box text
  tft.setTextSize(1);                          //parking box text 
  tft.print("You Want To Go :");               //parking box text

  
  tft.fillRoundRect(70,150,80,40,2,DarkGreen);   //button parking gate1
  tft.drawRoundRect(70,150,80,40,2,DarkCyan);    //button parking gate1
  tft.setCursor(75,162);                         //button parking gate1
  tft.setTextColor(Black);                       //button parking gate1
  tft.setTextSize(2);                            //button parking gate1
  tft.print("Gate-1");                           //button parking gate1
  
  tft.fillRoundRect(175,150,80,40,2,DarkGreen);    //button parking gate2
  tft.drawRoundRect(175,150,80,40,2,DarkCyan);     //button parking gate2
  tft.setCursor(180,162);                          //button parking gate2
  tft.setTextColor(Black);                         //button parking gate2
  tft.setTextSize(2);                              //button parking gate2
  tft.print("Gate-2");

}

String ClosestGate() {

    int park1read = 0;    //resetting values
    int park2read = 0;    //resetting values
    int park3read = 0;    //resetting values
    int park4read = 0;    //resetting values

    
  
    park1read = digitalRead(park1);
    park2read = digitalRead(park2);
    park3read = digitalRead(park3);
    park4read = digitalRead(park4);


//    Serial.println("New data");


//    Serial.println(park1read);    // For admin to monitor assigned parking
//    Serial.println(park2read);    // For admin to monitor assigned parking
//    Serial.println(park3read);    // For admin to monitor assigned parking
//    Serial.println(park4read);    // For admin to monitor assigned parking

    
    
    if (park1read == 1)
    {
       parkNo = "B01";
    }

    else if (park2read == 1)
    {
       parkNo = "B02";
    }

    else if (park3read == 1)
    {
       parkNo = "B03";
    }

    else if (park4read == 1)
    {
       parkNo = "B04";
    }
    else
    {
      parkNo = "Full";
    }
//    Serial.println(park3read);

    
    
    
    return parkNo;
}

void park(){
          tft.fillScreen(Black);                     //whole display
      
        tft.drawRect(0, 0, 320, 240, DarkCyan);            // border
        tft.drawRect(2, 2, 316, 236, Olive);               // border
        tft.drawRect(4, 4, 312, 232, DarkCyan);            // border

         
       
        tft.setCursor(80,15);                       //Welcome text
        tft.setTextColor(Magenta);                  //Welcome text
        tft.setTextSize(4);                         //Welcome text
        tft.print("Subidha");                       //Welcome text
        tft.setCursor(70,50);                       //Welcome text
        tft.setTextColor(Magenta);                  //Welcome text
        tft.setTextSize(2);                         //Welcome text
        tft.print("Parking soluion");               //Welcome text



}


void parkSpot(){

        tft.fillRect(20,80,280,140,DarkGrey);        //bottom part
        tft.fillRect(25,85,270,130,Navy);            //bottom part
        tft.setCursor(80,105);                       //parking box text
        tft.setTextColor(Yellow);                    //parking box text
        tft.setTextSize(2);                          //parking box text
        tft.print("Please park at");                 //parking box text
        tft.setCursor(110,140);                      //parking box text
        tft.setTextColor(GreenYellow);               //parking box text
        tft.setTextSize(6);                          //parking box text 
        tft.print(ClosestGate());                    //parking box text
        //delay(5000);

}


void parkFull(){
        tft.fillRect(20,80,280,140,Red);             //bottom part
        tft.fillRect(25,85,270,130,Navy);            //bottom part
        tft.setCursor(100,95);                       //parking box text
        tft.setTextColor(LightGrey);                 //parking box text
        tft.setTextSize(4);                          //parking box text
        tft.print("Sorry");                          //parking box text
        tft.setCursor(60,135);                       //parking box text
        tft.setTextColor(LightGrey);                 //parking box text
        tft.setTextSize(2);                          //parking box text
        tft.print("all parkings are"); 
        tft.setCursor(110,165);
        tft.setTextColor(Red);                       //parking box text
        tft.setTextSize(4);                          //parking box text
        tft.print("full"); 
//        tft.setCursor(40,160);                      //parking box text
//        tft.setTextColor(GreenYellow);              //parking box text
//        tft.setTextSize(3);                         //parking box text 
//        tft.print("See you again");                 //parking box text
        //delay(5000);

}

void parkNoti() {


  
  tft.fillScreen(Black);
  tft.drawRect(0, 0, 320, 240, DarkCyan);            // border
  tft.drawRect(2, 2, 316, 236, Olive);               // border
  tft.drawRect(4, 4, 312, 232, DarkCyan);            // border

  
  tft.setCursor(30,40);                       //Welcome text
  tft.setTextColor(LightGrey);                //Welcome text
  tft.setTextSize(2);                         //Welcome text
  tft.print("Thank You");                     //Welcome text
  tft.setCursor(30,60);                       //Welcome text
  tft.setTextColor(LightGrey);                //Welcome text
  tft.setTextSize(2);                         //Welcome text
  tft.print("For Using");  
  tft.setCursor(20,80);                       //Welcome text
  tft.setTextColor(Magenta);                  //Welcome text
  tft.setTextSize(3);                         //Welcome text
  tft.print("Subidha");                       //Welcome text
  tft.setCursor(18,100);                      //Welcome text
  tft.setTextColor(Magenta);                  //Welcome text
  tft.setTextSize(1);                         //Welcome text
  tft.print("______________________");        //underline

  
  tft.setCursor(10,135);                      //Welcome text
  tft.setTextColor(Blue);                     //Welcome text
  tft.setTextSize(2);                         //Welcome text
  tft.print("Please Follow");                 //Welcome text
  tft.setCursor(20,160);                      //Welcome text
  tft.setTextColor(LightGrey);                //Welcome text
  tft.setTextSize(2);                         //Welcome text
  tft.print("The Parking");  
  tft.setCursor(60,190);                       //Welcome text
  tft.setTextColor(White);                     //Welcome text
  tft.setTextSize(3);                          //Welcome text
  tft.print("MAP");                            //Welcome text

  
  tft.fillRect(175,20,135,200,White);          //bottom part

  tft.setCursor(220,40);                       //Welcome text
  tft.setTextColor(Navy);                      //Welcome text
  tft.setTextSize(3);                          //Welcome text
  tft.print(ClosestGate());
  tft.fillRect(185,80,115,130,Navy); 
  tft.setCursor(192,130);                       //Welcome text
  tft.setTextColor(LightGrey);                  //Welcome text
  tft.setTextSize(6);                           //Welcome text
  tft.print("MAP");                             //Welcome text



}

void parkNotiF() {


  
  tft.fillScreen(Black);
  tft.drawRect(0, 0, 320, 240, DarkCyan);            // border
  tft.drawRect(2, 2, 316, 236, Olive);               // border
  tft.drawRect(4, 4, 312, 232, DarkCyan);            // border

  
  tft.setCursor(35,60);                       //Welcome text
  tft.setTextColor(LightGrey);                //Welcome text
  tft.setTextSize(2);                         //Welcome text
  tft.print("Please Make an U turn");         //Welcome text
  tft.setCursor(130,90);                      //Welcome text
  tft.setTextColor(LightGrey);                //Welcome text
  tft.setTextSize(4);                         //Welcome text
  tft.print("And");  
  tft.setCursor(30,130);                       //Welcome text
  tft.setTextColor(Olive);                     //Welcome text
  tft.setTextSize(3);                          //Welcome text
  tft.print("Try Again Later");                //Welcome text
  tft.setCursor(30,150);                       //Welcome text
  tft.setTextColor(Olive);                     //Welcome text
  tft.setTextSize(1);                          //Welcome text
  tft.print("____________________________________________");        //underline

  
  tft.setCursor(50,175);                      //Welcome text
  tft.setTextColor(Green);                    //Welcome text
  tft.setTextSize(3);                         //Welcome text
  tft.print("See You Soon");                  //Welcome text


}

void serial() {                                    //to monitor or debug
    Serial.println("Emepty parkings are");
    Serial.println("B02");
    Serial.println("B03");
    Serial.println("B04");
    Serial.println("Allocated parking is ");
    Serial.print(parkNo);

}

TSPoint waitOneTouch() {

  // wait 1 touch to exit function
  
  TSPoint p;
  
  do {
    p= ts.getPoint(); 
  
    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT); //Pins configures again for TFT control
  
  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));
  
  return p;
}
