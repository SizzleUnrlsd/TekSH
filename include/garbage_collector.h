/**
 * Copyright (C) 2023 hugo
 * 
 * This file is part of TekSH.
 * 
 * TekSH is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TekSH is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with TekSH.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GARBAGE_COLLECTOR_H_
    #define GARBAGE_COLLECTOR_H_
    #include "glibc.h"

    typedef struct shell_s shell_t;

    typedef struct garbage_collector_s {
        void *pointer;
        u_int32_t index;
        char padded[4];
    }garbage_collector_t;

    void exit_shell(shell_t *shell);
    void init_garbage(shell_t *shell);
    void free_attribut(void *p, shell_t *shell);
    void garbage_collector(void *p, shell_t *shell);
    void *malloc_attribut(size_t size, shell_t *shell);
    void garbage_uncollector(garbage_collector_t *garbage);
    void *calloc_attribut(size_t __nmemb, size_t size, shell_t *shell);
    garbage_collector_t **realloc_struct(garbage_collector_t **p,
    size_t size, unsigned int len);


#endif /* !GARBAGE_COLLECTOR_H_ */
