Sprawozdanie z ćwiczeń numer 2
==============================

**Temat: „Dodawanie dodatnich liczb wielobajtowych w Asemblerze”**

## Opis realizacji

Dodawanie liczb wielobajtowych zrealizowano jako kolejne dodawania bajtów, począwszy od najmłodszego, z uwzględnieniem przeniesienia.
Aby zapobiec przypadkowej modyfikacji flagi przeniesienia (a taka następuje przy testowaniu opisanego później Z) zastosowano zapis i odtwarzanie stanu przeniesienia z użyciem osobnego rejestu (R19).

Ponieważ tak długie wartości muszą być przechowywane w tablicach (a te są w tym wypadku w pamięci RAM mikrokontrolera) użyto specjalnych rejestrów X i Y do przechowywania w nich adresów aktualnie przetwarzanych bajtów.

Argumenty mogą mieć długość przekraczającą 255 bajtów, użyto więc specjalnego rejestru Z do przechowywania licznika bajtów pozostałych do przetworzenia.
Mikrokontrolery AVR nie posiadają instrukcji do porównywania rejestrów X, Y i Z m.in. z bezpośrednim operandem, co wymusiło porównywanie poszczególnych połówek słowa oddzielnie, z uwzględnieniem przeniesienia.

Po zakończeniu wykonywania głównej pętli ustawiany jest poprawny stan flagi przeniesienia.
