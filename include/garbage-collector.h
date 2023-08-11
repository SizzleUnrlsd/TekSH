// Copyright (C) 2023 hugo
// 
// This file is part of garbage.
// 
// garbage is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// garbage is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with garbage.  If not, see <http://www.gnu.org/licenses/>.

#ifndef GARBAGE_COLLECOR_
#define GARBAGE_COLLECOR_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <setjmp.h>
#include <signal.h>
#include <errno.h>

#ifndef STATIC_SIZE_
#define STATIC_SIZE_
    #define STATIC_SIZE 100000

#endif

#define _set_errno(val) (errno = (val))


#ifndef _wur_
#define _wur_
    #define _wur __attribute__((__warn_unused_result__))

#endif

#ifndef _GB_UNUSED_
#define _GB_UNUSED_
    #define UNUSED_ARG __attribute__((unused))

#endif

#define GB_CONSTRUCTOR __attribute__((constructor))

#define GB_DESTRUCTOR __attribute__((destructor))

#define ADDR_FRAME_CURRENT_FUNCTION __builtin_frame_address(0)

#define ADDR_FRAME_PARENT_FUNCTION __builtin_frame_address(1)

#define _malloc(__size) _malloc_wrapper(__size, __func__)

#define _mallocbucket(__size) _malloc_wrapper_bucket(__size, __func__)

#define _realloc(__ptr, __size) _realloc_wrapper(__ptr, __size, __func__)

#define _free(ptr) _free_wrapper(ptr)

#define garbage_backup_ptr(ptr) get_ptr(ptr, __func__)

#define garbage_backup_bucket_ptr(ptr) get_ptr_bucket(ptr, __func__)

#define DUMP(varname) #varname;

#pragma pack (1)  
typedef struct allocation_block_s {
    uintptr_t *ptr;
    uintptr_t *addr_frame;
    const char *caller_function;
    size_t size;
    size_t limit_size;
    uint32_t counter;
    bool unreachable;
    bool bucket;
} allocation_block_t;
#pragma pop

/* garbageopt options that actually do something */
#define G_PRINTABLE         -1
#define G_DISABLE           -2
/* not implemented */

_wur void *_malloc_wrapper(size_t __size, const char *caller_function);

_wur void *_malloc_wrapper_bucket(size_t __size, const char *caller_function);

_wur void *_realloc_wrapper(void *__ptr, size_t __size, const char *caller_function);

void _free_wrapper(void *ptr);

extern void get_ptr(void *ptr, const char *caller_function);

extern void get_ptr_bucket(void *ptr, const char *caller_function);

extern void garbage_constructor(void);

extern void garbage_routine(void);

extern void garbage_stat(void);

#endif /* !GARBAGE_COLLECTOR */
