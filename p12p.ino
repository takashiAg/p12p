class Moter_p12p {
  public:
    int  pin_A,
         pin_B,
         pin_Speed,
         pin_ref,
         moter_pos;
    Moter_p12p(int driver_pin_A, int driver_pin_B, int driver_pin_C, int analog_input_pin) {
      pin_A = driver_pin_A;
      pin_B = driver_pin_B;
      pin_Speed = driver_pin_C;
      pin_ref = analog_input_pin;
      moter_pos=0;
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
  private:
    void extend_moter() {
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_A, HIGH);
      digitalWrite(pin_Speed, HIGH);

    }
    void shrink_moter() {
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, HIGH);
      digitalWrite(pin_Speed, HIGH);
    }
    void stop_moter() {
      digitalWrite(pin_Speed, LOW);
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
    }

    int get_moter_pos() {
      return map(analogRead(pin_ref), 0, 1023, 0, 100);
    }
};

Moter_p12p moter_1 = Moter_p12p(2, 3, 4, A0),
           moter_2 = Moter_p12p(5, 6, 7, A1);

int point = 0;

void setup() {
  Serial.begin(9600);
}


void loop() {

  if (Serial.available() > 0) {
    int charactor = Serial.read();
    
    if (charactor > 100) {
      point = 0;
      return;
    }
    if (point == 0) {
      moter_1.set_moter(charactor);
    } else if (point == 1) {
      moter_2.set_moter(charactor);
    }
    point++;
  }

  Serial.print(moter_1.moter_pos);
  Serial.print('\t');
  Serial.print(moter_2.moter_pos);
  Serial.println('\n');

  //必ず挿れて
  moter_1.update_position();
  moter_2.update_position();
  delay(100);
}



