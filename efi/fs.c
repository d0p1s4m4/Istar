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

#include "istar/efi/types.h"
#include <istar/efi.h>
#include <istar/efi/protocol/file.h>
#include <istar/efi/protocol/loaded_image.h>
#include <istar/efi/protocol/simple_file_system.h>
#include <istar/memory.h>

static EfiLoadedImageProtocol *fs_loaded_image = NULL;
static EfiSimpleFileSystemProtocol *fs_volume = NULL;
static EfiFileProtocol *fs_root = NULL;

int
fs_initialize(void)
{
	static EfiGuid loaded_image_guid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
	static EfiGuid simple_file_system_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
	EfiBootServices *boot;

	boot = efi_get_boot_services();
	if (boot == NULL)
	{
		return (-1);
	}

	if (boot->open_protocol(efi_get_handle(), &loaded_image_guid,
		(void **)&fs_loaded_image, efi_get_handle(), NULL,
		EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL) != EFI_SUCCESS)
	{
		return (-1);
	}

	if (boot->open_protocol(fs_loaded_image->device_handle,
		&simple_file_system_guid, (void **)&fs_volume, efi_get_handle(),
		NULL, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL) != EFI_SUCCESS)
	{
		return (-1);
	}

	if (fs_volume->open_volume(fs_volume, &fs_root) != EFI_SUCCESS)
	{
		return (-1);
	}

	return (0);
}

EfiFileProtocol *
fs_open(wchar_t *file)
{
	EfiFileProtocol *fp;

	if (fs_root->open(fs_root, &fp, file, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY))
	{
		return (NULL);
	}

	return (fp);
}

char *
fs_readall(EfiFileProtocol *fp, uintn_t *size)
{
	char *content;

	*size = 511;
	/*fp->read(fp, size, NULL);*/

	content = memory_alloc(*size + 1);
	if (content == NULL)
	{
		return (NULL);
	}

	content[*size] = '\0';
	if (fp->read(fp, size, content) != EFI_SUCCESS)
	{
		memory_free(content);
		return (NULL);
	}
	return (content);
}
