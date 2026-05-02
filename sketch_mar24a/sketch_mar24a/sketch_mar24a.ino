const int led=9;
const int led1=10;
const int led2=11;

void setup () {
  pinMode (led, OUTPUT);
   pinMode (led1, OUTPUT);
    pinMode (led2, OUTPUT); }

void loop () {
digitalWrite (led, HIGH);
digitalWrite (led1, HIGH);
digitalWrite (led2, HIGH);
delay (1000);

digitalWrite (led, HIGH);
digitalWrite (led1, LOW);
digitalWrite (led2, LOW);
delay (1000);

digitalWrite (led1, HIGH);
digitalWrite (led, LOW);
digitalWrite (led2, LOW);
delay (1000);

digitalWrite (led2, HIGH);
digitalWrite (led1, LOW);
digitalWrite (led, LOW);
delay (1000);
}
