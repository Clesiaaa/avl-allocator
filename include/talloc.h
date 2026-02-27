#include <stdint.h>
#include <stdio.h>

#ifndef TALLOC_H
#define TALLOC_H

void *t_alloc(size_t size);
void *t_allocx(size_t size);
void *t_allocw(size_t size);

void t_freew(void *ptr);
#endif