__asm__ (
    ".code16gcc\n\t"
    ".align 4\n\t"
    "call kmain"
);

/* types */
typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int		uint32_t;

/* floppy */
extern void floppy_read(char *buffer, int sector, int track, int head, int drive);
extern void floppy_reset(void);

/* irq */
extern void enable_irq(void);
extern uint8_t inb(uint16_t port);
extern void outb(uint8_t v, uint16_t port);
extern void registerinterrupt(int irq, void* handler);

/* kernel */
extern void halt(void);

/* keyboard */
extern char getchar(void);
extern void keyboardhandler(void);

/* shell */
extern void shell(void);

/* syscall */
void syscall(void);

/* terminal */
extern void print(char *s);
extern void putchar(char c);
extern void printhex8(uint8_t n);
extern void printhex16(uint16_t n);
extern void printhex32(uint32_t n);