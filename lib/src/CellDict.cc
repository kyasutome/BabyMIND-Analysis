// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME CellDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "Cell.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *Cell_Dictionary();
   static void Cell_TClassManip(TClass*);
   static void *new_Cell(void *p = 0);
   static void *newArray_Cell(Long_t size, void *p);
   static void delete_Cell(void *p);
   static void deleteArray_Cell(void *p);
   static void destruct_Cell(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Cell*)
   {
      ::Cell *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Cell));
      static ::ROOT::TGenericClassInfo 
         instance("Cell", "Cell.hpp", 10,
                  typeid(::Cell), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Cell_Dictionary, isa_proxy, 0,
                  sizeof(::Cell) );
      instance.SetNew(&new_Cell);
      instance.SetNewArray(&newArray_Cell);
      instance.SetDelete(&delete_Cell);
      instance.SetDeleteArray(&deleteArray_Cell);
      instance.SetDestructor(&destruct_Cell);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Cell*)
   {
      return GenerateInitInstanceLocal((::Cell*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Cell*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Cell_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Cell*)0x0)->GetClass();
      Cell_TClassManip(theClass);
   return theClass;
   }

   static void Cell_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_Cell(void *p) {
      return  p ? new(p) ::Cell : new ::Cell;
   }
   static void *newArray_Cell(Long_t nElements, void *p) {
      return p ? new(p) ::Cell[nElements] : new ::Cell[nElements];
   }
   // Wrapper around operator delete
   static void delete_Cell(void *p) {
      delete ((::Cell*)p);
   }
   static void deleteArray_Cell(void *p) {
      delete [] ((::Cell*)p);
   }
   static void destruct_Cell(void *p) {
      typedef ::Cell current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Cell

namespace {
  void TriggerDictionaryInitialization_CellDict_Impl() {
    static const char* headers[] = {
"Cell.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "CellDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$Cell.hpp")))  Cell;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "CellDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "Cell.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Cell", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("CellDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_CellDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_CellDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_CellDict() {
  TriggerDictionaryInitialization_CellDict_Impl();
}
