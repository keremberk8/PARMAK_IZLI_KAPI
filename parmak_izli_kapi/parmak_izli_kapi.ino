#include <Adafruit_Fingerprint.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RFID.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

#define PIN            4   // LED'in bağlı olduğu pin
#define NUMPIXELS      7    // Toplam 7 LED
#define MZ80_PIN 9

// PIN TANIMLAMALARI
SoftwareSerial mySerial(2, 3); 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
RFID kart(7, 5); 
LiquidCrystal_I2C lcd(0x27, 20, 4);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte yusuf_emre[4] = {20 , 205 , 157 , 207};
byte jjyusuf_telefon[4] = {136,29,129,66};
byte jyusuf[4] = {147, 66, 3, 23};
byte ensar[4] = {163, 216, 103, 23};
byte erdem[4] = {227, 121, 69, 23};
byte salih[4] = {74, 32, 68, 22};
byte zehra[4] = {107 , 130 , 228, 17};
byte can[4] = {35, 215, 184, 27};
byte cagdas[4] = {9, 162, 62, 152};
byte yusufhoca[4] = {36 , 47 , 157 , 207};
byte yusufhoca_air[4] = {20 , 228 , 182 , 207};
byte yusufhoca_telefon[4] = {136, 29, 98, 245};
byte omer[4] = {57, 55, 241, 151};
byte baris[4] = {169, 145, 238, 151};
byte ozkan[4] = {89, 86, 233, 151};
byte kerem[4] = {36 , 129 , 126 , 207};
byte kerem_telefon[4] = {136, 29, 251, 228};
byte yusuf[4] = {201, 18, 234, 151};
byte tikenoglu[4] = {41, 212, 233, 151};
byte onay[4] = {105, 121, 250, 151};
byte cigidem[4] = {169, 145, 237, 151};
byte ufuk[4] = {121, 188, 235, 151};
byte ahmet[4] = {2000027, 220003, 48000, 27000};
byte erkut[4] = {137, 235, 235, 151};
byte nejat[4] = {243 , 203 , 246 , 36};
byte tuana[4] = {83, 94, 187, 21};
byte ecrin[4] = {115 , 28 , 168 , 245};
byte sevval[4] = {179,192,31,246};
byte doga[4] = {3,131,185,252};
byte kutay[4] = {147,254,165,253};
byte baturalp[4] = {68 , 138 , 134 , 207};
byte eser[4] = {193,30,20,13};
byte ramazan[4] = {114,0,95,81};
byte yedekbos7[4] = {179,192,31,246};
byte yedekbos6[4] = {3,49,32,253};
byte yedekbos5[4] = {147,203,198,245};
byte yedekbos4[4] = {99,228,38,21};
byte yedekbos3[4] = {195,29,143,253};
byte yedekbos2[4] = {115,28,168,245};
byte yedekbos1[4] = {107,130,228,17};
byte efe[4] = {68 , 120 , 168 , 207};
byte akif[4] = {84 , 82 , 152 , 207};
byte tagefe[4] = {243 , 248 , 178 , 253};
byte erman[4] = {164 , 237 , 144 , 207};
byte umut[4] = {132 , 102 , 167 , 207};
byte admin[4] = {131 , 97 , 243 , 36 };
byte mudur[4] = {147 , 124 , 9 , 37};



int kapi = 6;

void setup() {
  Serial.begin(9600);

  SPI.begin();
  kart.init();
  lcd.init();           
  lcd.backlight();
  pixels.begin();
  pixels.setBrightness(255); // Maksimum parlaklık

  pinMode(8,OUTPUT); //Buzzer pini
  pinMode(kapi,OUTPUT); //kapi pini
  pinMode(MZ80_PIN, INPUT);
  
  // Parmak İzi Setup
  finger.begin(57600); 
  if (finger.verifyPassword()) {
    Serial.println("Sensör BULUNDU!");
    finger.LEDcontrol(FINGERPRINT_LED_BREATHING, 100, FINGERPRINT_LED_PURPLE);
  } else {
    Serial.println("Sensör Bulunamadı!");
    while (1);
  }
  digitalWrite(kapi, LOW);
  lcd.setCursor(0,0);
  lcd.print("Parmak izinizi veya"); 
  lcd.setCursor(0,1);
  lcd.print("kartinizi okutunuz");
}

void loop() {
  beyaz_yak(); // Hiçbir şey okunmadığında sürekli beyaz yanar
  // --- MZ-80 SENSÖR KONTROLÜ ---
  if (digitalRead(MZ80_PIN) == LOW) {
    lcd.clear();
    ekranaYaz("SENSOR ALGILADI", "KAPI ACILIYOR...");
    giris_buzzer(); 
    anaEkran();     
  }
  if (kart.isCard()) {
    if (kart.readCardSerial()) {
      kart_kisiler(); 
    }
    kart.halt();
  } 
  
  parmak_izini_bul();
}

void parmak_izini_bul() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return; // Parmak yoksa anında döner, RFID'yi engellemez

p = finger.image2Tz();
  if (p != FINGERPRINT_OK) {
    finger.LEDcontrol(FINGERPRINT_LED_FLASHING, 25, FINGERPRINT_LED_RED, 10);
 yanlis_buzzer();
    delay(500); // Kırmızının görünmesi için kısa bir süre
    anaEkran(); // LED'i tekrar MOR yapması için ana ekranı çağırıyoruz
    return; 
  }

  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {

    finger.LEDcontrol(FINGERPRINT_LED_FLASHING, 25, FINGERPRINT_LED_BLUE, 5);
        lcd.clear();
    if (finger.fingerID == 1 || finger.fingerID == 2) {
      ekranaYaz("Yusuf DINC", "BABAPARATOR");
       giris_buzzer();
    } 
    else if (finger.fingerID == 8 || finger.fingerID == 9 || finger.fingerID == 10) {
      ekranaYaz("Kerem Berk BOY", "<3");
       giris_buzzer_ozel();
    }
       else if (finger.fingerID == 34 || finger.fingerID == 22|| finger.fingerID == 27) {
      ekranaYaz("Efe Selim SAFAK", "DOSEMECI");
       giris_buzzer_ozel();
    }
        else if (finger.fingerID == 40 || finger.fingerID == 41 || finger.fingerID == 42  || finger.fingerID == 43) {
      ekranaYaz("Yusuf Emre TASCI", "MECHATRONIC ENGINEER");
       giris_buzzer_ozel();
    }
      else if (finger.fingerID == 6 || finger.fingerID == 33 || finger.fingerID == 21 || finger.fingerID == 11 || finger.fingerID == 16) {
      ekranaYaz("Akif Arda AKSOY", "KINGO KONGOO");
       giris_buzzer();
    }
         else if (finger.fingerID == 33 || finger.fingerID == 24) {
      ekranaYaz(" AKIN", "MAKİNE");
       giris_buzzer();
    }
           else if (finger.fingerID == 50 || finger.fingerID == 51 ) {
       ekranaYaz("Yilmaz OZCAN", "CZAL MUDUR");
       giris_buzzer();
    }
    else {
      ekranaYaz("ID: " + String(finger.fingerID), "Tanimli Parmak");
    }
    anaEkran();
  }
  else {
    finger.LEDcontrol(FINGERPRINT_LED_FLASHING, 25, FINGERPRINT_LED_RED, 10);
    yanlis_buzzer();
    delay(1000); // Kırmızıyı gör
    anaEkran();  // Tekrar mor yap
  }
}

void kart_kisiler() {
  lcd.clear();
if (esit_mi(yusufhoca) ||esit_mi(yusufhoca_air)) {
      ekranaYaz("Yusuf DINC", "BABAPARATOR");
      giris_buzzer();
    } 
    else if (esit_mi(kerem)) {
      ekranaYaz("Kerem Berk BOY", "<3");
          giris_buzzer_ozel();
    }
       else if (esit_mi(efe) ||esit_mi(tagefe)) {
      ekranaYaz("Efe Selim SAFAK", "DOSEMECI");
          giris_buzzer_ozel();
    }
        else if (esit_mi(yusuf_emre)) {
      ekranaYaz("Yusuf Emre TASCI", "MECHATRONIC ENGINEER");
          giris_buzzer_ozel();
    }
      else if (esit_mi(akif)) {
      ekranaYaz("Akif Arda AKSOY", "KINGO KONGOO");
          giris_buzzer();
    }
         else if (esit_mi(baturalp)) {
      ekranaYaz(" AKIN", "MAKINE");
          giris_buzzer();
    }
       else if (esit_mi(erman)) {
      ekranaYaz("Erman ", "CHAVO");
          giris_buzzer();
    }
       else if (esit_mi(umut)) {
      ekranaYaz("Umut", "EL ISITICI");
          giris_buzzer();
    }
        else if (esit_mi(nejat)) {
      ekranaYaz("Nejat ABI", "TEKNIK SERVIS");
          giris_buzzer();
    }
            else if (esit_mi(admin)) {
      ekranaYaz("ADMIN", "ADMIN");
          giris_buzzer();
    }
            else if (esit_mi(mudur)) {
      ekranaYaz("Yilmaz OZCAN", "CZAL MUDUR");
          giris_buzzer();
    }
  else {
    yanlis_buzzer();
  }
  delay(2000);
  anaEkran();
}

boolean esit_mi(byte b[]) {
  return (kart.serNum[0] == b[0] && kart.serNum[1] == b[1] && kart.serNum[2] == b[2] && kart.serNum[3] == b[3]);
}

void ekranaYaz(String satir1, String satir2) {
  lcd.setCursor(0, 0);
  lcd.print(satir1);
  lcd.setCursor(0, 1);
  lcd.print(satir2);
}

void anaEkran() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Parmak izinizi veya"); 
  lcd.setCursor(0,1);
  lcd.print("kartinizi okutunuz");
  digitalWrite(0, LOW);
finger.LEDcontrol(FINGERPRINT_LED_BREATHING, 120, FINGERPRINT_LED_PURPLE);
}
void giris_buzzer_ozel(){
digitalWrite(kapi, HIGH); // Kapıyı hemen aç

  // 100 tur sürecek bir döngü (Her tur 20ms = Toplam 2 saniye)
  for (int j = 0; j < 100; j++) {
    
    // --- BUZZER YÖNETİMİ (Delay kullanmadan) ---
    // Her 'j' adımı 20ms'ye denk gelir.
    if (j == 0)  tone(8, 660); // 0. ms: İlk Mi başla
    if (j == 5)  noTone(8);    // 100. ms: Sus
    if (j == 7)  tone(8, 660); // 140. ms: İkinci Mi başla
    if (j == 12) noTone(8);    // 240. ms: Sus
    if (j == 15) tone(8, 880); // 300. ms: La başla
    if (j == 30) noTone(8);    // 600. ms: Melodiyi bitir

    // --- LED HAREKETİ ---
    // Her döngüde renk tonunu j'ye bağlı olarak kaydırıyoruz
    for (int i = 0; i < NUMPIXELS; i++) {
      int pikselTonu = (j * 800) + (i * 65536L / NUMPIXELS); 
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pikselTonu, 255, 255)));
    }
    pixels.show(); // LED'leri hemen güncelle
    
    delay(20); // Bu kısa bekleme hem animasyon hızı hem de zamanlama birimidir
  }

  digitalWrite(kapi, LOW); // Kapıyı kapat
}
void giris_buzzer(){
  yesil_yak();
  digitalWrite(kapi, HIGH);
tone(8, 660); delay(100); // Kısa Mi
noTone(8);    delay(50);  // Çok kısa es
tone(8, 660); delay(100); // Kısa Mi (Tekrar)
noTone(8);    delay(50);
tone(8, 880); delay(300); // Yüksek La (Bitiriş vurgusu)
noTone(8);
delay(2000);
digitalWrite(kapi, LOW);
}
void yanlis_buzzer_ozel() {
  kirmizi_yak();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   HATALI GIRIS!   "); // Üst satır sabit uyarı

  // --- 3 SANİYELİK GERİ SAYIM VE BOMBA EFEKTİ ---
  for (int i = 3; i > 0; i--) {
    // LCD Alt Satır Güncelleme
    lcd.setCursor(0, 1);
    lcd.print("Bekle: ");
    lcd.print(i);
    lcd.print(" saniye... ");

    // Her saniye içinde hızlanan 3 bip (Bomba tiktak efekti)
    for (int j = 0; j < 3; j++) {
      tone(8, 800);  
      delay(100);    
      noTone(8);
      delay(200 - (j * 50)); // Saniye içinde de hızlanma hissi
    }
  }

  // --- FİNAL: LCD MESAJI VE TİZ HATA SESİ ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  ERISIM REDDEDILDI ");
  lcd.setCursor(0, 1);
  lcd.print("   TEKRAR DENEYIN   ");

  tone(8, 2500);   // İstediğin o uzun ve tiz final sesi
  delay(1000);     // 1 saniye boyunca çal
  noTone(8);
}
void yanlis_buzzer(){
   kirmizi_yak();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   HATALI GIRIS!   "); 
  tone(8, 150); // Kalın ton
  delay(400);   // Biraz uzunca çal
  noTone(8);
  delay(100);   // Kısa bir sessizlik
  tone(8, 150); // Tekrar kalın ton
  delay(400);
  noTone(8);
}
void beyaz_yak(){
for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255)); // Tam güç Beyaz
  }
  pixels.show();
}
void yesil_yak(){
for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Tam güç yeşil
  }
  pixels.show();
}
void kirmizi_yak(){
for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Tam güç kırmızı
  }
  pixels.show();
}
void rgb_yak(long kaydirma){
for (int i = 0; i < NUMPIXELS; i++) {
    int pikselTonu = kaydirma + (i * 65536L / NUMPIXELS);
    pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pikselTonu, 255, 255)));
  }
  pixels.show();
}