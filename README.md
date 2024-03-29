
# Brailletouch
  Dispositivo braille para personas con discapacidad visual y sordociegas / Braille device for visually impaired and deafblind people

English / Ingles:

Braille Device for Visually Impaired and Deafblind People

It's amazing how expensive assistive technology is. A small flagil braille display costs more than $1,200 USD and a good quality one goes from $3,000 to $6,000. That's why I am developing an open-source project. This is by no means a finished product. Being an open-source project, I hope others will improve the design. In the near future, with the help of volunteers, Brailletouch will reduce the cost of a braille display by 90% and allow anyone who is visually impaired or deafblind to read and write braille, as well as use a computer or mobile device efficiently and without noise.

So if you know someone, if you are a creator, if you are curious or if you want to help, feel free to enter our repository https://github.com/brailletouch/Brailletouch and help me build a community around Brailletouch.

The encoder is practically the heart of the braille display. Most commercial braille displays have 40 or 80 braille cells. Since the most expensive part of a braille display is the braille cells, which cost more than $35 each, we are designing a new form of braille display with 40 virtual cells and a single physical braille cell, reducing most of the cost. We are talking about a braille cell that can be made from 3D printed parts. I designed a different system. Instead of activating 40 cells at the same time and applying all the power to 40 physical cells, Brailletouch uses a physical encoder and a virtual braille display of 40 touch sensors placed in a matrix. In this way, the braille text is gradually displayed in a single braille cell as the virtual cells are touched. Parts can be easily printed.



Spanish: / Español:

"Dispositivo braille para personas con discapacidad visual y sordociegas

Es sorprendente lo cara que es la tecnología de asistencia. Una pequeña pantalla braille flagil cuesta más de $1,200 USD y una de buena calidad va desde $3,000 a $6,000. Por eso estoy desarrollando un proyecto de código abierto. Esto no es de ninguna manera un producto terminado. Al ser un proyecto de código abierto, espero que otros mejoren el diseño. En un futuro cercano, con la ayuda de voluntarios, Brailletouch reducirá el costo de una pantalla braille en un 90% y permitirá que cualquier persona con discapacidad visual o sordoceguera lea y escriba braille, así como use una computadora o dispositivo móvil de manera eficiente y sin ruido.

Entonces, si conoces a alguien, si eres un creador, si tienes curiosidad o si quieres ayudar, no dudes en ingresar a nuestro repositorio https://github.com/brailletouch/Brailletouch y ayudarnos a construir una comunidad alrededor de Brailletouch.

El codificador es prácticamente el corazón de la pantalla braille. La mayoría de las pantallas braille comerciales tienen 40 u 80 celdas braille. Dado que lo más caro en una pantalla braille son las celdas braille, que cuestan más de $35 cada una, estamos diseñando una nueva forma de pantalla braille con 40 celdas virtuales y una sola celda braille física, lo que reduce la mayor parte del costo. Estamos hablando de una celda braille que se puede hacer a partir de piezas impresas en 3D. Diseñé un sistema diferente. En lugar de activar 40 celdas al mismo tiempo y aplicar toda la potencia a 40 celdas físicas, Brailletouch utiliza un codificador físico y una pantalla braille virtual de 40 sensores táctiles colocados en una matriz. De esta manera, el texto braille se muestra gradualmente en una sola celda braille a medida que se tocan las celdas virtuales. Las piezas se pueden imprimir fácilmente.


El proyecto consta principalmente de 3 partes. / The project consists mainly of 3 parts.

Diseño físico del dispositivo braille / Physical design of the braille device

Diseño de la electrónica y firmware / Electronics design and firmware

Diseño de la interfaz con un lector de pantalla de código libre / Interface design with a free code screen reader

# Diseño del dispositivo físico / Physical device design
Celda braille / Braille cell

Línea matricial de sensores 40 táctiles / Matrix line of 40 touch sensors

Botones / Buttons

Caja / Box

# Electrónica y firmware / Electronics and firmware
ESP32 y selección de power source, baterías o jack / ESP32 and selection of power source, batteries or jack.

1 - Controlador PWM / PWM controller

4 - PCF8574 Multiplexor/Demultiplexor 8 Canales / PCF8574 Multiplexor/Demultiplexor 8 Channels

Código .ino utilizando el IDE Arduino / .ino code using the Arduino IDE

# Interfaz con un lector de pantalla de código libre / Interface with a free code screen reader
NVDA - Windows

BrailleBack - Android

BRLTTY - Linux, Android, Windows

# Componentes necesarios
1 ESP32.

4 Servo motores.

4 PCF8574 Multiplexor/Demultiplexor 8 Canales

1 Celda braille (se está desarrollando con 4 servo motores para mover 8 pines, se puede usar cualquier celda braille sea punzó eléctrica de servo o de solenoide es solo una celda ya que los movimientos se simulan en la línea táctil)

1 Caja para su ensamblaje

1 Controlador PWM para mover todos los pines de manera simultánea y obtener lecturas más rápidas

Botones del teclado y cable para conexiones

Opcional:

Una pantalla si se quiere monitorear el texto

Un conector PS/2 si se quiere usar un teclado para escribir para una persona sordociega.

1 placa de circuito impreso de los sensores táctiles (todavía en desarrollo se busca poder controlar 40 posiciones con solo 9 pines que son los disponibles en el ESP32 con soporte táctil pines 2.4,12,13,14,15,27,32,33).

# Imágenes de referencia

![image](https://user-images.githubusercontent.com/9951014/143519725-5d493c91-513b-4640-ae0b-aba3ea0b435c.png)
![image](https://github.com/discapacidad5/brailletouch/blob/main/esp32-pca9685-hookup.jpg)
reference http://www.esp32learning.com/code/esp32-and-a-pcf8574-expander-example.php
PCF8574 library https://www.arduino.cc/reference/en/libraries/pcf8574-library/
![image](https://github.com/discapacidad5/brailletouch/blob/main/modulo-expansor-io-pcf8574.jpg)
![image](https://github.com/discapacidad5/brailletouch/blob/main/paltalla%20braille%201.png)
![image](https://github.com/discapacidad5/brailletouch/blob/main/paltalla%20braille%20celda%20braile.png)



![image](https://github.com/discapacidad5/brailletouch/blob/main/diagrama%201%20de%20coneciones%20brailletouch.png)


