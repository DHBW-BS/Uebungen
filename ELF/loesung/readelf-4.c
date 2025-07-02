#include <stdio.h>

//------------------------------------
// copy from elf.h
#include <stdint.h>

typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Xword;
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

typedef struct
{
  Elf64_Word    p_type;         /* Segment type */
  Elf64_Word    p_flags;        /* Segment flags */
  Elf64_Off     p_offset;       /* Segment file offset */
  Elf64_Addr    p_vaddr;        /* Segment virtual address */
  Elf64_Addr    p_paddr;        /* Segment physical address */
  Elf64_Xword   p_filesz;       /* Segment size in file */
  Elf64_Xword   p_memsz;        /* Segment size in memory */
  Elf64_Xword   p_align;        /* Segment alignment */
} Elf64_Phdr;
//------------------------------------

#define FILENAME "hello"

int main(int argc, char **argv) {
    FILE *fd;
    unsigned char buffer[64];

    Elf64_Ehdr *ehdr;
    Elf64_Phdr *phdr;

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

    ehdr = (Elf64_Ehdr *) buffer;

    printf("e_ident     = %s\n", ehdr->e_ident);
    printf("e_type      = %x\n", ehdr->e_type);
    printf("e_machine   = %x\n", ehdr->e_machine);
    printf("e_version   = %x\n", ehdr->e_version);
    printf("e_entry     = %llx\n", ehdr->e_entry);
    printf("e_phoff     = %llx\n", ehdr->e_phoff);
    printf("e_shoff     = %llx\n", ehdr->e_shoff);
    printf("e_flags     = %x\n", ehdr->e_flags);
    printf("e_ehsize    = %x\n", ehdr->e_ehsize);
    printf("e_phentsize = %x\n", ehdr->e_phentsize);
    printf("e_phnum     = %x\n", ehdr->e_phnum);
    printf("e_shentsize = %x\n", ehdr->e_shentsize);
    printf("e_shnum     = %x\n", ehdr->e_shnum);
    printf("e_shstrndx  = %x\n", ehdr->e_shstrndx);


    printf("\n");
    fread(buffer, 1, 56, fd);

    for (int i=0; i< 56; i++) {
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
    printf("\n");

    phdr = (Elf64_Phdr *) buffer;

    printf("p_type   =  %x\n", phdr->p_type);
    printf("p_flags  =  %x\n", phdr->p_flags);
    printf("p_offset =  %llx\n", phdr->p_offset);
    printf("p_vaddr  =  %llx\n", phdr->p_vaddr);
    printf("p_paddr  =  %llx\n", phdr->p_paddr);
    printf("p_filesz =  %llx\n", phdr->p_filesz);
    printf("p_memsz  =  %llx\n", phdr->p_memsz);
    printf("p_align  =  %llx\n", phdr->p_align);


    fclose(fd);

    return 0;
}