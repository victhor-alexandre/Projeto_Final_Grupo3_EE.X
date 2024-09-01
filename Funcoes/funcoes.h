/* 
 * File:   funcoes.h
 * Author: victhor
 *
 * Created on August 31, 2024, 9:18 PM
 */

#ifndef FUNCOES_H
#define	FUNCOES_H


#include <xc.h> // include processor files - each processor file is guarded.  

#define MAX_PASSO 450
    
uint16_t posicaoValvula, proximaPosicao;

void interrupt_MotorDePasso();

void Passo(uint16_t posicaoAtual, uint16_t posicaoDesejada);


#endif	/* FUNCOES_H */

