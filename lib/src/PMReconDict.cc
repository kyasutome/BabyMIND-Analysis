// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME PMReconDict
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
#include "PMRecon.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *PMRecon_Dictionary();
   static void PMRecon_TClassManip(TClass*);
   static void *new_PMRecon(void *p = 0);
   static void *newArray_PMRecon(Long_t size, void *p);
   static void delete_PMRecon(void *p);
   static void deleteArray_PMRecon(void *p);
   static void destruct_PMRecon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PMRecon*)
   {
      ::PMRecon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::PMRecon));
      static ::ROOT::TGenericClassInfo 
         instance("PMRecon", "PMRecon.hpp", 9,
                  typeid(::PMRecon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &PMRecon_Dictionary, isa_proxy, 0,
                  sizeof(::PMRecon) );
      instance.SetNew(&new_PMRecon);
      instance.SetNewArray(&newArray_PMRecon);
      instance.SetDelete(&delete_PMRecon);
      instance.SetDeleteArray(&deleteArray_PMRecon);
      instance.SetDestructor(&destruct_PMRecon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PMRecon*)
   {
      return GenerateInitInstanceLocal((::PMRecon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PMRecon*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *PMRecon_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::PMRecon*)0x0)->GetClass();
      PMRecon_TClassManip(theClass);
   return theClass;
   }

   static void PMRecon_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_PMRecon(void *p) {
      return  p ? new(p) ::PMRecon : new ::PMRecon;
   }
   static void *newArray_PMRecon(Long_t nElements, void *p) {
      return p ? new(p) ::PMRecon[nElements] : new ::PMRecon[nElements];
   }
   // Wrapper around operator delete
   static void delete_PMRecon(void *p) {
      delete ((::PMRecon*)p);
   }
   static void deleteArray_PMRecon(void *p) {
      delete [] ((::PMRecon*)p);
   }
   static void destruct_PMRecon(void *p) {
      typedef ::PMRecon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PMRecon

namespace {
  void TriggerDictionaryInitialization_PMReconDict_Impl() {
    static const char* headers[] = {
"PMRecon.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "PMReconDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$PMRecon.hpp")))  PMRecon;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "PMReconDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "PMRecon.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"PMRecon", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("PMReconDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_PMReconDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_PMReconDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_PMReconDict() {
  TriggerDictionaryInitialization_PMReconDict_Impl();
}
