/*
 * Copyright (c) 2022, d0p1
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.

 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
