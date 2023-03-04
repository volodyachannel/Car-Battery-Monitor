### Car-Battery-Monitor
## Устройство для удалённого мониторинга напряжения на АКБ автомобиля.
#### v. 0.0.1 (28/06/2022) Ссылка на видео: https://youtu.be/nR71C6GlNUE 

Функционал: ESP8266 через аналого-цифровой преобразователь и резисторный делитель измеряет напряжение на клеммах аккумулятора (или, в моём случае, в цепи прикуривателя !без нагрузки!) и выводит это значение на свой сервер. Посредством WiFi эти данные просматриваются с телефона и т.д.

В папке два скетча: 
**AP** - файл для создания точки доступа (Чтобы подключаться к плате с телефона), и обычный файл, чтобы плата подключалась к уже созданной точке доступа.

Для работы использовалось ядро для Arduino IDE: github.com/esp8266/Arduino
https://arduino.esp8266.com/stable/package_esp8266com_index.json
