
/**
  * @file pantallaLCD.h
  * @author SCTR
  *
  * @brief Recursos de manejo de la pantalla LCD de la placa STM32F429I-DISC1.
  *
  * Biblioteca de estructuras de datos y funciones codificadas en lenguaje C para el manejo de la pantalla
  * LCD de una placa STM32F429I-DISC1. Es una pantalla táctil en color de 240x320 puntos.
  *
  *
  * @mainpage
  *
  *
  * @section S1 Introducción
  *
  * Biblioteca de estructuras de datos y funciones codificadas en lenguaje C para el manejo de la pantalla
  * LCD de una placa STM32F429I-DISC1. Es una pantalla táctil en color de 240x320 puntos.
  *
  *
  * @section S2 Frame Buffers
  *
  * Se dispone de dos zonas de memoria en una RAM externa para implantar dos frame buffers.
  * Cada uno de ellos tiene un tamaño de 4 * 240 * 320 = 30720 bytes para representar el color de cada uno
  * de los puntos de la pantalla. En cada frame buffer se guarda el color de todos los puntos de la pantalla,
  * desde los puntos de la fila superior a los puntos de la inferior y dentro de cada fila desde el punto
  * situado en el extremo izquierdo al situado en el extremo derecho.
  *
  * Se utiliza la técnica de doble buffer para hacer que las transiciones entre dos escenas sea fluida
  * y sin parpadeos. Uno de los buffers está oculto mientras que el contenido del otro buffer se muestra en 
  * pantalla. La aplicación dibuja en el buffer oculto lo que se desea mostrar a continuación. Cuando ha 
  * finalizado el dibujado, la aplicación llama a la función LCD_intercambiaBuffers() para que el buffer
  * oculto pase a ser visible y el visible pase a ser oculto. Este intercambio es inmediato y el usuario ve
  * que se ha modificado la información en la pantalla y sin parpadeos.
  *
  * @see LCD_inicializa2Buffers(), LCD_intercambiaBuffers(), LCD_ancho(), LCD_alto(), LCD_setFondoColor(),
  *      LCD_setFondoImagen().
  *
  *
  * @section S3 Colores
  *
  * El color de cada punto de la pantalla se representa en 4 bytes en formato ARGB, cada byte (con valores de 
  * 0 a 255) representa un canal: 
  * - Canal A = Alpha = grado de transparencia, desde totalmente transparente (valor 0) a totalmente opaco 
  *   (valor 255). 
  * - Canal R = Red = componente roja del color, de 0 a 255. 
  * - Canal G = Green = componente verde del color, de 0 a 255. 
  * - Canal B = Blue = componente azul del color, de 0 a 255. 
  *
  * Hay que tener en cuenta que cada color se indica en formato ARGB en 32 bits y que este microcontrolador
  * está configurado en modo little-endian, por lo que los 4 bytes de cada color se guarda en memoria desde
  * el byte menos significativo al más significativo. Por ejemplo, el color 0x39d0a807 (A=0x39, R=0xd0,
  * G=0xa8, B=0x07) se guarda en memoria con la secuencia de bytes 0x07, 0xa8, 0xd0 y 0x39.
  *
  * Los colores guardados en los frame buffers serán opacos para que se muestren tal cual en la pantalla.
  * Los colores de imágenes adicionales que se van a visualizar en pantalla pueden tener un canal Alpha
  * menor que 255 para que se puedan mezclar con el fondo.
  *
  *
  * @section S4 Imágenes
  *
  * En esta biblioteca, cuando se utiliza una imagen, tiene que expresarse en una matriz de bytes donde
  * se indican los colores de todos sus puntos, desde la fila superior a la inferior y dentro de cada
  * fila de izquierda a derecha. 
  *
  * Para generar una matriz de bytes con todos los colores de una imagen disponible en un archivo en formato
  * JPG, PNG, etc, se puede utilizar un conversor como el disponible en https://lvgl.io/tools/imageconverter. 
  * En el formulario de esa página web hay que indicar: 
  * - `Image file`: hay que seleccionar el archivo de imagen. 
  * - `Color format`: hay que elegir la opción `CF_TRUE_COLOR_ALPHA`. 
  * - `Output format`: `C array`. 
  *
  * Finalmente, pulsando el botón `Convert` se genera y descarga un archivo del que hay que aprovechar los 
  * datos descritos desde la línea donde aparece `#if LV_COLOR_DEPTH == 32` hasta el siguiente `#endif` para
  * incorporarlos en una matriz de bytes. 
  *
  * Por cada imagen se puede crear en el proyecto un archivo de declaraciones con extensión .h
  * donde indicar la declaración de la matriz. Ejemplo: 
  * @code{.c}
  * extern const uint8_t im[];
  * // Declaración de la variable im con clase de almacenamiento externa consistente en una matriz de
  * // bytes donde se describe el color de cada punto de una imagen. 
  * @endcode
  *
  * Y un archivo con extensión .c donde se define la matriz. Ejemplo: 
  * @code{.c}
  * const uint8_t im[] = {0x07, 0xa8, 0xd0, 0x39};
  * // Matriz de bytes donde se describe el color de cada punto. En este ejemplo se describe un único punto
  * // de color 0x39d0a807, pero en una imagen normalmente habría varios puntos. 
  * @endcode
  *
  * @see LCD_dibujaImagen()
  *
  *
  * @section S5 Texto utilizando el canal Alpha
  *
  * Posibilidad de mostrar texto en juegos de caracteres de longitud variable (los caracteres pueden tener
  * diferente ancho, pero el mismo alto), pudiendo utilizar cualquier color y definiéndolos espedificando
  * para cada carácter el canal Alpha de sus puntos, que tendrá un valor de 0 para puntos del fondo y un
  * valor diferentes de 0 para puntos del carácter.
  *
  * Se pueden visualizar los caracteres de la tabla ASCII, desde el código 32 hasta el código 126.
  * Corresponden a letras minúsculas y mayúsculas del idioma inglés, dígitos numéricos y signos de
  * puntuación.
  *
  * También se pueden visualizar letras acentuadas, eñes y algunos símbolos adicionales, utilizando los
  * siguientes códigos:
  * - á = '\x7f'
  * - Á = '\x80'
  * - é = '\x81'
  * - É = '\x82'
  * - í = '\x83'
  * - Í = '\x84'
  * - ó = '\x85'
  * - Ó = '\x86'
  * - ú = '\x87'
  * - Ú = '\x88'
  * - ñ = '\x89'
  * - Ñ = '\x8a'
  * - ¿ = '\x8b'
  * - ¡ = '\x8c'
  * - € = '\x8d'
  * - º = '\x8e'
  *
  * Ejemplo:
  * @code{.c}
  * #include "JuegoAlpha15.h"
  * // Incluye la declaración de la estructura de datos JuegoAlpha15, de tipo LCD_JuegoCaracteresAlpha, para
  * // utilizar un juego de caracteres de 15 puntos de alto
  *
  * LCD_dibujaCadenaCaracteresAlpha(10, 70, "Posici\x85n ma\x89ana", 0xFF00FF00, 0, &JuegoAlpha15, 0, 100, 1);
  * // Dibuja desde el punto de coordenadas (10, 70) la cadena de caracteres "Posición mañana" en verde
  * // utilizando un juego de caracteres de 15 puntos de alto y dibujando sobre el fondo de la pantalla.
  * @endcode
  *
  * Se dispone de varios juegos de caracteres, cada uno de ellos definidos en los archivos JuegoAlphaxx.c y
  * JuegoAlphaxx.h, donde xx puede ser 13, 15, 17, 19 o 22, indicando la altura de cada carácter en puntos.
  *
  * @see LCD_JuegoCaracteresAlpha, LCD_dibujaCaracterAlpha(), LCD_dibujaCadenaCaracteresAlpha()
  *
  *
  * @section S6 Instalación
  *
  * Para utilizar esta biblioteca de funciones en un proyecto de tipo STM32 en STM32CubeIde, hay que añadir
  * los archivos pantallaLCD.h y pantallaLCD.c.
  *
  * En el caso de utilizar funciones de visualización de texto, hay que añadir también los archivos con los
  * juegos de caracteres que se vayan a emplear.
  * - Archivos JuegoAlphaxx.c y JuegoAlphaxx.h (donde xx puede ser 13, 15, 17, 19 o 22) para juegos de
  *   caracteres donde cada carácter tiene ancho variable y altura xx.
  *
  */


#ifndef INC_PANTALLA_H_
#define INC_PANTALLA_H_


#include <stdint.h>  // Para utilizar uint8_t, uint16_t y uint32_t
#include <string.h>  // Para utilizar strlen()
#include "stm32f429i_discovery.h"  // Para varios recursos de la placa
#include "stm32f429i_discovery_lcd.h"  // Recursos de manejo de la pantalla
#include "stm32f429i_discovery_ts.h"  // Recursos de manejo de la interfaz táctil


/** Dirección de memoria del frame buffer 0 */
#define LCD_FRAME_BUFFER_LAYER_0 (LCD_FRAME_BUFFER)

/** Dirección de memoria del frame buffer 1 */
#define LCD_FRAME_BUFFER_LAYER_1 (LCD_FRAME_BUFFER+0x130000)



/**
 * @brief Inicializa la pantalla para utilizar doble buffer.
 *
 * Inicializa la pantalla LCD para trabajar con dos frame buffers.
 *
 * Es necesario llamar a esta función una única vez al comienzo de la ejecución del programa antes de 
 * intentar visualizar algo en la pantalla. 
 */
void LCD_inicializa2Buffers();


/**
 * @brief Comprueba si la pantalla está pulsada. 
 *
 * Comprueba si se está pulsando la pantalla y determina en qué punto de la pantalla se está pulsando. 
 * Es necesario llamar a esta función antes de utilizar otras funciones que utilizan la interfaz táctil, como
 * LCD_pulsada(), LCD_xPulsacion() o LCD_yPulsacion().
 *
 * Ejemplo: 
 * @code{.c}
 * while(1) {  // Repite indefinidamente ...
 *     LCD_actualizaPulsacion();  // Actualiza el estado de la pulsación en la interfaz táctil
 *     int pulsada = LCD_pulsada();  // Buleano que indica si se pulsó la pantalla
 *     int x = LCD_xPulsacion();  // Coordenada X del punto sobre el que se pulsó la pantalla 
 *     int y = LCD_yPulsacion();  // Coordenada Y del punto sobre el que se pulsó la pantalla 
 * }
 * @endcode
 *
 * * @see LCD_pulsada(), LCD_resetPulsacion(), LCD_xPulsacion(), LCD_yPulsacion()
 */
void LCD_actualizaPulsacion();


/**
 * @brief Comprueba si la pantalla se ha pulsado.
 *
 * Determina si se ha pulsado la pantalla cuando se ha llamado a LCD_actualizaPulsacion() o si se ha
 * reseteado la pulsación en la pantalla mediante una llamada a LCD_resetPulsacion().
 *
 * @return Buleano cierto si la pantalla se ha pulsado.
 *
 * Ejemplo: 
 * @code{.c}
 * while(1) {  // Repite indefinidamente ...
 *     LCD_actualizaPulsacion();  // Actualiza el estado de la pulsación en la interfaz táctil
 *     int pulsada = LCD_pulsada();  // Buleano que indica si se pulsó la pantalla
 *     int x = LCD_xPulsacion();  // Coordenada X del punto sobre el que se pulsó la pantalla 
 *     int y = LCD_yPulsacion();  // Coordenada Y del punto sobre el que se pulsó la pantalla 
 * }
 * @endcode
 *
 * @see LCD_actualizaPulsacion(), LCD_resetPulsacion(), LCD_xPulsacion(), LCD_yPulsacion()
 */
int LCD_pulsada();


/**
 * @brief Resetea estado de pulsación
 *
 * Indica que ya se ha tratado la pulsación sobre la pantalla. Hay que llamar a esta función desde las
 * funciones de atención a componentes (botones, interruptores, etc) para que una vez un componente
 * ha tratado una pulsación sobre la pantalla, los demás componentes no lo hagan.
 *
 * @see LCD_actualizaPulsacion(), LCD_xPulsacion(), LCD_yPulsacion(), LCD_pulsada()
 */
void LCD_resetPulsacion();


/**
 * @brief Coordenada X de última pulsación.
 *
 * Determina la columna (0 a 239) del punto donde se ha pulsado por última vez la pantalla.
 *
 * @return Coordenada X de la última pulsación.
 *
 * Ejemplo: 
 * @code{.c}
 * while(1) {  // Repite indefinidamente ...
 *     LCD_actualizaPulsacion();  // Actualiza el estado de la pulsación en la interfaz táctil
 *     int pulsada = LCD_pulsada();  // Buleano que indica si se pulsó la pantalla
 *     int x = LCD_xPulsacion();  // Coordenada X del punto sobre el que se pulsó la pantalla 
 *     int y = LCD_yPulsacion();  // Coordenada Y del punto sobre el que se pulsó la pantalla 
 * }
 * @endcode
 *
 * @see LCD_actualizaPulsacion(), LCD_pulsada(), LCD_resetPulsacion(), LCD_yPulsacion()
 */
uint16_t LCD_xPulsacion();


/**
 * @brief Coordenada Y de última pulsación.
 *
 * Determina la fila (0 a 319) del punto donde se ha pulsado por última vez la pantalla.
 *
 * @return Coordenada Y de la última pulsación.
 *
 * Ejemplo: 
 * @code{.c}
 * while(1) {  // Repite indefinidamente ...
 *     LCD_actualizaPulsacion();  // Actualiza el estado de la pulsación en la interfaz táctil
 *     int pulsada = LCD_pulsada();  // Buleano que indica si se pulsó la pantalla
 *     int x = LCD_xPulsacion();  // Coordenada X del punto sobre el que se pulsó la pantalla 
 *     int y = LCD_yPulsacion();  // Coordenada Y del punto sobre el que se pulsó la pantalla 
 * }
 * @endcode
 *
 *
 *
 * @see LCD_actualizaPulsacion(), LCD_pulsada(), LCD_resetPulsacion(), LCD_xPulsacion()
 */
uint16_t LCD_yPulsacion();




int Get_bufferOculto();


void Set_buffreOculto(int bufferOculto);



/**
 * @brief Devuelve el ancho de la pantalla en puntos.
 * @return Número de puntos en cada fila de la pantalla.
 * @see LCD_alto().
*/
uint16_t LCD_ancho();


/**
 * @brief Devuelve el alto de la pantalla en puntos.
 * @return Número de puntos en cada columna de la pantalla.
 * @see LCD_ancho().
*/
uint16_t LCD_alto();


/**
 * @brief Intercambia en qué frame buffer se dibuja y qué frame buffer se visualiza.
 *
 * Se utilizan los frame buffers número 0 y número 1. Uno de ellos es el fame buffer visible, cuyo contenido
 * se muestra en la pantalla. El otro es el frame buffer oculto donde se dibuja nueva información a mostrar.
 * Con esta función el frame buffer oculto pasa a ser visible y el visible pasa a ser oculto. 
 *
 * Normalmente debería de existir un hilo dedicado a la visualización de información en pantalla. Este hilo
 * debería de consistir en un bucle contínuo que actualiza la información a visualizar y al final del bucle
 * llamaría a esta función para que la información actualizada aparezca en pantalla. 
 *
 * Ejemplo: 
 * @code{.c}
 * int dato = 10;  // Dato que quizás se modifica en el programa
 *
 * LCD_inicializa2Buffers(); // Inicializa la pantalla
 *
 * while(1) {  // Repite indefinidamente ...
 *
 *     LCD_setFondoColor(0xFF0000BB);  // Pone todo el frame buffer oculto a azul
 *
 *     // Aquí iría una sección de código donde se modifica el dato
 *
 *     LCD_dibujaCircunferencia(100, 100, dato, 0xFFFF0000, 0, 1000, 1);
 *     // Circunferencia en (100, 100), radio variable en función del dato y en color rojo
 *
 *     LCD_intercambiaBuffers();
 *     // La circunferencia se dibujó en el buffer oculto, al intercambiar los buffers se hace visible. 
 *  }
 * @endcode
 *
 * @see LCD_inicializa2Buffers().
 */
void LCD_intercambiaBuffers();

void LCD_intercambiaBuffers2();

/** 
 * @brief Establece color de fondo. 
 *
 * Borra todo el frame buffer oculto, pone todos sus puntos al color indicado y configura como fondo ese
 * color.
 *
 * Ejemplo: 
 * @code{.c}
 * LCD_setFondoColor(0xFF000000); // Establece como fondo el color negro
 * @endcode
 *
 * @param color Color de fondo utilizado, expresado en formato ARGB en 32 bits. 
 *
 * @see LCD_inicaliza2Buffers(), LCD_setFondoImagen().
 */
void LCD_setFondoColor(uint32_t color);


/** 
 * @brief Establece el fondo de la pantalla a partir de una imagen.
 *
 * Dibuja la imagen indicada en el frame buffer oculto para actuar como fondo. Debería de ser una
 * imagen de 240x320 puntos.
 *
 * Ejemplo: 
 * @code{.c}
 * const uint8_t imagen[] = { ... }; 
 * //  Imagen utilizada como fondo, en los puntos suspensivos irían los colores. 
 *
 * LCD_setFondoImagen(imagen);  // Establece la imagen como fondo
 * @endcode
 *
 * @param imagen Puntero a la zona de memoria donde se guarda la imagen de fondo a establecer, que tiene que
 *     tener una resolución de 240x320 puntos. Cada punto expresado en formato ARGB en 32 bits, con canal 
 *     Alpha 255, es decir, con colores opacos.
 *
 * @see LCD_inicializa2Buffers(), LCD_setFondoColor().
 */
void LCD_setFondoImagen(const uint8_t * imagen);


/**
 * @brief Dibuja un punto en el frame buffer oculto.
 *
 * Establece el color de un punto de la pantalla, utilizando el canal Alpha para realizar mezclas de colores,
 * pudiendo convertirlo a niveles de gris y pudiendo aplicarle un cierto grado de transparencia adicional.
 *
 * Ejemplo: 
 * @code{.c}
 * LCD_dibujaPunto(10, 10, 0xFFFF0000, 0, 50); 
 * // Dibuja un punto en rojo en la posición (10, 10) reduciendo su transparencia a un 50% y mezclando
 * // su color con el punto en la misma posición que hay en el frame buffer oculto. 
 * @endcode
 *
 * @param x Coordenada horizontal del punto, de 0 a 239. 
 * @param y Coordenada vertical del punto, de 0 a 319. 
 * @param color Color a establecer en el punto, expresado en formato ARGB en 32 bits. 
 * @param enBlancoYNegro Buleano que indica si hay que mostrar el punto en niveles de gris. 
 * @param transparencia Grado de transparencia aplicado al parámetro \p color, desde 0 (completamente 
 *     transparente) hasta 100 (color original). 
 *
 * @see LCD_dibujaPuntoOpaco().
 */
void LCD_dibujaPunto(uint16_t x, uint16_t y, uint32_t color, int enBlancoYNegro, int transparencia);


/**
 * @brief Dibuja un punto con color opaco en el frame buffer oculto. 
 *
 * Dibuja un punto en una posición de la pantalla, pero de forma más rápida que la función 
 * LCD_dibujaPunto() debido a que no se tiene en cuenta una posible mezcla de colores, ya que el color 
 * utilizado es completamente opaco. 
 *
 * Ejemplo: 
 * @code{.c}
 * LCD_dibujaPuntoOpaco(10, 10, 0xFFFF0000); 
 * // Dibuja un punto opaco en rojo en la posición (10, 10)
 * @endcode
 * 
 * @param x Coordenada horizontal del punto, de 0 a 239. 
 * @param y Coordenada vertical del punto, de 0 a 319. 
 * @param color Color utilizado, expresado en formato ARGB de 32 bits, con canal Alpha 255, totalmente 
 * opaco. 
 *
 * @see LCD_dibujaPunto().
 */
void LCD_dibujaPuntoOpaco(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Dibuja una línea en el frame buffer oculto. 
 *
 * Dibuja una línea con un color que une dos puntos en pantalla utilizando el 
 * <a href="https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm">algoritmo de Bressenham</a>. Puede 
 * convertir el color a niveles de gris y puede aplicarle un grado de transparencia.
 *
 * Ejemplo: 
 * @code{.c}
 * LCD_dibujaLinea(10, 10, 20, 20, 0x7FFF0000, 0, 50);
 * // Dibuja una línea en rojo semitransparente desde el punto (10, 10) al (20, 20) mezclando su color 
 * // con los colores de los puntos que hay en las mismas posiciones en el fondo de la pantalla. 
 * @endcode
 *
 * @param x0 Coordenada horizontal del punto inicial, de 0 a 239. 
 * @param y0 Coordenada vertical del punto inicial, de 0 a 319. 
 * @param x1 Coordenada horizontal del punto final, de 0 a 239. 
 * @param y1 Coordenada vertical del punto final, de 0 a 319. 
 * @param color Color utilizado para dibujar la línea, expresado en formato ARGB en 32 bits. 
 * @param enBlancoYNegro Buleano que indica si hay que mostrar la línea en niveles de gris. 
 * @param transparencia Grado de transparencia aplicado al parámetro \p color, desde 0 (completamente 
 *     transparente) hasta 100 (color original). 
 */
void LCD_dibujaLinea(int x0, int y0, int x1, int y1, uint32_t color, int enBlancoYNegro, int transparencia);


/**
 * @brief Dibuja una circunferencia en el frame buffer oculto. 
 *
 * Dibuja una circunferencia expresada con un centro y un radio. Dibuja el borde con un ancho de un punto en 
 * un determinado color. Puede convertir el color a niveles de gris y puede aplicarle un grado de
 * transparencia.
 *
 * Ejemplo: 
 *
 * @code{.c}
 * LCD_dibujaCircunferencia(100, 100, 30, 0xFFFF0000, 0, 100);
 * // Dibuja una circunferencia de centro (100, 100), radio 30 y color rojo
 * @endcode
 *
 * @param xc Coordenada horizontal del centro, de 0 a 239. 
 * @param yc Coordenada vertical del centro, de 0 a 319.  
 * @param r Radio de la circunferencia.
 * @param color Color utilizado para dibujar la circunferencia, expresado en formato ARGB en 32 bits. 
 * @param enBlancoYNegro Buleano que indica si hay que mostrar la circunferencia en niveles de gris. 
 * @param transparencia Grado de transparencia aplicado al parámetro \p color, desde 0 (completamente 
 *     transparente) hasta 100 (color original). 
 */
void LCD_dibujaCircunferencia(int xc, int yc, int r, uint32_t color, int enBlancoYNegro, int transparencia);

/**
 * @brief Dibuja un círculo en el frame buffer oculto.
 *
 * Dibuja una círculo expresado con un centro y un radio, rellenándolo con
 * un determinado color. Puede convertir el color a niveles de gris y puede aplicarle un grado de
 * transparencia.
 *
 * Ejemplo:
 *
 * @code{.c}
 * LCD_dibujaCircunferencia(100, 100, 30, 0xFFFF0000, 0, 100);
 * // Dibuja un círculo de centro (100, 100), radio 30 y color rojo
 * @endcode
 *
 * @param xc Coordenada horizontal del centro, de 0 a 239.
 * @param yc Coordenada vertical del centro, de 0 a 319.
 * @param r Radio del círculo.
 * @param color Color utilizado para dibujar el círculo, expresado en formato ARGB en 32 bits.
 * @param enBlancoYNegro Buleano que indica si hay que mostrar el círculo en niveles de gris.
 * @param transparencia Grado de transparencia aplicado al parámetro \p color, desde 0 (completamente
 *     transparente) hasta 100 (color original).
 */
void LCD_dibujaCirculo(int xc, int yc, int r, uint32_t color, int enBlancoYNegro, int transparencia);

/**
 * @brief Dibuja el borde de un rectángulo en el frame buffer oculto.
 *
 * Dibuja el borde de un rectángulo con un determinado color, situado en una posición y con unas dimensiones. 
 * Puede convertir el color a niveles de gris y puede aplicarle un grado de transparencia.
 *
 * Ejemplo: 
 * @code{.c}
 * LCD_dibujaRectangulo(10, 10, 100, 50, 0xFF00FF00, 0, 100);
 * // Dibuja un rectángulo con esquina superior izquierda en (10, 10), ancho 100, alto 50, en verde. 
 * @endcode
 *
 * @param xInicial Coordenada X de la esquina superior izquierda, de 0 a 239. 
 * @param yInicial Coordenada Y de la esquina superior izquierda, de 0 a 319. 
 * @param ancho Dimensión horizontal del rectángulo en puntos. 
 * @param alto Dimensión vertical del rectángulo en puntos. 
 * @param color Color utilizado para dibujar el rectángulo, expresado en formato ARGB en 32 bits. 
 * @param enBlancoYNegro Buleano que indica si hay que mostrar el rectángulo en niveles de gris. 
 * @param transparencia Grado de transparencia aplicado al parámetro \p color, desde 0 (completamente 
 *     transparente) hasta 100 (color original). 
 *
 * @see LCD_dibujaRectanguloRelleno(), LCDdibujaRectanguloRellenoOpaco().
 */
void LCD_dibujaRectangulo(uint16_t xInicial, uint16_t yInicial, uint16_t ancho, uint16_t alto,
	uint32_t color, int enBlancoYNegro, int transparencia);


/**
 * @brief Dibuja un rectángulo relleno de color en el frame buffer oculto.
 *
 * Dibuja un rectángulo relleno de un determinado color, situado en una posición y con unas dimensiones. 
 * Puede convertir el color a niveles de gris y puede aplicarle un grado de transparencia.
 *
 * Ejemplo: 
 * @code{.c}
 * LCD_dibujaRectanguloRelleno(10, 10, 100, 50, 0xFF0000FF, 0, 100);
 * // Dibuja un rectángulo con esquina superior izquierda en (10, 10), ancho 100, alto 50, relleno
 * // en azul. 
 * @endcode
 *
 * @param xInicial Coordenada X de la esquina superior izquierda, de 0 a 239. 
 * @param yInicial Coordenada Y de la esquina superior izquierda, de 0 a 319. 
 * @param ancho Dimensión horizontal del rectángulo en puntos. 
 * @param alto Dimensión vertical del rectángulo en puntos. 
 * @param color Color utilizado para rellenar el rectángulo, expresado en formato ARGB en 32 bits. 
 * @param enBlancoYNegro Buleano que indica si hay que mostrar el rectángulo en niveles de gris. 
 * @param transparencia Grado de transparencia aplicado al parámetro \p color, desde 0 (completamente 
 *     transparente) hasta 100 (color original). 
 *
 * @see LCD_dibujaRectangulo(), LCD_dibujaRectanguloRellenoOpaco().
 */
void LCD_dibujaRectanguloRelleno(uint16_t xInicial, uint16_t yInicial, uint16_t ancho, uint16_t alto,
	uint32_t color, int enBlancoYNegro, int transparencia);


/**
 * @brief Dibuja un rectángulo relleno de un color opaco en el frame buffer oculto.
 *
 * Dibuja un rectángulo opaco (color con Alpha 255) en una posición y con unas dimensiones. No se utiliza el 
 * canal Alpha para realizar mezclas de colores, por lo que el dibujado es más rápido que utilizando la 
 * función LCD_dibujaRectanguloRelleno(). 
 *
 * Ejemplo: 
 * @code{.c}
 * LCD_dibujaRectanguloRellenoOpaco(10, 10, 100, 50, 0xFF0000FF); 
 * // Dibuja un rectángulo con esquina superior izquierda en (10, 10), ancho 100, alto 50, relleno
 * // en azul. 
 * @endcode
 *
 * @param xInicial Coordenada X de la esquina superior izquierda, de 0 a 239. 
 * @param yInicial Coordenada Y de la esquina superior izquierda, de 0 a 319. 
 * @param ancho Dimensión horizontal del rectángulo en puntos. 
 * @param alto Dimensión vertical del rectángulo en puntos. 
 * @param color Color utilizado para rellenar el rectángulo, expresado en formato ARGB en 32 bits. El 
 *    canal Alpha tiene que ser 255 (color totalmente opaco).
 *
 * @see LCD_dibujaRectangulo(), LCD_dibujaRectanguloRelleno().
 */
void LCD_dibujaRectanguloRellenoOpaco(uint16_t xInicial, uint16_t yInicial, uint16_t ancho, uint16_t alto,
    uint32_t color);


void LCD_dibujaCuadrado(uint16_t xInicial, uint16_t yInicial, uint16_t lado, uint32_t color, int enBlancoYNegro, int transparencia);



/**
 * @brief Dibuja una imagen en el frame buffer oculto. 
 *
 * Dibuja una imagen en una posición con unas dimensiones. Puede convertir el color a niveles de gris y puede 
 * aplicarle un grado de transparencia. 
 *
 * Ejemplo: 
 * @code{.c}
 * const uint8_t im[] = { ... };  // En ... se indicarían los colores de los puntos de la imagen
 *
 * LCD_dibujaImagen(10, 10, 60, 100, im, 0, 50);
 * // Dibuja la imagen descrita en la matriz im situando su esquina superior izquierda en (10, 10), 
 * // con ancho 60, alto 100, haciendo los colores semitransparentes al 50%.
 * @endcode
 *
 * @param xImagen Coordenada x de la esquina superior izquierda, de 0 a 239. 
 * @param yImagen Coordenada y de la esquina superior izquierda, de 0 a 319.
 * @param ancho Ancho de la imagen en puntos. 
 * @param alto Alto de la imagen en puntos. 
 * @param imagen Puntero a la zona de memoria donde se describe el color de cada punto de la imagen en 
 *     formato ARGB en 32 bits. 
 * @param enBlancoYNegro Buleano que indica si hay que mostrar la imagen en niveles de gris. 
 * @param transparencia Grado de transparencia aplicado al color de cada punto de la imagen, desde 0 
 *     (completamente transparente) hasta 100 (color original). 
 *
 * @see LCD_dibujaImagenOpaca()
 */
void LCD_dibujaImagen(uint16_t xImagen, uint16_t yImagen, uint16_t ancho, uint16_t alto,
	const uint8_t * imagen, int enBlancoYNegro, int transparencia);

/**
 * @brief Dibuja una imagen opaca en el frame buffer oculto.
 *
 * Dibuja una imagen en una posición con unas dimensiones. Los colores de la imagen son opacos (canal A=255),
 * por lo que no hay que realizar mezclas de colores, agilizando así el dibujado.
 *
 * Ejemplo:
 * @code{.c}
 * const uint8_t im[] = { ... };  // En ... se indicarían los colores de los puntos de la imagen
 *
 * LCD_dibujaImagen(10, 10, 60, 100, im);
 * // Dibuja la imagen descrita en la matriz im situando su esquina superior izquierda en (10, 10),
 * // con ancho 60 y alto 100.
 * @endcode
 *
 * @param xImagen Coordenada x de la esquina superior izquierda, de 0 a 239.
 * @param yImagen Coordenada y de la esquina superior izquierda, de 0 a 319.
 * @param ancho Ancho de la imagen en puntos.
 * @param alto Alto de la imagen en puntos.
 * @param imagen Puntero a la zona de memoria donde se describe el color de cada punto de la imagen en
 *     formato ARGB en 32 bits.
 *
 * @see LCD_dibujaImagen()
 */
void LCD_dibujaImagenOpaca(uint16_t xImagen, uint16_t yImagen, uint16_t ancho, uint16_t alto,
	const uint8_t * imagen);



/**
 * @brief Estructura para un juego de caracteres utilizando el canal Alpha.
 *
 * Una estructura de este tipo representa a un juego de caracteres definido mediante el canal Alpha de
 * cada punto de cada carácter de la tabla ASCII (más algunos caracteres adicionales mencionados más
 * abajo) para indicar cómo se dibuja cada punto mezclando su color con el color del punto sobre el que se
 * superpone.
 *
 * En este juego de caracteres se indica sólo el canal Alpha, es decir, por cada punto del caracter se
 * indica un único byte. Esto permite dibujar texto en cualquier color (especificando las componentes
 * R, G y B) cuando se utiliza un determinado juego de caracteres.
 *
 * Todos los caracteres tienen el mismo alto en puntos, pero pueden tener ancho diferente.
 *
 */
typedef struct {
    /** @brief Alto de cada carácter en puntos, todos los caracteres tienen el mismo alto */
	uint8_t alto;
    /** @brief Matriz con enteros que indican la posición de cada carácter en la matriz `caracteres` */
	uint32_t posiciones[142-32+1];
	/** @brief Matriz de bytes donde se describe por cada carácter
	 * - el número de puntos de ancho, expresado en un byte
	 * - un byte por cada punto del carácter para indicar su componente alpha
	 */
	uint8_t caracteres[];
} LCD_JuegoCaracteresAlpha;


/**
 * @brief Dibuja un carácter.
 *
 * Dibuja el carácter `caracter` situándolo en una posición, utilizando un juego de caracteres,
 * con un color,
 * pudiendo visualizarlo en niveles de gris, aplicarle transparencia y mezclarlo sobre lo que ya hay
 * en el frame buffer oculto o sobre el fondo de la pantalla.
 *
 * Se pueden visualizar los caracteres de la tabla ASCII desde la posición 32 hasta la 126.
 *
 * Además se han incluido las letras acentuadas y eñe, en minúsculas y mayúsculas, y algunos símbolos,
 * con los siguientes códigos:
 * - á = '\\x7f'
 * - Á = '\\x80'
 * - é = '\\x81'
 * - É = '\\x82'
 * - í = '\\x83'
 * - Í = '\\x84'
 * - ó = '\\x85'
 * - Ó = '\\x86'
 * - ú = '\\x87'
 * - Ú = '\\x88'
 * - ñ = '\\x89'
 * - Ñ = '\\x8a'
 * - ¿ = '\\x8b'
 * - ¡ = '\\x8c'
 * - € = '\\x8d'
 * - º = '\\x8e'
 *
 * Ejemplo:
 * @code{.c}
 * #include <JuegoAlpha15.h>
 * // Incluye la declaración de la estructura juegoAlpha15 de tipo LCD_JuegoCaracteresAlpha para
 * // manejar un juego de caracteres de 15 puntos de alto. Los datos que describen el juego de
 * // caracteres se indican en JuegoAlpha15.c.
 *
 * LCD_dibujaCaracterAlpha(10, 10, 'A', 0xFFFF0000, & juegoAlpha15, 0, 100);
 * // Dibuja el carácter 'A' en rojo situando su esquina superior izquierda en (10, 10), utilizando el juego de
 * // caracteres juegoAlpha15 y mezclando sus colores.
 * @endcode
 *
 * @param x Coordenada X donde se dibuja el carácter
 * @param y Coordenada Y donde se dibuja el carácter
 * @param caracter Carácter que se va a dibujar
 * @param color Color con el que se va a dibujar
 * @param pJuegoCaracteres Puntero a la estructura donde se describe el juego de caracteres utilizado.
 * @param enBlancoYNegro Buleano. Cuando es cierto, el color se convierte a niveles de gris. 
 * @param transparencia Entero entre 0=transparente y 100=opaco para indicar un cierto grado de transparencia.
 *
 * @see LCD_JuegoCaracteresAlpha, LCD_anchoCaracter(), LCD_dibujaCadenaCaracteresAlpha().
 */
 
 
void LCD_dibujaCaracterAlpha(uint16_t x, uint16_t y, char caracter, uint32_t color,
		const LCD_JuegoCaracteresAlpha * pJuegoCaracteres,
		int enBlancoYNegro, int transparencia);

/**
 * @brief Ancho de un carácter expresado en puntos.
 *
 * Devuelve el número de puntos de ancho necesarios para representar un carácter utilizando
 * un juego de caracteres determinado.
 *
 * @param caracter Carácter del cual se desea obtener su ancho
 * @param pJuegoCaracteres Puntero a la estructura donde se describe el juego de caracteres utilizado.
 * @return Devuelve el número de puntos que ocupa el carácter en horizontal.
 *
 * @see LCD_JuegoCaracteresAlpha, LCD_anchoCadenaCaracteres()
 */
uint16_t LCD_anchoCaracterAlpha(char caracter, const LCD_JuegoCaracteresAlpha * pJuegoCaracteres);


/**
 * @brief Ancho de una cadena de caracteres expresado en puntos.
 *
 * Devuelve el número de puntos de ancho necesarios para representar una cadena de caracteres utilizando
 * un juego de caracteres determinado y con una cierta separación entre caracteres consecutivos.
 *
 * @param cadena Cadena de caracteres de la cual se desea obtener su ancho
 * @param pJuegoCaracteres Puntero a la estructura donde se describe el juego de caracteres utilizado.
 * @param separacion Separación en puntos entre dos caracteres consecutivos.
 *
 * @return Devuelve el número de puntos que ocupa la cadena en horizontal.
 *
 * @see LCD_JuegoCaracteresAlpha, LCD_anchoCaracter()
 */
uint16_t LCD_anchoCadenaCaracteresAlpha(const char* cadena,
	const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, uint16_t separacion);


/**
 * @brief Dibuja una cadena de caracteres.
 *
 * Dibuja la cadena de caracteres `cadena` situándola en una posición, utilizando un juego de caracteres,
 * en un color,
 * pudiendo visualizarla en niveles de gris y aplicarle transparencia.
 *
 * Se pueden visualizar los caracteres de la tabla ASCII desde la posición 32 hasta la 126.
 *
 * Además se han incluido las letras acentuadas y eñe, en minúsculas y mayúsculas, y algunos signoscon los
 * siguientes códigos:
 * - á = '\\x7f'
 * - Á = '\\x80'
 * - é = '\\x81'
 * - É = '\\x82'
 * - í = '\\x83'
 * - Í = '\\x84'
 * - ó = '\\x85'
 * - Ó = '\\x86'
 * - ú = '\\x87'
 * - Ú = '\\x88'
 * - ñ = '\\x89'
 * - Ñ = '\\x8a'
 * - ¿ = '\\x8b'
 * - ¡ = '\\x8c'
 * - € = '\\x8d'
 * - º = '\\x8e'
 *
 * Ejemplo:
 * @code{.c}
 * #include <JuegoAlpha15.h>
 * // Incluye la declaración de la estructura juegoAlpha15 de tipo LCD_JuegoCaracteresAlpha para
 * // manejar un juego de caracteres de 15 puntos de alto. Los datos que describen el juego de
 * // caracteres se indican en JuegoAlpha15.c.
 *
 * LCD_dibujaCadenaCaracteresAlpha(10, 10, "Hola", 0xFF00FF00, & juegoAlpha15, 0, 100);
 * // Dibuja la cadena "Hola" en verde, situando su esquina superior izquierda en (10, 10), utilizando el
 * // juego de caracteres juegoAlpha15.
 *
 * LCD_dibujaCadenaCaracteresAlpha(10, 40, "Ca\x89\x85n: 7\x8d", 0xFFFF0000, & juegoAlpha15, 0, 100);
 * // Dibuja la cadena "Cañón: 7€" en rojo, situando su esquina superior izquierda en (10, 40), utilizando
 * // el juego de caracteres juegoAlpha15.
 * @endcode
 *
 * @param xCadena Coordenada X donde se dibuja la cadena.
 * @param yCadena Coordenada Y donde se dibuja la cadena.
 * @param cadena Cadena de caracteres que se va a dibujar.
 * @param color Color con el que se va a dibujar.
 * @param separacion Separación horizontal en puntos entre caracteres consecutivos. 
 * @param pJuegoCaracteres Puntero a la estructura donde se describe el juego de caracteres utilizado.
 * @param enBlancoYNegro Buleano. Cuando es cierto, el color se convierte a niveles de gris. 
 * @param transparencia Entero entre 0=transparente y 100=opaco para indicar un cierto grado de transparencia.
 *
 * @see LCD_JuegoCaracteresAlpha(), LCD_dibujaCaracterAlpha().
 */
void LCD_dibujaCadenaCaracteresAlpha(uint16_t xCadena, uint16_t yCadena, const char* cadena, uint32_t color,
	uint16_t separacion,
	const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, int enBlancoYNegro, int transparencia);

//void LCD_dibujaCadenaLargaCaracteresAlpha(uint16_t xCadena, uint16_t yCadena, const char* cadena, uint32_t color, uint16_t separacion, const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, int enBlancoYNegro, int transparencia);


int LCD_SentidoHorizontal();

#endif /* INC_PANTALLA_H_ */