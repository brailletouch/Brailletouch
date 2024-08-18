


![Celda Braille 3D](https://github.com/brailletouch/Brailletouch/blob/main/Electronica%20&%20firmware/celda%20braille%20con%20motor%20de%20celular/image/assembly1.PNG?raw=true).

### **3D-Printed Braille Cell**

#### **Description**

This project details the construction of a Braille cell using cellphone vibrating motors. The cell is designed to be 3D printed and offers 
an accessible and customizable solution for visually impaired individuals.

#### **Key Components**

* **Vibrating Motors:** 8 individual vibrating motors, each responsible for raising one Braille dot.
* **L9110 Motor Drivers:** Used to control the direction of the vibrating motors.
* **74LS04 Logic Inverter:** Inverts the logic signal to control the motor direction with a single ESP32 pin.
* **ESP32:** Main microcontroller that generates the control signals for the motors.
* **Limit Switches (transistors):** Detect when the motors reach their limits and cut power to prevent damage.
* **3D Design:** The 3D files for the Braille cell are available in this repository for download and printing.

#### **Operation**

1. **Direction Control:**
   * A single pin of the ESP32 controls both directions of a motor.
   * When the pin is high, the motor rotates in one direction.
   * The 74LS04 inverts the signal when the pin is low, causing the motor to rotate in the opposite direction.

2. **Motor Stopping:**
   * The limit switches (transistors) detect when the motors reach the physical limits.
   * Upon detection, the switch cuts power to the corresponding motor, preventing it from continuing to rotate.

#### **Assembly Instructions**

1. **3D Printing:** Print all the parts using a compatible 3D printer.
2. **Assembly:** An assembled 3D file is provided as a reference in "assembly.STEP".
3. **Electrical Connection:** Connect the electronic components according to the schematic diagram provided in "schematic.png".
4. **Software Setup:** Upload the ESP32 firmware to the device. Replace the `Braille_disp(dato)` function with a custom function that
5. provides detailed control of each motor.

#### **Files**

* **3D Files:** Contain the 3D models of all Braille cell parts.
* **Schematic Diagram:** Shows the connection of all electronic components.
* **Firmware:** Source code for the ESP32.
* **Documentation:** Additional documentation about the project.

#### **Contributions**

Contributions are welcome. If you find any errors or want to improve this project, feel free to open an issue or submit a pull request.


___________________________________________________________________________________________________________________________________________________________________________________
### **Celda Braille Impresa en 3D**

#### **Descripción**

Este proyecto detalla la construcción de una celda Braille utilizando motores vibratorios de teléfonos móviles. 
La celda está diseñada para ser impresa en 3D y ofrece una solución accesible y personalizable para personas con discapacidad visual.

#### **Componentes Clave**

* **Motores vibratorios:** 8 motores vibratorios individuales, cada uno responsable de levantar un punto Braille.
* **Controladores de motor L9110:** Utilizados para controlar la dirección de los motores vibratorios.
* **Inversor lógico 74LS04:** Invierte la señal lógica para controlar la dirección de los motores con un solo pin del ESP32.
* **ESP32:** Microcontrolador principal que genera las señales de control para los motores.
* **Interruptores (transistores):** Detectan cuando los motores alcanzan los topes y cortan la alimentación para evitar daños.
* **Diseño 3D:** Los archivos 3D de la celda Braille están disponibles en este repositorio para su descarga e impresión.

#### **Funcionamiento**

1. **Control de dirección:**
   * Un solo pin del ESP32 controla ambas direcciones de un motor.
   * Cuando el pin está en alto, el motor gira en una dirección.
   * El 74LS04 invierte la señal cuando el pin está en bajo, haciendo que el motor gire en la dirección opuesta.

2. **Detención de motores:**
   * Los interruptores (transistores) detectan cuando los motores alcanzan los topes físicos.
   * Al detectar un tope, el interruptor corta la alimentación al motor correspondiente, evitando que continúe girando.

#### **Instrucciones de montaje**

1. **Impresión 3D:** Imprime todas las piezas utilizando una impresora 3D compatible.
2. **Ensamblaje:** Un archivo 3D ensamblado se proporciona como referencia en "assembly.STEP".
3. **Conexión eléctrica:** Conecta los componentes electrónicos según el diagrama esquemático proporcionado en "schematic.png".
4. **Configuración del software:** Carga el firmware del ESP32 en el dispositivo. Reemplaza la función `Braille_disp(dato)` con la función
5. personalizada que proporciona el control detallado de cada motor.

#### **Archivos**

* **Archivos 3D:** Contienen los modelos 3D de todas las piezas de la celda Braille.
* **Diagrama esquemático:** Muestra la conexión de todos los componentes electrónicos.
* **Firmware:** Código fuente para el ESP32.
* **Documentación:** Documentación adicional sobre el proyecto.

#### **Contribuciones**

Las contribuciones son bienvenidas. Si encuentras algún error o deseas mejorar este proyecto, no dudes en abrir un issue o enviar una pull request.



![Celda Braille 3D](https://github.com/brailletouch/Brailletouch/blob/main/Electronica%20&%20firmware/celda%20braille%20con%20motor%20de%20celular/image/assembly2.PNG?raw=true).

![Celda Braille 3D](https://github.com/brailletouch/Brailletouch/blob/main/Electronica%20&%20firmware/celda%20braille%20con%20motor%20de%20celular/image/assembly3.PNG?raw=true).


![Celda Braille 3D](https://github.com/brailletouch/Brailletouch/blob/main/Electronica%20&%20firmware/celda%20braille%20con%20motor%20de%20celular/image/assembly4.PNG?raw=true).



![Celda Braille 3D](https://github.com/brailletouch/Brailletouch/blob/main/Electronica%20&%20firmware/celda%20braille%20con%20motor%20de%20celular/image/assembly6.PNG?raw=true).


![Celda Braille 3D](https://github.com/brailletouch/Brailletouch/blob/main/Electronica%20&%20firmware/celda%20braille%20con%20motor%20de%20celular/image/assembly10.PNG?raw=true).





