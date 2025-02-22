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

int alarme = 0;  // VARIÁVEL GLOBAL QUE SERÁ UTILIZADA PARA CONTAGEM DE EVENTOS

void config_GPIO(){   // CONFIGURAÇÃO DAS GPIO's A SEREM UTILIZADAS

gpio_init(LED_ALARM);   // LED PARA INDICAR SITUAÇÃO DE ALARME
gpio_set_dir(LED_ALARM, GPIO_OUT);

gpio_init(LED_NORMAL);   // LED PARA INDICAÇÃO DE ESTADO NORMAL
gpio_set_dir(LED_NORMAL, GPIO_OUT);

gpio_init(PUSH_BUTTON_A);  // PUSH_BUTTON_A PARA SIMULAÇÃO DE OCORRÊNCIA DE ALARME
gpio_set_dir(PUSH_BUTTON_A, GPIO_IN);
gpio_pull_up(PUSH_BUTTON_A);

gpio_init(PUSH_BUTTON_B);   // PUSH_BUTTON_B PARA SIMULAÇÃO DE ATENDIMENTO AO ALARME
gpio_set_dir(PUSH_BUTTON_B, GPIO_IN);
gpio_pull_up(PUSH_BUTTON_B);

}

static void gpio_irq_handler(uint gpio, uint32_t events) { //TRATAMENTO DA INTERRUPÇÃO GERADA PELO EVENTO DE ALARME OU ATENDIMENTO DO MESMO
    if (gpio == PUSH_BUTTON_A) {
       alarme++;// incrementa a variável event para envio de mensagem de presença de alarme
    } else if (gpio == PUSH_BUTTON_B) {
        alarme = 0;  // retorna o valor da variável event para 0 o que indica que o alarme foi resolvido
    }
}


int main(){
                        // INICIALIZAÇÃO E CONFIGURAÇÃO
     stdio_init_all();
    config_GPIO();
                            // LINHAS PARA IDENTIFICAÇÃO E ENNCAMINHAMENTO DA INTERRUPÇÃO
gpio_set_irq_enabled_with_callback(PUSH_BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
sleep_ms(50);
gpio_set_irq_enabled_with_callback(PUSH_BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
sleep_ms(50);
                   
    while (true) {      // LOOP PRINPCIPAL=> IRÁ LER OS EVENTOS E ENVIAR AS INFORMAÇÕES

        if(alarme>0){
            gpio_put(LED_NORMAL, false);
            gpio_put(LED_ALARM, true);
            printf("\n\tExiste %d alarmes ativos!! \n", alarme);
        }
        else if(alarme==0){
            gpio_put(LED_ALARM, false);
            gpio_put(LED_NORMAL, true);
            printf("\n\tSISTEMA EM FUNCIONAMENTO NORMAL\n");
        }
        
        sleep_ms(5000);
    }
}
