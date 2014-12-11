Sprawozdanie z ćwiczeń 3.12.2014
================================

W zadaniu została użyta zmodyfikowana wersja "biblioteki" do obsługi wyświetlacza 7segmentowgo z poprzednich ćwiczeń.

Odczyt klawiatury jest realizowany przez odczyt kolejnych wierszy, a następnie „wyciągnięcie” z portu informacji o wciśnięctym przycisku w danym wierszu.
Odczytana wartość jest od razu przekazywana do zmiennej z licznikiem, która jest na bieżąco wyświetlana na wyświetlaczu.
Jeśli po odczytaniu wszystkich wierszy nie zostanie stwierdzone że jakikolwiek przycisk jest wciśnięty - wartość zmiennej jest przywracana do zera.
