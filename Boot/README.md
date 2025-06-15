# Boot

Das Programm boot.asm enthält einen Source Code für einen Boot Record. 
Mit
```
nasm -o boot.flp boot.asm
```
kann ein Floppy Image erzeugt werden, das in einem Virtual Guest gebooted werden kann. Es gibt eine Meldung auf den Terminal aus und beendet dann die Ausführung.

## Aufgabe Boot

A.1. Assemblieren Sie den Boot Sector mit
```
# nasm -o boot.flp boot.asm
```
oder
```
# make boot.flp
```
Laden Sie das Floppy Image `boot.flp` runter, laden es in Ihrem Virtual Guest als Floppy und starten Sie das Virtual System.

A.2. Schauen Sie sich das Assembler Programm an und verändern Sie es so, dass Sie mit Ihrem Namen begrüßt werden.

## Aufgabe Keyboard
