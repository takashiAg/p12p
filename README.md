# 使い方

シリアルモニタを開いて
a b c dのいずれかを送信
a - 0%(縮む)
b - 33%
c - 66%
d - 100%(伸びる)

# pin connection
- moter1
  - P+ → 5V
  - P- → GND
  - P  → A0
  - 2 → AIN1
  - 3 → AIN2
  - 4 → PWMA

- moter2
  - P+ → 5V
  - P- → GND
  - P  → A1
  - 5 → BIN1
  - 6 → BIN2
  - 7 → PWMB

# python使ってください
pip3 install pyaudio
python3 main.py