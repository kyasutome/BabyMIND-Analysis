// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME MCTrueDict
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
#include "MCTrue.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *MCTrue_Dictionary();
   static void MCTrue_TClassManip(TClass*);
   static void *new_MCTrue(void *p = 0);
   static void *newArray_MCTrue(Long_t size, void *p);
   static void delete_MCTrue(void *p);
   static void deleteArray_MCTrue(void *p);
   static void destruct_MCTrue(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MCTrue*)
   {
      ::MCTrue *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MCTrue));
      static ::ROOT::TGenericClassInfo 
         instance("MCTrue", "MCTrue.hpp", 9,
                  typeid(::MCTrue), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MCTrue_Dictionary, isa_proxy, 0,
                  sizeof(::MCTrue) );
      instance.SetNew(&new_MCTrue);
      instance.SetNewArray(&newArray_MCTrue);
      instance.SetDelete(&delete_MCTrue);
      instance.SetDeleteArray(&deleteArray_MCTrue);
      instance.SetDestructor(&destruct_MCTrue);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MCTrue*)
   {
      return GenerateInitInstanceLocal((::MCTrue*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::MCTrue*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MCTrue_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MCTrue*)0x0)->GetClass();
      MCTrue_TClassManip(theClass);
   return theClass;
   }

   static void MCTrue_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_MCTrue(void *p) {
      return  p ? new(p) ::MCTrue : new ::MCTrue;
   }
   static void *newArray_MCTrue(Long_t nElements, void *p) {
      return p ? new(p) ::MCTrue[nElements] : new ::MCTrue[nElements];
   }
   // Wrapper around operator delete
   static void delete_MCTrue(void *p) {
      delete ((::MCTrue*)p);
   }
   static void deleteArray_MCTrue(void *p) {
      delete [] ((::MCTrue*)p);
   }
   static void destruct_MCTrue(void *p) {
      typedef ::MCTrue current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MCTrue

namespace {
  void TriggerDictionaryInitialization_MCTrueDict_Impl() {
    static const char* headers[] = {
"MCTrue.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "MCTrueDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$MCTrue.hpp")))  MCTrue;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "MCTrueDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "MCTrue.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"MCTrue", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("MCTrueDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_MCTrueDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_MCTrueDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_MCTrueDict() {
  TriggerDictionaryInitialization_MCTrueDict_Impl();
}
