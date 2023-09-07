# LABORATORIO  1

## Muestreo con  FRDM-K64F

### Objetivo:

Manejar el modulo del conversor A/D integrado en el MCU MK64FN1M0VLL12 de la familia Kinetis K64.

### Descripción:

Realizar un programa aplicativo que sea capaz de digitalizar una señal a través del modulo del ADC disponible en la board FRDM-K64F a distintas velocidades de muestreo, las velocidades requeridas son 8K/S, 16K/S 22K/S, 44K/S y 48K/S. Los cambios de las velocidades de muestreo serán realizados con una de las teclas de la placa de evaluación, en forma de un buffer circular. Cada velocidad de muestreo se indicará a través de un color RGB del LED. Con otra tecla de la placa se habilitara la adquisición o se parara la misma (Run/Stop). Los valores adquiridos serán almacenados en memoria en un buffer circular de 512 muestras del tipo q15 (fraccional 15bits) y a su vez serán enviados a través del DAC (de 12bits).

### Presentación:

1. Mostrar el programa corriendo.

2. Subir un archivo conteniendo lo siguiente:
    - Configuración del ambiente (pantallas con timers, adc, etc)
    - Diagrama de diseño de la aplicación explicando sus partes
    - Código fuente de la misma con todo el proyecto.
