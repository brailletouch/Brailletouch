
# Brailletouch
Dispositivo braille para personas con discapacidad visual y sordociegas

# Edicion por Ed
El proyecto consta principalmente de 3 partes.
  Diseño fisico del dispositivo braile
  Diseño de la electronica y firmware
  Diseño de la interfaz con un lector de pantalla de codigo libre
 
# Diseño del dispositivo fisico
  Celda braile
  Botones
  Caja

# Electronica y firmware
  ESP32 y seleccion de power source, baterias o jack.
  Codigo .ino utilizando el IDE arduino
  
# Interfaz con un lector de pantalla de codigo libre
  Explorando opciones
  
  
# Texto original. Componentes nesesario

1  ESP32.

4 Servo motores.

1 Celda braille  (se esta desarrollando con 4 servo motores para mover 8 pines, se puede usar cualquier celda braille sea punzo eletrica de servo o de solenoide es solo una celda ya que los movimientos se simulan en la linea tactil)

1 Caja para su ensamble

1 Controldor  PWM para mover todos los pines de manera simultanea y optener lecturas muchos mas rapida

Botones del teclado y cable para coneciones

Opcional

Una pantalla si se quiere monitoriar el texto

Una conector PS/2 si se quiere usar un teclado para escribir  persona sordociega. 


1 placas de circuito impreso de los sensores tatil ( todavian en desarrollo se busca poder cotrolar 40 posiciones con masim 9 pines que son los disponibles en el ESP32 con soporte tactiles pines 2.4,12,13,14,15,27,32,33 ).
![image](https://user-images.githubusercontent.com/9951014/143519725-5d493c91-513b-4640-ae0b-aba3ea0b435c.png)
![image](https://github.com/discapacidad5/brailletouch/blob/main/paltalla%20braille%201.png)
![image](https://github.com/discapacidad5/brailletouch/blob/main/paltalla%20braille%20celda%20braile.png)


