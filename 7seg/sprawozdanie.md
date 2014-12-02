Sprawozdanie z ćwiczeń 26.11.2014
=================================

## Obsługa wyświetlacza
Do realizacji ćwiczenia konieczne było tzw. przemiatanie wyświetlaczy.
Z racji tego że ludzkie oko ma bezwładność około 50Hz i w danym momencie mogę mieć włączony tylko jeden wyświetlacz, zadanie „przemiatania” uruchamiam co 5ms.

## „Stoper”
Żeby nie zaśmiecać kolejnej części ćwiczenia, całość obsługi „stopera” i wyświetlacza przeniosłem do osobnej biblioteki (`7seg.h`, `7seg.c`).

Stoper liczy każde 100ms w liczniku `counter`. Z racji tego że maksymalną wartością jaką mogę wyświetlić na wyświetlaczu jest 9999s, czyli 99990 setek ms, licznik ten dostał typ aż uint32_t.

## Timer kontra scheduler
Rozwiązanie z wykorzystaniem „gołego” timera w pliku `main.c`, z uzyciem „schedulera” z poprzednich ćwiczeń w pliku `main_scheduler.c`.

Rozwiązania różnią się od siebie głównie miejscem wykonania kodu od przemiatania/inkrementacji licznika.
Inkrementacja w przerwaniu zwykle nie stanowi problemu, przemiatanie okazało się na tyle optymalne, że również „mieści” się w oknie czasowym między przerwaniami i nie wymaga żadnych dodatkowych zabiegów.
