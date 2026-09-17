# Parmak İzli Kapı

Okul ortamında oda girişini otomatikleştirmek için geliştirilen, **parmak izi ve RFID kart doğrulamasını** aynı sistemde birleştiren Arduino tabanlı erişim kontrol projesidir.

Sistem; yetkili kullanıcıları parmak izi veya kart üzerinden tanır, LCD ekran üzerinden durum bilgisi verir, NeoPixel ve buzzer ile geri bildirim sağlar ve başarılı doğrulamada kapı mekanizmasını tetikler. Kod yapısında ayrıca MZ-80 sensörü ile kapı açma senaryosu bulunur.

## ✨ Özellikler

- 🔐 Parmak izi ile kimlik doğrulama
- 💳 RFID kart ile giriş
- 🚪 Otomatik kapı kontrolü
- 📟 20x4 I2C LCD durum ekranı
- 💡 NeoPixel LED durum animasyonları
- 🔊 Başarılı ve hatalı giriş için sesli geri bildirim
- 📡 MZ-80 sensörü ile ek giriş senaryosu
- 👤 Kullanıcı bazlı parmak izi ve kart eşleştirme

## 🛠️ Donanım ve Teknolojiler

- Arduino
- Adafruit Fingerprint Sensor
- RFID RC522 / uyumlu RFID modülü
- 20x4 I2C LCD
- Adafruit NeoPixel
- MZ-80 sensörü
- Buzzer
- Kapı motoru / röle mekanizması

### Kullanılan Arduino kütüphaneleri

- `Adafruit_Fingerprint`
- `Wire`
- `LiquidCrystal_I2C`
- `RFID`
- `SPI`
- `Adafruit_NeoPixel`

## 🔄 Çalışma Mantığı

1. Sistem açıldığında parmak izi sensörü, RFID ve LCD başlatılır.
2. Kullanıcı parmak izini veya RFID kartını okutur.
3. Kimlik kayıtlıysa kullanıcı bilgisi LCD ekrana yazdırılır.
4. Başarılı doğrulamada kapı çıkışı aktif edilir ve görsel/sesli geri bildirim verilir.
5. Tanınmayan girişlerde hata geri bildirimi gösterilir.
6. Sistem tekrar bekleme ekranına döner.

## 📁 Proje Yapısı

```text
PARMAK_IZLI_KAPI/
├── parmak_izli_kapi/
│   └── parmak_izli_kapi.ino
└── README.md
```

## ⚙️ Yapılandırma

Kullanıcı kartları ve parmak izi ID'leri kaynak kod içerisinde tanımlanmaktadır. Yeni bir kullanıcı eklerken sensör ID'sinin ve RFID UID değerlerinin doğru şekilde eşleştirilmesi gerekir.

Donanım pinleri ve çevre birimleri de `.ino` dosyasındaki tanımlardan değiştirilebilir.

## ⚠️ Güvenlik Notu

Gerçek bir erişim kontrol sisteminde kart UID'leri, parmak izi ID'leri ve kullanıcı bilgileri kaynak kodunda düz metin olarak tutulmamalıdır. Bu proje eğitim ve prototipleme amacıyla hazırlanmıştır.

## 🚧 Geliştirme Durumu

**Prototip / aktif geliştirme**

Gelecekte kullanıcı yönetiminin daha modüler hale getirilmesi, yetkilendirme kayıtlarının kalıcı depolanması ve erişim loglarının tutulması planlanabilir.

## 📄 Lisans

Bu depoda ayrıca bir lisans belirtilmediği için kullanım koşulları proje sahibinin kararına bağlıdır.
