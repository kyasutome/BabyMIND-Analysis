// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME BMHitClusterDict
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
#include "BMHitCluster.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *BMHitCluster_Dictionary();
   static void BMHitCluster_TClassManip(TClass*);
   static void *new_BMHitCluster(void *p = 0);
   static void *newArray_BMHitCluster(Long_t size, void *p);
   static void delete_BMHitCluster(void *p);
   static void deleteArray_BMHitCluster(void *p);
   static void destruct_BMHitCluster(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BMHitCluster*)
   {
      ::BMHitCluster *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BMHitCluster));
      static ::ROOT::TGenericClassInfo 
         instance("BMHitCluster", "BMHitCluster.hpp", 9,
                  typeid(::BMHitCluster), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &BMHitCluster_Dictionary, isa_proxy, 0,
                  sizeof(::BMHitCluster) );
      instance.SetNew(&new_BMHitCluster);
      instance.SetNewArray(&newArray_BMHitCluster);
      instance.SetDelete(&delete_BMHitCluster);
      instance.SetDeleteArray(&deleteArray_BMHitCluster);
      instance.SetDestructor(&destruct_BMHitCluster);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BMHitCluster*)
   {
      return GenerateInitInstanceLocal((::BMHitCluster*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::BMHitCluster*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *BMHitCluster_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::BMHitCluster*)0x0)->GetClass();
      BMHitCluster_TClassManip(theClass);
   return theClass;
   }

   static void BMHitCluster_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_BMHitCluster(void *p) {
      return  p ? new(p) ::BMHitCluster : new ::BMHitCluster;
   }
   static void *newArray_BMHitCluster(Long_t nElements, void *p) {
      return p ? new(p) ::BMHitCluster[nElements] : new ::BMHitCluster[nElements];
   }
   // Wrapper around operator delete
   static void delete_BMHitCluster(void *p) {
      delete ((::BMHitCluster*)p);
   }
   static void deleteArray_BMHitCluster(void *p) {
      delete [] ((::BMHitCluster*)p);
   }
   static void destruct_BMHitCluster(void *p) {
      typedef ::BMHitCluster current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BMHitCluster

namespace {
  void TriggerDictionaryInitialization_BMHitClusterDict_Impl() {
    static const char* headers[] = {
"BMHitCluster.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "BMHitClusterDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$BMHitCluster.hpp")))  BMHitCluster;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "BMHitClusterDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "BMHitCluster.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"BMHitCluster", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("BMHitClusterDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_BMHitClusterDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_BMHitClusterDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_BMHitClusterDict() {
  TriggerDictionaryInitialization_BMHitClusterDict_Impl();
}
