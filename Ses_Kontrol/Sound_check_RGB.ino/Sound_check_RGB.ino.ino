int r_led = 10;
int b_led = 9;
int g_led = 11;


int Sensor = A0;

int clap = 0;
long detection_range_start = 0;
long detection_range = 0;
int color = 1;

void setup() 
{
  pinMode(r_led, OUTPUT);
  pinMode(b_led, OUTPUT);
  pinMode(g_led, OUTPUT);
  
  pinMode(Sensor, INPUT);
  pinMode(12, OUTPUT);
}
void loop()
{ 
  /*
  //renk kontrol
  digitalWrite(r_led, HIGH);
  digitalWrite(b_led, LOW);
  digitalWrite(g_led, LOW);
  */
  
  int status_sensor = digitalRead(Sensor);
  if (status_sensor == 0)
  {
    if (clap == 0)
    {
      detection_range_start = detection_range = millis();
      clap++;
    }
    else if (clap > 0 && millis() - detection_range >= 50)
    {
      detection_range = millis();
      clap++;
    }
  }
  if (millis() - detection_range_start >= 400)
  {
    if (clap == 2)
    {
      color++;
    }
    
    }
    clap = 0;
  }

  


  
