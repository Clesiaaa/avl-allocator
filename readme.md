<div align="center"> <image src="TA_enhanced.PNG" alt="Description"> </div>

# TurboAlloc — Enhanced Memory Allocator in C

A reimplementation of `malloc` and `free` in C, built as a learning project. Provides two allocator backends: a AVL, a linked list and a binary search tree.

---

## Features

- `t_alloc` / `t_free` — linked list allocator "talloc/tfree.h"
- `t_allocx` / `t_freex` — binary search tree allocator "talloc/tfree.h"
- `t_allocw` / `t_freew` — AVL/Red Black tree allocator in "turboalloc.h"

---

## UpComming Features

- `t_callocK`  — Enhanced callocator in LL, BST and AVLs
- `t_reallocK`  — Enhanced reallocator in LL, BST and AVLs
- `t_deallocK`  — Enhanced deallocator in LL, BST and AVLs
---

## Build

```bash
make
```

---

## Usage

```c
#include "talloc.h"
#include "tfree.h"

int *arr = t_alloc(10 * sizeof(int));   // linked list allocator
int *arr2 = t_allocx(10 * sizeof(int)); // BST allocator

t_free(arr); // linked list free
t_freex(arr2); // bst free
```

---

## Usage with AVL

```c
#include "turboalloc.h"

int *arr = t_allocw(10 * sizeof(int));   // AVL allocator
int *arr2 = t_allocxw(10 * sizeof(int)); //

t_freew(arr); // avl free
t_freew(arr2);
```

---

## How It Works

Each allocation prepends a metadata header (`block_t` or `node_t` or `ball_t`) to the requested memory zone. The pointer returned to the user points just after this header.

On free, the header is recovered by subtracting `sizeof(block_t)` from the pointer, and `is_free` is set to `1`. On the next allocation, free blocks of sufficient size are reused without calling `sbrk`.

---