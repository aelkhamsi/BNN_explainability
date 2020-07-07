#include "link.h"
#include <limits.h>


struct link* lnk__empty() {
  struct link* lnk = malloc(sizeof(struct link));
  lnk->head = END_MARK;
  return lnk;
}

struct lelement* llm__empty() {
  struct lelement* llm = malloc(sizeof(struct lelement));
  llm->pt = NULL;
  llm->next = NULL;
  return llm;
}

struct lelement* llm__create(void* pt, struct lelement* next) {
  struct lelement* llm = malloc(sizeof(struct lelement));
  llm->pt = pt;
  llm->next = next;
  return llm;
}


struct lelement* lnk__first(struct link* lnk) {
  return lnk->head;
}

int llm__is_end_mark(struct lelement* llm) {
  return llm == END_MARK;
}


int lnk__add_head(struct link* lnk, struct lelement* llm) {
  llm->next = lnk->head;
  lnk->head = llm;
  return 1;
}

struct lelement* lnk__remove_head(struct link* lnk) {
  if (llm__is_end_mark(lnk->head)) return NULL;
  struct lelement* head = lnk->head;
  lnk->head = head->next;
  head->next = NULL;
  return head;
}

struct lelement* llm__next(struct lelement* llm) {
  return llm->next;
}

int lnk__add_after(struct lelement* lel, struct lelement* after) {
  if (llm__is_end_mark(lel)) return 0;
  after->next = lel->next;
  lel->next = after;
  return 1;
}

struct lelement* lnk__remove_after(struct lelement* lel) {
  if (llm__is_end_mark(lel) || llm__is_end_mark(lel->next)) return NULL;
  struct lelement* after = lel->next;
  lel->next = after->next;
  after->next = NULL;
  return after;
}

int lnk__add_tail(struct link* lnk, struct lelement* lel) {
  struct lelement* cursor = lnk->head;
  if (llm__is_end_mark(cursor)) {
    lnk__add_head(lnk, lel);
    return 1;
  }
  while(!llm__is_end_mark(cursor->next)) {
    cursor = cursor->next;
  }
  lnk__add_after(cursor, lel);
  return 1;
}

struct lelement* lnk__remove_tail(struct link* lnk) {
  struct lelement* cursor = lnk->head;
  if (llm__is_end_mark(cursor)) return NULL;
  else if (llm__is_end_mark(cursor->next)) {
    cursor = lnk__remove_head(lnk);
    return cursor;
  }
  while(!llm__is_end_mark(cursor->next->next)) {
    cursor = cursor->next;
  }
  struct lelement* tail = lnk__remove_after(cursor);
  return tail;
}
