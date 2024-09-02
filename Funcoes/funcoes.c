#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "funcoes.h"

// Controle do motor de passo
//----------------------------------
// O motor de passo será controlado pela interrupção de um timer de 5ms.
// Cada interrupção, o controlador verifica se o motor já chegou na posição desejada, e se não, avança um único passo na direção em questão
// Necessário 1 controle de direção, um contador, um booleano para inicializar o motor.

void setPwm(uint16_t dutyValue){     //recebe o valor do pwm
    static uint16_t pwm;
    pwm = dutyValue;
    EPWM1_LoadDutyValue(pwm);
}

void interrupt_MotorDePasso(void){      //ativado a cada 5ms
    static uint16_t posicaoValvulaReset = MAX_PASSO;       //essa variável será decrementada e enviada ao motor de passo, até que ele desative o sensor
    if(resetPasso){     //se o reset estiver habilitado (resetPasso = 1))
        if(LIM_PORT){       //se o sensor estiver em 1
            Passo(posicaoValvulaReset, 0);      //dá um passo para abrir a valvula
            posicaoValvulaReset--;
        }else{              //se o sensor estiver em 0
            resetPasso = 0;             //desliga o reset
            posicaoValvula = 0;         //agora a posição padrão é zerada
            posicaoValvulaReset = MAX_PASSO;  //essa variavel é resetada em 450 para um futuro reset
        }
    }else{      //se o reset estiver desabilitado
        //atualiza a posicao atual da válvula e depois dá um passo.
        if(posicaoValvula > proximaPosicao){
            if(posicaoValvula>0) posicaoValvula--;
        }else if (posicaoValvula < proximaPosicao){
            if(posicaoValvula<MAX_PASSO) posicaoValvula++;
        }
        Passo(posicaoValvula, proximaPosicao);     //dá um passo de acordo com as posições atuais e desejada
    }
}

void Passo(uint16_t posicaoAtual, uint16_t posicaoDesejada){
    static uint8_t i;
    SM1_SetLow();
    SM2_SetLow();
    SM3_SetLow();
    SM4_SetLow();
    
    if(posicaoAtual > posicaoDesejada){
        i = (i==0) ? 3 : (i-1);       //decrementa i, se i = 0, então volta para i=3
    }else if (posicaoAtual < posicaoDesejada){
        i = (i==3) ? 0 : (i+1);       //incrementa i, se i = 3, então volta para i=0
    }
    
    switch(i){
        case 3:
            SM1_SetHigh();
            SM2_SetHigh();
            break;
        case 2:
            SM2_SetHigh();
            SM3_SetHigh();
            break;
        case 1:
            SM3_SetHigh();
            SM4_SetHigh();
            break;
        case 0:
            SM4_SetHigh();
            SM1_SetHigh();
            break;
    }
    
}


// rotina de controle
// Modelo PI (proporcional-integrador)
// Deve controlar ou o pwm, ou o motor de passo
// faz parte da máquina de estados. Ou seja, deve ser bypassed quando um dos modos de controle estiver inativo

void calcularErro(void){
    Erro = Setpoint - Distancia;        //Erro(k) = sp(K) - y(K)
}

void calcularSaidaControlador(void){
    SaidaControlador = (float)(sinal*Kc)*((Erro - Erro_1)+(T/Ti)*((Erro+Erro_1)/2)) + (float)(SaidaAnterior);
    
    //limitando a saída
    if(SaidaControlador < 0.0){
        SaidaControlador = 0.0;
    }else if(SaidaControlador > limite){
        SaidaControlador = limite;
    }
}

void guardarValoresDoControlador(void){
    Erro_1 = Erro;
    SaidaAnterior = SaidaControlador;
}

