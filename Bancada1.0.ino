#include <DFRobot_HX711_I2C.h>
#include <EmonLib.h>
#include <LiquidCrystal.h> //Biblioteca para o LCD

float medsc;
float tensao;
#define correnteCalibracao 18.40 // Valor de Calibração do Sensor 
#define potenciometro A0
#define esc 5
const int RPMV = 1000 // Constante RMP/V do motor. Valor exemplo tem que ver com a mecanica o RPM/V do motor
const int pinoSensor = A2; // Entrada Analógica 2 do Arduino
EnergyMonitor medidor; // Declaração de variável da Classe EnergyMonitor

LiquidCrystal lcd(11, 9, 4, 5, 6, 13);//definição das portas de conexao do lcd 
//Portas na Documentacao
void setup() {
    DFRobot_HX711_I2C.begin(); //inicia o sensor de carga
    DFRobot_HX711_I2C.getCalibration(); //calibra o sensor de carga

    Serial.begin(9600); // Define a velocidade da transmissão de dados em bits por segundos
    medidor.current(pinoSensor,correnteCalibracao); // Passa os parâmetros (Pino Analógico / Valor de Calibração)

    lcd.begin(16, 2);//proporcao do lcd em linhas e colunas respectivamente(inicia o lcd)

    pinMode(potenciometro, INPUT);
    pinMode(esc,OUTPUT);

}

void potenciometro_esc(){
    int Nivel_potenciometro = analogRead(potenciometro);
    int Nivel_esc = Nivel_potenciometro * 0.1749755620;
    analogWrite(esc,Nivel_esc);
}

void loop() {
    

    medsc = DFRobot_HX711_I2C.readWheight(6); // define medsc como a leitura do sensor de carga
<<<<<<< HEAD
   
    //medidor.calcVI(20,200) // Calcula a Potência (V*I) (20 semiciclos / tempo limite para fazer a medição)
=======
    medidor.calcVI(20,200) // Calcula a Potência (V*I) (20 semiciclos / tempo limite para fazer a medição)
>>>>>>> f2a1fb66d06a32bac91cb6d51cdbda768fb565b2
    double correnteFinal = medidor.Irms; // A variável "correnteFinal" recebe o valor da corrente em RMS
    tensao = medirTensao(); // Mede a tensão do sistema. De a cordo com o pedro tem jeito do arduino ler a resistencia do potenciometro,
                            // se nao tiver sempre tem como fazer uma regra de três
    
    potenciometro_esc();
    
    lcd.print("A: ");
    lcd.print(correnteFinal); // imprime a corrente na tela

    lcd.print("W: ");
    lcd.print(medsc);//Sensor de Carga

    lcd.setCursor(0,1);//muda para linha inferior do lcd
    
    lcd.print("RPM: ");
    lcd.print(RPMV*tensao)
    

    delay(2000);//Ajustar delay ideal

}