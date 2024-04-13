#ifndef IMCLASS_PR_H_
#define IMCLASS_PR_H_

#include <stdarg.h>
#include <stddef.h>

struct ImClass {
  void (*class_init)(void);
  size_t size;

  struct ImClass const *super_class;
  void *(*get_super)(register void *const self);
  void (*set_super)(register void *const self, register void *const super);

  void (*ctor)(register void *const self, register size_t const argc,
               register va_list *const args);

  /*************************** rule of three *********************************/
  void (*dtor)(register void *const self);
  void (*clone)(register void *const self, register void const *const from);
  void (*assign)(register void *const self, register void const *const from);
  int (*compare)(register void const *const a, register void const *const b);
  /***************************************************************************/

  char *(*to_string)(register void const *const self);
};

#define CLASS(k)                                                        \
  static void __Init__(void);                                           \
  static struct ImClass _##k = {__Init__, 0u,   NULL, NULL, NULL, NULL, \
                                NULL,     NULL, NULL, NULL, NULL};      \
  struct ImClass const *const k = &_##k;                                \
  static void __Init__(void)

#endif /* !IMCLASS_PR_H_ */
