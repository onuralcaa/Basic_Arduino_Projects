
// LED bağlatı pinleri
int r_led = 9;  // kırmızı
int g_led = 10; // yeşil
int b_led = 11; // mavi
float h = 0; //hue (ton) değeri
int r = 0, g = 0, b = 0; // renk değerleri


int Sensor = A0;

int clap = 0;
long detection_range_start = 0;
long detection_range = 0;
int color = 0;

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

  if (status1 == 1 && status2 == 0) mode = 0;
  else if (status1 == 0 && status2 == 0) mode = 1;
  else if (status1 == 0 && status2 == 1) mode = 2;



  switch (mode)
  {
    case 2:
      Mode2();
      break;

    case 1:
      Mode1();
      break;

    case 0:
      Mode0();
      break;
  }

}

void Mode0()
{

}

void Mode1()
{
  // Her seferinde hue değeri 0.001 artırılıyor ve 1 olduğunda başa dönülüyor
  h = h + 0.001;
  if (h >= 1.0) {
    h = 0;
  }
  // hue değeri r,g,b bileşenlerine çevriliyor
  h2rgb(h, r, g, b);

  // Ortak anot RGB LED
  analogWrite(r_led, 255 - r);
  analogWrite(g_led, 255 - g);
  analogWrite(b_led, 255 - b);

  delay(25);
}

void Mode2()
{
  int status_sensor = digitalRead(Sensor);
  if (status_sensor == 0)
  {
    if (clap == 0)
    {
      detection_range_start = detection_range = millis();
      clap++;
    }
    else if (clap > 0 && millis() - detection_range >= 60)
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
    if (color >= 7) color = 0;
    clap = 0;
  }

  //Serial.println(color);

  switch (color)
  {
    case 0://BEYAZ
      digitalWrite(r_led, HIGH);
      digitalWrite(g_led, HIGH);
      digitalWrite(b_led, HIGH);
      break;

    case 1://KIRMIZI
      digitalWrite(r_led, HIGH);
      digitalWrite(g_led, LOW);
      digitalWrite(b_led, LOW);
      break;

    case 2://YESİL
      digitalWrite(r_led, LOW);
      digitalWrite(g_led, HIGH);
      digitalWrite(b_led, LOW);
      break;

    case 3://MAVI
      digitalWrite(r_led, LOW);
      digitalWrite(g_led, LOW);
      digitalWrite(b_led, HIGH);
      break;

    case 4://SARI
      digitalWrite(r_led, HIGH);
      digitalWrite(g_led, HIGH);
      digitalWrite(b_led, LOW);
      break;

    case 5://TURKUAZ
      digitalWrite(r_led, LOW);
      digitalWrite(g_led, HIGH);
      digitalWrite(b_led, HIGH);
      break;

    case 6://MOR
      digitalWrite(r_led, HIGH);
      digitalWrite(g_led, LOW);
      digitalWrite(b_led, HIGH);
      break;
  }
}

void h2rgb(float H, int& R, int& G, int& B) {
  int var_i;
  float S=1, V=1, var_1, var_2, var_3, var_h, var_r, var_g, var_b;

  if ( S == 0 )              
  {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  }
  else
  {
    var_h = H * 6;
    if ( var_h == 6 ) var_h = 0;      
    var_i = int( var_h ) ;            
    var_1 = V * ( 1 - S );
    var_2 = V * ( 1 - S * ( var_h - var_i ) );
    var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );
    if ( var_i == 0 ) {
      var_r = V     ;
      var_g = var_3 ;
      var_b = var_1 ;
    }
    else if ( var_i == 1 ) {
      var_r = var_2 ;
      var_g = V;
      var_b = var_1 ;
    }
    else if ( var_i == 2 ) {
      var_r = var_1 ;
      var_g = V;
      var_b = var_3 ;
    }
    else if ( var_i == 3 ) {
      var_r = var_1 ;
      var_g = var_2 ;
      var_b = V;
    }
    else if ( var_i == 4 ) {
      var_r = var_3 ;
      var_g = var_1 ;
      var_b = V;
    }
    else {
    var_r = V;
    var_g = var_1 ;
    var_b = var_2 ;
    }
    R = (1-var_r) * 255;        
    G = (1-var_g) * 255;
    B = (1-var_b) * 255;
  }
}
