int ODien1 = 12;
int ODien2 = 13;
int preA2 = 0;
int preA3 = 0;
boolean a12 = 0, a13 = 0;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  pinMode(ODien1, OUTPUT);
  pinMode(ODien2, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  int tempa12 = digitalRead(12);
  int tempa13 = digitalRead(13);
  if(tempa12 == 1 && a12 == 0)
  {
    change(10);
  }
  if(tempa13 == 1 && a13 == 0)
  {
    change(11);
  }

  a12 = tempa12;
  a13 = tempa13;
}

void change(int c)
{
  if(digitalRead(c) == LOW)
  {
    digitalWrite(c, HIGH);
  }
  else
  {
    digitalWrite(c, LOW);
  }
}
