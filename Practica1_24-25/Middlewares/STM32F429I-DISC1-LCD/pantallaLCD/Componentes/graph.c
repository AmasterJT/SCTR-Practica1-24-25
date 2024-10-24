#include <cmsis_os2.h> // para osDelay()
#include <graph.h>
#include <math.h>
#include <stdio.h>  // Para sprintf()
#include <stdlib.h> // para abs()
#include <string.h>


// importamos las funciones para el manejo de la pantalla
#include "interfazLCD.h"
#include "graph.h"

#include "ColoresHexa.h" // importamos la paleta de colores en formato hexadecimal ARGB
#include <Imagenes.h>
#include <JuegoCaracteres.h> //importamos las tipografias

//------------------------------------------------------------------------------------------------------------
// funciones: inicializacion de los componenetes

void InicializaLineGraph(LineGraph *lineGraph, int16_t xInicial, uint16_t yInicial, uint16_t ancho,
                         uint16_t alto, int T, uint32_t backgroundColor, uint32_t axisColor, uint32_t graphColor,
                         int graphPadding) {

    lineGraph->xInicial = xInicial;
    lineGraph->yInicial = yInicial;
    lineGraph->ancho = ancho;
    lineGraph->alto = alto;
    lineGraph->T = T;
    lineGraph->backgroundColor = backgroundColor;
    lineGraph->axisColor = axisColor;
    lineGraph->graphColor = graphColor;
    lineGraph->graphPadding = graphPadding;
}

// Ahora usamos doble puntero para modificar el puntero original.
int setGraph(LineGraph **lineGraph, int ancho) {
    // Asignar memoria dinámica, incluyendo el array flexible
    *lineGraph = (LineGraph *)malloc(sizeof(LineGraph) + ancho * sizeof(float));

    if (*lineGraph == NULL) {
        printf("Error al asignar memoria para LineGraph.\n");
        return -1;
    }

    // Ejemplo de datos del gráfico (curva de seno)
    int sine[100] = {40, 42, 45, 47, 49, 52, 54, 57, 59, 61, 63, 65, 67, 69, 70, 72, 73, 75, 76, 77, 78, 78, 79, 79, 79, 80, 79, 79, 79, 78, 78, 77, 76, 75, 73, 72, 70, 69, 67, 65, 63, 61, 59, 57, 54, 52, 49, 47, 45, 42, 40, 38, 35, 33, 31, 28, 26, 23, 21, 19, 17, 15, 13, 11, 10, 8, 7, 5, 4, 3, 2, 2, 1, 1, 1, 0, 1, 1, 1, 2, 2, 3, 4, 5, 7, 8, 10, 11, 13, 15, 17, 19, 21, 23, 26, 28, 31, 33, 35, 38};

    // Convertimos los valores de 'sine[]' a float y los copiamos a 'lineGraph->y'
    for (int i = 0; i < ancho; i++) {
        (*lineGraph)->y[i] = (float)sine[i]; // Conversión a float
    }

    return 0;
}


//-------------------------------------------------------------------------------------------------------
// funciones: Dibujamos la grafica

void DrawGraph(LineGraph *lineGraph, int enBlancoYNegro, int transparencia){

	int16_t xInicial = lineGraph -> xInicial ;
	int16_t yInicial = lineGraph -> yInicial;
	int16_t ancho = lineGraph -> ancho;
	int16_t alto = lineGraph -> alto;
	int T = lineGraph -> T;
	uint32_t backgroundColor = lineGraph -> backgroundColor;
	uint32_t axisColor = lineGraph -> axisColor;
	uint32_t graphColor = lineGraph -> graphColor;
	int graphPadding = lineGraph -> graphPadding;

	LCD_dibujaRectanguloRelleno(xInicial, yInicial, ancho, alto, backgroundColor, enBlancoYNegro,transparencia);
	LCD_dibujaLinea(xInicial, yInicial + alto/2, xInicial + ancho, yInicial + alto/2, axisColor, enBlancoYNegro,transparencia);
	LCD_dibujaLinea(xInicial, yInicial, xInicial, yInicial + alto, axisColor, enBlancoYNegro,transparencia);

	int j = 0;
	for (int i = xInicial; i < xInicial + ancho; i++){
		LCD_dibujaPunto(i, lineGraph -> y[j], graphColor, enBlancoYNegro, transparencia);
		j++;
	}

}

//-------------------------------------------------------------------------------------------------------
// funciones: manejo de la grafica

void updateGraph(LineGraph *lineGraph, float puntoDeLaGrafica){

    // actualizamos los valores de las señales, los desplazamos a la izquierda
    for (int i = 0; i < lineGraph -> ancho; i++)
    	lineGraph -> y[i] = lineGraph -> y[i + 1]; // Desplaza la señal filtrada

    lineGraph -> y[lineGraph -> ancho -1] = puntoDeLaGrafica; // introducimos el ultimo punto en la grafica



}
