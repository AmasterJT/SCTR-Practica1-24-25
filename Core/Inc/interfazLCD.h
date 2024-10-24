
#ifndef INTERFAZLCD_H_
#define INTERFAZLCD_H_

#include <stdint.h>
#include <pantallaLCD.h>

/**
  * @file interfazLCD.h
  * @author SCTR
  *
  * @brief Recursos para interfaces de usuario en la pantalla LCD de la placa STM32F429I-DISC1.
  *
  * Biblioteca de estructuras de datos y funciones codificadas en lenguaje C para implantar diferentes
  * elementos de interfaz de usuario para aplicaciones que utilicen la pantalla
  * LCD de una placa STM32F429I-DISC1. Es una pantalla táctil en color de 240x320 puntos.
  *
  *
  * @mainpage
  *
  *
  * @section S1 Introducción
  *
  * Biblioteca de estructuras de datos y funciones codificadas en lenguaje C para implantar diferentes
  * elementos de interfaz de usuario para aplicaciones que utilicen la pantalla
  * LCD de una placa STM32F429I-DISC1. Es una pantalla táctil en color de 240x320 puntos.
  *
  * Utiliza la biblioteca pantallaLCD para la visualización en pantalla. Los colores e imágenes se
  * manejan según se explica en la documentación de esa biblioteca.
  *
  *
  * @section S2 Botones
  *
  * Cada botón se muestra utilizando una imagen.
  * Se le asocia una función que se ejecuta cuando se pulsa el botón en la pantalla.
  * Se puede hacer visible o invisible. Se puede habilitar o deshabilitar (en cuyo caso se muestra
  * semitransparente y en niveles de gris y no ejecuta la función si se pulsa).
  * Se puede modificar el texto, su color y la imagen.
  *
  * Ejemplo:
  * @code{.c}
  * int contador = 0;  // Entero para contaje
  *
  * void fBoton() {  // Función que atiende la pulsación sobre el botón
  *     contador = 0;  // Resetea el contador
  * }
  *
  * void StartDefaultTask(void *argument) {
  *
  *     char cadena[20];  // Cadena de caracteres para mostrar el contador como texto
  *
  *     LCD_inicializa2Buffers();  // Inicializa la pantalla para utilizar doble frame buffer
  *
  *     LCD_Boton boton;  // Estructura para manejar un botón
  *
  *     LCD_inicializaBoton(10, 10, 80, 29, imagenBoton, "Reset", &juegoAlpha15, 1, 0xFF000000,
  *         fBoton, 1, 1, &boton);
  *     // Inicializa un botón representado por la estructura 'boton'. Muestra la imagen descrita en la
  *     // matriz de bytes 'imagenBoton'. La esquina superior izquierda se situa en (10, 10) y tiene
  *     // 80 puntos de ancho por 29 puntos de alto. Inicialmente se muestra visible y habilitado.
  *     // Sobre el botón se muestra el texto "Reset" utilizando un juego de caracteres 'juegoAlpha15',
  *     // con 1 punto de separación entre caracteres consecutivos y en color negro 0xFF000000. Cuando se
  *     // pulsa el botón, se ejecuta la función fBoton().
  *
  *     while(1) {
  *         LCD_setFondoColor(0xFF0000FF);  // Borra el frame buffer oculto con el color 0xFF0000FF
  *
  *         contador ++;  // Incrementa un contador
  *
  *         sprintf(cadena, "%d", contador);  // Convierte el entero a cadena de caracteres
  *
  *         LCD_dibujaCadenaCaracteresAlpha(10, 50, cadena, 0xFFFFFFFF, 1, &juegoAlpha15, 0, 100);
  *         // Visualiza el contador en la posición (10, 50) en blanco separando con 1 punto los 
  *         // caracteres consecutivos y utilizando el juego de caracteres juegoAlpha15
  *
  *         LCD_actualizaPulsacion();  
  *         // Comprueba en la interfaz táctil si hubo alguna pulsación y determina dónde se ha pulsado
  *
  *         LCD_atiendeBoton(&boton);
  *         // Dibuja el botón en el frame buffer oculto.
  *         // Ejecuta la función asignada al botón si se pulsó sobre él.
  *
  *         LCD_intercambiaBuffers();  // Hace que el frame buffer oculto sea visible y el visible sea oculto
  *     }
  * }
  * @endcode
  *
  * @see LCD_Boton, LCD_inicializaBoton(), LCD_setVisibilidadBoton(), LCD_setHabilitacionBoton(),
  *     LCD_setTextoBoton(), LCD_setColorTextoBoton(), LCD_setImagenBoton(), LCD_atiendeBoton()
  *
  *
 */



///////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief Estructura para manejo de un botón.
 *
 * Representa a un botón que se muestra en pantalla en una posición con una imagen de unas dimensiones,
 * de forma que cuando se pulsa se ejecuta el código de una función. Se puede establecer un texto que se
 * muestra sobre el botón.
 *
  * @see LCD_inicializaBoton(), LCD_setVisibilidadBoton(), LCD_setHabilitacionBoton(),
  *     LCD_setTextoBoton(), LCD_setColorTextoBoton(), LCD_setImagenBoton(), LCD_atiendeBoton() */
typedef struct {
    /** @brief Coordenada X de la esquina superior izquierda */
    uint16_t x;
    /** @brief Coordenada Y de la esquina superior izquierda */
    uint16_t y;
    /** @brief Anchura del botón en puntos */
    uint16_t ancho;
    /** @brief Altura del botón en puntos */
    uint16_t alto;
    /** @brief Imagen para visualizar el botón */
    const uint8_t * imagen;
    /** @brief Texto a mostrar sobre el botón, como máximo 30 caracteres */
    char texto[31];
    /** @brief Juego de caracteres utilizado para mostrar el texto */
    const LCD_JuegoCaracteresAlpha * pJuegoCaracteres;
    /** @brief Separación en puntos entre caracteres consecutivos */
    uint8_t separacion;
    /** @brief Color del texto en formato ARGB de 32 bits */
    uint32_t colorTexto;
    /** @brief Posición del texto dentro del botón */
    uint16_t xTexto, yTexto;
    /** @brief Puntero a la función a ejecutar cuando se pulsa el botón */
    void (* funcion)();
    /** @brief Buleano cierto si el botón está habilitado. Si no está habilitado, se muestra
     * semitransparente y en niveles de gris y si se pulsa no se ejecuta la función. */
    int habilitado;
    /** @brief Buleano cierto si el botón está pulsado. */
    int pulsado;
    /** @brief Buleano cierto si el botón está visible. Si está invisible, no se dibuja. */
    int visible;
} LCD_Boton;


/**
 * @brief Inicializa una estructura de tipo LCD_Boton.
 *
 * Ejemplo:
 * @code{.c}
 * void f() {  // Función a ejecutar cuando se pulsa el botón
 *     ...  // Aquí irían sus instrucciones
 * }
 *
 * const uint8_t im[] = { ... };
 * // Imagen para mostrar el botón. En ... se indican los colores de sus puntos.
 *
 * LCD_Boton b;  // Estructura para manejar un botón
 *
 * LCD_inicializaBoton(10, 10, 80, 29, boton1Verde_80x29, "Reset", &juegoAlpha15, 1, 0xFF000000,
 *     f, 1, 1, &boton);
 * // Inicializa un botón representado por la estructura 'boton'. Muestra la imagen descrita en la
 * // matriz de bytes 'boton1Verde_80x29'. La esquina superior izquierda se situa en (10, 10) y tiene
 * // 80 puntos de ancho por 29 puntos de alto. Inicialmente se muestra visible y en color original.
 * // Sobre el botón se muestra el texto "Reset" utilizando un juego de caracteres 'juegoAlpha15',
 * // con 1 punto de separación entre caracteres consecutivos y en color negro 0xFF000000. Cuando se
 * // pulsa el botón, se ejecuta la función f().
 * @endcode
 *
 * @param x Coordenada X de la esquina superior izquierda.
 * @param y Coordenada Y de la esquina superior izquierda.
 * @param ancho Anchura del botón
 * @param alto Altura del botón
 * @param imagen Puntero a dónde están guardados los colores de la imagen utilizada para dibujar el botón,
 * el color de cada punto expresado en formato ARGB en 32 bits.
 * @param texto Texto a mostrar sobre el botón, como máximo 30 caracteres.
 * @param pJuegoCaracteres Puntero a una estructura de tipo LCD_JuegoCaracteresAlpha para indicar con
 *     qué juego de caracteres se muestra el texto.
 * @param separacion Separación en puntos entre caracteres consecutivos.
 * @param funcion Puntero a la función a ejecutar cuando se pulsa el botón.
 * @param habilitado Buleano para habilitar o deshabilitar el botón. Si no está habilitado, se muestra
 * semitransparente y en niveles de gris y si se pulsa no se ejecuta la función.
 * @param visible Buleano para mostrar u ocultar el botón.
 * @param pBoton Puntero a la estructura que hay que inicializar.
 *
 * @see LCD_Boton, LCD_setVisibilidadBoton(), LCD_setHabilitacionBoton(),
 *     LCD_setTextoBoton(), LCD_setColorTextoBoton(), LCD_setImagenBoton(), LCD_atiendeBoton() */
void LCD_inicializaBoton(uint16_t x, uint16_t y, uint16_t ancho, uint16_t alto, const uint8_t * imagen,
    char * texto, const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, uint8_t separacion, uint32_t colorTexto,
    void (*funcion)(), int habilitado,
    int visible, LCD_Boton * pBoton);

/**
 * @brief Establece la visibilidad de un botón.
 *
 * Ejemplo:
 * @code{.c}
 * LCD_Boton b;  // Estructura para representar a un botón
 * LCD_inicializaBoton(..., & b);  // Inicializa la estructura con los parámetros que se indicarían en ...
 * LCD_setVisibilidadBoton(0, & b);  // Oculta el botón
 * @endcode
 *
 * @param visibilidad Buleano que establece si el botón va a ser visible o invisible.
 * @param pBoton Puntero a la estructura que representa el botón.
 *
 * @see LCD_Boton, LCD_inicializaBoton(), LCD_setHabilitacionBoton(),
 *     LCD_setTextoBoton(), LCD_setColorTextoBoton(), LCD_setImagenBoton(), LCD_atiendeBoton() */
void LCD_setVisibilidadBoton(int visibilidad, LCD_Boton * pBoton);

/**
 * @brief Habilita o deshabilita un botón.
 *
 * Cuando un botón está habilitado y se pulsa, se ejecuta la función asociada al botón y se muestra
 * en pantalla con los colores originales de su imagen. Cuando está deshabilitado no se ejecuta la función
 * y el botón se muestra semitransparente en niveles de gris.
 *
 * Ejemplo:
 * @code{.c}
 * LCD_Boton b;  // Estructura para representar a un botón
 * LCD_inicializaBoton(..., & b);  // Inicializa la estructura con los parámetros que se indicarían en ...
 * LCD_setHabilitacionBoton(0, & b);  // Deshabilita el botón
 * @endcode
 *
 * @param habilitacion Buleano que establece si el botón va a estar habilitado o deshabilitado.
 * @param pBoton Puntero a la estructura que representa el botón.
 *
 * @see LCD_Boton, LCD_inicializaBoton(), LCD_setVisibilidadBoton(), 
 *     LCD_setTextoBoton(), LCD_setColorTextoBoton(), LCD_setImagenBoton(), LCD_atiendeBoton() */
void LCD_setHabilitacionBoton(int habilitacion, LCD_Boton * pBoton);

/**
 * @brief Modifica el texto mostrado sobre un botón.
 *
 * Establece el texto mostrado sobre el botón.
 *
 * Ejemplo:
 * @code{.c}
 * LCD_Boton b;  // Estructura para representar a un botón
 * LCD_inicializaBoton(..., & b);  // Inicializa la estructura con los parámetros que se indicarían en ...
 * LCD_setTextoBoton("Conectar", & b);  // Muestra el texto "Conectar" sobre el botón
 * @endcode
 *
 * @param texto Cadena de caracteres mostrada sobre el botón.
 * @param pBoton Puntero a la estructura que representa el botón.
 *
 * @see LCD_Boton, LCD_inicializaBoton(), LCD_setVisibilidadBoton(), LCD_setHabilitacionBoton(),
 *     LCD_setColorTextoBoton(), LCD_setImagenBoton(), LCD_atiendeBoton() */
void LCD_setTextoBoton(const char* texto, LCD_Boton * pBoton);

/**
 * @brief Establece el color del texto mostrado sobre un botón.
 *
 * Ejemplo:
 * @code{.c}
 * LCD_Boton b;  // Estructura para representar a un botón
 * LCD_inicializaBoton(..., & b);  // Inicializa la estructura con los parámetros que se indicarían en ...
 * LCD_setColorTextoBoton(0xFFFF0000, & b);  // El texto se muestra en rojo
 * @endcode
 *
 * @param color Entero de 32 bits que indica el color del texto en formato ARGB.
 * @param pBoton Puntero a la estructura que representa el botón.
 *
 * @see LCD_Boton, LCD_inicializaBoton(), LCD_setVisibilidadBoton(), LCD_setHabilitacionBoton(),
 *     LCD_setTextoBoton(), LCD_setImagenBoton(), LCD_atiendeBoton() */
void LCD_setColorTextoBoton(uint32_t color, LCD_Boton * pBoton);

/**
 * @brief Establece la imagen del botón.
 *
 * Ejemplo:
 * @code{.c}
 * const uint8_t imagen[] = {...};  // Imagen a mostrar
 * LCD_Boton b;  // Estructura para representar a un botón
 * LCD_inicializaBoton(..., & b);  // Inicializa la estructura con los parámetros que se indicarían en ...
 * LCD_setImagenBoton(imagen, & b);  // Establede la imagen
 * @endcode
 *
 * @param imagen Puntero a una zona de memoria donde están los colores de los puntos de la imagen.
 * @param pBoton Puntero a la estructura que representa el botón.
 *
 * @see LCD_Boton, LCD_inicializaBoton(), LCD_setVisibilidadBoton(), LCD_setHabilitacionBoton(),
 *     LCD_setTextoBoton(), LCD_setColorTextoBoton(), LCD_atiendeBoton() */
 void LCD_setImagenBoton(const uint8_t * imagen, LCD_Boton * pBoton);

/**
 * @brief Atiende la posible pulsación sobre el botón y lo dibuja.
 *
 * Comprueba si se ha pulsado el botón y si es así y está habilitado y visible, ejecuta la función asociada.
 * Dibuja el botón en el frame buffer oculto. 
 *
 * La llamada a esta función debería de realizarse desde un bucle en la tarea que se encarga de la
 * visualización en pantalla.
 *
 * Ejemplo:
 * @code{.c}
 * LCD_Boton b;  // Estructura para manejar un botón
 *
 * LCD_inicializaBoton(..., & b);  // Inicializa la estructura según los parámetros indicados en ...
 *
 * while(1) {
 *     LCD_actualizaPulsacion();  // Revisa el estado de la interfaz táctil
 *     LCD_atiendeBoton(& b);  // Atiende una posible pulsación sobre el botón y lo dibuja
 *     LCD_intercambiaBuffers(); 
 * }
 * @endcode
 *
 * @see LCD_Boton, LCD_inicializaBoton(), LCD_setVisibilidadBoton(), LCD_setHabilitacionBoton(),
 *     LCD_setTextoBoton(), LCD_setColorTextoBoton(), LCD_setImagenBoton(), 
 */
void LCD_atiendeBoton(LCD_Boton * pBoton);



#endif /* INTERFAZLCD_H_ */
