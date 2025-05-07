# BrailleTouch
Dispositivo Braille Digital Asequible y Open Source para Personas con Discapacidad Visual y Sordocieguera / Affordable and Open Source Digital Braille Device for Visually Impaired and Deafblind People

**¡Bienvenidos al repositorio del Proyecto BrailleTouch! / Welcome to the BrailleTouch Project repository!**

Este es un proyecto en **desarrollo activo**. La información, componentes y ejemplos mostrados reflejan el estado actual o intentos iniciales. Estamos explorando y desarrollando continuamente nuevas y más eficientes soluciones que se actualizarán aquí una vez validadas. ¡Tu participación es bienvenida en cada etapa!

This is a project in **active development**. The information, components, and examples shown reflect the current state or initial attempts. We are continuously exploring and developing new and more efficient solutions, which will be updated here once validated. Your participation is welcome at every stage!

Este proyecto es una iniciativa social de código abierto (Open Source) dedicada a democratizar el acceso a la tecnología Braille digital. Nuestro objetivo es reducir significativamente el alto costo de los dispositivos Braille actuales y proporcionar una herramienta innovadora, portátil y asequible que empodere a personas ciegas y sordociegas, mejorando su alfabetización, independencia, comunicación y participación plena en la sociedad.

This project is an open-source social initiative dedicated to democratizing access to digital Braille technology. Our goal is to significantly reduce the high cost of current Braille devices and provide an innovative, portable, and affordable tool that empowers blind and deafblind individuals, improving their literacy, independence, communication, and full participation in society.

---

## El Problema: Acceso Limitado a Tecnología Braille Digital Esencial / The Problem: Limited Access to Essential Digital Braille Technology

La tecnología Braille digital, como las pantallas Braille actualizables, es fundamental para la alfabetización, educación, empleo y acceso a la información en el mundo digital para personas con discapacidad visual. Sin embargo, su costo es prohibitivo. Dispositivos comerciales básicos cuestan más de $1,200 USD, y los de buena calidad oscilan entre $3,000 y $6,000 USD o incluso más.

Esta barrera económica es especialmente crítica para la comunidad sordociega. Para muchas personas que no pueden depender de la vista ni el oído, el Braille es la única vía autónoma para acceder al lenguaje escrito y al mundo digital. La inaccesibilidad de la tecnología Braille debido a su precio exacerba el riesgo de aislamiento y limita drásticamente sus oportunidades.

The high cost of current digital Braille technology, such as refreshable Braille displays, is a major barrier. Basic commercial devices cost over $1,200 USD, and good quality ones range from $3,000 to $6,000 USD or even more.

This economic barrier is particularly critical for the deafblind community. For many who cannot rely on sight or hearing, Braille is the only autonomous path to access written language and the digital world. The inaccessibility of Braille technology due to its price exacerbates the risk of isolation and drastically limits their opportunities.

---

## Nuestra Solución: BrailleTouch - Un Enfoque Innovador y Asequible / Our Solution: BrailleTouch - An Innovative and Affordable Approach

El Proyecto BrailleTouch aborda este problema desarrollando un dispositivo Braille electrónico de código abierto, diseñado para ser significativamente más asequible que las alternativas comerciales. Esto no es aún un producto terminado, sino un proyecto en desarrollo. Nuestra innovación clave para reducir costos y complejidad es radicalmente diferente:

The BrailleTouch Project addresses this problem by developing an open-source electronic Braille device, designed to be significantly more affordable than commercial alternatives. This is not a finished product yet, but a project under development. Our key innovation to reduce cost and complexity is radically different:

En lugar de utilizar múltiples celdas Braille físicas y costosas (cada celda individual puede costar $100-$150+ USD), BrailleTouch combina:

Instead of using multiple expensive physical Braille cells (each individual cell can cost $100-$150+ USD), BrailleTouch combines:

1.  Una **única celda Braille física** de alta calidad y rápida respuesta.
2.  Una **matriz de sensores táctiles** de bajo costo, que funciona como "celdas virtuales" que representan una línea de texto digital.

1.  A **single physical Braille cell** with high quality and fast response.
2.  A low-cost **tactile sensor matrix** that acts as "virtual cells" representing a line of digital text.

El usuario interactúa tocando la matriz táctil para "navegar" por la línea de texto digital. Al tocar una posición virtual, la única celda física, bajo otro dedo, se actualiza instantáneamente para mostrar el carácter que corresponde a esa posición. Esto simula la experiencia de leer una línea completa, carácter por carácter, permitiendo al usuario percibir la estructura del texto con mucho menos hardware.

The user interacts by touching the tactile matrix to "navigate" through the digital text line. By touching a virtual position, the single physical cell, under another finger, instantly updates to show the character corresponding to that position. This simulates the experience of reading a full line, character by character, allowing the user to perceive the text structure with much less hardware.

Estimamos que este enfoque puede reducir el costo del subsistema Braille en al menos un 95%, y el costo total del dispositivo en más de un 90% en comparación con las pantallas Braille actuales.

We estimate this approach can reduce the cost of the Braille subsystem by at least 95%, and the total device cost by over 90% compared to current Braille displays.

---

## Funcionalidades Clave y Potencial / Key Functionalities and Potential

BrailleTouch está diseñado para ofrecer una solución versátil:

BrailleTouch is designed to offer a versatile solution:

*   **Lectura de Texto:** Actúa como una pantalla Braille portátil y asequible para leer libros, documentos, correos electrónicos y navegar en la web. La matriz táctil ayuda a la orientación espacial en textos estructurados.
*   **Comunicación en Tiempo Real ("Oído Táctil"):** Crucial para personas sordociegas. Usando solo la celda física, permite recibir información hablada (vía transcripción automática con IA) de forma continua y fluida, como un "oído táctil". Su rapidez supera a las pantallas multicelda para este uso, esencial para seguir conversaciones, clases o eventos en vivo.
*   **Escritura Braille:** Incluirá un teclado Braille táctil integrado para entrada de texto bidireccional.
*   **Potencial con IA:** Se planea integrar IA para funciones avanzadas como reconocimiento de voz ambiental (con identificación de hablantes), resumen adaptativo, traducción multi-idioma y reconocimiento de imagen, abriendo un mundo de independencia sin precedentes.
*   **Alfabetización Temprana Autónoma:** Permite a niños sordociegos aprender Braille y lenguaje recibiendo información del entorno de forma continua, incluso sin padres/maestros que sepan Braille.

*   **Text Reading:** Acts as a portable and affordable Braille display for reading books, documents, emails, and browsing the web. The tactile matrix aids spatial orientation in structured texts.
*   **Real-Time Communication ("Tactile Ear"):** Crucial for deafblind individuals. Using only the physical cell, it enables receiving spoken information (via automatic AI transcription) continuously and fluently, like a "tactile ear". Its speed surpasses multi-cell displays for this use, essential for following live conversations, classes, or events.
*   **Braille Writing:** Will include an integrated tactile Braille keyboard for bidirectional text input.
*   **AI Potential:** AI integration is planned for advanced features like ambient voice recognition (with speaker identification), adaptive summarization, multi-language translation, and image recognition, opening up a world of unprecedented independence.
*   **Autonomous Early Literacy:** Enables deafblind children to learn Braille and language by receiving environmental information continuously, even without parents/teachers who know Braille.

---

## Estructura del Proyecto / Project Structure

El proyecto consta principalmente de 3 partes interconectadas:

The project consists mainly of 3 interconnected parts:

1.  **Diseño Físico del Dispositivo:** Creación de un diseño eficiente, ergonómico y de bajo costo para la celda Braille, la matriz táctil, los botones y la carcasa (explorando impresión 3D).
2.  **Diseño de la Electrónica y Firmware:** Desarrollo del hardware (ej. ESP32, controladores PWM, multiplexores) y el software interno que controla el dispositivo y la comunicación.
3.  **Diseño del Software/Interfaz:** Creación/adaptación de software para la traducción de texto a Braille, gestión de entrada, y compatibilidad con lectores de pantalla de código libre (NVDA, BrailleBack, BRLTTY) y futuras integraciones (apps móviles, IA).

1.  **Physical Device Design:** Creation of an efficient, ergonomic, and low-cost design for the Braille cell, tactile matrix, buttons, and case (exploring 3D printing).
2.  **Electronics and Firmware Design:** Development of the hardware (e.g., ESP32, PWM controllers, multiplexers) and the internal software that controls the device and communication.
3.  **Software/Interface Design:** Creation/adaptation of software for text-to-Braille translation, input management, and compatibility with open-source screen readers (NVDA, BrailleBack, BRLTTY) and future integrations (mobile apps, AI).

---

## Componentes Explorados en Intentos Iniciales / Components Explored in Initial Attempts

**Importante:** Esta sección detalla los componentes **utilizados o explorados en intentos iniciales**. El proyecto está en **desarrollo activo** y se están buscando soluciones **más eficientes y optimizadas** para el diseño final. Los componentes listados aquí sirvieron para dar ideas generales de formas sencillas de realizar un dispositivo, pero **no representan el conjunto final funcional**.

**Important:** This section details the components **used or explored in initial attempts**. The project is in **active development** and **more efficient and optimized** solutions are being sought for the final design. The components listed here served to give general ideas of simple ways to create a device, but **do not represent the final functional set**.

*   1 ESP32.
*   4 Servo motores / Servo motors. (Nota: Estos se usaron en intentos iniciales para mover pines junto con un sensor de ubicación. Se identificó que **no son lo suficientemente rápidos, son ruidosos y pueden desgastarse con el uso**. Aunque fueron útiles para empezar, la estrategia actual busca **actuadores más rápidos y fiables**. ¡Estamos trabajando en mejoras increíbles que se documentarán aquí una vez validadas!)
*   4 PCF8574 Multiplexor/Demultiplexor 8 Canales / PCF8574 Multiplexer/Demultiplexer 8 Channels
*   1 Celda braille (se exploraron mecanismos de actuador de celda con 4 servo motores para mover 8 pines; se busca compatibilidad con distintas tecnologías de actuador más eficientes como piezoeléctrica o de solenoide; la clave es usar SOLO una celda física ya que los movimientos en la línea completa se simulan en la interfaz táctil virtual) / 1 Braille cell (cell actuator mechanisms were explored with 4 servo motors to move 8 pins; compatibility with different, more efficient actuator technologies like piezoelectric or solenoid is sought; the key is to use ONLY one physical cell as full-line movements are simulated on the virtual tactile interface).
*   1 Caja para su ensamblaje (explorando impresión 3D) / 1 Box for assembly (exploring 3D printing).
*   1 Controlador PWM para mover todos los pines de manera simultánea y obtener lecturas más rápidas (aplicado a intentos con servos) / 1 PWM controller to move all pins simultaneously and get faster readings (applied to attempts with servos).
*   Botones del teclado táctil integrado y cable para conexiones / Integrated tactile keyboard buttons and connection cables.
*   Matriz de sensores táctiles (PCB, aún en desarrollo; intentos buscan controlar ~200 posiciones con pines táctiles del ESP32) / Tactile sensor matrix (PCB, still under development; attempts aim to control ~200 positions with ESP32 touch pins).
*   Opcional (para desarrollo o funcionalidades avanzadas): / Optional (for development or advanced functionalities):
    *   Una pantalla para monitorear el texto / A screen if you want to monitor the text.
    *   Un conector PS/2 si se quiere usar un teclado externo para escribir (alternativa a teclado USB/Bluetooth) / A PS/2 connector if you want to use an external keyboard for writing (alternative to USB/Bluetooth keyboard).
    *   Componentes para integración IA (hardware potente si es necesario) / Components for AI integration (powerful hardware if needed).
    *   Módulo de micrófono y circuitos de audio (para transcripción de voz) / Microphone module and audio circuits (for voice transcription).

---

## Imágenes de Referencia (Intentos Iniciales/Conceptos) / Reference Images (Initial Attempts/Concepts)

Las imágenes a continuación muestran **prototipos o intentos iniciales** para ilustrar el concepto y la estructura general del proyecto utilizando los componentes explorados. **NO representan el diseño final o un dispositivo completamente funcional.** El proyecto está en **desarrollo activo** y se están buscando soluciones **más eficientes y optimizadas**. Estas imágenes se mantienen aquí como **referencia histórica de los intentos iniciales**. Actualizaremos estas imágenes a medida que el desarrollo avance y se validen nuevas soluciones en este repositorio (`brailletouch/Brailletouch`).

The images below show **early prototypes or initial attempts** to illustrate the project's concept and general structure using the components explored. **They DO NOT represent the final design or a fully functional device.** The project is in **active development**, and **more efficient and optimized** solutions are being sought. These images are kept here as **historical reference of initial attempts**. We will update these images as development progresses and new solutions are validated in this repository (`brailletouch/Brailletouch`).

*   **Nota:** Los siguientes enlaces de imágenes apuntan a su ubicación original en otro repositorio o fuente externa (`discapacidad5` o `user-images`). Para que se muestren correctamente, deben estar accesibles en esas ubicaciones originales o ser subidas a este repositorio y actualizar los enlaces.
*   **Note:** The following image links point to their original location in another repository or external source (`discapacidad5` or `user-images`). For them to display correctly, they must remain accessible at those original locations or be uploaded to this repository and have the links updated.

![alt text](https://user-images.githubusercontent.com/9951014/143519725-5d493c91-513b-4640-ae0b-aba3ea0b435c.png)

![alt text](https://github.com/discapacidad5/brailletouch/blob/main/esp32-pca9685-hookup.jpg)

reference [http://www.esp32learning.com/code/esp32-and-a-pcf8574-expander-example.php](http://www.esp32learning.com/code/esp32-and-a-pcf8574-expander-example.php)
PCF8574 library [https://www.arduino.cc/reference/en/libraries/pcf8574-library/](https://www.arduino.cc/reference/en/libraries/pcf8574-library/)

![alt text](https://github.com/discapacidad5/brailletouch/blob/main/modulo-expansor-io-pcf8574.jpg)

![alt text](https://github.com/discapacidad5/brailletouch/blob/main/paltalla%20braille%201.png)

![alt text](https://github.com/discapacidad5/brailletouch/blob/main/paltalla%20braille%20celda%20braile.png)
![alt text](https://github.com/discapacidad5/brailletouch/blob/main/diagrama%201%20de%20coneciones%20brailletouch.png)

---

## Licencia / License

Este proyecto está bajo la **Licencia Abierta y Comunitaria Braille Touch (BTAC) v1.2**. Esta licencia garantiza que todo el código, hardware, conceptos, metodologías, mecanismos, innovaciones tecnológicas, invenciones y cualquier otra creación o desarrollo relacionado con el proyecto Braille Touch permanezcan abiertos y accesibles, y no puedan ser privatizados.

This project is licensed under the **Braille Touch Open and Community License (BTAC) v1.2**. This license ensures that all code, hardware, concepts, methodologies, mechanisms, technological innovations, inventions, and any other creations or developments related to the Braille Touch project remain open and accessible and cannot be privatized.

### Permisos / Permissions
- Puedes usar, copiar, modificar, distribuir y comercializar el código, hardware, conceptos, innovaciones y derivados del proyecto bajo las condiciones de esta licencia. / You may use, copy, modify, distribute, and commercialize the code, hardware, concepts, innovations, and derivatives of the project under the conditions of this license.

### Registro de Modificaciones / Modification Record
- Las modificaciones y mejoras deben incluir un registro detallado de todas las personas y entidades involucradas, con una descripción clara y enlaces al repositorio original. / Modifications and improvements must include a detailed record of all individuals and entities involved, with a clear description and links to the original repository.

### No Privatización / No Privatization
- El código y las innovaciones no pueden ser privatizados. Todo trabajo derivado debe permanecer bajo esta misma licencia. / The code and innovations cannot be privatized. All derivative work must remain under this same license.

### Compatibilidad y Comercialización / Compatibility and Commercialization
- Cualquier trabajo derivado debe ser distribuido bajo la misma licencia. La comercialización está permitida siempre que se respeten las condiciones de la licencia. / Any derivative work must be distributed under the same license. Commercialization is allowed as long as the license conditions are respected.

Para más detalles sobre la licencia, por favor revisa el archivo [LICENCIA](https://github.com/brailletouch/Brailletouch/blob/main/LICENCIA.md) en el repositorio. / For more details about the license, please review the [LICENSE](https://github.com/brailletouch/Brailletouch/blob/main/LICENSE.md) file in the repository.

