// Датчик влажности почвы
// http://makerplus.ru

// контакт подключения аналогового выхода датчика
int aPin=A0;
// контакты подключения светодиодов индикации
int ledPins[8]={4,5,6,7,8,9,10,11};
// переменная для сохранения значения датчика
int avalue=0;
// переменная количества светящихся светодиодов
int countled=8;
// значение полного полива
int minvalue=220;
// значение критической сухости
int maxvalue=600;

void setup()
{
// инициализация последовательного порта
Serial.begin(9600);
// настройка выводов индикации светодиодов
// в режим OUTPUT
for(int i=0;i<8;i++)
{
pinMode(ledPins[i],OUTPUT);
}

}

void loop()
{
// получение значения с аналогового вывода датчика
avalue=analogRead(aPin);
// вывод значения в монитор последовательного порта Arduino
Serial.print("avalue=");Serial.println(avalue);
// масштабируем значение на 8 светодиодов
countled=map(avalue,maxvalue,minvalue,0,7);
// индикация уровня влажности
for(int i=0;i<8;i++)
{
if(i<=countled)
digitalWrite(ledPins[i],HIGH); //зажигаем светодиод
else
digitalWrite(ledPins[i],LOW); // гасим светодиод
}
// пауза перед следующим получением значения 1000 мс
delay(1000);
}
