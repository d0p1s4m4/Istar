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

#ifndef ISTAR_EFI_PROTOCOL_LOADED_IMAGE_H
# define ISTAR_EFI_PROTOCOL_LOADED_IMAGE_H 1

# include <istar/efi.h>

/* guid -------------------------------------------------------------------- */

# define EFI_LOADED_IMAGE_PROTOCOL_GUID {0x5B1B31A1,0x9562,0x11d2,\
									{0x8E,0x3F,0x00,0xA0,0xC9,0x69,0x72,0x3B}}

/* revision ---------------------------------------------------------------- */

# define EFI_LOADED_IMAGE_PROTOCOL_REV 0x1000

/* protocol structure ------------------------------------------------------ */

typedef struct {
	uint64_t revision;
	EfiHandle parent_handle;
	EfiSystemTable *system_table;

	EfiHandle device_handle;
	void *file_path;
	void *reserved;

	uint32_t load_options_size;
	void *load_options;

	void *image_base;
	uint64_t image_size;
	EfiMemoryType image_code_type;
	EfiMemoryType image_data_type;
	void *unload;
} EfiLoadedImageProtocol;

#endif /* !ISTAR_EFI_PROTOCOL_LOADED_IMAGE_H */
