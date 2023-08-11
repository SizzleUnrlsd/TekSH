/**
 * Copyright (C) 2023 hugo
 * 
 * This file is part of garbage.
 * 
 * garbage is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * garbage is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with garbage.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "garbage-collector.h"

static uint32_t counter = 0;

static const uintptr_t *frame_base = NULL;

static allocation_block_t **allocation_array = NULL;

__attribute__((visibility("hidden"))) GB_CONSTRUCTOR void pre_main(void)
{
    allocation_array = calloc(STATIC_SIZE, sizeof(allocation_block_t*));
    if (!allocation_array) {
        _set_errno(ENOMEM);
        exit(ENOMEM);
    }

    return;
}

__attribute__((visibility("hidden"))) GB_DESTRUCTOR void garbage_destructor(void)
{
    uint32_t leak_memory = 0;

    for (uint32_t i = 0; allocation_array[i]; i++) {
        if (allocation_array[i]->unreachable == false && allocation_array[i]->ptr != NULL) {
            allocation_array[i]->unreachable = true;
            allocation_array[i]->caller_function = NULL;
            free(allocation_array[i]->ptr);
            allocation_array[i]->ptr = NULL;
            leak_memory++;
        }
        if (allocation_array[i]->bucket == true) {
            allocation_array[i]->unreachable = true;
            allocation_array[i]->caller_function = NULL;
            free(allocation_array[i]->ptr);
            allocation_array[i]->ptr = NULL;
        }
    }
    for (uint32_t i = 0; allocation_array[i]; i++) {
        if (allocation_array[i]) {
            free(allocation_array[i]);
            allocation_array[i] = NULL;
        }
    }
    free(allocation_array);
    return;
}

void garbage_constructor(void)
{
    frame_base = (uintptr_t*)ADDR_FRAME_PARENT_FUNCTION;
}

_wur void *
_malloc_wrapper(size_t __size, const char *caller_function)
{
    void *ptr = NULL;
    void *parent_frame = ADDR_FRAME_PARENT_FUNCTION;

    ptr = malloc(__size);
    if (!ptr) {
        _set_errno(ENOMEM);
        exit(ENOMEM);
    }

    allocation_array[counter] = (allocation_block_t*)malloc(sizeof(allocation_block_t));
    if (!allocation_array[counter]) {
        _set_errno(ENOMEM);
        exit(ENOMEM);
    }

    allocation_array[counter]->addr_frame = (uintptr_t*)parent_frame;
    allocation_array[counter]->ptr = (uintptr_t*)ptr;
    allocation_array[counter]->caller_function = caller_function;
    allocation_array[counter]->size = __size;
    allocation_array[counter]->limit_size = malloc_usable_size(ptr);
    allocation_array[counter]->counter = counter;
    allocation_array[counter]->unreachable = false;
    allocation_array[counter]->bucket = false;

    /* Increment index */
    ++counter;

    /* Assign next to NULL */
    allocation_array[counter + 1] = NULL;
    return ptr;
}

_wur void *
_malloc_wrapper_bucket(size_t __size, const char *caller_function)
{
    void *ptr = NULL;
    void *parent_frame = ADDR_FRAME_PARENT_FUNCTION;

    ptr = malloc(__size);
    if (!ptr) {
        _set_errno(ENOMEM);
        exit(ENOMEM);
    }

    allocation_array[counter] = (allocation_block_t*)malloc(sizeof(allocation_block_t));
    if (!allocation_array[counter]) {
        _set_errno(ENOMEM);
        exit(ENOMEM);
    }

    allocation_array[counter]->addr_frame = (uintptr_t*)parent_frame;
    allocation_array[counter]->ptr = (uintptr_t*)ptr;
    allocation_array[counter]->caller_function = caller_function;
    allocation_array[counter]->size = __size;
    allocation_array[counter]->limit_size = malloc_usable_size(ptr);
    allocation_array[counter]->counter = counter;
    allocation_array[counter]->unreachable = false;
    allocation_array[counter]->bucket= true;

    /* Increment index */
    ++counter;

    /* Assign next to NULL */
    allocation_array[counter + 1] = NULL;
    return ptr;
}

_wur void *
_realloc_wrapper(void *__ptr, size_t __size, const char *caller_function)
{
    void *ptr = NULL;
    bool known = false;
    uint32_t i = 0;

    if (__ptr == NULL)
        return NULL;

    /* Check if a ptr is known */
    for (; allocation_array[i]; ++i) {
        if (allocation_array[i]->ptr == (uintptr_t*)__ptr) {
            known = true;
            break;
        }
    }

    if (known == true) {
        ptr = (void*)realloc(__ptr, __size);
        if (!ptr) {
            _set_errno(ENOMEM);
            exit(ENOMEM);
        }
        if ((uintptr_t*)ptr == allocation_array[i]->ptr) {
            return ptr;
        } else {
            allocation_array[i]->ptr = NULL;
            allocation_array[i]->ptr = ptr;
            return ptr;
        }
    } else {
        ptr = (void*)realloc(__ptr, __size);
        if (!ptr) {
            _set_errno(ENOMEM);
            exit(ENOMEM);
        }
        get_ptr_bucket(ptr, caller_function);
        return ptr;
    }
}

void
_free_wrapper(void *ptr)
{
    if (ptr == NULL) {
        return;
    }

    for (uint32_t i = 0; allocation_array[i]; i++) {
        allocation_block_t *_ptr_object = allocation_array[i];
        if (ptr == _ptr_object->ptr) {
            _ptr_object->ptr = NULL;
            _ptr_object->unreachable = false;
            _ptr_object->bucket = false;
            free(ptr);
            ptr = NULL;
        }
    }

    return;
}

void get_ptr(void *ptr, const char *caller_function)
{
    uintptr_t *p = (uintptr_t*)ptr;
    void *parent_frame = ADDR_FRAME_PARENT_FUNCTION;

    for (uint32_t i = 0; allocation_array[i]; ++i) {
        /* Check if it's the same address */
        if (ptr == allocation_array[i]->ptr)
            return;
        if (counter <= allocation_array[i]->counter)
            counter = allocation_array[i]->counter;
    }

    allocation_array[counter] = malloc(sizeof(allocation_block_t));
    if (!allocation_array[counter]) {
        _set_errno(ENOMEM);
        exit(ENOMEM);
    }

    allocation_array[counter]->addr_frame = (uintptr_t*)parent_frame;
    allocation_array[counter]->ptr = p;
    allocation_array[counter]->caller_function = caller_function;
    allocation_array[counter]->size = sizeof(p);
    allocation_array[counter]->limit_size = malloc_usable_size((void*)p);
    allocation_array[counter]->counter = counter;
    allocation_array[counter]->unreachable = false;
    allocation_array[counter]->bucket = false;

    /* Increment index */
    counter++;

    /* Assign next to NULL */
    allocation_array[counter + 1] = NULL;
    return;
}

void get_ptr_bucket(void *ptr, const char *caller_function)
{
    uintptr_t *p = (uintptr_t*)ptr;
    void *parent_frame = ADDR_FRAME_PARENT_FUNCTION;

    for (uint32_t i = 0; allocation_array[i]; ++i) {
        /* Check if it's the same address */
        if (ptr == allocation_array[i]->ptr)
            return;
        if (counter <= allocation_array[i]->counter)
            counter = allocation_array[i]->counter;
    }

    allocation_array[counter] = malloc(sizeof(allocation_block_t));
    if (!allocation_array[counter]) {
        _set_errno(ENOMEM);
        exit(ENOMEM);
    }

    allocation_array[counter]->addr_frame = (uintptr_t*)parent_frame;
    allocation_array[counter]->ptr = p;
    allocation_array[counter]->caller_function = caller_function;
    allocation_array[counter]->size = sizeof(p);
    allocation_array[counter]->limit_size = malloc_usable_size((void*)p);
    allocation_array[counter]->counter = counter;
    allocation_array[counter]->unreachable = false;
    allocation_array[counter]->bucket = true;

    /* Increment index */
    counter++;

    /* Assign next to NULL */
    allocation_array[counter + 1] = NULL;
    return;
}

static void
mark(void)
{
    /* Supposed all pointer is unreachbale */
    for (uint32_t i = 0; allocation_array[i]; ++i) {
        allocation_block_t *_ptr_object = allocation_array[i];
        /* Set false because is already reachable */
        _ptr_object->unreachable = true;
    }
}

static void
sweep(void)
{
    for (uint32_t i = 0; allocation_array[i]; ++i) {
        allocation_block_t *_ptr_object = allocation_array[i];
        if (_ptr_object->ptr != NULL && _ptr_object->unreachable == true && _ptr_object->bucket == false) {
            _ptr_object->unreachable = false;
            free(_ptr_object->ptr);
            _ptr_object->ptr = NULL;
        }
    }

    return;
}

static void
garbage_dump(uintptr_t *relative_frame_pointer)
{
    for (;relative_frame_pointer < frame_base; relative_frame_pointer += 1) {
        uintptr_t *p = (uintptr_t*)*relative_frame_pointer;
        for (uint32_t i = 0; allocation_array[i]; i++) {
            allocation_block_t *_ptr_object = allocation_array[i];
            if (_ptr_object->ptr == NULL)
                continue;
            if (_ptr_object->ptr == p) {
                /* Set at false because is already reachable */
                _ptr_object->unreachable = false;
            }
        }
    }
}

void garbage_routine(void)
{
    uintptr_t *relative_frame_pointer = (uintptr_t*)ADDR_FRAME_CURRENT_FUNCTION;

    mark();
    garbage_dump(relative_frame_pointer);
    sweep();
    return;
}

void garbage_stat(void)
{
    uintptr_t *relative_frame_pointer = (uintptr_t*)ADDR_FRAME_CURRENT_FUNCTION;

    mark();
    garbage_dump(relative_frame_pointer);

    printf("RESUME\n");
    for (uint32_t i = 0; allocation_array[i]; i++) {
        printf("---------\n");
        if (allocation_array[i]->ptr == NULL) {
            printf("Caller Function [%s] -> addr : ___       : size ___\nALREADY FREED\n", allocation_array[i]->caller_function);
        } else {
            printf("Caller Function [%s] -> addr : %p : size : %ld\n",
            allocation_array[i]->caller_function, \
            (void*)allocation_array[i]->ptr,             \
            allocation_array[i]->size);           \
            if (allocation_array[i]->unreachable == true)
                printf("IS UNREACHABLE\n");
            else
                printf("IS REACHABLE\n");
        }
    }
    printf("---------\n\n");

    return;
}

void garbageopt(void)
{
    // not implemented
    return;
}

void garbage_memcheck(void)
{
    // not implemented
    return;
}
