#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SFE_BMP180.h>

#include <TinyGPS++.h>  //Librería del GPS
#include <SoftwareSerial.h>

#include "SensorPresion.h"
#include "SensorHumedad.h"
#include "SensorSalinidad.h"
#include "SensorTemperatura.h"
#include "SensorIluminacion.h"
#include "SensorGPS.h"
#include "Acelerometro.h"
#include "ConexionWifi.h"

#define PIN_HUMEDAD 3 //Pin A0 (entrada analógica)
#define PIN_TEMPERATURA 2 //Pin A1 (entrada analógica)
#define PIN_SALINIDAD 1 //Pin A2 (entrada analógica)
#define PIN_ILUMINACION 0 //Pin A3 (entrada analógica)
#define PIN_POWERPIN_SALINIDAD 5 


//Creamos instancia ADS1115
Adafruit_ADS1115 ads1115(0x48);


//CREAMOS LOS OBJETOS DE LAS CLASES DE LOS SENSORES:

//Sensor de temperatura
double a = 0.75; // Valor característico 1 según NTC
double b = 0.036; // Valor característico 2 según NTC
double calibracion = 1; // (Se suma a la temperatura, CALIBRACION)
SensorTemperatura sensor_temperatura (PIN_TEMPERATURA, &ads1115, a, b, calibracion);

//Sensor de humedad
int valorAire = 18670;  // Medimos valor en seco (CALIBRACION)
int valorAgua = 9520;  // Medimos valor en agua  (CALIBRACION)
SensorHumedad sensor_humedad (PIN_HUMEDAD, &ads1115, valorAire, valorAgua);

//Sensor de salinidad
int SinSal = 18797; // Valor agua sin sal (CALIBRACION)
int ConSal = 21500; // Valor agua con sal (CALIBRACION)
SensorSalinidad sensor_salinidad(PIN_SALINIDAD, PIN_POWERPIN_SALINIDAD, &ads1115, SinSal, ConSal);

//Sensor de iluminación
int valorOscuridad = 4007; // Valor sensor tapado (CALIBRACION)
int valorLuz = 30600; // Valor luz directa de linterna (CALIBRACION)
SensorIluminacion sensor_iluminacion(PIN_ILUMINACION, &ads1115, valorOscuridad, valorLuz);

//SETUP
void setup() {
  Serial.begin(9600);
  setup_ADC();
  setup_SensorPresion();
 // setup_GPS();

  setup_Acelerometro();

  setup_Wifi();
}

//LOOP
void loop() {
  
  getADC();
  double t = sensor_temperatura.getTemperatura();
  getPresion(t);
  getGPS();
  getAcelerometro();
  delay(2000);
  /*ESP.deepSleep(7 * 1000);
    */
    
}//()


//FUNCIÓN CONFIGURACIÓN DEL ADC
void setup_ADC(){
  ads1115.begin(); //Inicializa ads1115
  Serial.println("Ajustando la ganancia...");
  ads1115.setGain(GAIN_ONE);
  Serial.println("Tomando medidas del canal AIN0");
  Serial.println("Rango del ADC: +/- 4.096V (1 bit=2mV)");
}

//FUNCION PARA LEER TODOS LOS SENSORES CONECTADOS AL ADC
void getADC() { 
  Serial.println("------------------------");
  Serial.print("Humedad: ");
  int h = sensor_humedad.getHumedad();
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temperatura: ");
  double t = sensor_temperatura.getTemperatura();
  Serial.print(t);
  Serial.println("ºC");
  Serial.print("Salinidad: ");
  int s = sensor_salinidad.getSalinidad();
  Serial.print(s);
  Serial.println("%");
  Serial.print("Iluminación: ");
  int i = sensor_iluminacion.getIluminacion();
  Serial.print(i);
  Serial.println("%");
  sendParameters(h,i,t,s);
}
