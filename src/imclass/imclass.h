#ifndef IMCLASS_H_
#define IMCLASS_H_

#include <stddef.h>
#include <stdio.h>

struct ImClass;

extern struct ImClass const *class_of(register void const *const self);
extern struct ImClass const *super_class_of(register void const *const self);
extern struct ImClass const *super_class_of_class(

    register struct ImClass const *const klass);
extern size_t size_of(register void const *const self);

extern int is_a(register void const *const self,
                register struct ImClass const *const klass);
extern void *cast(register void *const self,
                  register struct ImClass const *const klass);

extern char *to_string(register void const *const self);
extern int fputobj(register void const *const self, register FILE *const fp);
extern int compare(register void const *const a, register void const *const b);

extern void *imalloc(register struct ImClass const *const klass,
                     size_t const argc, ...);

/***************************** rule of three *********************************/
extern void dealloc(register void *const self);
extern void *clone(register void const *const self);
extern void *assign(register void *const self, register void const *const from);
/*****************************************************************************/

#endif /* !IMCLASS_H_ */
