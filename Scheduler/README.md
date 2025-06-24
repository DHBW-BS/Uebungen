# Scheduler 

Das Programm `sched.c` implementiert einen Simulator für einen Round-Robin Scheduler.
Es werden 5 Threads gestartet, die Prozesse simulieren. Ein Prozess wird auf running gesetzt, indem `state` in der `task_struct` auf 1 gesetzt wird. Die Threads kommen nacheinander an die Reihe.
Die Ausgabe zeigt die `pid` des aktiven Threads.

## Aufgabe

1. Implementieren Sie eine Ausgabe der Prozessliste. Es sollen mindestens PID und S (Status) ausgegeben werden.

2. Implementieren Sie einen Timer, der nach dem angegebenen Intervall den Scheduler `schedule(void)` aufruft und nach dem Prozesswechel resetted wird.