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

/* terminal */
extern void print(char *s);
extern void printHex8(uint8_t n);
extern void putchar(char c);

static char keymap[] = {
	'\0', '\0', '1',  '2',  '3',  '4',  '5',  '6',		/* 00 */
	'7',  '8',  '9',  '0',  '\0', '\0', '\0', '\0',		/* 08 */
	'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',		/* 10 */
	'o',  'p',  '\0', '\0', '\n', '\0', 'a',  's',		/* 18 */
	'd',  'f',  'g',  'h',  'j',  'k',  'l',  '\0',		/* 20 */
	'\0', '\0', '\0', '\0', 'z',  'x', 'c',  'v',		/* 28 */
	'b',  'n',  'm',  '\0', '\0', '\0', '\0', '\0',		/* 30 */
	'\0', ' ',  '\0', '\0', '\0', '\0', '\0', '\0',		/* 38 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 40 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 48 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 50 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 58 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 60 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 68 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 70 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'		/* 78 */
};
