#include "imclass.h"
#include "imclass_pr.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static char *__strdup__(register char const *src);

static char *__strdup__(register char const *src) {
  register size_t const len = strlen(src);
  register char *const str = malloc(len + 1u);
  register char *p = NULL;

  p = str;
  while (*src) {
    *p++ = *src++;
  }
  *p = '\0';
  return str;
}

extern struct ImClass const *class_of(register void const *const self) {
  if (self == NULL) {
    return NULL;
  }
  return *(struct ImClass **)self;
}

extern struct ImClass const *super_class_of(register void const *const self) {
  if (self == NULL) {
    return NULL;
  }
  return class_of(self)->super_class;
}

extern struct ImClass const *super_class_of_class(
    register struct ImClass const *const klass) {
  return klass->super_class;
}

extern size_t size(register void const *const self) {
  if (self == NULL) {
    return 0u;
  }
  return class_of(self)->size;
}

extern int is_a(register void const *const self,
                register struct ImClass const *const klass) {
  register struct ImClass const *this_class = NULL;

  this_class = class_of(self);
  while (this_class != NULL) {
    if (this_class == klass) {
      return 1;
    }
    this_class = this_class->super_class;
  }
  return 0;
}

extern char *to_string(register void const *const self) {
  register struct ImClass const *const klass = class_of(self);
  if (klass->to_string != NULL) {
    return class_of(self)->to_string(self);
  } else {
    auto char address[50u] = {0};
    (void)sprintf(address, "%p", self);
    address[49u] = '\0';
    return __strdup__(address);
  }
}

extern int fputobj(register void const *const self, register FILE *const fp) {
  register char *const str = to_string(self);
  register int const ret = fputs(str, fp);
  free(str);
  return ret;
}

extern int compare(register void const *const a, register void const *const b) {
  if (a == b) {
    return 0;
  } else {
    register struct ImClass const *const klass1 = class_of(a);
    register struct ImClass const *const klass2 = class_of(b);
    if (klass1 != klass2) {
      return INT_MAX;
    } else if (klass1->compare != NULL) {
      return klass1->compare(a, b);
    } else {
      return (int)((char *)a - (char *)b);
    }
  }
}

extern void *imalloc(register struct ImClass const *const klass,
                     size_t const argc, ...) {
  register void *self = NULL;
  if (klass->class_init != NULL) {
    klass->class_init();
    ((struct ImClass *)klass)->class_init = NULL;
  }

  if ((klass->ctor == NULL) && (argc > 0u)) {
    return NULL;
  }

  self = calloc(1u, klass->size);
  if (klass->super_class != NULL) {
    /* default initialization of super */
    register void *const super = imalloc(klass->super_class, 0u);
    klass->set_super(self, super);
  }

  *((struct ImClass const **)self) = klass;

  if (klass->ctor != NULL) {
    auto va_list list;
    va_start(list, argc);
    klass->ctor(self, argc, &list);
    va_end(list);
  }

  return self;
}

/***************************** rule of three *********************************/
extern void dealloc(register void *const self) {
  register struct ImClass const *const klass = class_of(self);

  if (self == NULL) {
    return;
  }

  if (klass->super_class != NULL) {
    register void *const super = klass->get_super(self);
    dealloc(super);
    klass->set_super(self, NULL);
  }
  if (klass->dtor != NULL) {
    klass->dtor(self);
  }
  free(self);
}

extern void *clone(register void const *const self) {
  register struct ImClass const *const klass = class_of(self);
  register void *ret = NULL;
  if (klass->clone == NULL) {
    return NULL;
  }
  ret = imalloc(klass, 0u);
  klass->clone(ret, self);
  return ret;
}

extern void *assign(register void *const self,
                    register void const *const from) {
  register struct ImClass const *const klass = class_of(self);
  if (klass->assign == NULL) {
    return NULL;
  }
  if (klass->dtor != NULL) {
    klass->dtor(self);
  }
  klass->assign(self, from);
  return self;
}
/*****************************************************************************/

extern void *cast(register void *const self,
                  register struct ImClass const *const klass) {
  register struct ImClass const *this_class = NULL;
  register void *ret = NULL;

  ret = self;
  this_class = class_of(self);
  while (this_class != NULL) {
    if (this_class == klass) {
      return ret;
    }
    ret = this_class->get_super(ret);
    this_class = this_class->super_class;
  }
  return NULL;
}
