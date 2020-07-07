#include "link.h"
#include <assert.h>
#include <limits.h>



void test_lnk__empty() {
  struct link* lnk = lnk__empty();
  struct lelement* head = lnk->head;
  assert(head->pt == NULL && head->next == head);

  printf(" .");
  return;
}

void test_lnk__first() {
  //first lelement == END_MARK
  struct link* lnk = lnk__empty();
  struct lelement* end_mark = lnk__first(lnk);
  assert(end_mark->pt == NULL && end_mark->next == end_mark);

  //first lelement != END_MARK
  int data = 1;
  struct lelement head = {&data, end_mark};
  lnk->head = &head;
  struct lelement* first = lnk__first(lnk);
  assert(first->pt != NULL && first->next != first && first == &head);

  printf(" .");
  return;
}

void test_llm__is_end_mark() {
  //llm == END_MARK
  struct link* lnk = lnk__empty();
  struct lelement* end_mark = lnk->head;
  assert(llm__is_end_mark(end_mark));

  //llm != END_MARK
  int data = 1;
  struct lelement llm = {&data, end_mark};
  assert(!llm__is_end_mark(&llm));

  printf(" .");
  return;
}

void test_lnk__add_head() {
  struct link* lnk = lnk__empty();
  int data = 1;
  struct lelement head = {&data, NULL};
  assert(lnk__add_head(lnk, &head));
  assert(lnk->head == &head);
  assert(!llm__is_end_mark(lnk->head));
  assert(llm__is_end_mark(lnk->head->next));

  printf(" .");
  return;
}

void test_lnk__remove_head() {
  struct link* lnk = lnk__empty();
  assert(lnk__remove_head(lnk) == NULL);

  int data = 1;
  struct lelement head = {&data, NULL};
  lnk__add_head(lnk, &head);
  assert(lnk__remove_head(lnk) == &head);

  printf(" .");
  return;
}

void test_llm__next() {
  int data = 1;
  struct lelement end_mark = {&data, &end_mark};
  struct lelement lel = {&data, &end_mark};
  assert(llm__next(&lel) == &end_mark);
  assert(llm__next(&end_mark) == &end_mark);

  printf(" .");
  return;
}

void test_lnk__add_after() {
  struct link* lnk = lnk__empty();
  int data = 1;
  struct lelement after = {&data, NULL};
  assert(!lnk__add_after(lnk->head, &after));

  struct lelement lel = {&data, lnk->head};
  lnk->head = &lel;
  assert(lnk__add_after(&lel, &after));
  assert(lel.next == &after);
  assert(llm__is_end_mark(after.next));

  printf(" .");
  return;
}

void test_lnk__remove_after() {
  struct link* lnk = lnk__empty();
  assert(!lnk__remove_after(lnk->head));

  int data = 1;
  struct lelement lel1 = {&data, lnk->head};
  lnk->head = &lel1;
  assert(!lnk__remove_after(&lel1));

  struct lelement lel2 = {&data, lnk->head};
  lnk->head = &lel2;
  assert(lnk__remove_after(&lel2) == &lel1);
  assert(llm__is_end_mark(lel2.next));

  printf(" .");
  return;
}

void test_lnk__add_tail() {
  struct link* lnk = lnk__empty();
  int data = 1;
  struct lelement tail1 = {&data, NULL};
  assert(lnk__add_tail(lnk, &tail1));
  assert(lnk->head == &tail1);
  assert(llm__is_end_mark(tail1.next));

  struct lelement tail2 = {&data, NULL};
  assert(lnk__add_tail(lnk, &tail2));
  assert(lnk->head == &tail1);
  assert(tail1.next == &tail2);
  assert(llm__is_end_mark(tail2.next));

  printf(" .");
  return;
}

void test_lnk__remove_tail() {
  struct link* lnk = lnk__empty();
  assert(lnk__remove_tail(lnk) == NULL);

  int data = 1;
  struct lelement lel1 = {&data, lnk->head};
  lnk->head = &lel1;
  assert(lnk__remove_tail(lnk) == &lel1);

  struct lelement lel2 = {&data, lnk->head};
  lel1.next = &lel2;
  lnk->head = &lel1;
  assert(lnk__remove_tail(lnk) == &lel2);

  printf(" .");
  return;
}

int main() {
  test_lnk__empty();
  test_lnk__first();
  test_llm__is_end_mark();
  test_lnk__add_head();
  test_lnk__remove_head();
  test_llm__next();
  test_lnk__add_after();
  test_lnk__remove_after();
  test_lnk__add_tail();
  test_lnk__remove_tail();

  printf(" [");
  printf("\033[1;32m");
  printf("OK");
  printf("\033[0m");
  printf("]");

  printf("\n");
  return 0;
}
