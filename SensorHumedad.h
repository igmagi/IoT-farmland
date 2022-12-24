
// CLASE SENSOR HUMEDAD
class SensorHumedad{
  
  private:
  
    //pin: pin analógico
    int pin;
    
    //pAdc: puntero al objeto adc
    Adafruit_ADS1015 * pAdc;

    //AirValue: Valor del sensor de humedad en seco.
    int AirValue;
    
    //WaterValue: Valor del sensor de humedad en seco.
    int WaterValue;
    
    //Calcular % humedad
    int calcular_humedad(int vdig) {
      int humedad = 100*AirValue/(AirValue-WaterValue)-vdig*100/(AirValue-WaterValue);
      if(humedad<0){humedad=0;}
      else if(humedad>100){humedad=100;};
      return humedad;
    }
  
  public:
  
    SensorHumedad (int _pin, Adafruit_ADS1115 * _adc, int _AirValue, int _WaterValue) {
      (*this).pin = _pin;
      (*this).pAdc = _adc;
      (*this).AirValue = _AirValue;
      (*this).WaterValue = _WaterValue;
    }
    
    int getHumedad(){
      int vdig = (*pAdc).readADC_SingleEnded((*this).pin);
      int humedad = calcular_humedad(vdig);
      return humedad;
    }
};// class SensorHumedad
