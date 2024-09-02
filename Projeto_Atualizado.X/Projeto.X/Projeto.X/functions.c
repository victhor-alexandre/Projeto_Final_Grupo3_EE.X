#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/eusart.h"
#include "main.h"

//Função de cálculo da Temperatura e Velocidade do Som
void Temperatura_e_VelocidadeSom(){
    //Fazendo a conversão do valor de temperatura para unidades de engenharia
    // temp = valor do adc x resolução ((50-2)/1024) + 275
    Temp.Dado = (uint16_t)(ADC_GetConversion(8) * 0.0468) + 275;
    //Para cálculo da velocidade do som
    v_som = tabela_veloc_som[Temp.Dado];
    
}
// Função de cálculo da posição da bola no tubo
void Posicao_Bola_Tubo(){    
    //Variável responsável por transformar o tempo em unidades de engenharia (segundos)
    tempo_s = TMR1_ReadTimer() * P_fosc;
    //Cálculo da distância em milímetros
    D_mm.Dado = (uint16_t)(v_som * (tempo_s / 2)*1000);
    TMR1_WriteTimer(0);
}

