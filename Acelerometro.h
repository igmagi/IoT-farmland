#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C
/* 
#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18
*/
#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

#define interruptPin 4

//Funcion auxiliar lectura
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data){
   Wire.beginTransmission(Address);
   Wire.write(Register);
   Wire.endTransmission();
 
   Wire.requestFrom(Address, Nbytes);
   uint8_t index = 0;
   while (Wire.available())
      Data[index++] = Wire.read();
}
 
 
// Funcion auxiliar de escritura
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data){
   Wire.beginTransmission(Address);
   Wire.write(Register);
   Wire.write(Data);
   Wire.endTransmission();
}

/*
 *void handleInterrupt() {
    interruptCounter++;
  }
 */

void handleInterrupt(){
  
  Serial.println("El dispositivo ha sido movido");
}


void setup_Acelerometro(){
  //interruptPin por defecto a nivel alto. Cuando esté a nivel bajo se mandará la interrupción.
  pinMode(interruptPin, INPUT_PULLUP); 
  /*
  // Asociamos la interrupciÃ³n con el pin, con la función y con el umbral
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
 */
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
  
  Wire.begin();
  //Configuracion con los valores de la tabla: 
  
  I2CwriteByte(MPU9250_ADDRESS, 0x1C, 0x00);    //
  I2CwriteByte(MPU9250_ADDRESS, 0X6B, 0);
  I2CwriteByte(MPU9250_ADDRESS, 0X6C, 7);
  I2CwriteByte(MPU9250_ADDRESS, 0X1D, 9); //9
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x80);
  I2CwriteByte(MPU9250_ADDRESS, 0X38, 64); //0x40
  I2CwriteByte(MPU9250_ADDRESS, 0X69, 192);
  I2CwriteByte(MPU9250_ADDRESS, 0X1F, 2); //Sensibilidad
  I2CwriteByte(MPU9250_ADDRESS, 0X1E, 1);
  I2CwriteByte(MPU9250_ADDRESS, 0X6B, 32);
}

void getAcelerometro(){
  // ---  Lectura acelerometro y giroscopio ---
  uint8_t Buf[14];
  int FS_ACC = 16;
  int FS_GYRO = 2000;

  I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

  // Convertir registros acelerometro
  float ax = (Buf[0] << 8 | Buf[1]);
  float ay = (Buf[2] << 8 | Buf[3]);
  float az = Buf[4] << 8 | Buf[5];

  ax = (ax*FS_ACC/32768);
  ax = ax + 0.1;
  ay = (ay*FS_ACC/32768);
  ay = ay - 0.2;
  az = (az*FS_ACC/32768);
  az = az - 7.3;

  Serial.print("Aceleración en el eje X: ");
  Serial.print(ax, 2);
  Serial.println("g");

  Serial.print("Aceleración en el eje Y: ");
  Serial.print(ay, 2);
  Serial.println("g");
  
  Serial.print("Aceleración en el eje Z: ");
  Serial.print(az, 2);
  Serial.println("g");
}
