#include <DFRobot_HX711_I2C.h>
#include <EmonLib.h>
#include <LiquidCrystal.h> //Biblioteca para o LCD

float medsc;

#define correnteCalibracao 18.40 // Valor de Calibração do Sensor 

const int pinoSensor = A2; // Entrada Analógica 2 do Arduino
EnergyMonitor medidor; // Declaração de variável da Classe EnergyMonitor

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//definição das portas de conexao do lcd tem qu e conferir com o pessoal do hardware 

void setup() {
    DFRobot_HX711_I2C.begin(); //inicia o sensor de carga
    DFRobot_HX711_I2C.getCalibration(); //calibra o sensor de carga

    Serial.begin(9600); // Define a velocidade da transmissão de dados em bits por segundos
    medidor.current(pinoSensor,correnteCalibracao); // Passa os parâmetros (Pino Analógico / Valor de Calibração)

    lcd.begin(16, 2);//proporcao do lcd em linhas e colunas respectivamente(inicia o lcd)



}

void loop() {
    medsc = DFRobot_HX711_I2C.readWheight(6); // define medsc como a leitura do sensor de carga
   
    //medidor.calcVI(20,200) // Calcula a Potência (V*I) (20 semiciclos / tempo limite para fazer a medição)
    double correnteFinal = medidor.Irms; // A variável "correnteFinal" recebe o valor da corrente em RMS

    /*Serial.print("Corrente Medida: ");
    Serial.print(correnteFinal);
    Serial.print("A");*/

    lcd.print("A: ");
    lcd.print(correnteFinal); // imprime a corrente na tela

    lcd.print("W:");
    lcd.print("medsc");

    lcd.setCursor(0,1);//muda para linha inferior do lcd
    
}