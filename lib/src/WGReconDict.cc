// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME WGReconDict
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
#include "WGRecon.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *WGRecon_Dictionary();
   static void WGRecon_TClassManip(TClass*);
   static void *new_WGRecon(void *p = 0);
   static void *newArray_WGRecon(Long_t size, void *p);
   static void delete_WGRecon(void *p);
   static void deleteArray_WGRecon(void *p);
   static void destruct_WGRecon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WGRecon*)
   {
      ::WGRecon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::WGRecon));
      static ::ROOT::TGenericClassInfo 
         instance("WGRecon", "WGRecon.hpp", 9,
                  typeid(::WGRecon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &WGRecon_Dictionary, isa_proxy, 0,
                  sizeof(::WGRecon) );
      instance.SetNew(&new_WGRecon);
      instance.SetNewArray(&newArray_WGRecon);
      instance.SetDelete(&delete_WGRecon);
      instance.SetDeleteArray(&deleteArray_WGRecon);
      instance.SetDestructor(&destruct_WGRecon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WGRecon*)
   {
      return GenerateInitInstanceLocal((::WGRecon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::WGRecon*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *WGRecon_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::WGRecon*)0x0)->GetClass();
      WGRecon_TClassManip(theClass);
   return theClass;
   }

   static void WGRecon_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_WGRecon(void *p) {
      return  p ? new(p) ::WGRecon : new ::WGRecon;
   }
   static void *newArray_WGRecon(Long_t nElements, void *p) {
      return p ? new(p) ::WGRecon[nElements] : new ::WGRecon[nElements];
   }
   // Wrapper around operator delete
   static void delete_WGRecon(void *p) {
      delete ((::WGRecon*)p);
   }
   static void deleteArray_WGRecon(void *p) {
      delete [] ((::WGRecon*)p);
   }
   static void destruct_WGRecon(void *p) {
      typedef ::WGRecon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WGRecon

namespace {
  void TriggerDictionaryInitialization_WGReconDict_Impl() {
    static const char* headers[] = {
"WGRecon.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "WGReconDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$WGRecon.hpp")))  WGRecon;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "WGReconDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "WGRecon.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"WGRecon", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("WGReconDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_WGReconDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_WGReconDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_WGReconDict() {
  TriggerDictionaryInitialization_WGReconDict_Impl();
}
