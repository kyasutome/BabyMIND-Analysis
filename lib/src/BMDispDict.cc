// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME BMDispDict
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
#include "BMDisp.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *BMDisp_Dictionary();
   static void BMDisp_TClassManip(TClass*);
   static void *new_BMDisp(void *p = 0);
   static void *newArray_BMDisp(Long_t size, void *p);
   static void delete_BMDisp(void *p);
   static void deleteArray_BMDisp(void *p);
   static void destruct_BMDisp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BMDisp*)
   {
      ::BMDisp *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BMDisp));
      static ::ROOT::TGenericClassInfo 
         instance("BMDisp", "BMDisp.hpp", 9,
                  typeid(::BMDisp), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &BMDisp_Dictionary, isa_proxy, 0,
                  sizeof(::BMDisp) );
      instance.SetNew(&new_BMDisp);
      instance.SetNewArray(&newArray_BMDisp);
      instance.SetDelete(&delete_BMDisp);
      instance.SetDeleteArray(&deleteArray_BMDisp);
      instance.SetDestructor(&destruct_BMDisp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BMDisp*)
   {
      return GenerateInitInstanceLocal((::BMDisp*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::BMDisp*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *BMDisp_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::BMDisp*)0x0)->GetClass();
      BMDisp_TClassManip(theClass);
   return theClass;
   }

   static void BMDisp_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_BMDisp(void *p) {
      return  p ? new(p) ::BMDisp : new ::BMDisp;
   }
   static void *newArray_BMDisp(Long_t nElements, void *p) {
      return p ? new(p) ::BMDisp[nElements] : new ::BMDisp[nElements];
   }
   // Wrapper around operator delete
   static void delete_BMDisp(void *p) {
      delete ((::BMDisp*)p);
   }
   static void deleteArray_BMDisp(void *p) {
      delete [] ((::BMDisp*)p);
   }
   static void destruct_BMDisp(void *p) {
      typedef ::BMDisp current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BMDisp

namespace {
  void TriggerDictionaryInitialization_BMDispDict_Impl() {
    static const char* headers[] = {
"BMDisp.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "BMDispDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$BMDisp.hpp")))  BMDisp;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "BMDispDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "BMDisp.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"BMDisp", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("BMDispDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_BMDispDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_BMDispDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_BMDispDict() {
  TriggerDictionaryInitialization_BMDispDict_Impl();
}
