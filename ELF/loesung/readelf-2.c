#include <stdio.h>

//------------------------------------
// copy from elf.h
#include <stdint.h>

typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Off;

#define EI_NIDENT (16)

typedef struct
{
  unsigned char e_ident[EI_NIDENT]; /* Magic number and other info */
  Elf64_Half    e_type;             /* Object file type */
  Elf64_Half    e_machine;          /* Architecture */
  Elf64_Word    e_version;          /* Object file version */
  Elf64_Addr    e_entry;            /* Entry point virtual address */
  Elf64_Off     e_phoff;            /* Program header table file offset */
  Elf64_Off     e_shoff;            /* Section header table file offset */
  Elf64_Word    e_flags;            /* Processor-specific flags */
  Elf64_Half    e_ehsize;           /* ELF header size in bytes */
  Elf64_Half    e_phentsize;        /* Program header table entry size */
  Elf64_Half    e_phnum;            /* Program header table entry count */
  Elf64_Half    e_shentsize;        /* Section header table entry size */
  Elf64_Half    e_shnum;            /* Section header table entry count */
  Elf64_Half    e_shstrndx;         /* Section header string table index */
} Elf64_Ehdr;
//------------------------------------

#define FILENAME "hello"

int main(int argc, char **argv) {
    FILE *fd;
    unsigned char buffer[64];

    Elf64_Ehdr *ehdr;

    fd = fopen(FILENAME, "r");

    fread(buffer, 1, 64, fd);

    for (int i=0; i< 64; i++) {
        if (i%16 == 0) {
            printf("%08x  ", i);
        }
        printf("%02x", buffer[i]);
        if (i%16 == 15) {
            printf("\n");
        } else if (i%8 == 7) {
            printf("  ");
        } else {
            printf(" ");
        }
    }

    fclose(fd);

    ehdr = (Elf64_Ehdr *) buffer;

    printf("e_ident = %s\n", ehdr->e_ident);
    printf("e_type = %x\n", ehdr->e_type);
    printf("e_machine = %x\n", ehdr->e_machine);

    return 0;
}