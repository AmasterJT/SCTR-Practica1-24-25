
#include <stdio.h>  // Para sprintf()
#include <stdlib.h>  // para abs()
#include <cmsis_os2.h>  // para osDelay()
#include <pantallaLCD.h>

#include <math.h>
#include <string.h>


// -----------------------------------------------------------------------------------------
// Variables estáticas accesibles sólo desde el código de este archivo. 
// Contienen información sobre la pantalla LCD.

static uint16_t lcd_ancho, lcd_alto;  // Ancho y alto de la pantalla en puntos
static uint32_t* lcd_buffers[2];  // Direcciones de memoria de los frame buffers
static int lcd_bufferOculto;  // Frame buffer oculto donde se dibuja, puede ser 0 o 1
static uint16_t lcd_xPulsacion, lcd_yPulsacion;  // Coordenadas del punto de la última pulsación
static int lcd_pulsada;  // Buleano cierto si la pantalla se ha pulsado

static int SentidoHorizontal; // Buleano cierto si se quiere usar la pantalla horizontal
static int pantallaInvertida; // segun el sentido de la pantalla invertimos o no la pantalla

// -----------------------------------------------------------------------------------------

void LCD_inicializa2Buffers(int Horizontal, int sentido) {

    BSP_LCD_Init();
    BSP_LCD_Init();  // Inicializa la pantalla LCD

    lcd_ancho = BSP_LCD_GetXSize();  // Obtiene el ancho de la pantalla en número de puntos
    lcd_alto = BSP_LCD_GetYSize();  // Obtiene el alto de la pantalla
    lcd_buffers[0] = (uint32_t*)LCD_FRAME_BUFFER_LAYER_0;  // Dirección del frame buffer número 0
    lcd_buffers[1] = (uint32_t*)LCD_FRAME_BUFFER_LAYER_1;  // Dirección del frame buffer número 1

    lcd_pulsada = 0;  // Inicialmente la pantalla no se está pulsando

    BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER_LAYER_0);  // Inicializa frame buffer 0
    BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER_LAYER_1);  // Inicializa frame buffer 1

    lcd_bufferOculto = 0;  // Selecciona el frame buffer 0 para dibujar

    BSP_TS_Init(lcd_ancho, lcd_alto);
    // Indica a la interfaz táctil el ancho y alto de la pantalla en puntos


    SentidoHorizontal = Horizontal;
    pantallaInvertida = sentido;
} // LCD_inicializa2Buffers

int LCD_SentidoHorizontal() {
        return SentidoHorizontal; // Devuelve el ancho de la pantalla en puntos
} // LCD_SentidoHorizontal

int Get_bufferOculto(){
	return lcd_bufferOculto;
} // Get_bufferOculto

void Set_buffreOculto(int bufferOculto){
	lcd_bufferOculto = bufferOculto;
} // Set_buffreOculto

uint16_t LCD_ancho() {
    return lcd_ancho; // Devuelve el ancho de la pantalla en puntos
} // LCD_ancho


uint16_t LCD_alto() {
    return lcd_alto; // Devuelve el alto de la pantalla en puntos
} // LCD_alto


int LCD_pulsada() {
	// Devuelve un buleano que indica si se ha pulsado la pantalla en la última llamada a
	// LCD_actualizaPulsacion(). Devuelve un buleano falso si se llamó a LCD_resetPulsacion().

	return lcd_pulsada;
} // LCD_pulsada


void LCD_resetPulsacion() {
	lcd_pulsada = 0;  // Indica que no está pulsada para que no se traten pulsaciones posteriormente
} // LCD_resetPulsacion


uint16_t LCD_xPulsacion() {
	// Devuelve la coordenada X del punto donde se detectó la última pulsación dependiendo de la orientacion de la pantalla

	if (LCD_SentidoHorizontal()) return 320-lcd_yPulsacion;
	else return lcd_xPulsacion;
} // LCD_xPulsacion


uint16_t LCD_yPulsacion() {
	// Devuelve la coordenada Y del punto donde se detectó la última pulsación  dependiendo de la orientacion de la pantalla
	if (LCD_SentidoHorizontal()) return lcd_xPulsacion;
	else return lcd_yPulsacion;
} // LCD_yPulsacion


void LCD_actualizaPulsacion() {
	// Actualiza el estado de pulsación de la pantalla

    TS_StateTypeDef estadoTactil;  // Estructura para datos de interfaz táctil

    BSP_TS_GetState(&estadoTactil);  // Obtiene el estado de la interfaz táctil

    if (estadoTactil.TouchDetected) {  // Si se detectó pulsación
        lcd_xPulsacion = estadoTactil.X;  // Recoge coordenada X
        lcd_yPulsacion = 320 - estadoTactil.Y;  // y coordenada Y
        lcd_pulsada = 1;  // Indica que está pulsada
    } else lcd_pulsada = 0;  // Indica que no está pulsada
} // LCD_actualizaPulsacion


void LCD_setFondoColor(uint32_t color) {
    // Borra toda la pantalla y establece como fondo el color indicado por parámetro

    LCD_dibujaRectanguloRellenoOpaco(0, 0, 240, 320, color);
    // Pone todos los puntos en el frame buffer oculto al color indicado
} // LCD_setFondoColor


void LCD_setFondoImagen(const uint8_t * imagen) {
    // Borra toda la pantalla y establece como fondo la imagen de 240x320 puntos indicada por parámetro

    LCD_dibujaImagenOpaca(0, 0, 240, 320, imagen);
    // Dibuja la imagen de fondo
} // LCD_setFondoImagen


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
} // LCD_intercambiaBuffers



void LCD_intercambiaBuffers2() {

	// Mostramos el Buffer 1 y cambiamos el Buffer oculto

    while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));  // Espera a que la GPU finalice sincronismo con pantalla


        BSP_LCD_SetLayerVisible(0, DISABLE);  // Buffer 0 invisible
        BSP_LCD_SetLayerVisible(1, ENABLE);  // Buffer 1 visible
        lcd_bufferOculto = 1;  // Buffer donde se va a dibujar


} // LCD_intercambiaBuffers2


void LCD_dibujaPunto(uint16_t x, uint16_t y, uint32_t color, int enBlancoYNegro, int transparencia) {
    // Dibuja un punto en coordenadas ('x', 'y') con el color indicado en 'color'
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a niveles de gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)

    uint8_t * pColor = (uint8_t*) &color;  // Para acceder a los bytes del nuevo color

    uint16_t X, Y; // ejes de la pantalla

    // Establecemos los ejes segun la orientacion de la pantalla en los cuatro sentidos
    if (SentidoHorizontal == 1){ // si es horizontal
    	if (pantallaInvertida  == 0)  // no hay que invertir la pantalla
    	{Y=320-x; X=y;} // pantalla horizontal normal
    	else {Y=x; X=240-y;} // pantalla horizontal invertida
    }
    else{ // si esta en vertical
    	if (pantallaInvertida  == 0) // no hay que invertir la pantalla
    	{Y=y;X=x;} // pantalla vertical normal
    	else {X=240-x; Y=320-y;} // pantalla vertical invertida
    }



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

    if (alpha > 0 && alpha < 255) {
        // Si el nuevo color es semitransparente, hay que mezclar

        uint8_t * pFrameBuffer = (uint8_t*)(lcd_buffers[lcd_bufferOculto] +
            Y * lcd_ancho + X);  // Dirección del punto en el frame buffer

        pFrameBuffer[0] = (pFrameBuffer[0] * (0xFF - alpha) + pColor[0] * alpha) / 0xFF;
        pFrameBuffer[1] = (pFrameBuffer[1] * (0xFF - alpha) + pColor[1] * alpha) / 0xFF;
        pFrameBuffer[2] = (pFrameBuffer[2] * (0xFF - alpha) + pColor[2] * alpha) / 0xFF;
        pFrameBuffer[3] = 0xFF;
        // Mezcla los colores

    } else if (alpha == 0xFF) { // El color es opaco y hay que sustituir el color
        pColor[3] = alpha;  // Le pone al nuevo color un alpha de 0xFF
        *(lcd_buffers[lcd_bufferOculto] + Y * lcd_ancho + X) = color;
        // Copia el nuevo color en el frame buffer
    }

} // LCD_dibujaPunto


void LCD_dibujaPuntoOpaco(uint16_t x, uint16_t y, uint32_t color) {
// Dibuja un punto sin transparencia con un color opaco en una posición (x,y)

    *(lcd_buffers[lcd_bufferOculto] + y * lcd_ancho + x) = color;
    // Copia el nuevo color en el frame buffer
} // LCD_dibujaPuntoOpaco


void LCD_dibujaRectangulo(uint16_t xInicial, uint16_t yInicial, uint16_t ancho, uint16_t alto,
    uint32_t color, int enBlancoYNegro, int transparencia) {
    // Dibuja el contorno de un rectángulo cuya esquina superior izquierda está situada en (xInicial, yInicial) y
    // donde se indica el alto y ancho y el color.
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 100) a transparencia original (valor 0)
	transparencia = 100 - transparencia;

    for(int x = xInicial; x < xInicial + ancho; x++) { // Recorriendo el ancho del rectángulo
        LCD_dibujaPunto(x, yInicial, color, enBlancoYNegro, transparencia);
        LCD_dibujaPunto(x, yInicial + alto - 1, color, enBlancoYNegro, transparencia);
    }
    for(int y = yInicial; y < yInicial + alto; y++) { // Recorriendo el alto del rectángulo
        LCD_dibujaPunto(xInicial, y, color, enBlancoYNegro, transparencia);
        LCD_dibujaPunto(xInicial + ancho - 1, y, color, enBlancoYNegro, transparencia);
    }
} // LCD_dibujaRectangulo


void LCD_dibujaRectanguloRelleno(uint16_t xInicial, uint16_t yInicial, uint16_t ancho, uint16_t alto,
    uint32_t color, int enBlancoYNegro, int transparencia) {
    // Dibuja un rectángulo relleno cuya esquina superior izquierda está situada en (xInicial, yInicial) y
    // donde se indica el alto y ancho el color de sus puntos.
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 100) a transparencia original (valor 0)

    for(int x = xInicial; x < xInicial + ancho; x++)  // Recorriendo el lcd_ancho del rectángulo
        for(int y = yInicial; y < yInicial + alto; y++)  // y el alto
            LCD_dibujaPunto(x, y, color, enBlancoYNegro, 100-transparencia);
            // Dibuja cada punto del rectángulo con su color
} // LCD_dibujaRectanguloRelleno


void LCD_dibujaRectanguloRellenoOpaco(uint16_t xInicial, uint16_t yInicial, uint16_t ancho, uint16_t alto,
    uint32_t color) {
// Dibuja un rectángulo relleno de un color opaco.
// 'xInicial' e 'yInicial' indican las coordenadas de la esquina superior izquierda.
// 'ancho' y 'alto' son las dimensiones del rectángulo.

	uint32_t* p = lcd_buffers[lcd_bufferOculto] + yInicial * lcd_ancho + xInicial;
	uint16_t salto = lcd_ancho - ancho;
	int yFinal = yInicial + alto - 1;
	int xFinal = xInicial + ancho - 1;
    for(int y = yInicial; y <= yFinal; y++) { // Para cada fila de puntos
        for(int x = xInicial; x <= xFinal; x++) // Recorre los puntos de la fila
        	*(p++) = color;  // Establece el color del punto y apunta al siguiente
        p += salto;  // Apunta al primer punto de la siguiente fila
    }
} // LCD_dibujaRectanguloRellenoOpaco

void LCD_dibujaCuadrado(uint16_t xInicial, uint16_t yInicial, uint16_t lado,
    uint32_t color, int enBlancoYNegro, int transparencia) {

	LCD_dibujaRectanguloRelleno(xInicial, yInicial, lado, lado, color, enBlancoYNegro, transparencia);
} // LCD_dibujaCuadrado

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
} // LCD_dibujaLinea



static void dibujaPuntosCircunferencia(int xc, int yc, int x, int y, uint32_t color, int enBlancoYNegro,
    int transparencia) {
    // Utilizada por la función dibujaCirculo

    LCD_dibujaPunto(xc+x, yc+y, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc-x, yc+y, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc+x, yc-y, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc-x, yc-y, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc+y, yc+x, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc-y, yc+x, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc+y, yc-x, color, enBlancoYNegro, transparencia);
    LCD_dibujaPunto(xc-y, yc-x, color, enBlancoYNegro, transparencia);
} // dibujaPuntosCircunferencia


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
} // LCD_dibujaCircunferencia


static void dibujaPuntosCirculo(int xc, int yc, int x, int y, uint32_t color, int enBlancoYNegro,
    int transparencia) {
    // Utilizada por la función dibujaCirculo

	LCD_dibujaLinea(xc-x, yc+y, xc+x, yc+y, color, enBlancoYNegro, transparencia);
	LCD_dibujaLinea(xc-x, yc-y, xc+x, yc-y, color, enBlancoYNegro, transparencia);
	LCD_dibujaLinea(xc-y, yc+x, xc+y, yc+x, color, enBlancoYNegro, transparencia);
	LCD_dibujaLinea(xc-y, yc-x, xc+y, yc-x, color, enBlancoYNegro, transparencia);
} //dibujaPuntosCirculo


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
} // LCD_dibujaCirculo


void LCD_dibujaImagen(uint16_t xImagen, uint16_t yImagen, uint16_t ancho, uint16_t alto,
    const uint8_t * imagen, int enBlancoYNegro, int transparencia) {
    // Dibuja una imagen situando su esquina superior izquierda en 'xImagen', 'yImagen', que tiene
    // una resolución de 'ancho' puntos en horizontal y 'alto' puntos en vertical. Los bytes que
    // expresan el color de todos sus puntos (cada punto en 4 bytes en formato ARGB)
    // se encuentran en 'imagen'.
    // La magen se convierte a niveles de gris si 'enBlancoYNegro' es cierto.
    // Se le aplica el grado de transparencia indicado en 'transparencia', de 0 a 100.

	transparencia = 100 - transparencia;

	uint32_t * p = (uint32_t*) imagen;  // Para acceder a cada punto por separado

    for(uint16_t y = yImagen; y < yImagen + alto; y++)  // Recorriendo filas
        for (uint16_t x = xImagen; x < xImagen + ancho; x++) {  // y columnas
        	LCD_dibujaPunto(x, y, *p, enBlancoYNegro, transparencia);  // dibuja cada punto
            p++;  // Para acceder al color del siguiente punto
        }
} // LCD_dibujaImagen


void LCD_dibujaImagenOpaca(uint16_t xImagen, uint16_t yImagen, uint16_t ancho, uint16_t alto,
	  const uint8_t * imagen) {
    // Dibuja una imagen situando su esquina superior izquierda en 'xImagen', 'yImagen', que tiene
    // una resolución de 'ancho' puntos en horizontal y 'alto' puntos en vertical. Los bytes que
    // expresan el color de todos sus puntos (cada punto en 4 bytes en formato ARGB)
    // se encuentran en 'imagen'. La imagen es opaca, el canal Alpha de todos sus puntos es 0xFF.
    
	uint32_t * pFila = lcd_buffers[lcd_bufferOculto] + yImagen * lcd_ancho + xImagen;
	uint32_t * pFrameBuffer = pFila;
	uint32_t * p = (uint32_t*) imagen;  // Para acceder a cada punto por separado
    for(uint16_t y = yImagen; y < yImagen + alto; y++) { // Recorriendo filas
        for (uint16_t x = xImagen; x < xImagen + ancho; x++) {  // y columnas
        	* pFrameBuffer = * p;
            p++;  // Para acceder al color del siguiente punto
            pFrameBuffer++;
        }
    }
} // LCD_dibujaImagenOpaca


void LCD_dibujaCaracterAlpha(uint16_t xCaracter, uint16_t yCaracter, char caracter, uint32_t color,
	const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, int enBlancoYNegro, int transparencia) {
    // Dibuja el carácter 'caracter' en las coordenadas 'x', 'y' utilizando el juego de caracteres
    // apuntado por 'pJuegoCaracteres'.
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)

    // Completar
	uint8_t Alto = pJuegoCaracteres -> alto;
	uint8_t Ancho = LCD_anchoCaracterAlpha(caracter, pJuegoCaracteres);

	uint8_t CARACTER; // aqui selccionamos los bits a partir de donde podemos empezar a dibujar



	for(int y = 0; y < Alto; y++) {  // Recorriendo las filas
		for(int x = 0; x < Ancho; x++) {  // y las columnas de puntos

			CARACTER = pJuegoCaracteres -> caracteres[pJuegoCaracteres -> posiciones[caracter-32]+x+y*Ancho+1];
			//CARACTER=(((CARACTER*100)/255)+transparencia)/2; // hacemos la media entre la transparencia del caracter y la transparencia que queremos aplicar

			if (CARACTER != 0){
				LCD_dibujaPunto(x + xCaracter,y + yCaracter, color, enBlancoYNegro, (((CARACTER*100)/255) * (100-transparencia))/100);

				//LCD_dibujaPunto(x + xCaracter,y + yCaracter, color, 0, (CARACTER*100)/255);
			}
			else
				LCD_dibujaPunto(x + xCaracter,y + yCaracter, color, 0, 0); //si no hay nada dibujamos un punto transparente

		}
	}

} // LCD_dibujaCaracterAlpha


uint16_t LCD_anchoCaracterAlpha(char caracter, const LCD_JuegoCaracteresAlpha * pJuegoCaracteres) {
	  // Devuelve el ancho en puntos del carácter indicado en el primer parámetro, utilizando el juego de 
	  // caracteres indicado en el segundo parámetro
	  
	  // Completar
	int i = pJuegoCaracteres -> posiciones[caracter-32];
	return pJuegoCaracteres -> caracteres[i];

} // LCD_anchoCaracterAlpha


uint16_t LCD_anchoCadenaCaracteresAlpha(const char* cadena, const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, uint16_t separacion) {
	// Devuelve el ancho en puntos de la cadena de caracteres indicada en el primer parámetro, utilizando el juego de
	// caracteres indicado en el segundo parámetro y la separación entre caracteres indicada en el último parámetro

	// Completar
	 int longitud = strlen(cadena);
	 uint16_t AchoCadena =0;


	 for (int i = 0; i < longitud; i++) {
		 if (longitud == 1) AchoCadena += LCD_anchoCaracterAlpha(cadena[i],pJuegoCaracteres);
		 else if (i < longitud -1) AchoCadena += LCD_anchoCaracterAlpha(cadena[i],pJuegoCaracteres) + separacion;
		 else AchoCadena += LCD_anchoCaracterAlpha(cadena[i],pJuegoCaracteres);
	 }

	 return AchoCadena;

} // LCD_anchoCadenaCaracteresAlpha

/*
void LCD_dibujaCadenaCaracteresAlpha(uint16_t xCadena, uint16_t yCadena, const char* cadena, uint32_t color, uint16_t separacion,
    const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, int enBlancoYNegro, int transparencia) {
    // Dibuja la cadena de caracteres apuntada por 'cadena' a partir de las coordenadas 'x', 'y'
    // utilizando el juego de caracteres apuntado por 'pJuegoCaracteres'.
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)

    // Completar
	 int longitud = strlen(cadena);
	 //uint8_t Alto = pJuegoCaracteres -> alto;
	 uint8_t AnchoIncremental =0;
	 uint16_t AchoCaracter;

	 int LimiteH, LimiteV;

	 //limites de tamaño del parrafo
	 if (SentidoHorizontal == 0){ //pantalla vertical
		 LimiteH= lcd_ancho;
		 LimiteV = lcd_alto;
	 }
	 else{ //pantalla horizontal
		 LimiteV= lcd_ancho;
		 LimiteH = lcd_alto;
	 }

	 int PosX, PosY;

	 //int SaltoLinea = Alto + separacion;

	 for (int i = 0; i < longitud ; i++) {
		 AchoCaracter = LCD_anchoCaracterAlpha(cadena[i],pJuegoCaracteres);
		 PosX = xCadena + separacion*i + AnchoIncremental;
		 PosY = yCadena;

		 if (PosX+AchoCaracter <= LimiteH){
			 LCD_dibujaCaracterAlpha(PosX,PosY,cadena[i],color,pJuegoCaracteres,enBlancoYNegro,transparencia);
		 }

		 AnchoIncremental += AchoCaracter;

	 }

} // LCD_dibujaCadenaCaracteresAlpha
*/

void LCD_dibujaCadenaCaracteresAlpha(uint16_t xCadena, uint16_t yCadena, const char* cadena, uint32_t color, uint16_t separacion,  const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, int enBlancoYNegro, int transparencia) {
    // Dibuja la cadena de caracteres apuntada por 'cadena' a partir de las coordenadas 'x', 'y'
    // utilizando el juego de caracteres apuntado por 'pJuegoCaracteres'.
    // Si 'enBlancoYNegro' es un buleano cierto, convierte el color a gris
    // 'transparencia' es un factor entre 0 y 100 para aplicar un nivel de transparencia al color, desde
    // completamente transparente (valor 0) a transparencia original (valor 100)

	// el texto se ajusta al sentido de la pantalla, si el texto es muy largo se realizan los saltos de linea correspondientes (LimiteH)
	// si no se puede seguir escribiendo verticalemente porque se supera el espacio vertical (LimiteV) se deja de escribir

    // Completar
	 int longitud = strlen(cadena);
	 uint8_t Alto = pJuegoCaracteres -> alto; // el alto de todos los caracteres es el mismo
	 uint8_t AnchoIncremental =0;
	 uint16_t AchoCaracter;

	 int LimiteH, LimiteV;
	 int lcd_ancho = LCD_ancho(); // ancho de la pantalla
	 int lcd_alto = LCD_alto(); // alto de la pantalla

	 //limites de tamaño del texto
	 if (LCD_SentidoHorizontal() == 0){ //pantalla vertical
		 LimiteH= lcd_ancho; // 240
		 LimiteV = lcd_alto; // 320
	 }
	 else{ //pantalla horizontal
		 LimiteV= lcd_ancho; // 240
		 LimiteH = lcd_alto; // 320
	 }

	 int PosX, PosY; // coordenadas de cada caracter

	 // variables para los saltos de linea
	 int saltar=0;
	 int SaltoLinea = Alto + separacion;


	 // comenzamos a dibujar la cadena de caracteres
	 int PosXActual=0;
	 for (int i = 0; i < longitud + saltar ; i++) {
		 AchoCaracter = LCD_anchoCaracterAlpha(cadena[i-saltar],pJuegoCaracteres);

		 // definimos las coordenadas de cada caracter de la cadena de texto
		 PosX = xCadena + separacion*PosXActual + AnchoIncremental;
		 PosY = yCadena + saltar*SaltoLinea;

		 if (PosX+AchoCaracter <= LimiteH && PosY + Alto <= LimiteV){ // el texto no debe superar el ancho ni el alto de la pantalla
			 LCD_dibujaCaracterAlpha(PosX,PosY,cadena[i-saltar],color,pJuegoCaracteres,enBlancoYNegro,transparencia);

			 //accedemos al siguiente caracter
			 PosXActual++;
			 AnchoIncremental += AchoCaracter;
		 }
		 else{
			 saltar ++;// si se supera el ancho de la pantalla hacemos una salto de linea

			 // reiniciamos las variables para poder empezar a escribir la nueva linea a la misma distancia del borde que la linea origen
			 PosXActual=0;
			 AnchoIncremental = 0;
			 AchoCaracter=0;
		 }
	 }
} // LCD_dibujaCadenaLargaCaracteresAlpha
