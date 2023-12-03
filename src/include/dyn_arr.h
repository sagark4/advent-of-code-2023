#ifndef DYN_ARR_H
#define DYN_ARR_H
#include <stdlib.h>

#define INITIAL_CAPACITY 8

#define INIT_DYN_ARR_FUN(init_fun_name, struct_name, unit_type, cvar, capvar, storvar) \
  void init_fun_name(struct_name *ptr) {                                               \
    ptr->cvar = 0;                                                                     \
    ptr->capvar = INITIAL_CAPACITY;                                                    \
    void *result = malloc(INITIAL_CAPACITY * sizeof(unit_type));                       \
    if (result == NULL) exit(1);                                                       \
    ptr->storvar = ((unit_type *)result);                                              \
  }

#define PUSH_DYN_ARR_FUN(push_fun_name, struct_name, unit_type, cvar, capvar, storvar)          \
  void push_fun_name(struct_name *ptr, unit_type elt) {                                         \
    if (ptr->cvar == ptr->capvar) {                                                             \
      ptr->storvar = ((unit_type *)realloc(ptr->storvar, 2 * ptr->capvar * sizeof(unit_type))); \
      ptr->capvar *= 2;                                                                         \
    }                                                                                           \
    *(ptr->storvar + ptr->cvar) = elt;                                                          \
    ptr->cvar++;                                                                                \
  }

#define POP_DYN_ARR_FUN(pop_fun_name, struct_name, unit_type, cvar, capvar, storvar) \
  unit_type pop_fun_name(struct_name *ptr) { return *(ptr->storvar + --ptr->cvar); }

#define DELETE_DYN_ARR_FUN(delete_fun_name, struct_name, unit_type, cvar, capvar, storvar) \
  void delete_fun_name(struct_name *ptr) {                                                 \
    ptr->cvar = 0;                                                                         \
    ptr->capvar = 0;                                                                       \
    free(ptr->storvar);                                                                    \
    ptr->storvar = NULL;                                                                   \
  }

#define CREATE_DYN_ARR_FUNCS_STD_NAMES(struct_name, unit_type, cvar, capvar, storvar)        \
  INIT_DYN_ARR_FUN(init_dynarr_##struct_name, struct_name, unit_type, cvar, capvar, storvar) \
  PUSH_DYN_ARR_FUN(push_##struct_name, struct_name, unit_type, cvar, capvar, storvar)        \
  POP_DYN_ARR_FUN(pop_##struct_name, struct_name, unit_type, cvar, capvar, storvar)          \
  DELETE_DYN_ARR_FUN(delete_dynarr_##struct_name, struct_name, unit_type, cvar, capvar, storvar)

#endif  // DYN_ARR_H
