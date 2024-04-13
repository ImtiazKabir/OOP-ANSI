#include "child.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "../parent/parent.h"
#include "../imclass/imclass_pr.h"

static void _Constructor(register void *const self, register size_t const argc,
                         register va_list *const args);
static void _Destructor(register void *const self);
static void *_GetSuper(register void *const self);
static void _SetSuper(register void *const self, register void *const super);

static void _Constructor(register void *const self, register size_t const argc,
                         register va_list *const args) {
  (void)argc;
  (void)args;
  (void)puts("In child constructor");
  ((struct Child *)self)->bar = 200;
}

static void _Destructor(register void *const self) {
  (void)self;
  (void)puts("In child destructor");
}

static void *_GetSuper(register void *const self) {
  return ((struct Child *)self)->parent;
}

static void _SetSuper(register void *const self, register void *const super) {
  ((struct Child *)self)->parent = super;
}

CLASS(Child) {
  _Child.size = sizeof(struct Child);
  _Child.super_class = Parent;
  _Child.get_super = _GetSuper;
  _Child.set_super = _SetSuper;
  _Child.ctor = _Constructor;
  _Child.dtor = _Destructor;
}
