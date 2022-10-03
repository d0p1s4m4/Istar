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

#ifndef ISTAR_EFI_PROTOCOL_FILE_H
# define ISTAR_EFI_PROTOCOL_FILE_H 1

# include <istar/efi.h>

/* revision ---------------------------------------------------------------- */

# define EFI_FILE_PROTOCOL_REV			0x00010000
# define EFI_FILE_PROTOCOL_REV2			0x00020000
# define EFI_FILE_PROTOCOL_LATEST_REV	EFI_FILE_PROTOCOL_REV2

/* file mode --------------------------------------------------------------- */

# define EFI_FILE_MODE_READ		0x0000000000000001
# define EFI_FILE_MODE_WRITE	0x0000000000000002
# define EFI_FILE_MODE_CREATE	0x8000000000000000

/* file attribute ---------------------------------------------------------- */

# define EFI_FILE_READ_ONLY		0x0000000000000001
# define EFI_FILE_HIDDEN		0x0000000000000002
# define EFI_FILE_SYSTEM		0x0000000000000004
# define EFI_FILE_RESERVED		0x0000000000000008
# define EFI_FILE_DIRECTORY		0x0000000000000010
# define EFI_FILE_ARCHIVE		0x0000000000000020
# define EFI_FILE_VALID_ATTR	0x0000000000000037

/* guid -------------------------------------------------------------------- */

# define EFI_FILE_INFO_ID {0x09576e92, 0x6d3f, 0x11d2, \
							{0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

# define EFI_FILE_SYSTEM_INFO_ID {0x09576e93, 0x6d3f, 0x11d2, \
							{0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

/* protocol structure ------------------------------------------------------ */

typedef struct efi_file_protocol {
	uint64_t revision;
	EfiStatus	(*open)(struct efi_file_protocol *, struct efi_file_protocol **, \
							wchar_t *, uint64_t, uint64_t);
	EfiStatus	(*close)(struct efi_file_protocol *);
	EfiStatus	(*delete)(struct efi_file_protocol *);
	EfiStatus	(*read)(struct efi_file_protocol *, uintn_t *, void *);
	EfiStatus	(*write)(struct efi_file_protocol *, uintn_t *, void *);
	EfiStatus	(*get_position)(struct efi_file_protocol *, uint64_t *);
	EfiStatus	(*set_position)(struct efi_file_protocol *, uint64_t);
	EfiStatus	(*get_info)(struct efi_file_protocol *, EfiGuid *, uintn_t *, void *);
	EfiStatus	(*set_info)(struct efi_file_protocol *, EfiGuid *, uintn_t, void *);
	EfiStatus	(*flush)(struct efi_file_protocol *);

	/* Only in rev 2 */
	EfiStatus	(*open_ex)();
	EfiStatus	(*read_ex)();
	EfiStatus	(*write_ex)();
	EfiStatus	(*flush_ex)();
} EfiFileProtocol;

typedef struct {
	uint64_t size;
	uint64_t file_size;
	uint64_t physical_size;
	EfiTime create_time;
	EfiTime last_access_time;
	EfiTime modificayion_time;
	uint64_t attribute;
	wchar_t filename[256];
} EfiFileInfo;

typedef struct {
	uint64_t size;
	boolean_t read_only;
	uint64_t volume_size;
	uint64_t free_space;
	uint32_t block_size;
	wchar_t volume_label[256];
} EfiFileSystemInfo;

#endif /* !ISTAR_EFI_PROTOCOL_FILE_H */
