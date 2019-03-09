#include <avr/sleep.h>

const unsigned int LED_PIN = 0;
const unsigned int SW_PIN = 1;

const unsigned int LED_ON_DURATION_SEC = 60;

// Falling-edge handler: just wakeup
void on_falling(){}

void setup() {
  ACSR |= _BV(ACD);       // stop ADC
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(SW_PIN, INPUT);
}

void do_sleep(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(0,on_falling, LOW);
  sleep_cpu();

  // sleeping... -> Awake!

  sleep_disable();
  detachInterrupt(0);
}

void loop() {
  // if Switch is ON (door closed), just sleep now
  if (digitalRead(SW_PIN) == LOW){
    digitalWrite(LED_PIN, LOW);
    do_sleep();
    return;
  }

  // else, door is open now. light the led.
  digitalWrite(LED_PIN, HIGH);
  // off-timer. check every 0.5 sec for door-close detection
  for(unsigned int i=0; i<LED_ON_DURATION_SEC*2; i++){
    if (digitalRead(SW_PIN) == LOW){
      digitalWrite(LED_PIN, LOW);
      do_sleep();
      return;
    }
    delay(500);
  }
  
  // timer expired. sleep now.
  digitalWrite(LED_PIN, LOW);
  do_sleep();
}
