#define VT_PIN A5
#define AT_PIN A4

void setup()
{
  Serial.begin(9600);
}

void loop() 
{
  int rawVoltageReading = 0;
  int rawCurrentReading = 0;

  int numReadings = 10;
  int totalVoltageReading = 0;
  int totalCurrentReading = 0;

  for (int i = 0; i < numReadings; i++)
  {
    totalVoltageReading += analogRead(VT_PIN);
    totalCurrentReading += analogRead(AT_PIN);

    delay(20);
  }

  rawVoltageReading = totalVoltageReading / numReadings;
  rawCurrentReading = totalCurrentReading / numReadings;

  float vcc = readVcc() / 1000.0;  // convert mV to V
  float voltage = ((rawVoltageReading * vcc) / 1023) * vcc ;
  float current = (rawCurrentReading * vcc) / 1023;
  
  Serial.print(voltage);
  Serial.print(" / ");
  Serial.println(current);
  
  delay(500);
}

long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1125300L / result; // Back-calculate AVcc in mV
  return result;
}

