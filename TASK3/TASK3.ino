/* 
TASK NO.3 - 
Write a code to blink 2 LED's at 2 seconds and 1.7 seconds respectively. 
(do not use delay()  function in code).

Written by : Dhiraj Zen B K

In this task I have used Alarm Generation of timer0 and timer1 of ESP32 
to make led1 and led 2 blink at a rate of 2s and 1.7s respectively.

*/

hw_timer_t *timer0 = NULL;
hw_timer_t *timer1 = NULL;

const uint8_t led1 = 16;
const uint8_t led2 = 17;

volatile uint8_t led1State = 0;
volatile uint8_t led2State = 0;

//ISR for timer 0 
void IRAM_ATTR onTimer0(){
  
  led1State = 1 - led1State;
  digitalWrite(led1, led1State);
  // Serial.print("ISR for led1, time: ");
  // Serial.println(millis());
  
}

//ISR for timer 1
void IRAM_ATTR onTimer1(){
  
  led2State = 1 - led2State;
  digitalWrite(led2, led2State);
  // Serial.print("ISR for led2, time: ");
  // Serial.println(millis());
  
}

void setup() {

  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, 0);
  digitalWrite(led2, 0);

  timer0 = timerBegin(0, 80, true); // T0 CLK time period changed from 12.5ns -> 12.5ns * 80 = 1000us
  timerAttachInterrupt(timer0, &onTimer0, true);// Assigning ISR for T0 interrupt
  timerAlarmWrite(timer0, 2000000, true);// Generate interrupt every 2000000*1000us = 2s and autoreload timer
  Serial.println("Timer 0 configured.");

  timer1 = timerBegin(1, 80, true);// T1 CLK time period changed from 12.5ns -> 12.5ns * 80 = 1000us
  timerAttachInterrupt(timer1, &onTimer1, true);// Assigning ISR for T1 interrupt
  timerAlarmWrite(timer1, 1700000, true);// Generate interrupt every 1700000*1000us = 1.7s and autoreload timer
  Serial.println("Timer 1 configured.");

  timerAlarmEnable(timer0);
  timerAlarmEnable(timer1);

}

void loop(){}
