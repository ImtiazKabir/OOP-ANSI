#include "string.h"
#include "string_pr.h"

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../imclass/imclass_pr.h"

static char *__strdup__(register char const *const str);
static void _Constructor(register void *const self, register size_t const argc,
                         register va_list *const args);
static void _Destructor(register void *const self);
static void _Clone(register void *const self, register void const *const from);
static void _Assign(register void *const self, register void const *const from);
static char *_ToString(register void const *const self);

static char *__strdup__(register char const *const str) {
  register char *ret = NULL;

  if (str != NULL) {
    register size_t const len = strlen(str);
    ret = (char *)calloc(len + 1u, sizeof(*ret));
    if (ret != NULL) {
      (void)strncpy(ret, str, len);
      ret[len] = '\0';
    }
  }

  return ret;
}

static void _Constructor(register void *const self, register size_t const argc,
                         register va_list *const args) {
  (void)puts("In ctor");
  if (argc == 0u) {
    ((struct String *)self)->buffer = __strdup__("");
  } else {
    register char const *const arg = va_arg(*args, char const *);
    ((struct String *)self)->buffer = __strdup__(arg);
  }
}

static void _Destructor(register void *const self) {
  (void)puts("In dtor");
  if (self == NULL) {
    return;
  }
  free(((struct String *)self)->buffer);
  ((struct String *)self)->buffer = NULL;
}

static void _Clone(register void *const self, register void const *const from) {
  (void)puts("In clone");
  ((struct String *)self)->buffer =
      __strdup__(((struct String const *)from)->buffer);
}

static void _Assign(register void *const self,
                    register void const *const from) {
  (void)puts("In assign");
  ((struct String *)self)->buffer =
      __strdup__(((struct String const *)from)->buffer);
}

static char *_ToString(register void const *const self) {
  (void)puts("In to_string");
  return __strdup__(((struct String const *)self)->buffer);
}

CLASS(String) {
  _String.size = sizeof(struct String);
  _String.ctor = _Constructor;
  _String.dtor = _Destructor;
  _String.clone = _Clone;
  _String.assign = _Assign;
  _String.to_string = _ToString;
}
