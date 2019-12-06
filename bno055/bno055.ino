#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <VirtualWire.h>
 
Adafruit_BNO055 bno = Adafruit_BNO055(55);
char buffer[2];
 
void setup(void) 
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  Serial.println("Hey!");
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  Serial.println("TODO BIEN TODO CORRECTO");
  bno.setExtCrystalUse(true);
  
  // Initialize the IO and ISR
  vw_set_tx_pin(7);
  vw_setup(2000); // Bits per sec  
}
 
void loop(void) 
{
  sensors_event_t event; 
  bno.getEvent(&event);
  buffer[0] = (uint8_t)(event.orientation.y + 180);
  buffer[1] = (uint8_t)(event.orientation.z + 180);
  send(buffer);
  
  delay(50);
}

void send (char *message)
{
  digitalWrite(LED_BUILTIN,HIGH);
  vw_send((uint8_t *)message, 2);
  vw_wait_tx(); // Wait until the whole message is gone
  vw_send((uint8_t *)message, 2);
  vw_wait_tx();
  digitalWrite(LED_BUILTIN,LOW);
}
