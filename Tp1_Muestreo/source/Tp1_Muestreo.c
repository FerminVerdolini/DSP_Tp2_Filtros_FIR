/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Tp1_Muestreo.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#define CAN_FREC 5


uint16_t freccuencyBuff[CAN_FREC];
uint8_t currentFreccuency;


enum Colors{
    BLUE ,
    RED,
    GREEN,
    CYAN,
    YELLOW,
	MAGENTA,
    WHITE,

    C_LAST
};

void initBuffers(){
    currentFreccuency = 0;

    freccuencyBuff[0] = 8;
    freccuencyBuff[1] = 16;
    freccuencyBuff[2] = 22;
    freccuencyBuff[3] = 44;
    freccuencyBuff[4] = 48;
}

void setNextFrec(){
    currentFreccuency++;
    if(currentFreccuency >= CAN_FREC){
        currentFreccuency=0;
    }

    setLedColor(currentFreccuency);

    //TODO ACA NACHO DEBERIA CAMBIAR LA FRECUENCIA DEL ADC
    //Usando el array at current frec
}

void ConfigLeds(){
    gpio_pin_config_t led_config = { kGPIO_DigitalOutput,1};

    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, &led_config);
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);
}

void ConfigSW(){
    gpio_pin_config_t sw_config = { kGPIO_DigitalInput,0};

    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN, &sw_config);
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN, &sw_config);

    PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kPORT_InterruptFallingEdge);
    EnableIRQ(BOARD_SW2_IRQ);
    EnableIRQ(BOARD_SW3_IRQ);

}

void setLedColor(int color){

    switch(color){
        case YELLOW:
        GPIO_PortSet(BOARD_LED_BLUE_GPIO,BOARD_LED_BLUE_GPIO_PIN_MASK);
        GPIO_PortClear(BOARD_LED_RED_GPIO,BOARD_LED_RED_GPIO_PIN_MASK);
        GPIO_PortClear(BOARD_LED_GREEN_GPIO,BOARD_LED_GREEN_GPIO_PIN_MASK);
        break;
        case CYAN:
        GPIO_PortClear(BOARD_LED_BLUE_GPIO,BOARD_LED_BLUE_GPIO_PIN_MASK);
        GPIO_PortSet(BOARD_LED_RED_GPIO,BOARD_LED_RED_GPIO_PIN_MASK);
        GPIO_PortClear(BOARD_LED_GREEN_GPIO,BOARD_LED_GREEN_GPIO_PIN_MASK);
        break;
        case MAGENTA:
        GPIO_PortClear(BOARD_LED_BLUE_GPIO,BOARD_LED_BLUE_GPIO_PIN_MASK);
        GPIO_PortClear(BOARD_LED_RED_GPIO,BOARD_LED_RED_GPIO_PIN_MASK);
        GPIO_PortSet(BOARD_LED_GREEN_GPIO,BOARD_LED_GREEN_GPIO_PIN_MASK);
        break;
        case GREEN:
        GPIO_PortSet(BOARD_LED_BLUE_GPIO,BOARD_LED_BLUE_GPIO_PIN_MASK);
        GPIO_PortSet(BOARD_LED_RED_GPIO,BOARD_LED_RED_GPIO_PIN_MASK);
        GPIO_PortClear(BOARD_LED_GREEN_GPIO,BOARD_LED_GREEN_GPIO_PIN_MASK);
        break;
        case RED:
        GPIO_PortSet(BOARD_LED_BLUE_GPIO,BOARD_LED_BLUE_GPIO_PIN_MASK);
        GPIO_PortClear(BOARD_LED_RED_GPIO,BOARD_LED_RED_GPIO_PIN_MASK);
        GPIO_PortSet(BOARD_LED_GREEN_GPIO,BOARD_LED_GREEN_GPIO_PIN_MASK);
        break;
        case BLUE:
        GPIO_PortClear(BOARD_LED_BLUE_GPIO,BOARD_LED_BLUE_GPIO_PIN_MASK);
        GPIO_PortSet(BOARD_LED_RED_GPIO,BOARD_LED_RED_GPIO_PIN_MASK);
        GPIO_PortSet(BOARD_LED_GREEN_GPIO,BOARD_LED_GREEN_GPIO_PIN_MASK);
        break;
        case WHITE:
        GPIO_PortClear(BOARD_LED_BLUE_GPIO,BOARD_LED_BLUE_GPIO_PIN_MASK);
        GPIO_PortClear(BOARD_LED_RED_GPIO,BOARD_LED_RED_GPIO_PIN_MASK);
        GPIO_PortClear(BOARD_LED_GREEN_GPIO,BOARD_LED_GREEN_GPIO_PIN_MASK);
        break;
        default:
        break;
    }
}
/* TODO: insert other definitions and declarations here. */
void delay(){
	for(int i =0 ;i<800000; i++ ){
        __asm volatile ("nop");
	}
}
/*
 * @brief   Application entry point.
 */
int main(void) {

	
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    ConfigLeds();
    ConfigSW();

    initBuffers();

    PRINTF("Hello World\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        __asm volatile ("nop");
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
    }
    return 0 ;
}

void BOARD_SW2_IRQ_HANDLER(){
    GPIO_PortClearInterruptFlags(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN_MASK);
	setNextFrec();
}

void BOARD_SW3_IRQ_HANDLER(){
    GPIO_PortClearInterruptFlags(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN_MASK);
	setLedColor(CYAN);
}

