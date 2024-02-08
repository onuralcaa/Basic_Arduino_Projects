
// LED bağlatı pinleri
int rpin = 11;  // kırmızı
int gpin = 10; // yeşil
int bpin = 9; // mavi
float h = 0; //hue (ton) değeri
int r=0, g=0, b=0; // renk değerleri

//ses sensor pinleri
int r_led = 10;
int b_led = 9;
int g_led = 11;

int Sensor = A0;

int clap = 0;
long detection_range_start = 0;
long detection_range = 0;

int color = 1;

//Mode pinleri
#define sw1 2
#define sw2 3

int status1, status2; //switch durum değişkenleri

byte mode;

void setup() 
{
  Serial.begin(9600);

  pinMode(r_led, OUTPUT);
  pinMode(b_led, OUTPUT);
  pinMode(g_led, OUTPUT);

  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  
  pinMode(Sensor, INPUT);
}
void loop()
{ 
  status1 = digitalRead(sw1);
  status2 = digitalRead(sw2);

 if(status1 == 1 && status2 == 0) mode = 0;
 else if(status1 == 0 && status2 == 0) mode = 1;
 else if(status1 == 0 && status2 == 1) mode = 2;


   Serial.println(mode);
  
  /*
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

  */

}
  
