SFE_BMP180 pressure;

void setup_SensorPresion(){
// Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {

    Serial.println("BMP180 init fail\n\n");
    while (1); // Pause forever.
  }
}


void getPresion(double temperatura){
  char status;
  double T,P;//declaración de variables
  T = temperatura;

  status = pressure.startPressure(3);//función para verificar si funciona el sensor de presión
  if (status != 0){
    // Wait for the measurement to complete:
    delay(status); //Continuar cuando funciona

    status = pressure.getPressure(P, T);//Función para obtener la presión con dos variables
    Serial.print("Presión: ");
    Serial.print(P, 2);
    Serial.println("mb");
      
    }
    else{
      Serial.println("Presión: Error en la lectura.");
    }
}
