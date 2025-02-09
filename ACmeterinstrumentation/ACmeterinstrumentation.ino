#include "EmonLib.h"  // Incluir la librería EmonLib

EnergyMonitor emon1;  // Crear una instancia del medidor de energía

void setup() {  
  Serial.begin(9600);  // Iniciar la comunicación serial
  Serial.println("AC Power Meter");

  emon1.voltage(A3, 366, 3.6);  // Configurar sensor de voltaje: pin, calibración de voltaje, fase
  emon1.current(A6, 1.15999);   // Configurar sensor de corriente: pin, calibración de corriente
}

void loop() {
  Serial.println("Medición en curso...");
  
  emon1.calcVI(20, 4000);  // Calcular valores de voltaje y corriente
  double Vrms = emon1.Vrms;
  if (Vrms < 10) Vrms = 0;  // Filtrar valores bajos de voltaje

  double Irms = emon1.calcIrms(4000);  // Calcular Irms solamente
  double Phase = emon1.powerFactor;
  if (Vrms < 10 || Irms < 0.009) Phase = 0;  // Filtrar valores bajos de corriente
  
  double apparentPower = (Irms * Vrms);  // Calcular potencia aparente

  // Mostrar los resultados en el Monitor Serial
  Serial.print("Vrms: ");
  Serial.print(Vrms, 2);
  Serial.println(" V");
  
  Serial.print("Irms: ");
  Serial.print(Irms, 4);
  Serial.println(" A");

  Serial.print("Potencia aparente: ");
  Serial.print(apparentPower, 2);
  Serial.println(" W");

  Serial.print("Factor de potencia: ");
  Serial.println(Phase, 2);

  Serial.println("--------------------------");

  delay(2000);  // Esperar 2 segundos antes de la siguiente lectura
}
