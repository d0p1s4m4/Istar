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

#ifndef ISTAR_EFI_TYPES_H
# define ISTAR_EFI_TYPES_H 1

# include <stdint.h>

/* uintn_t, intn_t --------------------------------------------------------- */

# if defined(__x86_64__)
typedef uint64_t uintn_t;
typedef int64_t intn_t;
# elif defined(__i386__)
typedef uint32_t uintn_t;
typedef int32_t intn_t;
# else
#  error "Can't define uintn_t & intn_t"
# endif /* __x86_64__ */

/* wchar_t ----------------------------------------------------------------- */

typedef uint16_t wchar_t;

/* boolean_t --------------------------------------------------------------- */

# ifdef TRUE
#  undef TRUE
# endif /* TRUE */
# define TRUE 1

# ifdef FALSE
#  undef FALSE
# endif /* FALSE */
# define FALSE 0

typedef uint8_t boolean_t;

/* efi structs ------------------------------------------------------------- */

typedef uintn_t EfiStatus;
typedef void *EfiHandle;

typedef struct {
	uint32_t a;
	uint16_t b;
	uint16_t c;
	uint8_t d[8];
} EfiGuid;

typedef struct {
	uint64_t signature;
	uint32_t revision;
	uint32_t header_size;
	uint32_t crc32;
	uint32_t reserved;
} EfiTableHeader;

typedef struct {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t pad1;
	uint32_t nanosecond;
	uint16_t timezone;
	uint8_t daylight;
	uint8_t pad2;
} EfiTime;

/* memory ------------------------------------------------------------------ */

typedef enum
{
	EFI_RESERVED_MEMORY_TYPE,
	EFI_LOADER_CODE,
	EFI_LOADER_DATA,
	EFI_BOOT_SERVICES_CODE,
	EFI_BOOT_SERVICES_DATA,
	EFI_RUNTIME_SERVICES_CODE,
	EFI_RUNTIME_SERVICES_DATA,
	EFI_CONVENTIONAL_MEMORY,
	EFI_UNUSABLE_MEMORY,
	EFI_ACPI_RECLAIM_MEMORY,
	EFI_ACPI_MEMORY_NVS,
	EFI_MEMORY_MAPPED_IO,
	EFI_MEMORY_MAPPED_IO_PORT_SPACE,
	EFI_PAL_CODE,
	EFI_PERSISTENT_MEMORY,
	EFI_UNACCEPTED_MEMORY_TYPE,
	EFI_MAX_MEMORY_TYPE
} EfiMemoryType;

#endif /* !ISTAR_EFI_TYPES_H */
