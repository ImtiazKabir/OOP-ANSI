#include <stdio.h>
#include <stdlib.h>
#include "imclass/imclass.h"
#include "string/string.h"
#include "parent/parent.h"
#include "child/child.h"

static void _StringTest(void);
static void _ParentChildTest(void);

extern int main(register int const argc,
                register char const *const *const argv) {
  (void)argc;
  (void)argv;

  _ParentChildTest();

  return EXIT_SUCCESS;
}

static void _StringTest(void) {
  register struct String *str1 = NULL;
  register struct String *str2 = NULL;

  str1 = imalloc(String, 1u, "hello");
  str2 = imalloc(String, 1u, "world");

  (void)fputobj(str1, stdout);
  (void)fputc('\n', stdout);

  assign(str1, str2);

  (void)fputobj(str1, stdout);
  (void)fputc('\n', stdout);

  if (is_a(str1, String) != 0) {
    (void)puts("it is a string");
  }

  dealloc(str1);
  dealloc(str2);
}

static void _ParentChildTest(void) {
  register struct Child const *child = NULL;
  child = imalloc(Child, 0u);
  if (is_a(child, Child) != 0) {
    (void)puts("it is child");
  }
  if (is_a(child, Parent) != 0) {
    (void)puts("it is parent");
  }
  if (is_a(child, String) != 0) {
    (void)puts("it is string");
  }
  (void)fputobj(child, stdout);
  (void)fputc('\n', stdout);

  (void)fputobj(child->parent, stdout);
  (void)fputc('\n', stdout);

  (void)fputobj(cast((void *)child, Parent), stdout);
  (void)fputc('\n', stdout);

  dealloc((void *)child);
}
