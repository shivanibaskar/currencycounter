#include <LiquidCrystal.h> //the output pin is set to be 13 pin
LiquidCrystal lcd(4, 6, 7, 8, 9, 10);//creating an lcd object
int b, r, g, temp1 = 0, temp2 = 0;   //blue
int output = 13;//setting the output pin
unsigned int frequency = 0;
int totalbalance = 1000;//setting the total balance
//intialise all variables
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Currenycnter");
  lcd.setCursor(0, 1);
  delay(2000);
  lcd.clear();
  pinMode(2, OUTPUT);//S0
  pinMode(3, OUTPUT);//S1
  pinMode(11, OUTPUT);//S2
  pinMode(12, OUTPUT);//S3
  pinMode(13, INPUT);//OUT
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
}
//runs forever
void loop()
{
  int valueofproximity = digitalRead(A0);//reads input from proximity sensor
  int r = red();//calls the function that returns the frequency red value of the output by the colour sensor
  int b = blue(); //calls the function that returns the frequency blue value of the output by the colour sensor
  int g = green(); //calls the function that returns the frequency green value of the output by the colour sensor
  //print values to serial monitor
  Serial.println(r);
  Serial.println(b);
  Serial.println(g);
  Serial.println(valueofproximity);
  //the frequency values were determined by monitoring it for different currency notes and by taking the mean
  //code to detect a 10 rupee note
  if (r>=60 && r<=85 && b >=75 && b <= 100 && g >=70 && g <=95 && temp1 == 0 && valueofproximity == LOW)
  {
    temp1 = 1;
  }
  else if (valueofproximity == HIGH && temp1 == 1)
  {
    temp1 = 0;
    if(totalbalance>=10)
    {
    lcd.setCursor(0, 1);
    lcd.print("10 Rupees");
    Serial.println("10 Rupees");
    totalbalance=totalbalance-10;
    delay(1500);
    lcd.clear();
    }
  }
  //the frequency values were determined by monitoring it for different currency notes and by taking the mean
  //code to detect a 50 rupee note
  if (r >= 70 && r <= 80 && b >= 70 && b <= 85 && g >= 60 && g <=70 && temp2 == 0 && valueofproximity == LOW)
  {
    temp2 = 1;
  }
  else if (valueofproximity == HIGH && temp2 == 1)
  {
    temp2 = 0;
    if(totalbalance>=50)
    {
    lcd.setCursor(0, 1);
    lcd.print("50 Rupees");
    Serial.println("50 Rupees");
    totalbalance=totalbalance-50;
    delay(1500);
    lcd.clear();
    }
  }
  //the frequency values were determined by monitoring it for different currency notes and by taking the mean
  //code to detect a 100 rupee note
  if (r >= 150 && r <= 160 && b >= 170 && b <= 180 && g >= 190 && g <= 200 && temp1 == 0 && valueofproximity == LOW)
  {
    temp1 = 1;
  }
  else if (valueofproximity == HIGH && temp1 == 1)
  {
    temp1 = 0;
    if (totalbalance >= 100)
    {
      lcd.setCursor(0, 1);
      lcd.print("100 Rupees!!!");
      Serial.println("100 Rupees!!!");
      totalbalance = totalbalance - 10;
      delay(1500);
      lcd.clear();
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("Total Bal:");
  lcd.setCursor(11, 0);
  lcd.print(totalbalance); //to print the total after removal of every currency
  if(totalbalance<200)
  {
    lcd.setCursor(0, 1);
    lcd.print("spend wisely");
  }
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
