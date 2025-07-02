__asm__ (
    ".code16gcc\n\t"
    ".align 4\n\t"
    "call kmain"
);

/* types */
typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;

/* irq */
extern uint8_t inb(uint16_t port);
extern void outb(uint8_t v, uint16_t port);
extern void registerinterrupt(int irq, void* handler);

/* keyboard */
extern void keyboardhandler(void);

/* shell */
extern void shell(void);

/* terminal */
extern void print(char *s);
extern void printHex8(uint8_t n);
extern void putchar(char c);
