# System Call

## Aufgabe

1. Ändern Sie den Source Code, so daß Sie mit Ihrem Namen begrüßt (Hallo <Name>) werden und führen Sie das Programm aus.
2. Übersetzen Sie das Programm mit "-S" Flag, um das Assembler Listing zu erzeugen.
```
# make hello.s
```
oder
```
# cc -O2 -fno-asynchronous-unwind-tables -S hello.c
```
Schauen Sie sich den Assembler Code in `hello.s` an, um den Library Call zu finden, der für den Text I/O verwendet wird.
Was stellen Sie fest?
3. Ändern Sie nun den Source Code, um einen Chracter String zu verwenden, der Ihren Namen enthält.
Erzeugen Sie wieder den Assembler Source und schauen sich den Code in `hello.s` an. Finden Sie wieder den Library Call, der für die Ausgabe verwendet wird.
Was hat sich geändert?
4. Verfolgen Sie mit strace welche System Calls ausgeführt werden.
> strace ./hello
