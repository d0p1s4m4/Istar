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

#ifndef ISTAR_EFI_SERVICE_BOOT_H
# define ISTAR_EFI_SERVICE_BOOT_H 1

# include <istar/efi/types.h>

/* signature --------------------------------------------------------------- */

# define EFI_BOOT_SERVICES_HEADER_SIGNATURE     0x56524553544f4f42

/* open protocol def ------------------------------------------------------- */

# define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL	0x00000001
# define EFI_OPEN_PROTOCOL_GET_PROTOCOL			0x00000002
# define EFI_OPEN_PROTOCOL_TEST_PROTOCOL		0x00000004
# define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER	0x00000008
# define EFI_OPEN_PROTOCOL_BY_DRIVER			0x00000010
# define EFI_OPEN_PROTOCOL_EXCLUSIVE			0x00000020

/* boot services ----------------------------------------------------------- */

typedef struct {
	EfiTableHeader header;

	/* task priority */
	void *raise_tpl;
	void *restore_tpl;

	/* memory */
	void *allocate_pages;
	void *free_pages;
	void *get_memory_map;
	EfiStatus	(*allocate_pool)(EfiMemoryType, uintn_t, void **);
	EfiStatus	(*free_pool)(void *);

	/* event & timer */
	void *create_event;
	void *set_timer;
	void *wait_for_event;
	void *signal_event;
	void *close_event;
	void *check_event;

	/* protocol handler */
	void *install_protocol_interface;
	void *reinstall_protocol_interface;
	void *uninstall_protocol_interface;
	EfiStatus (*handle_protocol)(EfiHandle, EfiGuid *, void **);
	void *reserved;
	void *register_protocol_notify;
	EfiHandle locate_handle;
	void *locate_device_path;
	void *install_configuration_table;

	/* image */
	void *load_image;
	void *start_image;
	void *exit;
	void *unload_image;
	void *exit_boot_services;

	/* misc */
	void *get_next_monotonic_count;
	void *stall;
	void *set_watchdog_timer;

	/* EFI 1.1+ */

	/* driver support */
	void *connect_controller;
	void *disconnect_controller;

	/* open and close protocol */
	EfiStatus (*open_protocol)(EfiHandle, EfiGuid *, void **, EfiHandle, \
								EfiHandle, uint32_t);
	void *close_protocol;
	void *open_protocol_information;

	/* library */

	/* 32-bit crc */

	/* misc */
} EfiBootServices;

#endif /* !ISTAR_EFI_SERVICE_BOOT_H */
