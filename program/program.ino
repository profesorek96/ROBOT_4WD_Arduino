// Motor 1
#define SILNIKA1 2 //przodu prawa strona
#define SILNIKA2 3//tylu prawa strona
#define SPWMA 9 //pwm prawa strona

//int dir1PinA = 2;
//int dir2PinA = 3;
//int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
#define SILNIKB1 4 //przodu lewa strona
#define SILNIKB2 5 //tylu lewa strona
#define SPWMB 10 //pwm lewa strona

//int dir1PinB = 4;
//int dir2PinB = 5;
//int speedPinB = 10; // Needs to be a PWM pin to be able to control motor speed

bool ON_OFF;
int R_X=0;
int R_Y=0;
unsigned int PWMA,PWMB;



void setup() {
Serial.begin(9600);


//Mostek H Silniki
pinMode(SILNIKA1,OUTPUT);
pinMode(SILNIKA2,OUTPUT);
pinMode(SPWMA,OUTPUT);
pinMode(SILNIKB1,OUTPUT);
pinMode(SILNIKB2,OUTPUT);
pinMode(SPWMB,OUTPUT);


//ustawienie czestotliwosci PWM powyzej ludzkiej slyszalnosci
TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz

//Zerowanie zmiennych
ON_OFF=false;
R_X=0;
R_Y=0;
PWMA=0;
PWMB=0;




}

void loop() {

// Initialize the Serial interface:

  if (Serial.available() > 0) {
    String ramka = Serial.readStringUntil('\n');
    if(ramka[0]=='o')
    {
      ON_OFF=!ON_OFF;
      delay(50);
      if(ON_OFF)Serial.write("led 1\n");
      else Serial.write("led 0\n");
    }
    if(ON_OFF)
    {
      if(ramka[0]=='X')
      {
        ramka.remove(0,2);
        Serial.println('X');
        R_X=ramka.toInt();
        Serial.println(R_X); //wywalenia
      }

      if(ramka[0]=='Y')
      {
        ramka.remove(0,2);
        Serial.println('Y');
        R_Y=ramka.toInt();
        Serial.println(R_Y); //wywalenia
      }
      //do przodu
      if(R_X<0) 
      {
        digitalWrite(SILNIKA1,HIGH);
        digitalWrite(SILNIKA2,LOW);
        digitalWrite(SILNIKB1,HIGH);
        digitalWrite(SILNIKB2,LOW);
        PWMA = -(R_X+R_Y);
        PWMB = -R_X; 
      }

      //do tylu
      else 
      {
        digitalWrite(SILNIKA1,LOW);
        digitalWrite(SILNIKA2,HIGH);
        digitalWrite(SILNIKB1,LOW);
        digitalWrite(SILNIKB2,HIGH);
        PWMA = R_X+R_Y;
        PWMB = R_X; 
      }

      if(PWMA<0)PWMA = 0;
      if(PWMA>255)PWMA = 255;
      if(PWMB<0)PWMB = 0;
      if(PWMB>255)PWMB=255;

      analogWrite(SPWMA,PWMA);
      analogWrite(SPWMB,PWMB);
      


      
    }
    else
    {
      R_X=0;
      R_Y=0;
      PWMA=0;
      PWMB=0;
      digitalWrite(SILNIKA1,LOW);
      digitalWrite(SILNIKA2,LOW);
      digitalWrite(SILNIKB1,LOW);
      digitalWrite(SILNIKB2,LOW);
      analogWrite(SPWMA,PWMA);
      analogWrite(SPWMB,PWMB);
      
      
    }
  }
}
