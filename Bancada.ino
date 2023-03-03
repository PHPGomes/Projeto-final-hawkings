#include <DFRobot_HX711_I2C.h>
#include <EmonLib.h>

#include "HX711.h"//Biclioteca do sensor de Carga

#include <Wire.h> // Biblioteca utilizada para fazer a comunicação com o I2C
#include <Adafruit_LiquidCrystal.h>

float medsc;
float tensao;
float Porcentagem_Potenciometro;
float correnteCalibracao = 18.40; // Valor de Calibração do Sensor 
int esc = 5;
const int RPMV = 1000;// Constante RMP/V do motor. Valor exemplo tem que ver com a mecanica o RPM/V do motor
const int pinoSensor = A2; // Entrada Analógica 2 do Arduino
EnergyMonitor medidor; // Declaração de variável da Classe EnergyMonitor

#define DT A2
#define SCK A1

HX711 escala;

Adafruit_LiquidCrystal lcd(0x30 , 16, 2); // Chamada da funcação LiquidCrystal para ser usada com o I2C

//Portas na Documentacao
void setup() {
    Serial.begin(9600);// Define a velocidade da transmissão de dados em bits por segundos
    Wire.begin();

    escala.begin (DT, SCK);
    Serial.println(escala.read());
    escala.set_scale(5555556.55); 

    escala.tare(0);

    medidor.current(pinoSensor,correnteCalibracao); // Passa os parâmetros (Pino Analógico / Valor de Calibração)

    
    //lcd.init(); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
    //lcd.setBacklight(HIGH); // Serve para iniciar a comunicação com o display já conectado
   // Serial.print("dfghjkl;");
    //lcd.backlight(); // Serve para ligar a luz do display*/
   // Serial.print("dfghjkl;");
    
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
    Serial.print(analogRead(A0)/1023.0*100);
    Serial.println("%: ");
    
    
    delay(1000);//Ajustar delay ideal

    Serial.println("\n\n");
    

}