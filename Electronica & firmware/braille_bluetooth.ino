//resto de codigo  para usar en futuro para  reconocer letra en caso de conectar directamente un teclado bluetooth

/*
//Braille binario
int binary[63][8]={{0,0,0,0,0,0,0,0},{0,1,1,0,1,1,0,0},{0,0,0,1,0,0,0,0},{0,1,0,1,1,1,0,0},{1,1,1,0,0,1,0,0},{1,1,0,0,0,1,0,0},{1,1,1,0,1,1,0,0},{1,0,1,1,1,1,0,0},{0,1,1,1,1,1,0,0},{1,0,0,0,0,1,0,0},{0,1,0,0,1,1} ,{0,0,0,0,0,1} ,{0,0,0,0,1,1,0,0},{0,1,0,0,0,1,0,0},{0,1,0,0,1,0,0,0},
        {0,0,0,1,1,1,0,0},{0,0,1,0,0,0,0,0},{0,0,1,0,1,0,0,0},{0,0,1,1,0,0,0,0},{0,0,1,1,0,1,0,0},{0,0,1,0,0,1,0,0},{0,0,1,1,1,0,0,0},{0,0,1,1,1,1,0,0},{0,0,1,0,1,1,0,0},{0,0,0,1,1,0,0,0},{1,0,0,1,0,1,0,0},{0,0,0,1,0,1,0,0},{1,0,1,0,0,1,0,0},{1,1,1,1,1,1,0,0},{0,1,0,1,1,0,0,0},{1,1,0,1,0,1,0,0},
        {0,1,0,0,0,0,0,0},{1,0,0,0,0,0,0,0},{1,0,1,0,0,0,0,0},{1,1,0,0,0,0,0,0},{1,1,0,1,0,0,0,0},{1,0,0,1,0,0,0,0},{1,1,1,0,0,0,0,0},{1,1,1,1,0,0,0,0},{1,0,1,1,0,0,0,0},{0,1,1,0,0,0,0,0},{0,1,1,1,0,0,0,0},{1,0,0,0,1,0,0,0},{1,0,1,0,1,0,0,0},{1,1,0,0,1,0,0,0},{1,1,0,1,1,0,0,0},{1,0,0,1,1,0,0,0},{1,1,1,0,1,0,0,0},{1,1,1,1,1,0,0,0},{1,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0},{0,1,1,1,1,0,0,0},{1,0,0,0,1,1,0,0},{1,0,1,0,1,1,0,0},{0,1,1,1,0,1,0,0},{1,1,0,0,1,1,0,0},{1,1,0,1,1,1,0,0},{1,0,0,1,1,1,0,0},
        {0,1,1,0,0,1,0,0},{1,0,1,1,0,1,0,0},{1,1,1,1,0,1,0,0},{0,1,0,1,0,0,0,0},{0,1,0,1,0,1}};
//Ascii codigo
char ascii[63]={' ', '!', '"', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/', 
        '0','1','2','3','4','5','6','7','8','9',':',';','<','=','>','?',
        '@','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
         '[','\\',']','^','_'};
int Received;
char data[16] ="brailletouch 01";  
char input;
int* output;
int temp =0;
*/



#include "BluetoothSerial.h"

#include <ESP32Servo.h>
#include <Stream.h> // Para poder tener una referencia a Serial

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


BluetoothSerial SerialBT;

char data[16] ="brailletouch 01"; 
int velocidad = 100;

ESP32PWM pwm;
// posicioens de los servos
int right1 = 135;
int right2 = 180;
int center = 90;
int left1 = 45;
int left2 = 0;
int pausacaract = 20; // minimo 15 recomendado 20

Servo sevo1;
Servo sevo2;
Servo sevo3;
Servo sevo4;
//Servo sevo5;
//Servo sevo6;
//Servo sevo7;
//Servo sevo8;



int minUs = 500;
 int maxUs = 2400;
// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33 
int sevo1Pin = 19; // Un servo en el pin 15
int sevo2Pin = 17; // Otro servo en el pin 16
int sevo3Pin = 21; // Un servo en el pin 14
int sevo4Pin = 32; // Otro servo en el pin 32
//int sevo5Pin = 14; // Un servo en el pin 4
//int sevo6Pin = 33; // Otro servo en el pin 33
//int sevo7Pin = 15; // Otro servo en el pin 19
//int sevo8Pin = 25; // Otro servo en el pin 21


// clase lee serial
class LeeUTF8 {
  public:
    LeeUTF8(Stream &entrada) :
      entrada(entrada),
      valorTemporal(0),
      valor(-1),
      bytesTotales(0),
      bytesLeidos(0) {};
    int16_t available() {
      if (this->valor == -1) {
        this->valor = this->read();
      }
      return (this->valor != -1);
    }
    int16_t read() {
      if (this->valor != -1) {
        int16_t valorLeido = this->valor;
        this->valor = -1;
        return valorLeido;
      }
      int16_t lectura = this->entrada.read();
      if (lectura < 0) {
        return -1;
      }
      if ((lectura & 0b11000000) == 0b10000000) {      // Los bytes que vienen después del primero
        if (this->bytesTotales > 1) { // Si se esperan en total más de un byte
          this->valorTemporal <<= 6; // Desplazamos el valor 6 bits a la izquierda 
          this->valorTemporal |= lectura & 0b00111111; // 10xxxxxx
          if (++this->bytesLeidos >= this->bytesTotales) { // Si ya se han leído todos los bytes esperados
            return this->resultado(this->valorTemporal); // Devolvemos el resultado
          }
          else {
            return -1; // No hay valor disponible aún
          }
        }
        else {
          return this->resultado(-2); // Error
        }
      }
      else if ((lectura & 0b11100000) == 0b11000000) { // El primero de dos bytes
        this->valorTemporal = lectura & 0b00011111;    // 110yyyyy
        return this->empezando(2);
      }
      else if ((lectura & 0b11110000) == 0b11100000) { // El primero de tres bytes
        this->valorTemporal = lectura & 0b00001111;    // 1110zzzz
        return this->empezando(3);
      }
      else if ((lectura & 0b11111000) == 0b11110000) { // El primero de cuatro bytes 
        this->valorTemporal = lectura & 0b00000111;    // 11110uuu
        return this->empezando(4);
      }
      else { // Asumimos que es un solo byte (aunque sea erróneo)
        return this->resultado(lectura);
      }
    }
  private:
    Stream &entrada;
    int16_t valorTemporal;
    int16_t valor;
    uint8_t bytesTotales;
    uint8_t bytesLeidos;
    int16_t empezando(uint8_t setBytesTotales) {
      this->bytesTotales = setBytesTotales;
      this->bytesLeidos = 1;
      return -1;
    }
    int16_t resultado(int16_t valorObtenido) {
      this->bytesTotales = 0;
      this->bytesLeidos = 0;
      this->valor = -1;
      return valorObtenido;
    }
};



 LeeUTF8 leeUTF8(Serial);
 LeeUTF8 LeeBTUTF8(SerialBT);

void setup() {
  
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  sevo1.setPeriodHertz(50);      // Standard 50hz servo
  sevo2.setPeriodHertz(50);      // Standard 50hz servo
  sevo3.setPeriodHertz(50);      // Standard 50hz servo
  sevo4.setPeriodHertz(50);      // Standard 50hz servo
//  sevo5.setPeriodHertz(50);      // Standard 50hz servo
//  sevo6.setPeriodHertz(50);      // Standard 50hz servo 
//  sevo7.setPeriodHertz(50);      // Standard 50hz servo      
//  sevo8.setPeriodHertz(50);      // Standard 50hz servo    
}



void loop() {
  
   if (leeUTF8.available() || LeeBTUTF8.available()) { // revisa si hay dato en Serial o en el SerialBT y procesa
   int dato;
             if (leeUTF8.available()) { // Si hay dato en el Serial
             dato = leeUTF8.read(); // Lo lee del Serial
              }
         else {
             dato = LeeBTUTF8.read(); // Lo lee del BluetoothSerial si no lo había en el Serial
              }
   if ((dato >= 0x2800) && (dato <= 0x28FF)) {  // comprueb si los datos estan en  braille y prosesa 
        sevo1.attach(sevo1Pin, minUs, maxUs);
        sevo2.attach(sevo2Pin, minUs, maxUs);
        pwm.attachPin(27, 10000);//10khz
        sevo3.attach(sevo3Pin, minUs, maxUs);
        sevo4.attach(sevo4Pin, minUs, maxUs);
//      sevo5.attach(sevo5Pin, minUs, maxUs);  
//      sevo6.attach(sevo6Pin, minUs, maxUs);
//      sevo7.attach(sevo6Pin, minUs, maxUs);
//      sevo8.attach(sevo6Pin, minUs, maxUs);
   
        Serial.println("recibiendo datos braile");                   // recibe datos braille
        Serial.println();                   // Deja una línea en blanco
        servo_disp(dato);
        delay(velocidad);         //   controla la velocidad  con que sale el carater
        
      }
   else if ((dato >= 0x0020) && (dato <= 0x27FF) || (dato >= 0x2900)) {  // lo datos no son braille
//        sevo1.attach(sevo1Pin, minUs, maxUs);
//        sevo2.attach(sevo2Pin, minUs, maxUs);
//        pwm.attachPin(27, 10000);//10khz
//        sevo3.attach(sevo3Pin, minUs, maxUs);
//        sevo4.attach(sevo4Pin, minUs, maxUs);
//      sevo5.attach(sevo5Pin, minUs, maxUs);  
//      sevo6.attach(sevo6Pin, minUs, maxUs);
//      sevo7.attach(sevo6Pin, minUs, maxUs);
//      sevo8.attach(sevo6Pin, minUs, maxUs);
   
        Serial.println("datos no braile");                   // recibe datos no braille
        Serial.println(dato, HEX);
        Serial.println();                   // Deja una línea en blanco
//        servo_disp(dato);
        delay(velocidad);         //   controla la velocidad  con que sale el carater
        
      }
   else
      {
//    Serial.print(Serial.available());
  
      delay(50);
      sevo1.detach();
      sevo2.detach();
      sevo3.detach();
      sevo4.detach();
//    sevo5.detach();
//    sevo6.detach();
//    sevo7.detach();
//    sevo8.detach();
      pwm.detachPin(27);
  
      }  
    
//  Serial.println(dato, HEX);
  }
 
}




void servo_disp(int dato)
{
  if ((dato >= 0x2800) && (dato <= 0x28FF)) {
  sevo1.write(center);
  delay(pausacaract);
  sevo2.write(center);
  delay(pausacaract);
  sevo3.write(center);
  delay(pausacaract);
  sevo4.write(center);
  delay(pausacaract);
//  sevo5.write(center);
//  delay(pausacaract);
//  sevo6.write(center);
//  delay(pausacaract);
//  sevo7.write(center);
//  delay(pausacaract);
//  sevo8.write(center);
//  delay(pausacaract);
  }
      
    if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 1) == 0 ) && ( bitRead(dato, 2) == 0) && ( bitRead(dato, 3) == 0 ) && ( bitRead(dato, 4) == 0) && ( bitRead(dato, 5) == 0 ) && ( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
     {
       sevo1.write(center);
       delay(pausacaract);
       sevo2.write(center);
       delay(pausacaract);
       sevo3.write(center);
       delay(pausacaract);
       sevo4.write(center);
       delay(pausacaract);
/*       sevo5.write(center);
       delay(pausacaract);
       sevo6.write(center);
       delay(pausacaract);
       sevo7.write(center);
       delay(pausacaract);
       sevo8.write(center); 
       delay(pausacaract);    */
       Serial.print("Espacio en blanco...\n"); 
       SerialBT.print("Espacio en blanco...\n");    
      }      
    if(( bitRead(dato, 0) == 1) && ( bitRead(dato, 3) == 1 ) )
     {
       sevo1.write(left2);   
       delay(pausacaract);
       Serial.print("punto 1 y 4...\n"); 
       SerialBT.print("punto 1 y 4...\n");    
      }
     if(( bitRead(dato, 0) == 1) && ( bitRead(dato, 3) == 0 ) )
      {  
    
       sevo1.write(left1);
       delay(pausacaract);
       Serial.print("punto 1...\n");
       SerialBT.print("punto 1...\n"); 
      
      }   
    if(( bitRead(dato, 3) == 1) && ( bitRead(dato, 0) == 0 ))
     {
      sevo1.write(right1);
      delay(pausacaract);
       Serial.print("punto 4...\n");
       SerialBT.print("punto 4...\n");
     }   
    if(( bitRead(dato, 1) == 1) && ( bitRead(dato, 4) == 1 ) )
     {    
      sevo2.write(left2);
      delay(pausacaract);
      Serial.print("punto 2 y 5...\n");
      SerialBT.print("punto 2 y 5...\n");
      }
if(( bitRead(dato, 1) == 1) && ( bitRead(dato, 4) == 0 ) )
      { 
       sevo2.write(left1);
       delay(pausacaract);
       Serial.print("punto 2...\n");
       SerialBT.print("punto 2...\n");
       }
if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 1 ) )
       {
       sevo2.write(right1);
       delay(pausacaract);
       Serial.print("punto 5...\n"); 
       SerialBT.print("punto 5...\n");    
//    digitalWrite(k+2, HIGH);
       }
      if(( bitRead(dato, 2) == 1) && ( bitRead(dato, 5) == 1 ) )
      { 
      sevo3.write(left2);
      delay(pausacaract);
      Serial.print("punto 3 y 6...\n");
      SerialBT.print("punto 3 y 6...\n");  
      }
      if(( bitRead(dato, 2) == 1) && ( bitRead(dato, 5) == 0 ) )
      {
    sevo3.write(left1);
    delay(pausacaract);
    Serial.print("punto 3...\n");
    SerialBT.print("punto 3...\n");    
     }   
    if(( bitRead(dato, 5) == 1) && ( bitRead(dato, 3) == 0 ) )
    {
    sevo3.write(right1);
    delay(pausacaract);
     Serial.print("punto 6...\n");
     SerialBT.print("punto 6...\n");    
//    digitalWrite(k+2, HIGH);
     }   
    if(( bitRead(dato, 6) == 1) && ( bitRead(dato, 7) == 1 ) )
     { 
      sevo4.write(left2);
      delay(pausacaract);
      Serial.print("punto 7 y 8..\n");
      SerialBT.print("punto 7 y 8..\n");  
     }
    if(( bitRead(dato, 6) == 1) && ( bitRead(dato, 7) == 0 ) )
     {
      sevo4.write(left1);
      delay(pausacaract);
     Serial.print("punto 7...\n");
     SerialBT.print("punto 7...\n");  
     }
    if(( bitRead(dato, 7) == 1) && ( bitRead(dato, 6) == 0 ) )
     {
     sevo4.write(right1);
     delay(pausacaract);
     Serial.print("punto 8...\n"); 
     SerialBT.print("punto 8...\n");    
//   digitalWrite(k+2, HIGH);
   }
 
}
