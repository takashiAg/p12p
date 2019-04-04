const int analogInPin = A0;


const int driver_pinA = 2,
          driver_pinB = 3,
          driver_pinC = 4;


int moter_pos = 0;
//int   moter_pos_real = 0;

void setup() {
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    int  charactor = Serial.read();
    switch (charactor) {
      case 'a':
        set_moter(100);
        break;
      case 'b':
        set_moter(66);
        break;
      case 'c':
        set_moter(33);
        break;
      case 'd':
        set_moter(0);
        break;
    }
  }

  //必ず挿れて
  update_position();

  Serial.print(get_moter_pos()); Serial.print('\t');
  //  Serial.print(pos);
  Serial.print('\n');
}

int get_moter_pos() {
  return map(analogRead(analogInPin), 0, 1023, 0, 100);
}

void extend_moter() {
  digitalWrite(driver_pinB, LOW);
  digitalWrite(driver_pinA, HIGH);
  digitalWrite(driver_pinC, HIGH);

}
void shrink_moter() {
  digitalWrite(driver_pinA, LOW);
  digitalWrite(driver_pinB, HIGH);
  digitalWrite(driver_pinC, HIGH);
}
void stop_moter() {
  digitalWrite(driver_pinC, LOW);
  digitalWrite(driver_pinA, LOW);
  digitalWrite(driver_pinB, LOW);
}

void update_position() {
  int moter_pos_real = get_moter_pos();
  if (moter_pos_real - moter_pos < -10)
    extend_moter();
  else if (moter_pos_real - moter_pos > 10)
    shrink_moter();
  else
    stop_moter();
}

void set_moter(int pos) {
  moter_pos = pos;
}
