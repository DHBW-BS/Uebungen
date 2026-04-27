# Übungen

## Aufgabe Boot

In Verzeichnis boot ist in  `boot.asm` enthält ein Assembler Source Code für einen Boot Record. 
Mit
```
nasm -o boot.flp boot.asm
```
kann ein Floppy Image erzeugt werden, das in einem Virtual Guest gebooted werden kann. Es gibt eine Meldung auf den Terminal aus und
beendet dann die Ausführung.

1. Assemblieren Sie den Boot Sector mit
```
# nasm -o boot.flp boot.asm
```
oder
```
# make boot.flp
```
Laden Sie das Floppy Image `boot.flp` runter, laden es in Ihrem Virtual Guest als Floppy und starten Sie das Virtual System.

2. Schauen Sie sich das den Assembler Source Code in `boot.asm` an und verändern Sie es so, dass Sie mit Ihrem Namen begrüßt werden.

## Aufgabe Load

Der Code im Verzeichnis `load` enthält in boot.asm den Assembler Code um von einer Floppy zu starten und dann vom zweiten Sektor
der Floppy ein Programm zu laden, dessen Source Code sich in kernel.c befindet. In kernel.c ist C Code der eine Welcome Message
ausgibt und dann das System anhält.

1. Erzeugen Sie das Floppy Image mit dem Kommando
```
# make boot.flp
```
Laden Sie das Floppy Image `boot.flp` runter, laden es in Ihrem Virtual Guest als Floppy und starten Sie das Virtual System.

2. Schauen Sie sich den Source Code in `kernel.c` an und verändern Sie ihn so, dass Sie mit Ihrem Namen begrüßt werden.

## Aufgabe Keyboard

Im Verzeichnis Keyboard ist der Source Code nun so organisiert, daß der Code zur Ausgabe nach terminal.c verschoben wurde. Es gibt
2 C Source Dateen `kernel.c`und `terminal.c` die zu `kernel.bin` gelinkt werden.

Das Programm `kernel.c` enthält einen Keyboard Treiber. Wenn das System mit dem Floppy Image gestartet wird, ist kann es
Tastendrücke entgegen nehmen.

Das Floppy Image kann wieder mit
```
# make boot.flp
```
erzeugt werden.

1. Implementieren Sie die Routine `printhex8`, so daß der Tastencode auf den Bildschirm ausgegeben wird.

2. Erweitern Sie die Ausgabe, so daß das ASCII Zeichen der gedrückten Taste auf den Bildschirm ausgeben wird. Es ist zweckmäßig dazu den
Release der Taste zu ignorieren.

3. Verändern Sie das Programm so, dass bei gleichzeitigem drücken der Shift-Taste das entsprechende Zeichen in Großbuchstaben ausgegeben wird.

## Aufgabe Keyboard Buffer

1. Implementieren Sie die Routine `getchar`, so daß die eingegeben Zeichen in einer Loop von der Routine `shell` abgeholt werden und auf dem Bildschirm
erscheinen. Bei einem Return soll die Eingabe ausgewertet werden und eine neue Command Eingabe begonnen werden.

## Aufgabe Shell

1. Implementieren Sie in der Routine `shell` ein erstes Command exit mit dem `shell` beendet und das System angehalten wird.
