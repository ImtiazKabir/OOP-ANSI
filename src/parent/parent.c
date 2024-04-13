#include "parent.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "../imclass/imclass_pr.h"

static void _Constructor(register void *const self, register size_t const argc,
                         register va_list *const args);
static void _Destructor(register void *const self);

static void _Constructor(register void *const self, register size_t const argc,
                         register va_list *const args) {
  (void)argc;
  (void)args;
  (void)puts("In parent constructor");
  ((struct Parent *)self)->foo = 20;
}

static void _Destructor(register void *const self) {
  (void)self;
  (void)puts("In parent destructor");
}

CLASS(Parent) {
  _Parent.size = sizeof(struct Parent);
  _Parent.ctor = _Constructor;
  _Parent.dtor = _Destructor;
}
