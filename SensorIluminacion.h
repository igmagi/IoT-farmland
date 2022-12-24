
// CLASE SENSOR ILUMINACIÓN
class SensorIluminacion{

  private:

    //pin: pin analógico
    int pin;

    //pAdc: puntero al objeto adc
    Adafruit_ADS1015 * pAdc;

    //DarkValue: Valor del sensor de iluminación en la oscuridad.
    int DarkValue;

    //LightValue: Valor del sensor de iluminación con la máxima luz.
    int LightValue;

    //Calcular % iluminación
    int calcular_iluminacion(int vdig) {
      int iluminacion = 100*DarkValue/(DarkValue-LightValue)-vdig*100/(DarkValue-LightValue);
      if(iluminacion<0){iluminacion=0;}
      else if(iluminacion>100){iluminacion=100;};
      return iluminacion;
    }

  public:

    SensorIluminacion (int _pin, Adafruit_ADS1115 * _adc, int _DarkValue, int _LightValue) {
      (*this).pin = _pin;
      (*this).pAdc = _adc;
      (*this).DarkValue = _DarkValue;
      (*this).LightValue = _LightValue;
    }

    int getIluminacion(){
      int vdig = (*pAdc).readADC_SingleEnded((*this).pin);
      int iluminacion = calcular_iluminacion(vdig);
      return iluminacion;
    }
};// class SensorIluminacion
