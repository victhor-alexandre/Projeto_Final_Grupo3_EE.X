/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1827
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "main.h"


uint8_t bin2ascii(uint8_t vBin){
    vBin = vBin & 0x0F;                             // Apaga nible alto
    if(vBin<10){                                    // Se valor < 0xA
        vBin = vBin + 0x30; // 0..9                 // Acresecenta 0x30 (ascii '0')
    }
    else{                                           // se n�o
        vBin = vBin + 0x37; // A..F                 // accrescenta 0x37 (ascii '0'+7)
    }
    return vBin;
}

uint16_t ascii2bin(char *ascii){
    // Fun��o para converter uma string ASCII de tr�s d�gitos para um n�mero bin�rio
    uint16_t result = 0;
        // Converter o primeiro caractere
    if (ascii[0] >= '0' && ascii[0] <= '9') {
        result += (ascii[0] - '0') * 100;
    } else {
        return 0xFFFF; // Retorna 0xFFFF (65535) como valor de erro
    }
    
    // Converter o segundo caractere
    if (ascii[1] >= '0' && ascii[1] <= '9') {
        result += (ascii[1] - '0') * 10;
    } else {
        return 0xFFFF; // Retorna 0xFFFF (65535) como valor de erro
    }
    
    // Converter o terceiro caractere
    if (ascii[2] >= '0' && ascii[2] <= '9') {
        result += (ascii[2] - '0');
    } else {
        return 0xFFFF; // Retorna 0xFFFF (65535) como valor de erro
    }
    
    return result; // Retorna o valor bin�rio correspondente
}

/*
void Motor(uint16_t P){
    
    if(P > Est_atual){
        passos = P - Est_atual;
        Horario();
    }else{
         passos = Est_atual - P;
         AntiHorario();
    }
    Est_atual = P;
}

void RX_Dado(){
    if (EUSART_is_rx_ready()) {                   //Verifica se houve recep��o de dados no USART
        char ChRX = EUSART_Read(); 
            
        if (ChRX == INI_Q){
                Cnt_RX = 0;
            } else if (ChRX == FIM_Q) {
                Analisa_RX();
            } else {
                if (Cnt_RX < BUFFER_MAX) {
                    BufferRX[Cnt_RX] = ChRX;
                    Cnt_RX++;
                }
            }
    } 
}

void Analisa_RX(){ 
    char comando = BufferRX[0];
    
    for (uint8_t i=3;i>0;i--){
       DadosCh[i-1] = BufferRX[i];            //Armazenando o buffer de recep��o em outro de tratamento
    }
    //AuxRX.Dado = ascii2bin(DadosCh);
    
    switch(comando){
        case 'P':
           AuxRX.Dado = ascii2bin(DadosCh);
           if(AuxRX.Dado<101){
               uint16_t PWM = 10.23*AuxRX.Dado;
               EPWM1_LoadDutyValue(PWM);
           }else{
               //Erro();
           }
      break;
      case 'F':
           AuxRX.Dado = ascii2bin(DadosCh);
           if(AuxRX.Dado<101){
               uint16_t Prxo_Estado = 5.12*AuxRX.Dado;
               Motor(Prxo_Estado);
           }else{
               //Erro();
           }
      break;
      //default: 
     // ERRO();
      }
      
}

void AntiHorario() {
   for(uint8_t i=0;i<passos;i++) { 
     
     passo1();
     __delay_us(10);
     passo2();
     __delay_us(10);
     passo3();
     __delay_us(10);
     passo4();
     __delay_us(10);
   }
}

void Horario() {
    int i=0;
   while(i < passos) {
     passo4();
     __delay_us(10);
     passo3();
     __delay_us(10);
     passo2();
     __delay_us(10);
     passo1();
     __delay_us(10);
     i++;
   }
}

void passo1() {
  SM1_SetHigh();
  SM2_SetHigh();
  SM3_SetLow();
  SM4_SetLow();
}

void passo2() {
  SM1_SetLow();
  SM2_SetHigh();
  SM3_SetHigh();
  SM4_SetLow();
}

void passo3() {
  SM1_SetLow();
  SM2_SetLow();
  SM3_SetHigh();
  SM4_SetHigh();
}

void passo4() {
  SM1_SetHigh();
  SM2_SetLow();
  SM3_SetLow();
  SM4_SetHigh();
}

*/     

void F_Temperatura(){
    Temp.Dado = ADC_GetConversion(8);
    Temperatura[0] = (Temp.Dado/1000);
    Temperatura[1] = (Temp.Dado/100)%10;
    Temperatura[2] = (Temp.Dado/10)%10;
    Temperatura[3] = 0x2E;
    Temperatura[4] = (Temp.Dado)%10;
    Temperatura[5] = 0x43;
    
 
}
 
void Velocidade_Som(){
    float V_som = (3304 + ((float)Temp.Dado * 5.9)); //V = 330,4 + 0,59T / Multiplicado por 10 para preservar a casa decimal
    F_Posicao(V_som);
}  
  
void F_Posicao(){ 
    TMR1_GATE_ISR();
// TMR1_WriteTimer(0);
    // TRIGGER_SetHigh();
    // TMR1_StartSinglePulseAcquisition();
    // TRIGGER_SetLow();
    // while(TMR1GIF == 0)
    
    // Tempo = TMR1_ReadTimer();
    // D_mm.Dado = (uint16_t)((V*(float)Tempo)/2);
}

void TX_Dado(){
    //$TTT.T,PP.P<cr>
    BufferTX[0] = '$';
    BufferTX[1] = Temperatura[3];
    BufferTX[2] = Temperatura[2];
    BufferTX[3] = Temperatura[1];
    BufferTX[4] = '.';
    BufferTX[5] = Temperatura[0];
    BufferTX[6] = ',';
    BufferTX[7] = Posicao[2];
    BufferTX[8] = Posicao[1];
    BufferTX[9] = '.';
    BufferTX[10] = Posicao[0];
    BufferTX[11] = 0x0D;

    //Transmite Buffer de dados
    for (int i = 0; i < 12; i++) {
        EUSART_Write(BufferTX[i]);
    }
}






void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //NTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

   // TMR0_SetInterruptHandler(TX_Dado);
    TMR1_GateInterruptHandler(F_Posicao);    //É chamada toda vez que o Echo for de nível lógico alto p/ baixo

    while (1)
    {
        F_Temperatura();
        Velocidade_Som();
      //RX_Dado();
    }
}
/**
 End of File
*/