# Boot

Das Programm `boot.asm` enthält einen Source Code für einen Boot Record. 
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

Das Programm `keyboard.asm` enthält einen Keyboard Treiber. Wenn das System mit dem Floppy Image gestartet wird, ist kann es Tastendrücke entgegen nehmen. Wenn eine Taste gedrückt wird, wird die Nummer der Taste in hexadezimaler Darstellung ausgegeben.

B.1. Assemblieren Sie den Boot Sector mit
```
# nasm -o keyboard.flp keyboard.asm
```
oder
```
# make keyboard.flp
```
Laden Sie das Floppy Image `keyboard.flp` runter, laden es in Ihrem Virtual Guest als Floppy und starten Sie das Virtual System.

B.2. Schauen Sie sich das Assembler Programm an und verändern Sie es so, dass hinter dem Code der Taste das ASCII Zeichen der Taste in Kleinbuchstaben ausgegeben wird.

B.3. Verändern Sie das Programm so, dass bei gleichzeitigem drücken der Shift-Taste das entsprechende Zeichen in Großbuchstaben ausgegeben wird.
