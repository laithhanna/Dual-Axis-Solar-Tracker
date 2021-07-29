//Servo motor library
#include <Servo.h>
//Declare two servos
Servo servo_updown;
Servo servo_rightleft;
//declare servo pins
const int servoPin_updown = 9;
const int servoPin_rightleft = 10;

//Liquid Crystal library
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define ANALOG_IN_PIN A5 // analog pin A5 will be connected to a voltage divider to perform power calculations regarding the solar panel

//Initialize variables
int topRight_LDR= 0;              // top right LDR connected to analog pin A0                                        
int topLeft_LDR = 1;              // top left LDR connected to analog pin A1                          
int botRight_LDR = 2;             // bottom right LDR connected to analog pin A2                       
int botLeft_LDR = 3;              // bottom light LDR connected to analog pin A3 
                  
int topr;                         // to store the value of the top right LDR
int topl;                         // to store the value of the top left LDR
int botr;                         // to store the value of the bottom right LDR
int botl;                         // to store the value of the bottom left LDR
int threshold_value=10;           //to stabalize the system and increase the measurement sensitivity 

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);                 
  servo_updown.attach(servoPin_updown);                //Servo motor up-down movement
  servo_rightleft.attach(servoPin_rightleft);          //Servo motor right-left movement
}

void loop()
{
  // power calculations
    float adcVolt = analogRead(ANALOG_IN_PIN)*5.0/1023;
    float panelVoltage = 2*adcVolt;                // adcVolt=(R2/R1+R2)*panelVoltage but R1=R2=1000 Ohms  => panelVoltage=2*adcVolt)
    float current = panelVoltage/2000;            //  I=panelVoltage/(R1+R2)=> panelVoltage/2000 
    float power = panelVoltage*current;          // P = I * V

    lcd.setCursor(0,0);
    lcd.print("V="); lcd.print(panelVoltage);
    lcd.setCursor(8,0);
    lcd.print("I= "); lcd.print(current);
    lcd.setCursor(0,1);
    lcd.print("Power= "); lcd.print(power);
    delay(1000);
  
    Solartracker();               //solar panel movement function
    
}

//solar panel movement

void Solartracker(){
  
     //capturing analog values of each LDR
     topr= analogRead(topRight_LDR);         
     topl= analogRead(topLeft_LDR);         
     botr= analogRead(botRight_LDR);         
     botl= analogRead(botLeft_LDR);         

    // calculating average values
     int avgtop = (topr + topl) / 2;     //top LDRs average value
     int avgbot = (botr + botl) / 2;     //bottom LDRs average value
     int avgleft = (topl + botl) / 2;    //left LDRs average value
     int avgright = (topr + botr) / 2;   //right LDRs average value
   
    //elevation (up-down) and azimuth(left-right) movements calculations
     int diffelev = avgtop - avgbot;      
     int diffazi = avgright - avgleft;    
    
    //left-right movement of solar panel
     
      if (abs(diffazi) >= threshold_value){                           //if absolute value of azimuth difference >= 10(threshold value) solar panel will change its position 
       if (diffazi > 0) {                                             // avgright > avgleft ===> solar panel moves to the right 
        if (servo_rightleft.read() < 180) {
          servo_rightleft.write((servo_rightleft.read() + 2));
        }
      }
      if (diffazi <  0) {                                            // avgright < avgleft ===> solar panel moves to the left  
        if (servo_rightleft.read() > 0) {
          servo_rightleft.write((servo_rightleft.read() - 2));
        }
      }
    }
             
      //up-down movement of solar tracker

      if (abs(diffelev) >= threshold_value){                         //if absolute value of elevation difference >= 10(threshold value) solar panel will change its position 
       if (diffelev > 0) {                                           // avgtop > avgbot ===> solar panel moves upward
        if (servo_updown.read() < 148) {
          servo_updown.write((servo_updown.read() + 2));
        }
      }
      if (diffelev <  0) {                                           // avgtop < avgbot ===> solar panel moves downward
        if (servo_updown.read() > 32) {
          servo_updown.write((servo_updown.read() - 2));
        }
      }
    }       
 }  
