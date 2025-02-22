/*          

Projeto de Sistema Embarcado desenvolvido em atendimento à proposta final do curso TIC37

Residente.: Jackson da Silva Carneiro

***********     ALARME DE FALHA DE  PRESSÃO DE GASES*            *******************
*/
                    // INCLUSÃO DE BIBLIOTECAS
#include <stdio.h>
#include "pico/stdlib.h"
                           // DEFINIÇÃO DAS ENTRADAS E SAÍDAS NECESSÁRIAS
#define PUSH_BUTTON_A 5
#define PUSH_BUTTON_B 6
#define LED_NORMAL 11
#define LED_ALARM 13

int event = 0;

void config_GPIO(){

    
}





int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
