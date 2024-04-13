#ifndef PARENT_H_
#define PARENT_H_

#include "../imclass/imclass.h"

struct Parent {
  struct ImClass *klass;
  int foo;
};

extern struct ImClass const *const Parent;

#endif /* !PARENT_H_ */
