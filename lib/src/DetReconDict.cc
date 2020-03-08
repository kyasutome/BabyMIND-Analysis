// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME DetReconDict
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
#include "DetRecon.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *DetRecon_Dictionary();
   static void DetRecon_TClassManip(TClass*);
   static void *new_DetRecon(void *p = 0);
   static void *newArray_DetRecon(Long_t size, void *p);
   static void delete_DetRecon(void *p);
   static void deleteArray_DetRecon(void *p);
   static void destruct_DetRecon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DetRecon*)
   {
      ::DetRecon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::DetRecon));
      static ::ROOT::TGenericClassInfo 
         instance("DetRecon", "DetRecon.hpp", 9,
                  typeid(::DetRecon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &DetRecon_Dictionary, isa_proxy, 0,
                  sizeof(::DetRecon) );
      instance.SetNew(&new_DetRecon);
      instance.SetNewArray(&newArray_DetRecon);
      instance.SetDelete(&delete_DetRecon);
      instance.SetDeleteArray(&deleteArray_DetRecon);
      instance.SetDestructor(&destruct_DetRecon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DetRecon*)
   {
      return GenerateInitInstanceLocal((::DetRecon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::DetRecon*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *DetRecon_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::DetRecon*)0x0)->GetClass();
      DetRecon_TClassManip(theClass);
   return theClass;
   }

   static void DetRecon_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_DetRecon(void *p) {
      return  p ? new(p) ::DetRecon : new ::DetRecon;
   }
   static void *newArray_DetRecon(Long_t nElements, void *p) {
      return p ? new(p) ::DetRecon[nElements] : new ::DetRecon[nElements];
   }
   // Wrapper around operator delete
   static void delete_DetRecon(void *p) {
      delete ((::DetRecon*)p);
   }
   static void deleteArray_DetRecon(void *p) {
      delete [] ((::DetRecon*)p);
   }
   static void destruct_DetRecon(void *p) {
      typedef ::DetRecon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DetRecon

namespace {
  void TriggerDictionaryInitialization_DetReconDict_Impl() {
    static const char* headers[] = {
"DetRecon.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "DetReconDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$DetRecon.hpp")))  DetRecon;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "DetReconDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "DetRecon.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"DetRecon", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DetReconDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DetReconDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_DetReconDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_DetReconDict() {
  TriggerDictionaryInitialization_DetReconDict_Impl();
}
