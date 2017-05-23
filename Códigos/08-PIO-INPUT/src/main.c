/**************************************************************************
* Rafael Corsi   - Insper 
* rafael.corsi@insper.edu.br        
*
* Computação Embarcada
*
* 08-PIO-ENTRADA
************************************************************************/


#include "asf.h"
#include "conf_clock.h"

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#define BLINK_PERIOD     1000
int blink = BLINK_PERIOD;
/**
 * LEDs
 */
#define LED_PIO_ID		ID_PIOC
#define LED_PIO         PIOC
#define LED_PIN			8
#define LED_PIN_MASK	(1<<LED_PIN) 

#define LED1_PIO_ID		ID_PIOC
#define LED1_PIO         PIOC
#define LED1_PIN			19
#define LED1_PIN_MASK	(1<<LED_PIN)

#define LED2_PIO_ID		ID_PIOD
#define LED2_PIO         PIOD
#define LED2_PIN			26
#define LED2_PIN_MASK	(1<<LED_PIN)

#define LED3_PIO_ID		ID_PIOD
#define LED3_PIO         PIOD
#define LED3_PIN			11
#define LED3_PIN_MASK	(1<<LED_PIN)

/**
 * Botão
 */ 
#define BUT_PIO_ID		ID_PIOA
#define BUT_PIO         PIOA
#define BUT_PIN			11
#define BUT_PIN_MASK	(1 << BUT_PIN)

#define BUT1_PIO_ID		ID_PIOA
#define BUT1_PIO        PIOA
#define BUT1_PIN		2
#define BUT1_PIN_MASK	(1 << BUT_PIN)

#define BUT2_PIO_ID		ID_PIOD
#define BUT2_PIO        PIOD
#define BUT2_PIN		30
#define BUT2_PIN_MASK	(1 << BUT_PIN)

#define BUT3_PIO_ID		ID_PIOC
#define BUT3_PIO        PIOC
#define BUT3_PIN		13
#define BUT3_PIN_MASK	(1 << BUT_PIN)

/************************************************************************/
/* Prototipação                                                        */
/************************************************************************/
void ledConfig();

/************************************************************************/
/* Funções	                                                            */
/************************************************************************/



/**
 * @Brief Inicializa o pino do LED
 */
void ledConfig(){
	PMC->PMC_PCER0 = (1<<LED_PIO_ID);	
	PIOC->PIO_OER  = (1 << LED_PIN);
	PIOC->PIO_PER  = (1 << LED_PIN);
	PIOC->PIO_CODR = (1 << LED_PIN);
	
	PMC->PMC_PCER0 = (1<<LED1_PIO_ID);
	PIOC->PIO_OER  = (1 << LED1_PIN);
	PIOC->PIO_PER  = (1 << LED1_PIN);
	PIOC->PIO_CODR = (1 << LED1_PIN);
	
	PMC->PMC_PCER0 = (1<<LED2_PIO_ID);
	PIOD->PIO_OER  = (1 << LED2_PIN);
	PIOD->PIO_PER  = (1 << LED2_PIN);
	PIOD->PIO_CODR = (1 << LED2_PIN);
	
	PMC->PMC_PCER0 = (1<<LED3_PIO_ID);
	PIOD->PIO_OER  = (1 << LED3_PIN);
	PIOD->PIO_PER  = (1 << LED3_PIN);
	PIOD->PIO_CODR = (1 << LED3_PIN);
};

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main(void)
{

	/************************************************************************/
	/* Inicialização básica do uC                                           */
	/************************************************************************/
	sysclk_init();
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	/************************************************************************/
	/* Inicializa perifericos                                               */
	/************************************************************************/
	// Configura LED em modo saída
	ledConfig();

	// Configura botao
	PMC->PMC_PCER0= (1<<BUT_PIO_ID);
	PIOA->PIO_PER = (1<<BUT_PIN);
	PIOA->PIO_ODR = (1<<BUT_PIN);
	PIOA->PIO_PUER= (1<<BUT_PIN);
	PIOA->PIO_IFER= (1<<BUT_PIN);
	
	PMC->PMC_PCER0= (1<<BUT1_PIO_ID);
	PIOA->PIO_PER = (1<<BUT1_PIN);
	PIOA->PIO_ODR = (1<<BUT1_PIN);
	PIOA->PIO_PUER= (1<<BUT1_PIN);
	PIOA->PIO_IFER= (1<<BUT1_PIN);
	
	PMC->PMC_PCER0= (1<<BUT2_PIO_ID);
	PIOD->PIO_PER = (1<<BUT2_PIN);
	PIOD->PIO_ODR = (1<<BUT2_PIN);
	PIOD->PIO_PUER= (1<<BUT2_PIN);
	PIOD->PIO_IFER= (1<<BUT2_PIN);
	
	PMC->PMC_PCER0= (1<<BUT3_PIO_ID);
	PIOC->PIO_PER = (1<<BUT3_PIN);
	PIOC->PIO_ODR = (1<<BUT3_PIN);
	PIOC->PIO_PUER= (1<<BUT3_PIN);
	PIOC->PIO_IFER= (1<<BUT3_PIN);
	
	
	/************************************************************************/
	/* Super loop                                                           */
	/************************************************************************/
	while(1){
		//botão placa
		if( PIOA->PIO_PDSR & (1<<BUT_PIN) ){
			
			PIOC->PIO_SCDR = (1 << LED_PIN);
		}
		else{
			PIOC->PIO_CODR = (1 << LED_PIN);
		}
		
		//botão 1 OLED
		if( PIOA->PIO_PDSR & (1<<BUT1_PIN) ){
			PIOC->PIO_SODR = (1 << LED1_PIN);
		}
		else{
			PIOC->PIO_CODR = (1 << LED1_PIN);
		}
		
		//botão 2 OLED
		if( PIOD->PIO_PDSR & (1<<BUT2_PIN) ){
			PIOD->PIO_SODR = (1 << LED2_PIN);
		}
		else{
			PIOD->PIO_CODR = (1 << LED2_PIN);
		}
		
		//botão 3 OLED
		if( PIOC->PIO_PDSR & (1<<BUT3_PIN) ){
			PIOD->PIO_SODR = (1 << LED3_PIN);
		}
		else{
			PIOD->PIO_CODR = (1 << LED3_PIN);
		}			  
	};
}

