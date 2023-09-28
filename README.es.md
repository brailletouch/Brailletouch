# Brailletouch - Dispositivo Braille Asequible para Personas con Discapacidad Visual y Sordoceguera
[![en](https://img.shields.io/badge/lang-en-red.svg)](README.md)

## Tabla de Contenidos
- [Descripción General](#descripción-general)
- [Componentes del Proyecto](#componentes-del-proyecto)
  - [Diseño Físico del Dispositivo](#1-diseño-físico-del-dispositivo)
  - [Electrónica y Firmware](#2-electrónica-y-firmware)
  - [Interfaz con Lectores de Pantalla](#3-interfaz-con-lectores-de-pantalla)
- [Componentes Necesarios](#componentes-necesarios)
- [Imágenes de Referencia](#imágenes-de-referencia)
- [Participa](#participa)

## Descripción General

Brailletouch es un proyecto de código abierto dedicado a crear un dispositivo Braille asequible, haciendo que la tecnología asistencial sea accesible para todos. Las pantallas Braille tradicionales a menudo vienen con un precio elevado, que oscila entre $1,200 y $6,000 USD. Nuestra misión es reducir estos costos hasta en un 90%, permitiendo que personas con discapacidad visual y sordoceguera puedan leer, escribir en Braille, y usar computadoras o dispositivos móviles de manera eficiente y silenciosa.

Ya sea que seas un desarrollador, una mente curiosa, o alguien que quiere marcar la diferencia, te invitamos a unirte a nuestra comunidad en [GitHub](https://github.com/brailletouch) y ayudarnos a dar forma al futuro de Brailletouch.

## Componentes del Proyecto

Brailletouch consta de tres componentes esenciales:

### 1. Diseño Físico del Dispositivo

- Celda Braille
- Matriz de 40 Sensores Táctiles
- Botones
- Caja de Ensamblaje

### 2. Electrónica y Firmware

- Microcontrolador ESP32
- Selección de Fuente de Alimentación (Baterías o Jack)
- Controlador PWM
- Multiplexor/Demultiplexor PCF8574 (8 Canales)
- Código para el IDE de Arduino (.ino)

### 3. Interfaz con Lectores de Pantalla

- NVDA (Windows)
- BrailleBack (Android)
- BRLTTY (Linux, Android, Windows)

## Componentes Necesarios

Para construir Brailletouch, necesitarás los siguientes componentes:

- 1 Microcontrolador ESP32
- 4 Servomotores
- 4 Multiplexores/Demultiplexores PCF8574 (8 Canales)
- 1 Celda Braille (desarrollada con 4 servomotores; cualquier tipo de celda Braille funcionará)
- Caja de Ensamblaje
- Controlador PWM (para control de pines simultáneo y lecturas más rápidas)
- Botones de teclado y cables
- Opcional: Una pantalla para monitoreo de texto
- Opcional: Conector PS/2 para entrada de teclado (para personas sordociegas)
- 1 Placa de Circuito Impreso para sensores táctiles (aún en desarrollo para controlar 40 posiciones con solo 9 pines disponibles en ESP32)

## Imágenes de Referencia

![image](https://user-images.githubusercontent.com/9951014/143519725-5d493c91-513b-4640-ae0b-aba3ea0b435c.png)

![image](https://github.com/discapacidad5/brailletouch/blob/main/esp32-pca9685-hookup.jpg) [Referencia](http://www.esp32learning.com/code/esp32-and-a-pcf8574-expander-example.php) [Librería PCF8574](https://www.arduino.cc/reference/en/libraries/pcf8574-library/)

![image](https://github.com/discapacidad5/brailletouch/blob/main/modulo-expansor-io-pcf8574.jpg)

![image](https://github.com/discapacidad5/brailletouch/blob/main/paltalla%20braille%201.png)

![image](https://github.com/discapacidad5/brailletouch/blob/main/paltalla%20braille%20celda%20braile.png)

![image](https://github.com/discapacidad5/brailletouch/blob/main/diagrama%201%20de%20coneciones%20brailletouch.png)

## Participa

Agradecemos las contribuciones de desarrolladores, diseñadores, probadores, y cualquier persona interesada en ayudarnos a hacer realidad Brailletouch. Sigue estos pasos para empezar:

### 1. Haz un Fork del Repositorio

Comienza haciendo un fork de este repositorio en tu propia cuenta de GitHub. Esto creará una copia del proyecto en la que podrás trabajar sin afectar al repositorio principal.

![Fork](https://docs.github.com/assets/images/help/repository/fork_button.jpg)

### 2. Clona el Repositorio

Luego, clona el repositorio forkeado en tu máquina local. Abre una terminal y usa el siguiente comando, reemplazando `[tu-nombre-de-usuario]` con tu nombre de usuario de GitHub:

```bash
git clone https://github.com/[tu-nombre-de-usuario]/Brailletouch.git