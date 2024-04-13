#ifndef CHILD_H_
#define CHILD_H_

#include "../imclass/imclass.h"
#include "../parent/parent.h"

struct Child {
  struct ImClass *klass;
  struct Parent *parent;
  int bar;
};

extern struct ImClass const *const Child;

#endif /* !CHILD_H_ */
