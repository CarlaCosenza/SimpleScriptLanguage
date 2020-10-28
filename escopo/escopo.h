#ifndef escopo 
#define escopo

#define MAX_NEST_LEVEL 64

#define IS_TYPE_KIND(k) ((k) == KindArrayType  || \
                         (k) == KindStructType || \
                         (k) == KindAliasType  || \
                         (k) == KindScalarType)

typedef enum Tipos{
	KindVar,
	KindParam,
	KindFunction,
	KindField,

	KindArrayType,
	KindStructType,
	KindAliasType,
	KindScalarType,

	KindUniversal,

	KindUndefined = -1
} Tipos;


typedef struct Object {
  int name;
  struct Object* next;

  Tipos kind;

  union {
    struct {
        struct Object *pType;
        int nIndex;
        int nSize;
    } Var, Param, Field;
    struct {
        struct Object *pRetType;
        struct Object *pParams;
        int nIndex;
        int nParams;
        int nVars;
    } Function;
    struct {
        struct Object *pElemType; int nNumElems;
        int nSize;
    } Array;
    struct {
        struct Object *pFields;
        int nSize;
    } Struct;
    struct {
        struct Object *pBaseType;
        int nSize;
    } Alias,Type;
  };
} Object, * PObject;

extern PObject symbol_table[MAX_NEST_LEVEL];
extern int symbol_table_level;

extern Object int_;
extern PObject pInt;

extern Object char_;
extern PObject pChar;

extern Object bool_;
extern PObject pBool;

extern Object string_;
extern PObject pString;

extern Object universal_;
extern PObject pUniversal;

int new_block();
int end_block();

PObject define_symbol(int name);
PObject search_symbol_in_scope(int name);
PObject search_symbol_globally(int name);
int check_types(PObject t1, PObject t2);

#endif