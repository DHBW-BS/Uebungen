asm (
    ".code16gcc\n\t"
    ".align 4\n\t"
    "call kmain"
);

static void putchar(char c) {
    asm volatile (
        "mov  %0, %%al\n\t"
        "mov  $0x0e, %%ah\n\t"
        "int  $0x10"
        : /* no output */
        : "d" (c)
        : "ax");

    return;
}

static void print(char *s) {
    char *c;

    while (*(c = s++) != 0) {
        putchar(*c);
    }

    return;
}

int kmain(void) {
    print("starting kernel ...\r\n");

    asm volatile (
        "cli\n\t"
        "hlt");
}
