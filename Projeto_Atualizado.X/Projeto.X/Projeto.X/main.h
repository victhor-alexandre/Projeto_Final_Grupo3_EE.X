<<<<<<< HEAD
/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include <xc.h> // include processor files - each processor file is guarded.

#define INI_Q      '$'
#define FIM_Q       0x0D
#define BUFFER_MAX  7
//------------------------------------------------------------------------------------------------------------------------------------------------------
//Variáveis e tabelas
//Vetor com os valores da velocidade do som para cada uma das possíveis temperaturas
__eeprom float tabela_veloc_som[] = {0.00, 20.05, 28.36, 34.74, 40.11, 44.84 
,49.12, 53.06, 56.72, 60.16, 63.42, 66.51, 69.47, 72.31, 75.04
, 77.67, 80.22, 82.69, 85.09, 87.42, 89.69, 91.90, 94.07
, 96.18, 98.25, 100.27, 102.26, 104.21, 106.12, 108.00
, 109.84, 111.66, 113.45, 115.21, 116.94, 118.65, 120.33
, 121.99, 123.63, 125.24, 126.84, 128.41, 129.97, 131.51
, 133.03 , 134.53, 136.02, 137.49, 138.94, 140.38, 141.81
};
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Arrays
char Temperatura[5];               //< Temperatura         
char Posicao[4];                   //< Posição
char BufferTX[13];              //< Buffer para Transmissão
char BufferRX[5];
char DadosCh[3];
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Estrutura de dados (Union)
union{                             //< União entre 2 bytes de dados.
    uint16_t Dado;                 //< Valor de 16 bits que contem os bytes b1 e b0.
    struct{
        uint8_t b0;                //< Byte b0 
        uint8_t b1;                //< Byte b1  
    };
}Temp,D_mm,AuxRX;                      //< Variaveis de Temperatura e Posicão

//union{                             //< União entre os nibles a serem transmitidos ou recebidos.
//    uint16_t nibbles;              //< Valor de 16 bits que contem os nibles n3, n2, n1 e n0.
//    struct{
//        uint8_t n0 : 4;            //< Nible n0 
//        uint8_t n1 : 4;            //< Nible n1  
//        uint8_t n2 : 4;            //< Nible n2 
//        uint8_t n3 : 4;            //< Nible n3 
//    };
//}Temp_TX,D_TX;                        //< Variável com o valor Temperatura e Posicão para envio.

typedef union{          ///< Uni?o
    uint16_t v16;       ///< Valor uint16
    uint8_t v8[2];      ///< Valor com os 2 bytes que formam o uint16
    struct{             ///< Estrutura com os nibbles que forman o uint16
        uint8_t n0 : 4; ///< nibble n0 
        uint8_t n1 : 4; ///< nibble n1  
        uint8_t n2 : 4; ///< nibble n2 
        uint8_t n3 : 4; ///< nibble n3 
    };
}uint16_u;
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Variavel global 16 bits
uint16_t Tempo, passos, Est_atual;                    // Variavel para armazenar o Tempo do Pulso
uint8_t  Cnt_RX;

// Variavel global float
float v_som;
const float P_fosc = 0.000001; 
float tempo_s = 0;
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Funções
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Aquisição da Temperatura do sensor LM35
 * @param
 * @return
 */
void Temperatura_e_VelocidadeSom();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Aquisição da Posição da bola no Tubo
 * @param  V valor da velocidade do Ar
 * @return
 */
void Posicao_Bola_Tubo(void);
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Interrupção para o Motor de Passo
 */
void Interrupcao();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Transforma valor binario em ASCII.
 * @param vBin Valor binario de 4 bits;
 * @return Valor ASCII de 8 bits.
 */
uint8_t bin2ascii(uint8_t vBin);
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Transforma valor ASCII em binário.
 * @param vAscii Valor ASCII de 8 bits
 * @return Valor binario de 4 bits;
 */
//uint16_t ascii2bin(char *ascii, int );
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Analisa dados recebidos e executa acções necessárias.
 */
void RX_Dado();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Envia os dados via protocolo serial.
 */
void TX_Dado();
//------------------------------------------------------------------------------------------------------------------------------------------------------
///**
// * Função para ajustar a velocidade do som
// */
//void Velocidade_Som();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Função auxiliar para passo 1
 */
void passo1();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função auxiliar para passo 2
 */
void passo2();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função auxiliar para passo 3
 */
void passo3();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função auxiliar para passo 4
 */
void passo4();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função auxiliar para sentido Anti-Horario
 */
void AntiHorario();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função auxiliar para sentido Horario
 */
void Horario();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função para analisar o buffer RX
 */
void Analisa_RX();

=======
/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include <xc.h> // include processor files - each processor file is guarded.

#define INI_Q      '$'
#define FIM_Q       0x0D
#define BUFFER_MAX  7
//------------------------------------------------------------------------------------------------------------------------------------------------------
//Variáveis e tabelas
//Vetor com os valores da velocidade do som para cada uma das possíveis temperaturas
__eeprom float tabela_veloc_som[] = {28.36,34.74,40.11,44.84,49.12,
53.06,56.72,60.16,63.42,66.51,69.47,72.31,75.04,77.67,80.22,
82.69,85.09,87.42,89.69,91.90,94.07,96.18,98.25,100.27,
102.26,104.21,106.12,108.00,109.84,111.66,113.45,115.21,
116.94,118.65,120.33,121.99,123.63,125.24,126.84,128.41,
129.97,131.51,133.03,134.53,136.02,137.49,138.94,140.38,141.81};
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Arrays
char Temperatura[5];               //< Temperatura         
char Posicao[4];                   //< Posição
char BufferTX[13];              //< Buffer para Transmissão
char BufferRX[5];
char DadosCh[3];
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Estrutura de dados (Union)
union{                             //< União entre 2 bytes de dados.
    uint16_t Dado;                 //< Valor de 16 bits que contem os bytes b1 e b0.
    struct{
        uint8_t b0;                //< Byte b0 
        uint8_t b1;                //< Byte b1  
    };
}Temp,D_mm,AuxRX;                      //< Variaveis de Temperatura e Posicão

//union{                             //< União entre os nibles a serem transmitidos ou recebidos.
//    uint16_t nibbles;              //< Valor de 16 bits que contem os nibles n3, n2, n1 e n0.
//    struct{
//        uint8_t n0 : 4;            //< Nible n0 
//        uint8_t n1 : 4;            //< Nible n1  
//        uint8_t n2 : 4;            //< Nible n2 
//        uint8_t n3 : 4;            //< Nible n3 
//    };
//}Temp_TX,D_TX;                        //< Variável com o valor Temperatura e Posicão para envio.

typedef union{          ///< Uni?o
    uint16_t v16;       ///< Valor uint16
    uint8_t v8[2];      ///< Valor com os 2 bytes que formam o uint16
    struct{             ///< Estrutura com os nibbles que forman o uint16
        uint8_t n0 : 4; ///< nibble n0 
        uint8_t n1 : 4; ///< nibble n1  
        uint8_t n2 : 4; ///< nibble n2 
        uint8_t n3 : 4; ///< nibble n3 
    };
}uint16_u;
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Variavel global 16 bits
uint16_t Tempo, passos, Est_atual;                    // Variavel para armazenar o Tempo do Pulso
uint8_t  Cnt_RX;

// Variavel global float
float v_som;
const float P_fosc = 0.000001; 
float tempo_s = 0;
//------------------------------------------------------------------------------------------------------------------------------------------------------
// Funções
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Aquisição da Temperatura do sensor LM35
 * @param
 * @return
 */
void Temperatura_e_VelocidadeSom();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Aquisição da Posição da bola no Tubo
 * @param  V valor da velocidade do Ar
 * @return
 */
void Posicao_Bola_Tubo(void);
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Interrupção para o Motor de Passo
 */
void Interrupcao();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Transforma valor binario em ASCII.
 * @param vBin Valor binario de 4 bits;
 * @return Valor ASCII de 8 bits.
 */
uint8_t bin2ascii(uint8_t vBin);
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Transforma valor ASCII em binário.
 * @param vAscii Valor ASCII de 8 bits
 * @return Valor binario de 4 bits;
 */
//uint16_t ascii2bin(char *ascii, int );
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Analisa dados recebidos e executa acções necessárias.
 */
void RX_Dado();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Envia os dados via protocolo serial.
 */
void TX_Dado();
//------------------------------------------------------------------------------------------------------------------------------------------------------
///**
// * Função para ajustar a velocidade do som
// */
//void Velocidade_Som();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Função auxiliar para passo 1
 */
void passo1();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função auxiliar para passo 2
 */
void passo2();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função auxiliar para passo 3
 */
void passo3();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função auxiliar para passo 4
 */
void passo4();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função auxiliar para sentido Anti-Horario
 */
void AntiHorario();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função auxiliar para sentido Horario
 */
void Horario();
//------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Função para analisar o buffer RX
 */
void Analisa_RX();

>>>>>>> 2ad5bec33a971b468d2875604a7d78680d0c99b2
#endif	/* XC_HEADER_TEMPLATE_H */