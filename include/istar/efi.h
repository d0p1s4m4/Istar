/*
 * Copyright (c) 2021, d0p1
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

#ifndef ISTAR_EFI_H
# define ISTAR_EFI_H 1

/* spec: https://uefi.org/sites/default/files/resources/UEFI_Spec_2_9_2021_03_18.pdf */

# include <istar/types.h>
# include <istar/efi/service/boot.h>
# include <istar/efi/service/runtime.h>
# include <istar/efi/protocol/simple_text_input.h>
# include <istar/efi/protocol/simple_text_output.h>

/* Spec version ------------------------------------------------------------- */

# define EFI_SPEC_REV_1_02 ((1 << 16) | (2))
# define EFI_SPEC_REV_1_10 ((1 << 16) | (10))
# define EFI_SPEC_REV_2_00 ((2 << 16) | (0))
# define EFI_SPEC_REV_2_10 ((2 << 16) | (10))
# define EFI_SPEC_REV_2_20 ((2 << 16) | (20))
# define EFI_SPEC_REV_2_30 ((2 << 16) | (30))
# define EFI_SPEC_REV_2_31 ((2 << 16) | (31))
# define EFI_SPEC_REV_2_40 ((2 << 16) | (40))
# define EFI_SPEC_REV_2_50 ((2 << 16) | (50))
# define EFI_SPEC_REV_2_60 ((2 << 16) | (60))
# define EFI_SPEC_REV_2_70 ((2 << 16) | (70))
# define EFI_SPEC_REV_2_80 ((2 << 16) | (80))
# define EFI_SPEC_REV_2_90 ((2 << 16) | (90))

/* header signature --------------------------------------------------------- */

# define EFI_SYSTEM_TABLE_HEADER_SIGNATURE      0x5453595320494249

/* return value ------------------------------------------------------------- */

# define EFI_SUCCESS 0

/* time -------------------------------------------------------------------- */

# define EFI_TIME_ADJUST_DAYLIGHT	0x01
# define EFI_TIME_IN_DAYLIGHT		0x02

# define EFI_UNSPECIFIED_TIMEZONE	0x07FF

/* efi table --------------------------------------------------------------- */

typedef struct {
	EfiTableHeader header;
} EfiConfigurationTable;

typedef struct {
	EfiTableHeader header;
	wchar_t *firmware_vendor;
	uint32_t firmware_rev;
	EfiHandle console_in_handle;
	EfiSimpleTextInputProtocol *console_in_proto;
	EfiHandle console_out_handle;
	EfiSimpleTextOutputProtocol *console_out_proto;
	EfiHandle console_err_handle;
	EfiSimpleTextOutputProtocol *console_err_proto;
	EfiRuntimeServices *runtime_services;
	EfiBootServices *boot_services;
	uintn_t table_entries_count;
	EfiConfigurationTable *config_table;
} EfiSystemTable;

void efi_initialize(EfiHandle handle, EfiSystemTable *table);
EfiSystemTable *efi_get_system_table(void);
EfiHandle *efi_get_handle(void);
EfiBootServices *efi_get_boot_services(void);

#endif /* !ISTAR_EFI_H */
