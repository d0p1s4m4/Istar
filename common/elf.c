#include <istar/elf.h>
#include <istar/string.h>

int
elf64_validate_header(uint8_t *buffer, size_t size)
{
	Elf64Header *hdr;

	if (size < sizeof(Elf64Header))
	{
		return (-1);
	}

	hdr = (Elf64Header *)buffer;

	if (hdr->machine != MACH_AMD64)
	{
		return (-1);
	}

	return (0);
}

int
elf32_validate_header(uint8_t *buffer, size_t size)
{
	Elf32Header *hdr;

	if (size < sizeof(Elf32Header))
	{
		return (-1);
	}

	hdr = (Elf32Header *)buffer;

	if (hdr->machine != MACH_X86)
	{
		return (-1);
	}

	return (0);
}

int
elf_validate(uint8_t *buffer, size_t size)
{
	ElfIdent *ident;

	if (size < sizeof(ElfIdent))
	{
		return (-1);
	}
	
	ident = (ElfIdent *)buffer;

	if (strncmp((char *)ident->magic, ELF_MAGIC, 4) != 0)
	{
		return (-1);
	}

	if (ident->class == CLASS_64)
	{
		return (elf64_validate_header(buffer, size));
	}

	return (elf32_validate_header(buffer, size));
}
