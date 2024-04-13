#ifndef STRING_PR_H_
#define STRING_PR_H_

#include "../imclass/imclass.h"
#include <stddef.h>

struct String {
  struct ImClass const *klass;
  char *buffer;
};

#endif /* !STRING_PR_H_ */
