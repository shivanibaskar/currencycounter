int output = 13;//the output pin is set to be 13 pin
unsigned int frequency = 0;
#include <LiquidCrystal.h> //header line to include display interface
LiquidCrystal lcd(4, 6, 7, 8, 9, 10);//object for lcd is created
//the colours are declared
int blue1;
int red1;
int green1;

int a = 0, b = 0;
int total = 1000; //the total amount of money in the wallet

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("  Smart Wallet  ");//printing the initial start up message on the lcd
  lcd.setCursor(0, 1);
  delay(2000);
  lcd.clear();
  //setting all the data directions of the digital pins
  pinMode(2, OUTPUT);//S0
  pinMode(3, OUTPUT);//S1
  pinMode(11, OUTPUT);//S2
  pinMode(12, OUTPUT);//S3
  pinMode(13, INPUT);//OUT
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
}

void loop()
{
  int sensor = digitalRead(A0);
  int red1 = red();//calls the function that returns the frequency red value of the output by the colour sensor
  int blue1 = blue();//calls the function that returns the frequency blue value of the output by the colour sensor
  int green1 = green();//calls the function that returns the frequency green value of the output by the colour sensor

  //to print the frequency of all rgb colours in the serial monitor
  Serial.println(red1);
  Serial.println(blue1);
  Serial.println(green1);
  Serial.println("-----------------------------");

  //the frequency values were determined by monitoring it for different currency notes and by taking the mean
  //code to detect a 50 rupee note
  if (red1 >= 25 && red1 <= 30 && blue1 >= 30 && blue1 <= 33 && green1 >= 25 && green1 <=30 && b == 0 && sensor == HIGH)
  {
    b = 1;
  }
  else if (sensor == LOW && b == 1)
  {
    b = 0;
    if(total>=50)
    {
    lcd.setCursor(0, 1);
    lcd.print("50 Rupees!!!");
    Serial.println("50 Rupees!!!");
    total=total-50;//deducting 50 rupee from the wallet
    delay(1500);
    lcd.clear();
    }
  }
  

  //the frequency values were determined by monitoring it for different currency notes and by taking the mean
  //code to detect a 10 rupee note
  if (red1>=60 && red1<=85 && blue1 >=75 && blue1 <= 100 && green1 >=70 && green1 <=95 && a == 0 && sensor == HIGH)//sensor will be high because of close proximity
  {
    a = 1;
  }
  else if (sensor == LOW && a == 1)//sensor low means currency note was removed
  {
    a = 0;
    if(total>=10)
    {
    lcd.setCursor(0, 1);
    lcd.print("10 Rupees!!!");
    Serial.println("10 Rupees!!!");
    total=total-10;//deducting 10 rupee from the wallet
    delay(1500);
    lcd.clear();
    }
  }


  lcd.setCursor(0, 0);
  lcd.print("Total Bal:");
  lcd.setCursor(11, 0);
  lcd.print(total);//to print the total after removal of every currency
  delay(1000);
}

// get the output colour frequency of red content in the currency
int red()
{
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  frequency = pulseIn(output, LOW);
  return frequency;
}

// get the output colour frequency of blue content in the currency
int blue()
{
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  frequency = pulseIn(output, LOW);
  return frequency;
}

// get the output colour frequency of green content in the currency
int green()
{
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  frequency = pulseIn(output, LOW);
  return frequency;
}
