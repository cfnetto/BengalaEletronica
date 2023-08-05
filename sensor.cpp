#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

const int buzzer = 9;
int dist = 0, dist_old = 0;
unsigned long timeout = 0;


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  pinMode(buzzer, OUTPUT);
  
  sensor.init();
  sensor.setTimeout(500);

  // Perfil de longo alcance
  sensor.setSignalRateLimit(0.1);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
}

void loop()
{
  dist = sensor.readRangeSingleMillimeters();
    
  filtrar_sinal();
  if (dist < 1900) {
    tone(buzzer, 264, 300);
    delay(dist);
    noTone(buzzer);
  }  
  else if (dist < 1500) {
    tone(buzzer, 330, 600);
    delay(dist);
    noTone(buzzer);
  } 
  else if (dist < 1000) {
      tone(buzzer, 392, 800);
      delay(dist);
      noTone(buzzer);
  }   
  else if (dist < 750) {
    tone(buzzer, 494, 600);
    delay(dist);
    noTone(buzzer);
  }  
  else if (dist < 500) {
    tone(buzzer, 663, 300);
    delay(dist);
    noTone(buzzer);
  }  
  else {
    noTone(buzzer);
  }
}

void filtrar_sinal()
{
  // Se a distância medida for maior que 8000 e ainda não tiver passado 1 segundo de timeout
  if (dist > 2200)
  {
    // Descarta a medição feita e iguala ela à anterior
    dist = dist_old;
  }
  else // Caso contrário (medição < 8000 ou passou do timeout)
  {
    // Não descarta a medição atual e atualiza a medição antiga para a atual
    dist_old = dist;
    timeout = millis(); // Reseta o valor da variável do timeout
  }
}
