# OS16C

In dieser Aufgabe wird ein minimales Betriebssystem in C entwickelt. Es gibt einen loader `boot.asm` in Assembler, der den in C implementierten 
kernel `kernel.bin`lädt. \
Für den Compile braucht es einiges an Flags, um dem Compiler mitzuteilen, daß wir ein Standalone Programm ohne Libraries und Builtin Funktionen 
bauen wollen. Deshalb ist es ratsam den Makefile zu verwenden.

## Aufgabe OS16C

1. Bauen Sie die Vorgabe mit
```
# make boot.flp
```
Laden Sie das Floppy Image `boot.flp` runter, laden es in Ihrem Virtual Guest als Floppy und starten Sie das Virtual System.

2. Implementieren Sie einen Keyboard Handler, der einen Tastendrucke entgegen nimmt und das Zeichen auf dem Bildschirm anzeigt.

3. Implementieren Sie eine minimale Shell, die das Kommando `exit` entgegen nimmt und damit das System anhält.

4. Implementieren Sie ein `dump` Kommando , das die ersten 16 Byte auf der Floppy `boot.flp` liest und das Verzeichnis auf dem Bildschirm anzeigt.

5. Laden Sie das Floppy Image `data.flp` runter und verwenden es im zweiten Floppy Drive.
Lesen Sie das FAT Verzeichnis auf der Floppy `data.flp` und implementieren Sie ein `dir`Kommando, mit dem das Verzeichnis auf dem Bildschirm 
angezeigt wird.

6. Implementieren Sie einen System Call Handler, der auf `INT 0x20` reagiert und eine Fehlermeldung für unbekannte System Calls ausgibt.

7. Laden Sie eines der `.COM` Programme von der Floppy und führen es aus. 