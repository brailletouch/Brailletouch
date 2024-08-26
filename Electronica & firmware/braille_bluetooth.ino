/*
 * Brailletouch - Open Source Braille Display
 *
 * Description:
 * This code is part of the Brailletouch project, an open-source initiative aimed at reducing the cost of braille displays.
 The project uses a combination of physical and virtual braille cells to make assistive technology more accessible.
 *
 * Project Repository:
 * GitHub: https://github.com/brailletouch/Brailletouch
 *
 * License:
 * This code is licensed under the Braille Touch Open and Community License (BTAC) v1.2.
 You are free to use, copy, modify, and distribute this code under the conditions of this license. For more details, 
 please review the LICENSE file in the repository.
 *
 * Contact:
 * Cergio Monasterio
 * WhatsApp: +58 412 999 4784 (Please communicate in Spanish only) 
 *
 * Date: 26/08/2024
 * Version: 1.1
 *
 * Copyright (c) 2024 Brailletouch
 * This code is provided "as is", without warranty of any kind. For licensing terms, see the LICENSE file.
 */


#include "BluetoothSerial.h"

#include <ESP32Servo.h>
#include <Stream.h> // Para poder tener una referencia a Serial

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define CELL 15
//int datos;
//int u = 0;
//int recibido[CELL];
BluetoothSerial SerialBT;
char data[16] ="brailletouch 01";

ESP32PWM pwm;
// posicioens de los servos
int right1 = 135;
int right2 = 180;
int center = 90;
int left1 = 45;
int left2 = 0;
int repetir = 5; // minimo 10
int ciclos = 1; // recomendado 1
int pausacaract = 1; // recomendado 1
int velocidad = 60; // recomendado 60 esto no debe controlar la velocidad si se lee con las celdas virtuales


Servo sevo1;
Servo sevo2;
Servo sevo3;
Servo sevo4;

int minUs = 500;
 int maxUs = 2400;
// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33 
int sevo1Pin = 19; // Un servo en el pin 15
int sevo2Pin = 17; // Otro servo en el pin 16
int sevo3Pin = 21; // Un servo en el pin 14
int sevo4Pin = 32; // Otro servo en el pin 32


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





// Clase para controlar un buffer de únicamente "valores númericos de caracteres Braille"

class BufferBraille {

  public:

    // Constructor al que se le indica cuántos caracteres Braille va a tener

    BufferBraille(size_t longitud) :

      longitud(longitud), 

      buffer(new int16_t[longitud]),

      indiceEntrada(0),

      limpiarAntes(false) { this->clear(); };



    // Destructor, no hace falta invocarlo

    ~BufferBraille() { delete[] this->buffer; }



    // Para limpiar el buffer y pone el índice de entrada a 0

    void clear() {

      for (size_t i = 0; i < this->longitud; i++) {

        this->buffer[i] = 0x2800;

      }

      this->indiceEntrada = 0;

      this->limpiarAntes = false;

    }



    // Obtiene el valor de la posición indicada. Si se sale de rango devuelve cero

    int16_t get(size_t indice) const {

      if (indice >= this->longitud) {

        return 0x2800;

      }

      return this->buffer[indice];

    }



    // Establece el valor en la posición dada. Si no se indica la posición (indice) entonces lo mete a continuación del último metido

    // Retorna true si lo ha metido y false si no lo ha mentido porque se sale del rango

    bool set(int16_t valor, size_t indice = static_cast<size_t>(-1)) {

      if (this->limpiarAntes) {

        this->clear();

      }

      if (indice == static_cast<size_t>(-1)) {

        indice = this->indiceEntrada;

      }

      this->indiceEntrada = indice + 1;

      if (indice >= this->longitud) {

        return false;

      }

      if ((valor < 0x2800) || (valor > 0x28FF)) {

        valor = 0x2800;

      }

      this->buffer[indice] = valor;

      return true;

    }



    // Si se invoca esta función, el buffer permanecerá igual, pero se borrará en cuanto se le añada otro valor

    void setLimpiarAntes() {

      this->limpiarAntes = true;

    }



    // Retorna el tamaño del buffer (el valor que se le pasó en el constructor)

    size_t size() const {

      return this->longitud;

    }

  private:

    size_t longitud;

    int16_t* const buffer;

    size_t indiceEntrada;

    bool limpiarAntes;

};





LeeUTF8 leeUTF8(Serial);
LeeUTF8 LeeBTUTF8(SerialBT);


BufferBraille buffer(CELL); // Declaramos el buffer de 20 caracteres para las pruebas



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

  Serial.println(F("Meta cararteres Braille en UTF-8"));

}



void loop() {

  if (leeUTF8.available() || LeeBTUTF8.available()) {

    int dato; // Leemos el dato ya disponible. Cuidado, la variable ha de ser int;

             if (leeUTF8.available()) { // Si hay dato en el Serial
             dato = leeUTF8.read(); // Lo lee del Serial
              }
         else {
             dato = LeeBTUTF8.read(); // Lo lee del BluetoothSerial si no lo había en el Serial
              } 

    if ((dato >= 0x2800) && (dato <= 0x28FF)) { // Si el dato corresponde a un carácter Braille

      if (buffer.set(dato)) {                   // Metemos el carácter en el buffer y si no se ha desbordado...

//        for (size_t i = 0; i < buffer.size(); i++) {  // .. recorremos todo el buffer (no hace falta recordar qué tamaño tiene ya que lo podemos saber con buffer.size()

//          Serial.print(' ');                    // Ponemos un caráctes de separador

          Serial.print(dato, HEX);     // Mostramos el valor en hexadecimal
          Serial.print(' ');                    // Ponemos un caráctes de separador
//          Serial.println(i);
//          Serial.println("recibiendo datos braile");                   // recibe datos braille
//          Serial.println();                   // Deja una línea en blanco
          servo_disp(dato);
          delay(velocidad);

//        }

        Serial.println();                       // Terminamos la línea

      }

    }

    else if (dato == 13) {                        // Si el dato que ha entrado es un retorno de carro...

      buffer.setLimpiarAntes();                   // Le indicamos al buffer que queremos que se mantenga, pero que se borre antes de meter el próximo dato

      for (size_t i = 0; i < buffer.size(); i++) {// Mostramos el contenido del buffer para verificas que mantiene lo que tenía

//        Serial.println("datos del boffer antes de borrar");
        Serial.print(' ');

        Serial.print(buffer.get(i), HEX);

      }

      Serial.println();

    }

     else if ((dato >= 0x0020) && (dato <= 0x27FF) || (dato >= 0x2900)) {   // lo datos no son braille
     
      Serial.println("datos no braile");                   // recibe datos no braille
      Serial.println(dato, HEX);
      Serial.println(dato);
      Serial.write(dato);        
      Serial.println();                   // Deja una línea en blanco
      delay(1);         //   controla la velocidad  con que sale el carater

      // codigo para probar celda virtual desde la app de android

                if (dato == '1') {
                   Serial.println("Valor 0");
                   servo_disp(buffer.get(0));
                   Serial.println(buffer.get(0));
                  }
                else  if (dato == '2') {
                   Serial.println("Valor 1");
                   servo_disp(buffer.get(1));
                   Serial.println(buffer.get(1));
                  }
                else  if (dato == '3') {
                   Serial.println("Valor 2");
                   servo_disp(buffer.get(2));
                   Serial.println(buffer.get(2));
                  }
                else  if (dato == '4') {
                   Serial.println("Valor 3");
                   servo_disp(buffer.get(3));
                   Serial.println(buffer.get(3));
                  }
                else  if (dato == '5') {
                   Serial.println("Valor 4");
                   servo_disp(buffer.get(4));
                   Serial.println(buffer.get(4));
                  }
                else  if (dato == '6') {
                   Serial.println("Valor 5");
                   servo_disp(buffer.get(5));
                   Serial.println(buffer.get(5));
                  }
                else  if (dato == '7') {
                   Serial.println("Valor 6");
                   servo_disp(buffer.get(6));
                   Serial.println(buffer.get(6));
                  }
                else  if (dato == '8') {
                   Serial.println("Valor 7");
                   servo_disp(buffer.get(7));
                   Serial.println(buffer.get(7));
                  }
                else  if (dato == '9') {
                   Serial.println("Valor 8");
                   servo_disp(buffer.get(8));
                   Serial.println(buffer.get(8));
                  }
                else  if (dato == '0') {
                   Serial.println("Valor 9");
                   servo_disp(buffer.get(9));
                   Serial.println(buffer.get(9));
                  }
                else  if (dato == 'a') {
                   Serial.println("Valor 10");
                   servo_disp(buffer.get(10));
                   Serial.println(buffer.get(10));
                  }
                else  if (dato == 'b') {
                   Serial.println("Valor 11");
                   servo_disp(buffer.get(11));
                   Serial.println(buffer.get(11));
                  }
                else  if (dato == 'c') {
                   Serial.println("Valor 12");
                   servo_disp(buffer.get(12));
                   Serial.println(buffer.get(12));
                  }
                else  if (dato == 'd') {
                   Serial.println("Valor 13");
                   servo_disp(buffer.get(13));
                   Serial.println(buffer.get(13));
                  }
                else  if (dato == 'e') {
                   Serial.println("Valor 14");
                   servo_disp(buffer.get(14));
                   Serial.println(buffer.get(14));
                  }
                else  if (dato == 'f') {
                   Serial.println("Valor 15");
                   servo_disp(buffer.get(15));
                   Serial.println(buffer.get(15));
                  }
                else  if (dato == 'g') {
                   Serial.println("Valor 16");
                   servo_disp(buffer.get(16));
                   Serial.println(buffer.get(16));
                  }
                else  if (dato == 'h') {
                   Serial.println("Valor 17");
                   servo_disp(buffer.get(17));
                   Serial.println(buffer.get(17));
                  }
                else  if (dato == 'i') {
                   Serial.println("Valor 18");
                   servo_disp(buffer.get(18));
                   Serial.println(buffer.get(18));
                  }
                else  if (dato == 'j') {
                   Serial.println("Valor 19");
                   servo_disp(buffer.get(19));
                   Serial.println(buffer.get(19));
                 }
                else  if (dato == 'k') { // pone todo en blanco
                    Serial.println("lebanto el dedo");
                    SerialBT.println("lebanto el dedo");
                    sevo1.attach(sevo1Pin, minUs, maxUs);
                    sevo2.attach(sevo2Pin, minUs, maxUs);
                    pwm.attachPin(27, 10000);//10khz
                    sevo3.attach(sevo3Pin, minUs, maxUs);
                    sevo4.attach(sevo4Pin, minUs, maxUs);
                    delay(pausacaract);
                    sevo1.write(center);
                    delay(pausacaract);
                    sevo2.write(center);
                    delay(pausacaract);
                    sevo3.write(center);
                    delay(pausacaract);
                    sevo4.write(center);
                    delay(pausacaract);
                
                  }
                  
                                             
             else {
                Serial.println("otro dato");
                Serial.println();                   // Deja una línea en blanco
                  }    

            }
   
      }


}





void servo_disp(int dato)
{
//delay(velocidad);         //   controla la velocidad  con que sale el carater
  if ((dato >= 0x2800) && (dato <= 0x28FF)) {
        sevo1.attach(sevo1Pin, minUs, maxUs);
        sevo2.attach(sevo2Pin, minUs, maxUs);
        pwm.attachPin(27, 10000);//10khz
        sevo3.attach(sevo3Pin, minUs, maxUs);
        sevo4.attach(sevo4Pin, minUs, maxUs);
        delay(pausacaract);

  
  
  
  
for (int i = 0; i < repetir; i++)
        {      
    if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 1) == 0 ) && ( bitRead(dato, 2) == 0) && ( bitRead(dato, 3) == 0 ) && ( bitRead(dato, 4) == 0) && ( bitRead(dato, 5) == 0 ) && ( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
     {
      for (int index = 0; index < ciclos; index++)
        {
        sevo1.write(center);
        delay(pausacaract);
        sevo2.write(center);
        delay(pausacaract);
        sevo3.write(center);
        delay(pausacaract);
        sevo4.write(center);
        delay(pausacaract);
                if( i == repetir -1 )
          {
           Serial.print("Espacio en blanco...\n"); 
           SerialBT.print("Espacio en blanco...\n");  
          }
        } 
  
      }      
    if(( bitRead(dato, 0) == 1) && ( bitRead(dato, 3) == 1 ) )
     {
       for (int index = 0; index < ciclos; index++)
      {
        sevo1.write(left2);   
        delay(pausacaract);
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }

      }

      }
     if( i == repetir -1 )
       {      
       Serial.print("punto 1 y 4...\n"); 
       SerialBT.print("punto 1 y 4...\n"); 
      }
    }     
     if(( bitRead(dato, 0) == 1) && ( bitRead(dato, 3) == 0 ) )
      {  
     for (int index = 0; index < ciclos; index++)
       {
        sevo1.write(left1);
        delay(pausacaract);

   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
       }
      }
       if( i == repetir -1 )
        {
       Serial.print("punto 1...\n");
       SerialBT.print("punto 1...\n");
        }
     }     
    if(( bitRead(dato, 3) == 1) && ( bitRead(dato, 0) == 0 ))
      {
     for (int index = 0; index < ciclos; index++)
      {      
        sevo1.write(right1);
        delay(pausacaract);
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
      }
     }
      if( i == repetir -1 )
       {
      Serial.print("punto 4...\n");
      SerialBT.print("punto 4...\n");
      }
     }       
    if(( bitRead(dato, 1) == 1) && ( bitRead(dato, 4) == 1 ) )
     {    
    for (int index = 0; index < ciclos; index++)
       {      
        sevo2.write(left2);
        delay(pausacaract);
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
      }
     }
      if( i == repetir -1 )
      {
      Serial.print("punto 2 y 5...\n");
      SerialBT.print("punto 2 y 5...\n");
     }
     }      
if(( bitRead(dato, 1) == 1) && ( bitRead(dato, 4) == 0 ) )
      { 
    for (int index = 0; index < ciclos; index++)
      {       
        sevo2.write(left1);
        delay(pausacaract);
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
       }
     }
       if( i == repetir -1 )
      {
       Serial.print("punto 2...\n");
       SerialBT.print("punto 2...\n");
      }
     }       
if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 1 ) )
       {
     for (int index = 0; index < ciclos; index++)
        {      
        sevo2.write(right1);
        delay(pausacaract);
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
       }
     }
       if( i == repetir -1 )
       {
       Serial.print("punto 5...\n"); 
       SerialBT.print("punto 5...\n");
       }
     }       
      if(( bitRead(dato, 2) == 1) && ( bitRead(dato, 5) == 1 ) )
      { 
    for (int index = 0; index < ciclos; index++)
        {      
        sevo3.write(left2);
        delay(pausacaract); 
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
        }
     }
      if( i == repetir -1 )
       {
      Serial.print("punto 3 y 6...\n");
      SerialBT.print("punto 3 y 6...\n");
      }
     }      
      if(( bitRead(dato, 2) == 1) && ( bitRead(dato, 5) == 0 ) )
      {
     for (int index = 0; index < ciclos; index++)
        {   
        sevo3.write(left1);
        delay(pausacaract);
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
        }
     }
     if( i == repetir -1 )
      {
    Serial.print("punto 3...\n");
    SerialBT.print("punto 3...\n"); 
     }
   }
     
    if(( bitRead(dato, 5) == 1) && ( bitRead(dato, 2) == 0 ) )
    {
  for (int index = 0; index < ciclos; index++)
       {    
        sevo3.write(right1);
        delay(pausacaract); 
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
       }
     }
     if( i == repetir -1 )
       {
     Serial.print("punto 6...\n");
     SerialBT.print("punto 6...\n");  
       }
   }
    
    if(( bitRead(dato, 6) == 1) && ( bitRead(dato, 7) == 1 ) )
     { 
   for (int index = 0; index < ciclos; index++)
       {      
        sevo4.write(left2);
        delay(pausacaract);
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
       }
     }
       if( i == repetir -1 )
       {
      Serial.print("punto 7 y 8..\n");
      SerialBT.print("punto 7 y 8..\n"); 
      }
   }
     
    if(( bitRead(dato, 6) == 1) && ( bitRead(dato, 7) == 0 ) )
     {
  for (int index = 0; index < ciclos; index++)
        {       
        sevo4.write(left1);
        delay(pausacaract);
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
        }
     }
    if( i == repetir -1 )
      {
         Serial.print("punto 7...\n");
         SerialBT.print("punto 7...\n");
      }
   }
     
    if(( bitRead(dato, 7) == 1) && ( bitRead(dato, 6) == 0 ) )
     {
   for (int index = 0; index < ciclos; index++)
       {     
        sevo4.write(right1);
        delay(pausacaract);
   if(( bitRead(dato, 0) == 0) && ( bitRead(dato, 3) == 0 ))
      {
       if (sevo1.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo1.write(center);
        delay(pausacaract);
         }

      }
   if(( bitRead(dato, 1) == 0) && ( bitRead(dato, 4) == 0 ))
      {
       if (sevo2.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo2.write(center);
        delay(pausacaract);
         }
      }
   if(( bitRead(dato, 2) == 0) && ( bitRead(dato, 5) == 0 ))
      {
       if (sevo3.read() != center)   //  si la posicion del servo es diferete a la ultima 
         { 
        sevo3.write(center);
        delay(pausacaract);
         }
      }      
   if(( bitRead(dato, 6) == 0) && ( bitRead(dato, 7) == 0 ))
      {
       if (sevo4.read() != center)   // si la posicion del servo es diferete a la ultima 
         { 
        sevo4.write(center);
        delay(pausacaract);
         }
       }
     }
     if( i == repetir -1 )
     {
     Serial.print("punto 8...\n"); 
     SerialBT.print("punto 8...\n");
    }
   }
  } 
 }
       delay(50);
      sevo1.detach();
      sevo2.detach();
      sevo3.detach();
      sevo4.detach();
      pwm.detachPin(27);
}
