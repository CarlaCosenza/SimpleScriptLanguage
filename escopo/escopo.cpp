#include <stdio.h>
#include <stdlib.h>

#include "escopo.h"

Object int_        = { -1, NULL, KindScalarType};
PObject pInt       = &int_;

Object char_       = { -1, NULL, KindScalarType};
PObject pChar      = &char_;

Object bool_       = { -1, NULL, KindScalarType};
PObject pBool      = &bool_;

Object string_     = { -1, NULL, KindScalarType};
PObject pString    = &string_;

Object universal_  = { -1, NULL, KindScalarType};
PObject pUniversal = &universal_;


PObject symbol_table[MAX_NEST_LEVEL];
int symbol_table_level = 0;

int new_block() {
  symbol_table_level++;
  symbol_table[symbol_table_level] = NULL;
  return symbol_table_level;
}

int end_block() {
  return --symbol_table_level;
}

PObject define_symbol(int name) {
  PObject obj = (PObject) malloc(sizeof(Object));

  obj->name = name;
  obj->kind = KindUndefined;
  obj->next = symbol_table[symbol_table_level];
  symbol_table[symbol_table_level] = obj;

  return obj;
}

PObject search_symbol_in_scope(int name) {
  PObject obj = symbol_table[symbol_table_level];
  while (obj != NULL) {
    if (obj->name == name)
      return obj;
    obj = obj->next;
  }

  return obj;
}

PObject search_symbol_globally(int name) {
  PObject obj;

  for (int i = symbol_table_level; i >= 0; i--) {
    obj = symbol_table[i];

    while (obj != NULL) {
      if (obj->name == name)
        return obj;
      obj = obj->next;
    }
  }

  return obj;
}

int check_types(PObject t1, PObject t2)
{
  /**/ if (t1 == t2) return 1;
  else if (t1 == pUniversal || t2 == pUniversal) return 1;
  else if (t1->kind == KindUniversal || t2->kind == KindUniversal) return 1;
  else if(t1->kind == KindAliasType && t2->kind != KindAliasType){
    return check_types(t1->Alias.pBaseType,t2);
  }
  else if(t1->kind != KindAliasType && t2->kind == KindAliasType){
    return check_types(t1,t2->Alias.pBaseType);
  }
  else if (t1->kind == t2->kind) {
    if (t1->kind == KindAliasType) {
      return check_types(t1->Alias.pBaseType, t2->Alias.pBaseType);
    } else if (t1->kind == KindArrayType) {
      if (t1->Array.nNumElems == t2->Array.nNumElems) {
        return check_types(t1->Array.pElemType, t2->Array.pElemType);
      }
    } else if (t1->kind == KindStructType) {
      PObject f1 = t1->Struct.pFields;
      PObject f2 = t2->Struct.pFields;
      while (f1 != NULL && f2 != NULL) {
        if (!check_types(f1->Field.pType, f2->Field.pType))
          return 0;
      }
      return (f1 == NULL && f2 == NULL);
    }
  }
  return 0;
}