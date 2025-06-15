# Boot

Das Programm boot.asm enthält einen Source Code für einen Boot Record. 
Mit
```
nasm -o boot.flp boot.asm
```
kann ein Floppy Image erzeugt werden, das in einem Virtual Guest gebooted werden kann. Es gibt eine Meldung auf den Terminal aus und beendet dann die Ausführung.

## Aufgabe

A.1. Schauen Sie sich das Assembler Programm an und verändern Sie es so, dass Sie mit Ihrem Namen begrüßt werden.