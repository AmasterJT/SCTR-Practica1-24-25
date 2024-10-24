#include "interfazLCD.h"
#include <stdio.h>  // Para sprintf()
#include <string.h>  // Para strcmp()



void LCD_inicializaBoton(uint16_t x, uint16_t y, uint16_t ancho, uint16_t alto, const uint8_t * imagen,
		char * texto, const LCD_JuegoCaracteresAlpha * pJuegoCaracteres, uint8_t separacion, uint32_t colorTexto,
		void (*funcion)(), int habilitado,
		int visible, LCD_Boton * pBoton) {

    pBoton->x = x;
    pBoton->y = y;
    // Coordenadas de la esquina superior izquierda del botón

    pBoton->ancho = ancho;
    pBoton->alto = alto;
    // Dimensiones del botón en puntos

    pBoton->imagen = imagen;
    // Imagen utilizada para mostrar el botón

    strcpy(pBoton->texto, texto);
    pBoton->pJuegoCaracteres = pJuegoCaracteres;
    pBoton->separacion = separacion;
    pBoton->xTexto = (ancho - LCD_anchoCadenaCaracteresAlpha(texto, pJuegoCaracteres, separacion)) / 2;
    pBoton->yTexto = (alto - pJuegoCaracteres->alto) / 2;
    pBoton->colorTexto = colorTexto;
    // Texto y juego de caracteres mostrado sobre el botón

    pBoton->funcion = funcion;
    // Función a ejecutar cuando se pulsa el botón

    pBoton->habilitado = habilitado;
    // Indica si se muestra habilitado

    pBoton->pulsado = 0;
    // Inicialmente no está pulsado

    pBoton->visible = visible;
    // Indica si hay que mostrar el botón

}


void LCD_setVisibilidadBoton(int visibilidad, LCD_Boton * pBoton) {

    pBoton->visible = visibilidad;  // Guarda la nueva visibilidad
}


void LCD_setHabilitacionBoton(int habilitacion, LCD_Boton * pBoton) {

    pBoton->habilitado = habilitacion;  // Lo recuerda
}


void LCD_setTextoBoton(const char* texto, LCD_Boton * pBoton) {

	strcpy(pBoton->texto, texto);
    pBoton->xTexto = (pBoton->ancho - LCD_anchoCadenaCaracteresAlpha(texto, pBoton->pJuegoCaracteres,
    	pBoton->separacion)) / 2;
}


void LCD_setColorTextoBoton(uint32_t color, LCD_Boton * pBoton) {

    pBoton->colorTexto = color;
}


void LCD_setImagenBoton(const uint8_t * imagen, LCD_Boton * pBoton) {

	pBoton->imagen = imagen;
}


void LCD_atiendeBoton(LCD_Boton * pBoton) {

	int opacidad; // Para expresar el grado de opacidad (de 0 a 100) con el que se va a dibujar
	int enBlancoYNegro;  // Buleano cierto si hay que dibujarlo en blanco y negro

	if (pBoton->visible) pBoton->visible=0;
	else pBoton->visible = 1;

	if (pBoton->visible) {  // Si el botón tiene que ser visible ...
		if (pBoton->habilitado) {  // Si está habilitado ...
			opacidad = 100;  // Totalmente opaco
			enBlancoYNegro = 0;  // Se va a mostra en color
		}
		else {  // Si es visible pero no está habilitado
			opacidad = 70;  // Se muestra semitransparente
			enBlancoYNegro = 1;  // y en niveles de gris
		}
	} else {  // Si no es visible
		opacidad = 0;  // Se muestra completamente transparente
		enBlancoYNegro = 0;
	}

	LCD_dibujaImagen(pBoton->x, pBoton->y, pBoton->ancho, pBoton->alto, pBoton->imagen, enBlancoYNegro,
		opacidad);
	// Finalmente dibuja la imagen para mostrar el botón con la opacidad y color establecidos

	LCD_dibujaCadenaCaracteresAlpha(pBoton->x + pBoton->xTexto, pBoton->y + pBoton->yTexto, pBoton->texto,
		pBoton->colorTexto, pBoton->separacion, pBoton->pJuegoCaracteres, 0, 100);
	// Dibuja el texto sobre el botón

    if (pBoton->habilitado && pBoton->visible) {  // Si el botón está habilitado y es visible ...

        if (LCD_pulsada() && LCD_xPulsacion() > pBoton->x && LCD_xPulsacion() < pBoton->x + pBoton->ancho &&
                LCD_yPulsacion() > pBoton->y && LCD_yPulsacion() < pBoton->y + pBoton->alto) {
            // Si se ha pulsado la pantalla dentro de las coordenadas de la superficie ocupada por el
            // botón ...

            if (!pBoton->pulsado)  // Si el botón no estaba pulsado previamente ...
                pBoton->funcion();  // Ejecuta la función asociada al botón

            pBoton->pulsado = 1;  // Indica que se está pulsando el botón

        } else pBoton->pulsado = 0;  // Si no, indica que no se está pulsando el botón

    } else pBoton->pulsado =0;  // Si no, indica que no se está pulsando el botón
}




