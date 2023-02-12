#include <EmonLib.h>
#define correnteCalibracao 18.40 // Valor de Calibração do Sensor 
const int pinoSensor = A2; // Entrada Analógica 2 do Arduino
EnergyMonitor medidor; // Declaração de variável da Classe EnergyMonitor

void setup() {
  Serial.begin(9600); // Define a velocidade da transmissão de dados em bits por segundos
  medidor.current(pinoSensor,correnteCalibracao); // Passa os parâmetros (Pino Analógico / Valor de Calibração)
}

void loop() {

  medidor.calcVI(20,200) // Calcula a Potência (V*I) (20 semiciclos / tempo limite para fazer a medição)
  double correnteFinal = medidor.Irms; // A variável "correnteFinal" recebe o valor da corrente em RMS

    Serial.print("Corrente Medida: ");
    Serial.print(correnteFinal);
    Serial.print("A");

}
