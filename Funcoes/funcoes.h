/* 
 * File:   funcoes.h
 * Author: victhor
 *
 * Created on August 31, 2024, 9:18 PM
 */

#ifndef FUNCOES_H
#define	FUNCOES_H

#define Kc 0.1
#define T 0.01      //10 ms
#define Ti 0.1      //1 ms


#include <xc.h> // include processor files - each processor file is guarded.  

#define MAX_PASSO 420
    
uint16_t posicaoValvula, proximaPosicao;

float Erro = 0, Erro_1 = 0;
float SaidaControlador=0.0, SaidaAnterior=0.0;
bool modoControle;  //0 = controle desativado, 1 = controle ativado
bool tipoControle;  //0 = controle do pwm, 1 = controle do motor de passo;
float Setpoint, Distancia;
#define limite ((tipoControle) ? (float)(1023.0) : (float)(420.0))         //limite da saída do controlador muda com o tipo de operação
                                    //1023 para o pwm, 420 para o motor de passo
#define sinal  ((tipoControle) ? 1 : -1)     
//como o motor de passo segue operação inversa (para aumentar o fluxo de ar, diminui-se a posição da válvula)
//então invertemos o sinal de Kp com essa variável, de acordo com o modo de operação

void setPwm(uint16_t dutyValue);

void interrupt_MotorDePasso();

void Passo(uint16_t posicaoAtual, uint16_t posicaoDesejada);

void calcularErro(void);

void calcularSaidaControlador(void);

void guardarValoresDoControlador(void);

#endif	/* FUNCOES_H */

