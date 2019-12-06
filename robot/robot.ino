#include <VirtualWire.h>

char message[VW_MAX_MESSAGE_LEN];        // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
byte velocidad, giro;

// Pines para motores
#define MOTOR_IZQUIERDA_A 6
#define MOTOR_IZQUIERDA_B 3
#define MOTOR_DERECHA_A 10
#define MOTOR_DERECHA_B 11

void setup()
{
  Serial.begin(9600);
  pinMode(MOTOR_IZQUIERDA_A, OUTPUT);
  pinMode(MOTOR_IZQUIERDA_B, OUTPUT);
  pinMode(MOTOR_DERECHA_A, OUTPUT);
  pinMode(MOTOR_DERECHA_B, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);

  vw_setup(2000); // Bits per sec
  vw_set_rx_pin(7);
  vw_rx_start(); // Start the receiver

  velocidad = 0;
  giro = 0;
  digitalWrite(MOTOR_DERECHA_A, LOW);
  digitalWrite(MOTOR_DERECHA_B, LOW);
  digitalWrite(MOTOR_IZQUIERDA_A, LOW);
  digitalWrite(MOTOR_IZQUIERDA_B, LOW);
}

void loop()
{
  if (vw_get_message(message, &messageLength)) // Non-blocking
  {
    velocidad = (uint8_t)message[0];
    giro = (uint8_t)message[1];
    if (velocidad > 220){
      // REVERSA
      digitalWrite(MOTOR_DERECHA_A, LOW);
      digitalWrite(MOTOR_DERECHA_B, HIGH);
      digitalWrite(MOTOR_IZQUIERDA_A, LOW);
      digitalWrite(MOTOR_IZQUIERDA_B, HIGH);  
    }
    // DERECHA
    else if (giro < 160) {
      analogWrite(MOTOR_DERECHA_B, LOW);
      analogWrite(MOTOR_DERECHA_A, 255);
      analogWrite(MOTOR_IZQUIERDA_B, 255);
      analogWrite(MOTOR_IZQUIERDA_A, LOW);
    }
    // IZQUIERDA
    else if(giro > 200){
      analogWrite(MOTOR_DERECHA_B, 255);
      analogWrite(MOTOR_DERECHA_A, LOW);
      analogWrite(MOTOR_IZQUIERDA_B, LOW);
      analogWrite(MOTOR_IZQUIERDA_A, 255);
    } 
    // FRENTE
    else if(velocidad < 160) {
      analogWrite(MOTOR_DERECHA_A, 255);
      analogWrite(MOTOR_DERECHA_B, LOW);
      analogWrite(MOTOR_IZQUIERDA_A, 220);
      analogWrite(MOTOR_IZQUIERDA_B, LOW);
    }
    else{
      // FRENAR
      digitalWrite(MOTOR_DERECHA_A, LOW);
      digitalWrite(MOTOR_DERECHA_B, LOW);
      digitalWrite(MOTOR_IZQUIERDA_A, LOW);
      digitalWrite(MOTOR_IZQUIERDA_B, LOW);
    }
  }
}
