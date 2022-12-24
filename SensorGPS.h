/******************************************************************************
GTI - Semestre 1A
GPS A2235H 
Conectar RXI al pin 12 del ESP8266
Conectar TXO al pin 13 del ESP8266
Usamos el pin 15 para inicializar el GPS
ATENCION: no poner el GPS sobre el Sparkfun 

******************************************************************************/

#define RX_PIN  12 // GPS RXI
#define TX_PIN  13 // GPS TX0
#define INIT_PIN 15 // Pin para  Inicializar el GPS


#define GPS_BAUD  4800  // Velocidad de comunicación serie 

TinyGPSPlus gps; // Definimos el objeto gps

SoftwareSerial ss(RX_PIN,TX_PIN); // Creamos una UART software para comunicación con el GPS

/////////////////////////////////////////////////////////////////////////////////////////
///// FUNCIONES

// Función espera 1s para leer del GPS
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while(ss.available())
    {
      gps.encode(ss.read());  // Leemos del gps
    }
  } while(millis() - start < ms);
}
// Función para encender/apagar mediante un pulso
void switch_on_off()
{
   // Power on pulse
  digitalWrite(INIT_PIN,LOW);
  delay(200);
  digitalWrite(INIT_PIN,HIGH);
  delay(200); 
  digitalWrite(INIT_PIN,LOW);
 }


/////////////////////////////////////////////////////////////////////////
// CONFIGURACION
////////////////////////////////////////////////////////////////////////
void setup_GPS() {
  
  ss.begin(GPS_BAUD); // Inicializar la comunicación con el GPS
 
  pinMode(INIT_PIN,OUTPUT); 
  switch_on_off(); // Pulso para encender el GPS

}

/////////////////////////////////////////////////////////////////////////
// BUCLE
////////////////////////////////////////////////////////////////////////
void getGPS() {
  if(gps.location.isValid()){ // Si el GPS está recibiendo los mensajes NMEA

    Serial.print("Latitud: ");
    Serial.print(gps.location.lat(),6);
    Serial.print('\n');
    Serial.print("Longitud: ");
    Serial.print(gps.location.lng(),6);
    Serial.print('\n');
  }
  else  // Si no recibe los mensajes
  {
    
    Serial.print("Satelites a la vista: ");
    Serial.println(gps.satellites.value());
  }
  
}
