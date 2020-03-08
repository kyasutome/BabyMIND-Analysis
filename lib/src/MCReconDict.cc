// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME MCReconDict
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
#include "MCRecon.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *MCRecon_Dictionary();
   static void MCRecon_TClassManip(TClass*);
   static void *new_MCRecon(void *p = 0);
   static void *newArray_MCRecon(Long_t size, void *p);
   static void delete_MCRecon(void *p);
   static void deleteArray_MCRecon(void *p);
   static void destruct_MCRecon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MCRecon*)
   {
      ::MCRecon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MCRecon));
      static ::ROOT::TGenericClassInfo 
         instance("MCRecon", "MCRecon.hpp", 9,
                  typeid(::MCRecon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MCRecon_Dictionary, isa_proxy, 0,
                  sizeof(::MCRecon) );
      instance.SetNew(&new_MCRecon);
      instance.SetNewArray(&newArray_MCRecon);
      instance.SetDelete(&delete_MCRecon);
      instance.SetDeleteArray(&deleteArray_MCRecon);
      instance.SetDestructor(&destruct_MCRecon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MCRecon*)
   {
      return GenerateInitInstanceLocal((::MCRecon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::MCRecon*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MCRecon_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MCRecon*)0x0)->GetClass();
      MCRecon_TClassManip(theClass);
   return theClass;
   }

   static void MCRecon_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_MCRecon(void *p) {
      return  p ? new(p) ::MCRecon : new ::MCRecon;
   }
   static void *newArray_MCRecon(Long_t nElements, void *p) {
      return p ? new(p) ::MCRecon[nElements] : new ::MCRecon[nElements];
   }
   // Wrapper around operator delete
   static void delete_MCRecon(void *p) {
      delete ((::MCRecon*)p);
   }
   static void deleteArray_MCRecon(void *p) {
      delete [] ((::MCRecon*)p);
   }
   static void destruct_MCRecon(void *p) {
      typedef ::MCRecon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MCRecon

namespace {
  void TriggerDictionaryInitialization_MCReconDict_Impl() {
    static const char* headers[] = {
"MCRecon.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "MCReconDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$MCRecon.hpp")))  MCRecon;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "MCReconDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "MCRecon.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"MCRecon", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("MCReconDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_MCReconDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_MCReconDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_MCReconDict() {
  TriggerDictionaryInitialization_MCReconDict_Impl();
}
