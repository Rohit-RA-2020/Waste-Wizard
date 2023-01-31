

// include the library code:
#include <LiquidCrystal.h>
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define Relay_Up 8
#define Relay_Down 9
#define Relay_Pnumatic 10

#define MQ135 A0
#define MQ4 A1

char data;
//--------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("CRANE           ");
  pinMode(Relay_Up, OUTPUT);
  pinMode(Relay_Down, OUTPUT);
  pinMode(Relay_Pnumatic, OUTPUT);

  digitalWrite(Relay_Up, HIGH);
  digitalWrite(Relay_Down, HIGH);
  digitalWrite(Relay_Pnumatic, LOW);
  delay(2000);
  lcd.clear();
}
//---------------------------------------------------------------------
void loop() {
  if (Serial.available() > 0) {
    data = Serial.read();
    Serial.print(data);
    Serial.print("\n");
    //===============================
    if (data == 'F') {
      digitalWrite(Relay_Up, LOW);
      lcd.setCursor(0, 1);
      lcd.print("DIRE:UP   ");
      delay(50);
    } else if (data == 'B') {
      digitalWrite(Relay_Down, LOW);
      lcd.setCursor(0, 1);
      lcd.print("DIRE:DOWN ");
      delay(5);
    }
    //==================================================
    else if (data == 'R') {
      digitalWrite(Relay_Pnumatic, LOW);
      lcd.setCursor(0, 0);
      lcd.print("M:OPEN  ");
      delay(5);
    } else if (data == 'L') {
      digitalWrite(Relay_Pnumatic, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("M:CLOSE ");
      delay(5);
    }
    //===============================================
    else {
      digitalWrite(Relay_Up, HIGH);
      digitalWrite(Relay_Down, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("STOP     ");
      delay(5);
    }
    //===============================================
  }
  int MQ4_Data = analogRead(MQ4);
  lcd.setCursor(9, 1);
  lcd.print("Q4:" + String(MQ4_Data) + String(" "));

  int MQ135_Data = analogRead(MQ135);
  lcd.setCursor(9, 0);
  lcd.print("G:" + String(MQ135_Data) + String(" "));
}
