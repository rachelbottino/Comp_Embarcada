/************************************************************************
* Rafael Corsi   - Insper
* rafael.corsi@insper.edu.br
*
* Computação Embarcada
*
* 10-PIO-INTERRUPCAO
*
* [ref] http://www.atmel.com/Images/Atmel-42142-SAM-AT03258-Using-Low-Power-Mode-in-SAM4E-Microcontroller_Application-Note.pdf
* [ref] https://www.eecs.umich.edu/courses/eecs373/labs/refs/M3%20Guide.pdf
************************************************************************/


#include "asf.h"
#include "conf_clock.h"
#include "sysclk.h"



/************************************************************************/
/* Defines                                                              */
/************************************************************************/

/**
 * LED Kit
 */
#define LED_PIO_ID		ID_PIOC
#define LED_PIO         PIOC
#define LED_PIN		    8
#define LED_PIN_MASK    (1<<LED_PIN)

/** LEDs OLED **/
#define LED1_PIO_ID		ID_PIOA
#define LED1_PIO        PIOA
#define LED1_PIN		0
#define LED1_PIN_MASK   (1<<LED1_PIN)

#define LED2_PIO_ID		ID_PIOC
#define LED2_PIO        PIOC
#define LED2_PIN		30
#define LED2_PIN_MASK   (1<<LED2_PIN)

#define LED3_PIO_ID		ID_PIOB
#define LED3_PIO        PIOB
#define LED3_PIN		2
#define LED3_PIN_MASK   (1<<LED3_PIN)

/**
 * Botão
 */
#define BUT_PIO_ID      ID_PIOA
#define BUT_PIO         PIOA
#define BUT_PIN		    11
#define BUT_PIN_MASK    (1 << BUT_PIN)
#define BUT_DEBOUNCING_VALUE  79

/** Botões OLED **/

#define BUT1_PIO_ID		ID_PIOD
#define BUT1_PIO		PIOD
#define BUT1_PIN		28
#define BUT1_PIN_MASK	(1 << BUT1_PIN)
#define BUT1_DEBOUNCING_VALUE  79

#define BUT2_PIO_ID		ID_PIOC
#define BUT2_PIO		PIOC
#define BUT2_PIN		31
#define BUT2_PIN_MASK	(1 << BUT2_PIN)
#define BUT2_DEBOUNCING_VALUE  79

#define BUT3_PIO_ID		ID_PIOA
#define BUT3_PIO		PIOA
#define BUT3_PIN		19
#define BUT3_PIN_MASK	(1 << BUT3_PIN)
#define BUT3_DEBOUNCING_VALUE  79

/************************************************************************/
/* prototype                                                             */
/************************************************************************/
void led_init(int estado, uint32_t led_id, Pio *led_pio, const uint32_t led_pin_mask);
void but_init(uint32_t but_id, Pio *but_pio, const uint32_t but_pin_mask, uint32_t attribute, void (*but_handler) (uint32_t, uint32_t));
void but_Handler();
void but1_Handler();
void but2_Handler();
void but3_Handler();

/************************************************************************/
/* Interrupçcões                                                        */
/************************************************************************/

void but_Handler(){
    /*
     *  limpa interrupcao do PIO
     */
    uint32_t pioIntStatus;
    pioIntStatus =  pio_get_interrupt_status(BUT_PIO);
    
   /**
    *  Toggle status led
    */
   if(pio_get_output_data_status(LED_PIO, LED_PIN_MASK))
    pio_clear(LED_PIO, LED_PIN_MASK);
   else
    pio_set(LED_PIO,LED_PIN_MASK);    
}

void but1_Handler(){
    /*
     *  limpa interrupcao do PIO
     */
    uint32_t pioIntStatus;
    pioIntStatus =  pio_get_interrupt_status(BUT1_PIO);
    
   /**
    *  Toggle status led 1
    */
   if(pio_get_output_data_status(LED1_PIO, LED1_PIN_MASK))
    pio_clear(LED1_PIO, LED1_PIN_MASK);
   else
    pio_set(LED1_PIO,LED1_PIN_MASK);    
}

void but2_Handler(){
    /*
     *  limpa interrupcao do PIO
     */
    uint32_t pioIntStatus;
    pioIntStatus =  pio_get_interrupt_status(BUT2_PIO);
    
   /**
    *  Toggle status led 2
    */
   if(pio_get_output_data_status(LED2_PIO, LED2_PIN_MASK))
    pio_clear(LED2_PIO, LED2_PIN_MASK);
   else
    pio_set(LED2_PIO,LED2_PIN_MASK);    
}

void but3_Handler(){
    /*
     *  limpa interrupcao do PIO
     */
    uint32_t pioIntStatus;
    pioIntStatus =  pio_get_interrupt_status(BUT3_PIO);
    
   /**
    *  Toggle status led 3
    */
   if(pio_get_output_data_status(LED3_PIO, LED3_PIN_MASK))
    pio_clear(LED3_PIO, LED3_PIN_MASK);
   else
    pio_set(LED3_PIO,LED3_PIN_MASK);    
}

/************************************************************************/
/* Funções	                                                            */
/************************************************************************/

/**
 * @Brief Inicializa o pino do LED
 */
void led_init(int estado, uint32_t led_id, Pio *led_pio, const uint32_t led_pin_mask){
    pmc_enable_periph_clk(led_id);
    pio_set_output(led_pio, led_pin_mask, 1, 0, 0 );
};

/**
 * @Brief Inicializa o pino do BUT
 *  config. botao em modo entrada enquanto 
 *  ativa e configura sua interrupcao.
 */
void but_init(uint32_t but_id, Pio *but_pio, const uint32_t but_pin_mask, uint32_t attribute, void (*but_handler) (uint32_t, uint32_t)){
    /* config. pino botao em modo de entrada */
    pmc_enable_periph_clk(but_id);
    pio_set_input(but_pio, but_pin_mask, PIO_PULLUP | PIO_DEBOUNCE); 
    
    /* config. interrupcao em borda de descida no botao do kit */
    /* indica funcao (but_Handler) a ser chamada quando houver uma interrupção */
    pio_enable_interrupt(but_pio, but_pin_mask);
    pio_handler_set(but_pio, but_id, but_pin_mask, attribute, but_handler); // attribute = PIO_IT_RISE_EDGE(borda de subida) ou PIO_IT_FALL_EDGE(borda de descida) ou PIO_IT_RE_OR_HL(subida e descida)
    
    /* habilita interrupçcão do PIO que controla o botao */
    /* e configura sua prioridade                        */
    NVIC_EnableIRQ(but_id);
    NVIC_SetPriority(but_id, 1);
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
	/* Inicializao I/OS                                                     */
	/************************************************************************/
	
	/*LED e Botão Kit*/
	led_init(1,LED_PIO_ID,LED_PIO,LED_PIN_MASK);
    but_init(BUT_PIO_ID,BUT_PIO,BUT_PIN_MASK,PIO_IT_FALL_EDGE,but_Handler);
	
	/*LED e Botão 1*/
	led_init(0,LED1_PIO_ID,LED1_PIO,LED1_PIN_MASK);
	but_init(BUT1_PIO_ID,BUT1_PIO,BUT1_PIN_MASK,PIO_IT_RISE_EDGE,but1_Handler); //Botão 1 = borda de subida
	
	/*LED e Botão 2*/
	led_init(1,LED2_PIO_ID,LED2_PIO,LED2_PIN_MASK);
	but_init(BUT2_PIO_ID,BUT2_PIO,BUT2_PIN_MASK,PIO_IT_FALL_EDGE,but2_Handler); //Botão 2 = borda de descida
	
	/*LED e Botão 3*/
	led_init(1,LED3_PIO_ID,LED3_PIO,LED3_PIN_MASK);
	but_init(BUT3_PIO_ID,BUT3_PIO,BUT3_PIN_MASK,PIO_IT_RE_OR_HL,but3_Handler); //Botão 3 = borda de subida e descida

	/************************************************************************/
	/* Super loop                                                           */
	/************************************************************************/
	while(1){
		/*LED kit apagado*/
		pio_set(LED_PIO, LED_PIN_MASK);	
		
       /* entra em modo sleep */
       pmc_sleep(SLEEPMGR_SLEEP_WFI);
	   
	   /*blink 3s*/
	   for (char i = 0; i <=5; i++) {
		   pio_clear(LED_PIO, LED_PIN_MASK);
		   delay_ms(250);
		   pio_set(LED_PIO, LED_PIN_MASK);
		   delay_ms(250);
	   }	   
	};
}


