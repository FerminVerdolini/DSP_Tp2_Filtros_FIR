# LABORATORIO  2

## Muestreo con  FRDM-K64F

### Objetivo:

Realizar Diseños e Implementación de filtros FIR usando procesamiento de Bloque y de Muestras simples

### Descripción:

Realizar un programa aplicativo que sea capaz de aplicar un filtro FIR, por muestras, a un buffer de memoria de 512 muestras, que es adquirido con el Laboratorio #1 teniendo en cuenta las frecuencias de muestreo de 80 16 KHz, 22 KHz, 44 10Hzy 48 KHz. Con una de las teclas de la placa de evaluación FROM-K64F, se hablitara la aplicación del filtro o se hace bypass del filtro a un buffer de salida distinto del buffer de entrada De este buffer de salida se enviaran las muestras al DAC de la palca FROM-K64F. Visualizar el resultado utilizando un osciloscopio y comparar los resultados.

### Requerimientos de los filtros:

- Pasa Bajos: Fc= 3600Hz Astop-30db
- Pasa Altos: Fc 35 Hz Astop-30db
- Pasa Banda Fc1-35Hz, Fc2-3500Hz Astop-30db
- Elimina Banda Fr 50 Hz Bw-15 Hz Astop=25db

### Presentación:

Subir un archivo con: (uno por grupo, poner los nombres de todos

1. Mostrar el programa corriendo.
2. Diagrama de diseño de la aplicación
3. Código fuente de la misma con todo el proyecto en KDS.
4. Fotos de las formas de onda mas significativas
