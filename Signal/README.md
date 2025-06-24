# Signal

Das Programm `pi.c` berechnet die ersten 500 Nachkommastellen der Kreiszahl Pi. Mit `SIGQUIT (CTRL-4) wird die Berechnung abgebrochen, das Program gibt das aktuelle Ergebnis aus und beendet sich.

## Aufgabe

1. Implementieren Sie einen Signal Handler, der das aktuelle Zwischenergebnis ausgibt und dann die Berechnung fortsetzt.