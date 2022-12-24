
// CLASE SENSOR TEMPERATURA         

class SensorTemperatura {
  
  private:
  
    //pin: pin analógico
    int pin;
    
    //pAdc: puntero al objeto adc
    Adafruit_ADS1015 * pAdc;
    
    //a: Valor característico depende de NTC
    double a;
    
    //b: Valor característico depende de NTC
    double b;
    
    //calibracion: valor a sumar para que la temperatura leída se ajuste a la temperatura real
    double calibracion;
    
    //int tensiondigital -> funcion() -> double tensionanalogica 
    double calcular_tension_analogica(int vdig) {
      return (4.096*vdig)/32767;
    }
    //double tensionanalogica -> funcion() -> double temperatura
    double calcular_temperatura(double vanalog){
      return ((vanalog-a)/(b)) + calibracion;
    }
    
  public:
    //CONSTRUCTOR (_pin: pin de la señal, _adc: puntero al objeto adc, _a: valor 1 ntc, _b: valor 2 ntc, _calibracion: diferencia de temperatura real con la que muestra el sensor)
    SensorTemperatura(const int _pin, Adafruit_ADS1115 * _adc, double _a, double _b, double _calibracion){
      (*this).pin= _pin;
      (*this).pAdc = _adc;
      (*this).a = _a;
      (*this).b = _b;
      (*this).calibracion = _calibracion;
    }
    
    //LEE LA TEMPERATURA (Devuelve la temperatura)
    double getTemperatura(){
      int vdig = (*pAdc).readADC_SingleEnded((*this).pin);
      double vanalog = calcular_tension_analogica(vdig);
      double temperatura = calcular_temperatura(vanalog);
      return temperatura;
    }
 
  
  
}; // class SensorTemperatura
