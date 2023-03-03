#include <EmonLib.h>// Para o sensor de Corrente
#include "HX711.h"//Para o sensor de carga
#include <Wire.h> // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h>//Bibllioteca do LCD

float medsc;
float tensao;
float Porcentagem_Potenciometro;
float correnteCalibracao = 18.40; // Valor de Calibração do Sensor 
int esc = 5;
const int RPMV = 1000;// Constante RMP/V do motor. Valor exemplo tem que ver com a mecanica o RPM/V do motor
const int pinoSensor = A2; // Entrada Analógica 2 do Arduino
EnergyMonitor medidor; // Declaração de variável da Classe EnergyMonitor
HX711 escala;//Sensor de carga

#define DT A2
#define SCK A1

LiquidCrystal_I2C lcd(0x3f , 16, 2); // Chamada da funcação LiquidCrystal para ser usada com o I2C

void setup() {
    Serial.begin(9600);// Define a velocidade da transmissão de dados em bits por segundos
    Wire.begin();

    escala.begin (DT, SCK);
    Serial.println(escala.read());
    escala.set_scale(5555556.55); 

    escala.tare(0);

    medidor.current(pinoSensor,correnteCalibracao); // Passa os parâmetros (Pino Analógico / Valor de Calibração)
   
    /*lcd.init(); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
    //lcd.setBacklight(HIGH); // Serve para iniciar a comunicação com o display já conectado
    lcd.backlight(); // Serve para ligar a luz do display
    Comentado devido a falha do LCD */
    
    pinMode(A0, INPUT);
    pinMode(esc,OUTPUT);

}

void potenciometro_esc(){
    int Nivel_potenciometro = analogRead(A0); // leitura analogica potenciômetro
    int Nivel_esc = Nivel_potenciometro * 0.1749755620; //conversor do potenciometro para o esc (valor entre 0 e 1023, para um valor entre 0 e 179)
    Porcentagem_Potenciometro = (Nivel_potenciometro/1023)*100; //Porcentagem de acionamento do potenciômetro
    analogWrite(esc,Nivel_esc); // acionamento esc
}

void loop() {
    
    medsc = escala.get_value(1);// define medsc como a leitura do sensor de carga
  
    double correnteFinal = medidor.Irms; // A variável "correnteFinal" recebe o valor da corrente em RMS                    
    potenciometro_esc();
    tensao = Porcentagem_Potenciometro * 10000;// Mudar valor da resistencia
    
    Serial.print("A: ");
    Serial.println(correnteFinal); // imprime a corrente na tela

    Serial.print("W: ");
    Serial.println(medsc);//Sensor de Carga

    //led.setCursor(0,1);//muda para linha inferior do lcd
    //troca tudo Serial para LCD para funcionar o lcd
    Serial.print("RPM: ");
    Serial.println(RPMV*tensao);

    ///pORCENTAGEM DO POTENCIOMETRO
    Serial.print((analogRead(A0)/1023.0)*100);
    Serial.println("%: ");
    
    Serial.print(char(8));
    delay(100);//Ajustar delay ideal
    Serial.println("\n\n");
}
    medidor.current(pinoSensor,correnteCalibracao); // Passa os parâmetros (Pino Analógico / Valor de Calibração)
   
    /*lcd.init(); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
    //lcd.setBacklight(HIGH); // Serve para iniciar a comunicação com o display já conectado
    
    lcd.backlight(); // Serve para ligar a luz do display
    //lcd nao esta funcionando usando o serial print mesmo
    */
    pinMode(A0, INPUT);
    pinMode(esc,OUTPUT);

}

void potenciometro_esc(){
    int Nivel_potenciometro = analogRead(A0); // leitura analogica potenciômetro
    int Nivel_esc = Nivel_potenciometro * 0.1749755620; //conversor do potenciometro para o esc (valor entre 0 e 1023, para um valor entre 0 e 179)
    Porcentagem_Potenciometro = (Nivel_potenciometro/1023)*100; //Porcentagem de acionamento do potenciômetro
    analogWrite(esc,Nivel_esc); // acionamento esc
}

void loop() {
    
    medsc = escala.get_value(1);// define medsc como a leitura do sensor de carga
    //medidor.calcVI(20,200) // Calcula a Potência (V*I) (20 semiciclos / tempo limite para fazer a medição)
    double correnteFinal = medidor.Irms; // A variável "correnteFinal" recebe o valor da corrente em RMS                    
    potenciometro_esc();
    tensao = Porcentagem_Potenciometro * 10000;// Mudar valor da resistencia
    
    Serial.print("A: ");
    Serial.println(correnteFinal); // imprime a corrente na tela

    Serial.print("W: ");
    Serial.println(medsc);//Sensor de Carga

    //Serial.setCursor(0,1);//muda para linha inferior do lcd
    
    Serial.print("RPM: ");
    Serial.println(RPMV*tensao);

    ///pORCENTAGEM DO POTENCIOMETRO
    Serial.print((analogRead(A0)/1023.0)*100);
    Serial.println("%: ");
    
    delay(100);//Ajustar delay ideal
    Serial.println("\n\n");
}
