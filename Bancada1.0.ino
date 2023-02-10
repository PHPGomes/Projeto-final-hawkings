#include <DFRobot_HX711_I2C.h>

float medsc;

void setup() {
DFRobot_HX711_I2C.begin(); //inicia o sensor de carga
DFRobot_HX711_I2C.getCalibration(); //calibra o sensor de carga
}

void loop() {
medsc = DFRobot_HX711_I2C.readWheight(6); // define medsc como a leitura do sensor de carga
}
