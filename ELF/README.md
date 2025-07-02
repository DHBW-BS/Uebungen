# ELF

Das Programm `hello.c` implementiert ein "Hello World" Programm in C und `print.asm` ein "Hello World" Programm in Assembler.

## Aufgabe ELF

1. Übersetzen Sie `hello.c` und führen Sie es aus.

2. Implementieren Sie ein Programm `readelf`, das die ersten 64 Byte von `hello` liest und auf dem Bildschirm ausgibt.

3. In den ersten 64 Byte steht bei einem Programm der ELF Header (bei 32 Bit in den ersten 56 Byte). Ändern Sie readelf 
ab, so daß es die ELF Informationen ausgibt. Nutzen Sie dazu die Informationen aus `/usr/include/elf.h`oder dem angegeben Wikipedia Artikel.

4. Nach dem ELF Header steht der erste Program Header. Die Größe des Program Headers steht im ELF Header.

Ändern Sie `readelf` so ab, daß es die Bytes des ersten Programm Headers auf den Bildschirm ausgibt. Implementieren Sie die Ausgabe analog
zum ELF Header die Information aus dem Program Header ausgibt.

Nutzen Sie dazu wieder die Informationen aus `/usr/include/elf.h`oder dem angegeben Wikipedia Artikel.

5. Assemblieren Sie `print.asm` unter Linux, linken es und führen es aus.
```
# nasm -f elf64 print.asm
# ld -o print print.o
```

6. Schreiben Sie einen ELF Header und einen Program Header an den Anfang des Assembler Programms, so daß das Programm nur noch assembliert 
werden muß und ohne Linkage gestartet werden kann.

Schauen Sie in die ELF Spezifikation und in die Ausgabe von `readelf`, um zu sehen was im ELF Header und im Program Header stehen muß.

Assemblieren Sie `print.asm` mit Listing Ausgabe, damit Sie die INhalt und Formattierung Ihres ELF und Program Headers sehen.
```
# nasm -l print.lst print.asm
```

## Informationen
https://en.wikipedia.org/wiki/Executable_and_Linkable_Format