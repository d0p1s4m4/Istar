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

#include <istar/console.h>
#include <istar/efi.h>

static EfiSimpleTextOutputProtocol *console_out = NULL;

int
console_initialize(void)
{
	if (efi_get_system_table() == NULL)
		return (-1);

	console_out = efi_get_system_table()->console_out_proto;

	if (console_out == NULL)
		return (-1);

	console_out->reset(console_out, FALSE);

	return (0);
}

void
console_wprint(wchar_t *wstr)
{
	if (console_out == NULL)
		return;

	console_out->wprint(console_out, wstr);
}

void
console_putchar(char c)
{
	static wchar_t buffer[2] = { 0 };

	if (console_out == NULL)
		return;

	if (c == '\n')
	{
		console_wprint(L"\r\n"); /* fuck efi */
	}
	else
	{
		buffer[0] = c;
		console_out->wprint(console_out, buffer);
	}
}

