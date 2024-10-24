#ifndef Graficas_H_
#define Graficas_H_

#include "pantallaLCD.h"

#include <cmsis_os2.h> // para osDelay()
#include <math.h>
#include <stdint.h>
#include <stdio.h>  // Para sprintf()
#include <stdlib.h> // para abs()
#include <string.h>

// -----------------------------------------------------------------------------------------------------------------
// estructuras para el manejo de la grafica

typedef struct {

    uint16_t xInicial;
    uint16_t yInicial;
    uint16_t ancho;
    uint16_t alto;

    int T;           // periodo de muestreo
    int graphPoints; // cantidad de puntos en la horizontal que podemos representar en la grafica

    uint32_t backgroundColor; // color del fondo de la grafica
    uint32_t axisColor;       // color de los ejes
    uint32_t graphColor;      //  color de la curva de la grafica
    int graphPadding; // distancia entre la grafica y los bordes verticales de la grafica

    int Xscale;
    int Yscale;


    float y[]; //matriz para guardar la vertical de la grafica
    // const LCD_JuegoCaracteresAlpha * pJuegoCaracteres;
    // uint8_t separacion;

    // void (* pFuncion)(void);

    // int finalizacion; // parametro que indica si la barra de progreso esta al 100%
} LineGraph;

//------------------------------------------------------------------------------------------------------------
// funciones: inicializacion de los componenetes

void InicializaLineGraph(LineGraph *lineGraph, int16_t xInicial, uint16_t yInicial, uint16_t ancho, uint16_t alto, int T, uint32_t backgroundColor, uint32_t axisColor, uint32_t graphColor,
                         int graphPadding);

int setGraph(LineGraph **lineGraph, int ancho);

//-------------------------------------------------------------------------------------------------------
// funciones: Dibujamos la grafica

void DrawGraph(LineGraph *lineGraph, int enBlancoYNegro, int transparencia);

//-------------------------------------------------------------------------------------------------------
// funciones: manejo de la grafica

void updateGraph(LineGraph *lineGraph, float puntoDeLaGrafica);

//-------------------------------------------------------------------------------------------------------
// funciones: ejemplo de graficas
int sine[100] = {40, 42, 45, 47, 49, 52, 54, 57, 59, 61,
				 63, 65, 67, 69, 70, 72, 73, 75, 76, 77,
				 78, 78, 79, 79, 79, 80, 79, 79, 79, 78,
				 78, 77, 76, 75, 73, 72, 70, 69, 67, 65,
				 63, 61, 59, 57, 54, 52, 49, 47, 45, 42,
				 40, 38, 35, 33, 31, 28, 26, 23, 21, 19,
				 17, 15, 13, 11, 10, 8,  7,  5,  4,  3,
				 2,  2,  1,  1,  1,  0,  1,  1,  1,  2,
				 2,  3,  4,  5,  7,  8,  10, 11, 13, 15,
				 17, 19, 21, 23, 26, 28, 31, 33, 35, 38};
#endif /* Graficas_H_ */
