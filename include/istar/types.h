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

#ifndef ISTAR_TYPES_H
# define ISTAR_TYPES_H 1

# include <stdint.h>

/*
 * +---------------------------------------------------------------------------+
 * | ALL TYPES BELLOW ARE ONLY FOR EFI DO NOT USE ELSE WHERE                   |
 * +---------------------------------------------------------------------------+
 */

# if defined(__x86_64__)
typedef uint64_t uintn_t;
typedef int64_t intn_t;
# elif defined(__i386__)
typedef uint32_t uintn_t;
typedef int32_t intn_t;
# else
# warning "Can't define uintn_t and intn_t"
# endif /* __x86_64 */

/* wchar -------------------------------------------------------------------- */

typedef uint16_t wchar_t;

/* boolean ------------------------------------------------------------------ */

# ifdef TRUE
#  undef TRUE
# endif /* TRUE */
# define TRUE 1

# ifdef FALSE
#  undef FALSE
# endif /* FALSE */
# define FALSE 0

typedef uint8_t boolean_t;

#endif /* !ISTAR_TYPES_H */
