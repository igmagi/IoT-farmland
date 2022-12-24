
//CLASE SENSOR SALINIDAD
class SensorSalinidad {
  
  private: 
 
    //pin: pin analógico
    int pin;
    
    //pAdc: puntero al objeto adc
    Adafruit_ADS1015 * pAdc;
    
    //Pin de alimentación de la señal
    int powerPin;

    //SinSal: Valor del sensor en agua sin sal
    int SinSal;

    //ConSal: Valor del sensor en agua con sal
    int ConSal;
    
    //Función para emitir la señal
    void emitir (){
      digitalWrite((*this).powerPin, HIGH);
    }
    //Función para dejar de emitir la señal
    void parar (){
      digitalWrite((*this).powerPin, LOW);             
    }
    //Función para leer el valor del ADC
    int leerTensionDigital (){
      int16_t vdig = (*pAdc).readADC_SingleEnded ((*this).pin);
      return vdig;
    }

  public:
    
    SensorSalinidad (int _pin, int _powerpin, Adafruit_ADS1115 * _adc, int _SinSal, int _ConSal) {
      
    (*this).pin = _pin;
    (*this).pAdc = _adc;
    (*this).SinSal = _SinSal;
    (*this).ConSal = _ConSal;
    (*this).powerPin = _powerpin;
    pinMode(_powerpin, OUTPUT);
   
    }
         
    int getSalinidad(){
  
    (*this).emitir();
    int lectura = (*this).leerTensionDigital (); // Encendemos y apagamos el sensor para medir el voltaje 
    (*this).parar();
    int salinidad = (100*SinSal)/(SinSal-ConSal)-lectura*100/(SinSal-ConSal);

    if (salinidad < 0) {salinidad = 0;} 
    else if (salinidad > 100) {salinidad = 100;}

    return salinidad;

    }
};//class SensorSalinidad
