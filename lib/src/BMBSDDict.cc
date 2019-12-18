// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME BMBSDDict
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
#include "BMBSD.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *BMBSD_Dictionary();
   static void BMBSD_TClassManip(TClass*);
   static void *new_BMBSD(void *p = 0);
   static void *newArray_BMBSD(Long_t size, void *p);
   static void delete_BMBSD(void *p);
   static void deleteArray_BMBSD(void *p);
   static void destruct_BMBSD(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BMBSD*)
   {
      ::BMBSD *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BMBSD));
      static ::ROOT::TGenericClassInfo 
         instance("BMBSD", "BMBSD.hpp", 9,
                  typeid(::BMBSD), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &BMBSD_Dictionary, isa_proxy, 0,
                  sizeof(::BMBSD) );
      instance.SetNew(&new_BMBSD);
      instance.SetNewArray(&newArray_BMBSD);
      instance.SetDelete(&delete_BMBSD);
      instance.SetDeleteArray(&deleteArray_BMBSD);
      instance.SetDestructor(&destruct_BMBSD);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BMBSD*)
   {
      return GenerateInitInstanceLocal((::BMBSD*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::BMBSD*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *BMBSD_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::BMBSD*)0x0)->GetClass();
      BMBSD_TClassManip(theClass);
   return theClass;
   }

   static void BMBSD_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_BMBSD(void *p) {
      return  p ? new(p) ::BMBSD : new ::BMBSD;
   }
   static void *newArray_BMBSD(Long_t nElements, void *p) {
      return p ? new(p) ::BMBSD[nElements] : new ::BMBSD[nElements];
   }
   // Wrapper around operator delete
   static void delete_BMBSD(void *p) {
      delete ((::BMBSD*)p);
   }
   static void deleteArray_BMBSD(void *p) {
      delete [] ((::BMBSD*)p);
   }
   static void destruct_BMBSD(void *p) {
      typedef ::BMBSD current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BMBSD

namespace {
  void TriggerDictionaryInitialization_BMBSDDict_Impl() {
    static const char* headers[] = {
"BMBSD.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "BMBSDDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$BMBSD.hpp")))  BMBSD;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "BMBSDDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "BMBSD.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"BMBSD", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("BMBSDDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_BMBSDDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_BMBSDDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_BMBSDDict() {
  TriggerDictionaryInitialization_BMBSDDict_Impl();
}
