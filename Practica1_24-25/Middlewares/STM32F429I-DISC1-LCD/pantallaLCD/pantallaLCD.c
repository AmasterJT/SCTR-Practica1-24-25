
//12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567

#include <stdio.h>  // Para sprintf()
#include <stdlib.h>  // para abs()
#include <cmsis_os2.h>  // para osDelay()
#include <pantallaLCD.h>


// -----------------------------------------------------------------------------------------
// Variables estáticas accesibles sólo desde el código de este archivo. 
// Contienen información sobre la pantalla LCD.

static uint16_t lcd_ancho, lcd_alto;  // Ancho y alto de la pantalla en puntos
static uint32_t* lcd_buffers[2];  // Direcciones de memoria de los frame buffers
static int lcd_bufferOculto;  // Frame buffer oculto donde se dibuja, puede ser 0 o 1
static uint16_t lcd_xPulsacion, lcd_yPulsacion;  // Coordenadas del punto de la última pulsación
static int lcd_pulsando;  // Buleano cierto si la pantalla se está pulsando
static int horizontal;  // Buleano cierto si la pantalla se utiliza en orientación horizontal

static int invertida;

// -----------------------------------------------------------------------------------------

void LCD_inicializa2Buffers(int enHorizontal, int estaInvertida) {

	horizontal = enHorizontal;  // Guarda el parámetro
	invertida = estaInvertida;

    BSP_LCD_Init();
    BSP_LCD_Init();  // Inicializa la pantalla LCD

    if (horizontal) {
    	lcd_ancho = BSP_LCD_GetYSize();  // Obtiene el ancho de la pantalla
    	lcd_alto = BSP_LCD_GetXSize();  // Obtiene el alto de la pantalla
    } else {
        lcd_ancho = BSP_LCD_GetXSize();  // Obtiene el ancho de la pantalla
        lcd_alto = BSP_LCD_GetYSize();  // Obtiene el alto de la pantalla
    }
    lcd_buffers[0] = (uint32_t*)LCD_FRAME_BUFFER_LAYER_0;  // Dirección del frame buffer número 0
    lcd_buffers[1] = (uint32_t*)LCD_FRAME_BUFFER_LAYER_1;  // Dirección del frame buffer número 1

    lcd_pulsando = 0;  // Inicialmente la pantalla no se está pulsando

    BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER_LAYER_0);  // Inicializa frame buffer 0
    BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER_LAYER_1);  // Inicializa frame buffer 1

    lcd_bufferOculto = 0;  // Selecciona el frame buffer 0 para dibujar

    BSP_TS_Init(lcd_ancho, lcd_alto);
    // Indica a la interfaz táctil el ancho y alto de la pantalla en puntos
}

// -----------------------------------------------------------------------------------------

uint16_t LCD_ancho() {
    // Devuelve el ancho de la pantalla en puntos

    return lcd_ancho;
}

// -----------------------------------------------------------------------------------------

uint16_t LCD_alto() {
    // Devuelve el alto de la pantalla en puntos

    return lcd_alto;
}

// -----------------------------------------------------------------------------------------

int LCD_pulsando() {
	// Devuelve un buleano que indica si se está pulsando la pantalla

	return lcd_pulsando;
}

// -----------------------------------------------------------------------------------------

void LCD_resetPulsacion() {
	lcd_pulsando = 0;  // Indica que no está pulsada para que no se traten pulsaciones
}

// -----------------------------------------------------------------------------------------

uint16_t LCD_xPulsacion() {
	// Devuelve la coordenada X del punto donde se detectó la última pulsación

	return lcd_xPulsacion;
}

// -----------------------------------------------------------------------------------------

uint16_t LCD_yPulsacion() {
	// Devuelve la coordenada Y del punto donde se detectó la última pulsación

	return lcd_yPulsacion;
}

// -----------------------------------------------------------------------------------------

void LCD_actualizaPulsacion() {
	// Actualiza el estado de pulsación de la pantalla

    TS_StateTypeDef estadoTactil;  // Estructura para datos de interfaz táctil

    BSP_TS_GetState(&estadoTactil);  // Obtiene el estado de la interfaz táctil

    if (estadoTactil.TouchDetected) {  // Si se detectó pulsación
    	if (horizontal) {
    		lcd_xPulsacion = estadoTactil.Y;
    		lcd_yPulsacion = 239 - estadoTactil.X;
    	} else {
            lcd_xPulsacion = estadoTactil.X;  // Recoge coordenada X
            lcd_yPulsacion = 319 - estadoTactil.Y;  // y coordenada Y
    	}
        lcd_pulsando = 1;  // Indica que se pulsó
    } else lcd_pulsando = 0;  // Indica que no se pulsó
}

// -----------------------------------------------------------------------------------------

void LCD_setFondoColor(uint32_t color) {
    // Borra toda la pantalla y establece como fondo el color indicado por parámetro

    LCD_dibujaRectanguloRellenoOpaco(0, 0, lcd_ancho, lcd_alto, color);
    // Pone todos los puntos en el frame buffer oculto al color indicado
}

// -----------------------------------------------------------------------------------------

void LCD_setFondoImagen(const uint8_t * imagen) {
    // Borra toda la pantalla y establece como fondo la imagen de 240x320 puntos indicada por parámetro

    LCD_dibujaImagenOpaca(0, 0, lcd_ancho, lcd_alto, imagen);
    // Dibuja la imagen de fondo
}

// -----------------------------------------------------------------------------------------

void LCD_intercambiaBuffers() {
    // Cambia en qué frame buffer se dibuja y qué frame buffer se visualiza

    while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));  // Espera a que la GPU finalice sincronismo con pantalla
    if (lcd_bufferOculto == 0) {  // Si se dibujó en el buffer 0
        BSP_LCD_SetLayerVisible(1, DISABLE);  // Buffer 1 invisible
        BSP_LCD_SetLayerVisible(0, ENABLE);  // Buffer 0 visible
        lcd_bufferOculto = 1;  // Buffer donde se va a dibujar
    } else {
        BSP_LCD_SetLayerVisible(0, DISABLE);  // Buffer 0 invisible
        BSP_LCD_SetLayerVisible(1, ENABLE);  // Buffer 1 ivisible
        lcd_bufferOculto = 0;  // Buffer donde se dibuja
    }
}

// -----------------------------------------------------------------------------------------

void LCD_dibujaPunto(uint16_t x, uint16_t y, uint32_t color, int enBlancoYNegro, int transparencia) {
    // Dibuja un punto en coordenadas ('x', 'y') con el color indicado en 'color'
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a niveles de gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)
    uint8_t * pColor = (uint8_t*) &color;  // Para acceder a los bytes del nuevo color

    if (enBlancoYNegro) {  // Si hay que convertir a niveles de gris ...

        uint8_t gris = ((int)pColor[0] + pColor[1] + pColor[2]) / 3;
        // Obtiene la media de las componentes RGB

        pColor[0] = gris;
        pColor[1] = gris;
        pColor[2] = gris;
        // Guarda la media en las componentes RGB del color
    }

    uint8_t alpha = pColor[3] * transparencia / 100;
    // Canal alpha del nuevo color modificado por el grado de transparencia a aplicar

    uint32_t * p32;

  	if (invertida) {

  		 x = lcd_ancho - x;
		 y = lcd_alto - y;
    }

    if (horizontal){

    	p32 = lcd_buffers[lcd_bufferOculto] + (239 - y) + lcd_alto * x;
    }
    else{

    	p32 = lcd_buffers[lcd_bufferOculto] + y * lcd_ancho + x;

    }

    if (alpha > 0 && alpha < 255) {
        // Si el nuevo color es semitransparente, hay que mezclar

        uint8_t * p8 = (uint8_t*)p32;  // Dirección del punto en el frame buffer

        p8[0] = (p8[0] * (0xFF - alpha) + pColor[0] * alpha) / 0xFF;
        p8[1] = (p8[1] * (0xFF - alpha) + pColor[1] * alpha) / 0xFF;
        p8[2] = (p8[2] * (0xFF - alpha) + pColor[2] * alpha) / 0xFF;
        p8[3] = 0xFF;
        // Mezcla los colores

    } else if (alpha == 0xFF) { // El color es opaco y hay que sustituir el color
        pColor[3] = alpha;  // Le pone al nuevo color un alpha de 0xFF
        *p32 = color;
        // Copia el nuevo color en el frame buffer
    }
}

// -----------------------------------------------------------------------------------------

void LCD_dibujaPuntoOpaco(uint16_t x, uint16_t y, uint32_t color) {
// Dibuja un punto sin transparencia con un color opaco en una posición (x,y)

	if (horizontal)
		*(lcd_buffers[lcd_bufferOculto] + (239 - y) + lcd_alto * x) = color;
	else
        *(lcd_buffers[lcd_bufferOculto] + y * lcd_ancho + x) = color;
    // Copia el nuevo color en el frame buffer
}

// -----------------------------------------------------------------------------------------

void LCD_dibujaRectangulo(uint16_t xInicial, uint16_t yInicial, uint16_t ancho, uint16_t alto,
    uint32_t color, int enBlancoYNegro, int transparencia) {
    // Dibuja el contorno de un rectángulo cuya esquina superior izquierda está situada en (xInicial, yInicial) y
    // donde se indica el alto y ancho y el color.
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)

    for(int x = xInicial; x < xInicial + ancho; x++) { // Recorriendo el ancho del rectángulo
        LCD_dibujaPunto(x, yInicial, color, enBlancoYNegro, transparencia);
        LCD_dibujaPunto(x, yInicial + alto - 1, color, enBlancoYNegro, transparencia);
    }
    for(int y = yInicial; y < yInicial + alto; y++) { // Recorriendo el alto del rectángulo
        LCD_dibujaPunto(xInicial, y, color, enBlancoYNegro, transparencia);
        LCD_dibujaPunto(xInicial + ancho - 1, y, color, enBlancoYNegro, transparencia);
    }
}

// -----------------------------------------------------------------------------------------

void LCD_dibujaRectanguloRelleno(uint16_t xInicial, uint16_t yInicial, uint16_t ancho, uint16_t alto,
    uint32_t color, int enBlancoYNegro, int transparencia) {
    // Dibuja un rectángulo relleno cuya esquina superior izquierda está situada en (xInicial, yInicial) y
    // donde se indica el alto y ancho el color de sus puntos.
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)

    for(int x = xInicial; x < xInicial + ancho; x++)  // Recorriendo el lcd_ancho del rectángulo
        for(int y = yInicial; y < yInicial + alto; y++)  // y el alto
            LCD_dibujaPunto(x, y, color, enBlancoYNegro, transparencia);
            // Dibuja cada punto del rectángulo con su color
}

// -----------------------------------------------------------------------------------------

void LCD_dibujaRectanguloRellenoOpaco(uint16_t xInicial, uint16_t yInicial, uint16_t ancho, uint16_t alto,
    uint32_t color) {
// Dibuja un rectángulo relleno de un color opaco.
// 'xInicial' e 'yInicial' indican las coordenadas de la esquina superior izquierda.
// 'ancho' y 'alto' son las dimensiones del rectángulo.

	int yFinal = yInicial + alto - 1;
	int xFinal = xInicial + ancho - 1;
	if (horizontal) {
		uint32_t* p = lcd_buffers[lcd_bufferOculto] + (239 - yInicial - alto + 1) + lcd_alto * xInicial;
		uint16_t salto = lcd_alto - alto;
	    for(int x = xInicial; x <= xFinal; x++) { // Para cada fila de puntos
	        for(int y = yInicial; y <= yFinal; y++) // Recorre los puntos de la fila
	        	*(p++) = color;  // Establece el color del punto y apunta al siguiente
	        p += salto;  // Apunta al primer punto de la siguiente fila
        }
	} else {
		uint32_t* p = lcd_buffers[lcd_bufferOculto] + yInicial * lcd_ancho + xInicial;
		uint16_t salto = lcd_ancho - ancho;
	    for(int y = yInicial; y <= yFinal; y++) { // Para cada fila de puntos
	        for(int x = xInicial; x <= xFinal; x++) // Recorre los puntos de la fila
	        	*(p++) = color;  // Establece el color del punto y apunta al siguiente
	        p += salto;  // Apunta al primer punto de la siguiente fila
        }
	}
}

// -----------------------------------------------------------------------------------------

void LCD_dibujaLinea(int x0, int y0, int x1, int y1, uint32_t color, int enBlancoYNegro, int transparencia) {
    // Dibuja una línea que une el punto indicado en 'x0', 'y0' con el punto indicado en 'x1', 'y1'
    // en el color 'color' utilizando el algoritmo de Bressenham
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    while(1) {
        LCD_dibujaPunto(x0, y0, color, enBlancoYNegro, transparencia);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

// -----------------------------------------------------------------------------------------

static void dibujaPuntosCircunferencia(int xc, int yc, int x, int y, uint32_t color, int enBlancoYNegro,
    int transparencia) {
    // Utilizada por la función LCD_dibujaCircunferencia

    LCD_dibujaPunto(xc+x, yc+y, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc-x, yc+y, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc+x, yc-y, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc-x, yc-y, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc+y, yc+x, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc-y, yc+x, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc+y, yc-x, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc-y, yc-x, color, enBlancoYNegro, transparencia);
}


void LCD_dibujaCircunferencia(int xc, int yc, int r, uint32_t color, int enBlancoYNegro, int transparencia) {
    // Dibuja una circunferencia cuyo centro se indica en 'xc', 'yc', de radio 'r' y con el color
    // indicado en 'color' utilizando el algoritmo de Bressenham
    // https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)

    int x = 0, y = r;
    int d = 3 - 2 * r;
    dibujaPuntosCircunferencia(xc, yc, x, y, color, enBlancoYNegro, transparencia);
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else d = d + 4 * x + 6;
        dibujaPuntosCircunferencia(xc, yc, x, y, color, enBlancoYNegro, transparencia);
    }
}

// -----------------------------------------------------------------------------------------

static void dibujaPuntosCirculo(int xc, int yc, int x, int y, uint32_t color, int enBlancoYNegro,
    int transparencia) {
    // Utilizada por la función LCD_dibujaCirculo

	LCD_dibujaLinea(xc-x, yc+y, xc+x, yc+y, color, enBlancoYNegro, transparencia);
	LCD_dibujaLinea(xc-x, yc-y, xc+x, yc-y, color, enBlancoYNegro, transparencia);
	LCD_dibujaLinea(xc-y, yc+x, xc+y, yc+x, color, enBlancoYNegro, transparencia);
	LCD_dibujaLinea(xc-y, yc-x, xc+y, yc-x, color, enBlancoYNegro, transparencia);
}


void LCD_dibujaCirculo(int xc, int yc, int r, uint32_t color, int enBlancoYNegro, int transparencia) {
    // Dibuja un círculo cuyo centro se indica en 'xc', 'yc', de radio 'r' y con el color
    // indicado en 'color' utilizando el algoritmo de Bressenham
    // https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)

    int x = 0, y = r;
    int d = 3 - 2 * r;
    dibujaPuntosCirculo(xc, yc, x, y, color, enBlancoYNegro, transparencia);
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else d = d + 4 * x + 6;
        dibujaPuntosCirculo(xc, yc, x, y, color, enBlancoYNegro, transparencia);
    }
}

// -----------------------------------------------------------------------------------------

void LCD_dibujaImagen(uint16_t xImagen, uint16_t yImagen, uint16_t ancho, uint16_t alto,
    const uint8_t * imagen, int enBlancoYNegro, int transparencia) {
    // Dibuja una imagen situando su esquina superior izquierda en 'xImagen', 'yImagen', que tiene
    // una resolución de 'ancho' puntos en horizontal y 'alto' puntos en vertical. Los bytes que
    // expresan el color de todos sus puntos (cada punto en 4 bytes en formato ARGB)
    // se encuentran en 'imagen'.
    // La magen se convierte a niveles de gris si 'enBlancoYNegro' es cierto.
    // Se le aplica el grado de transparencia indicado en 'transparencia', de 0 a 100.

    uint32_t * p = (uint32_t*) imagen;  // Para acceder a cada punto por separado

    for(uint16_t y = yImagen; y < yImagen + alto; y++)  // Recorriendo filas
        for (uint16_t x = xImagen; x < xImagen + ancho; x++) {  // y columnas
            LCD_dibujaPunto(x, y, *p, enBlancoYNegro, transparencia);  // dibuja cada punto
            p++;  // Para acceder al color del siguiente punto
        }
}

// -----------------------------------------------------------------------------------------

void LCD_dibujaImagenOpaca(uint16_t xImagen, uint16_t yImagen, uint16_t ancho, uint16_t alto,
	const uint8_t * imagen) {

	uint16_t xFinal = xImagen + ancho - 1;  // Coordenada X máxima de la imagen
	uint16_t yFinal = yImagen + alto - 1;  // Coordenada Y máxima de la imagen
	uint32_t * pImagen = (uint32_t*) imagen;  // Para acceder a cada punto por separado

	if (horizontal) {  // Si pantalla en horizontal ...
		uint32_t * pFrameBuffer = lcd_buffers[lcd_bufferOculto] + (239 - yImagen - alto + 1) +
			lcd_alto * xImagen;  // Puntero al primer punto en el frame buffer
		uint16_t salto = lcd_alto - alto;  // Para saltar a la siguiente fila de puntos en la imagen
		for(uint16_t y = yImagen; y <= yFinal; y++) { // Recorriendo filas
			for (uint16_t x = xImagen; x <= xFinal; x++)   // y columnas
				* (pFrameBuffer++) = * (pImagen++);  // Copia los puntos en el frame buffer
            pFrameBuffer += salto;  // Salta a la siguiente fila
		}
	} else {  // Programación similar si pantalla en vertical
		uint32_t * pFrameBuffer = lcd_buffers[lcd_bufferOculto] + yImagen * lcd_ancho + xImagen;
		uint16_t salto = lcd_ancho - ancho;
		for(uint16_t x = xImagen; x <= xFinal; x++) {
			for (uint16_t y = yImagen; y < yFinal; y++)
				* (pFrameBuffer++) = * (pImagen++);
			pFrameBuffer += salto;
		}
	}
}

// -----------------------------------------------------------------------------------------

void LCD_dibujaCaracterAlpha(uint16_t x, uint16_t y, char caracter, uint32_t color,
	const LCD_JuegoCaracteresAlpha * pJuegoCaracteres,
    int enBlancoYNegro, int transparencia) {
    // Dibuja el carácter 'caracter' en las coordenadas 'x', 'y' utilizando el juego de caracteres
    // apuntado por 'pJuegoCaracteres'.
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris.
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100).

	const uint8_t * p = pJuegoCaracteres->caracteres + pJuegoCaracteres->posiciones[caracter - 32];
	// Apunta a donde se describe el caracter a visualizar

	int ancho = * p;  // El primer byte indica el ancho del carácter

	p++;
	for (int x1 = 0; x1 < ancho; x1++)  // Recorriendo el ancho
		for (int y1 = 0; y1 < pJuegoCaracteres->alto; y1++) {  // y el alto del carácter
			uint32_t colorPunto = color & 0x00FFFFFF;  // Utiliza las componentes RGB
			colorPunto |= p[x1 + y1 * ancho] << 24;  // Le añade la componente Alpha
			LCD_dibujaPunto(x + x1, y + y1, colorPunto, enBlancoYNegro, transparencia);  // DIbuja el punto
		}
}

// -----------------------------------------------------------------------------------------

uint16_t LCD_anchoCaracterAlpha(char caracter, const LCD_JuegoCaracteresAlpha * pJuegoCaracteres) {
	// Devuelve el ancho de un carácter en un juego de caracteres

	return pJuegoCaracteres->caracteres[pJuegoCaracteres->posiciones[caracter - 32]];
}

// -----------------------------------------------------------------------------------------

uint16_t LCD_anchoCadenaCaracteresAlpha(const char* cadena,
	const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, uint16_t separacion) {
	// Devuelve el ancho en puntos de un texto en un juego de caracteres, utilizando una cierta separación
	// entre caracteres consecutivos

	uint16_t resultado = (strlen(cadena) - 1) * separacion;  // Suma todas las separaciones

	int i = 0;

	while(cadena[i])   // Para cada carácter en el texto
		resultado += LCD_anchoCaracterAlpha(cadena[i++], pJuegoCaracteres);
		// Añade el ancho del carácter

	return resultado;
}

// -----------------------------------------------------------------------------------------

void LCD_dibujaCadenaCaracteresAlpha(uint16_t xCadena, uint16_t yCadena, const char* cadena, uint32_t color, uint16_t separacion,
    const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, int enBlancoYNegro, int transparencia) {
    // Dibuja la cadena de caracteres apuntada por 'cadena' a partir de las coordenadas 'x', 'y'
    // utilizando el juego de caracteres apuntado por 'pJuegoCaracteres'.
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)

    int i = 0;  // Índice para acceder a cada posición de la cadena

    uint16_t x = xCadena;  // Coordenada X de comienzo de la cadena

    while(cadena[i]) {  // Mientras no se llegue al 0 final de la cadena ...

        LCD_dibujaCaracterAlpha(x,
            yCadena, cadena[i], color, pJuegoCaracteres, enBlancoYNegro, transparencia);
        // Dibuja el carácter i-ésimo de la cadena

        x += LCD_anchoCaracterAlpha(cadena[i], pJuegoCaracteres);  // Añade el ancho del carácter

        for (int x1 = 0; x1 < separacion; x1++)
        	for (int y1 = 0; y1 < pJuegoCaracteres->alto; y1++)
        		LCD_dibujaPunto(x + x1, yCadena + y1, color, enBlancoYNegro, 0);

        x += separacion;  // Salta la separación entre caracteres

        i++;  // Para acceder al siguiente carácter
    }
}





