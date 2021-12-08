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

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#define MBR_PART_LOC 440
#define MBR_PART_SIZE 70

extern char _binary_istar_bin_start[];
extern char _binary_istar_bin_end[];

static char *prg_name;
static char mbr_partition_table[MBR_PART_SIZE];

int
read_data(int fd, int loc, char *buff, ssize_t size)
{
	if (lseek(fd, loc, SEEK_SET) < 0)
	{
		perror(prg_name);
		return (-1);
	}

	if (read(fd, buff, size) != size)
	{
		perror(prg_name);
		return (-1);
	}
	return (0);
}

int
write_data(int fd, int loc, char *buff, ssize_t size)
{
	if (lseek(fd, loc, SEEK_SET) < 0)
	{
		perror(prg_name);
		return (-1);
	}

	if (write(fd, buff, size) < 0)
	{
		perror(prg_name);
		return (-1);
	}

	return (0);
}

int
process_img(int fd)
{
	size_t bootloader_size;

	if (read_data(fd, MBR_PART_LOC, mbr_partition_table, MBR_PART_SIZE) < 0)
	{
		fprintf(stderr, "failed to read MBR Partition Table\n");
		return (-1);
	}

	bootloader_size = _binary_istar_bin_end - _binary_istar_bin_start;
	if (write_data(fd, 0, _binary_istar_bin_start, bootloader_size) < 0)
	{
		fprintf(stderr, "failed to write Istar bootloader code\n");
		return (-1);
	}

	if (write_data(fd, MBR_PART_LOC, mbr_partition_table, MBR_PART_SIZE) < 0)
	{
		fprintf(stderr, "failed to write back MBR Partition Table\n");
		return (-1);
	}

	return (0);
}

int
main(int argc, char *argv[])
{
	int fd;
	int ret_val;

	if (argc < 2)
	{
		fprintf(stderr, "Error: usage %s <disk image>", argv[0]);
		return (EXIT_FAILURE);
	}

	prg_name = argv[0];

	fd = open(argv[1], O_RDWR);
	if (fd < 0)
	{
		perror(argv[1]);
		return (EXIT_FAILURE);
	}

	ret_val = EXIT_SUCCESS;
	if (process_img(fd) < 0)
	{
		ret_val = EXIT_FAILURE;
	}
	close(fd);
	return (ret_val);
}
