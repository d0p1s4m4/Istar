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

#include <istar/console.h>
#include <istar/fs.h>
#include <istar/memory.h>
#include <istar/efi.h>

EfiStatus
efi_main(EfiHandle handle, EfiSystemTable *system_table)
{
	FILE *fp;
	char *buff;

	efi_initialize(handle, system_table);

	if (console_initialize() < 0)
	{
		return (-1);
	}
	
	console_printf("vendor: %w\n", system_table->firmware_vendor);

	if (fs_initialize() < 0)
	{
		console_printf("Can't open volume\n");
		return (-1);
	}

	if ((fp = fs_open("EFI/BOOT/istar.lisp")) == NULL)
	{
		console_printf("can't open istar.lisp\n");
	}

	if ((buff = fs_readall(fp)) == NULL)
	{
		console_printf("can't read istar.lisp\n");
	}
	else
	{
		console_printf(buff);
	}
	memory_free(buff);
	fs_close(fp);

	while (1);
	return (0);
}
