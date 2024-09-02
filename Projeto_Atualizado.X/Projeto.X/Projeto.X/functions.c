#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/eusart.h"
#include "main.h"

//Fun��o de c�lculo da Temperatura e Velocidade do Som
void Temperatura_e_VelocidadeSom(){
    //Fazendo a convers�o do valor de temperatura para unidades de engenharia
    // temp = valor do adc x resolu��o ((50-2)/1024) + 275
    Temp.Dado = (uint16_t)(ADC_GetConversion(8) * 0.0468) + 275;
    //Para c�lculo da velocidade do som
    v_som = tabela_veloc_som[Temp.Dado];
    
}
// Fun��o de c�lculo da posi��o da bola no tubo
void Posicao_Bola_Tubo(){    
    //Vari�vel respons�vel por transformar o tempo em unidades de engenharia (segundos)
    tempo_s = TMR1_ReadTimer() * P_fosc;
    //C�lculo da dist�ncia em mil�metros
    D_mm.Dado = (uint16_t)(v_som * (tempo_s / 2)*1000);
    TMR1_WriteTimer(0);
}

