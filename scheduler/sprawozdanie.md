Sprawozdanie z ćwiczeń 5 i 12.11.2014
=====================================

Celem ćwiczenia było zaprojektowanie modułu do szeregowania zadań w oparciu o zdarzenia występujące ze stałą częstotliwością.

## Opis realizacji
Zadania przechowywane są w tablicy o rozmiarze określonym na `MAX_NUMBER_OF_TASKS`, który jest jednocześnie ograniczeniem ilości możliwych priorytetów.

Funkcja `schedule` powinna być wywoływana co stałą ilość czasu. Funkcja `execute` zawiera nieskończoną pętlę wykonującą pożądane zadania.

Funkcja `AddTask` została podzielona na `add_task`, które dodaje zadania do cyklicznego wykonywania, i funkcję `add_disposable`, która dodaje zadania do jednorazowego wykonania po określonym czasie.
Zadania które mają się wykonać tylko raz zostają oznaczone jako wyłączone ("disabled") tuż przed faktycznym ich wykonaniem.

Funkcje oznaczone jako "disabled" są pomijane przez "scheduler" i `execute`, więc usuwanie zadań zostało zrealizowane funkcją `disable_task`.

Funkcje ("lambdy"/"callbacki") mają możliwość zwrócenia stanu wykonania (sukces/porażka), w obecnej wersji zadania które zwróciły błąd są usuwane ze "schedulera".

Z racji tego że tablica z informacjami o zadaniach wykorzystywana jest jednocześnie przez funkcję wykonywaną docelowo w przerwaniu jak i przez funkcję z głównego wątku, konieczne było wprowadzenie prostej synchronizacji,
polegającej na wyłączaniu przerwań w odpowiednich momentach w głównym wątku.

## Notatki
W repozytorium załączam również przykładowy plik wykorzystujący bibliotekę (main.c), kod który udało się wypracować jeszcze na pierwszych ćwiczeniach (old_main.c) oraz mój przykładowy Makefile, wystarczający do wygodnego kompilowania i testowania pod Linuksem (stworzony daaawno temu, przydający się do dziś ;) ).

Aby nie duplikować kodu dla `add_task` i `add_disposable`, wspólną część przeniosłem do `add_event`. `add_event` i tablicę z taskami wyrzuciłem z tablicy symboli (static), inline w `add_event` kontrowersyjny, ale póki mam dużo flasha powinno być ok a zawsze to kilka operacji na stosie/skoków mniej, tak samo z powszechnym unsigned int/int zamiast mniejszych jednostek - prywatnie przeniosłem/przenoszę się na STM32 stąd trochę szastam RAMem i flashem…
