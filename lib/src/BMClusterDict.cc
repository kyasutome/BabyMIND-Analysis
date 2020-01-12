// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME BMClusterDict
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
#include "BMCluster.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *BMCluster_Dictionary();
   static void BMCluster_TClassManip(TClass*);
   static void *new_BMCluster(void *p = 0);
   static void *newArray_BMCluster(Long_t size, void *p);
   static void delete_BMCluster(void *p);
   static void deleteArray_BMCluster(void *p);
   static void destruct_BMCluster(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BMCluster*)
   {
      ::BMCluster *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BMCluster));
      static ::ROOT::TGenericClassInfo 
         instance("BMCluster", "BMCluster.hpp", 9,
                  typeid(::BMCluster), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &BMCluster_Dictionary, isa_proxy, 0,
                  sizeof(::BMCluster) );
      instance.SetNew(&new_BMCluster);
      instance.SetNewArray(&newArray_BMCluster);
      instance.SetDelete(&delete_BMCluster);
      instance.SetDeleteArray(&deleteArray_BMCluster);
      instance.SetDestructor(&destruct_BMCluster);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BMCluster*)
   {
      return GenerateInitInstanceLocal((::BMCluster*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::BMCluster*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *BMCluster_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::BMCluster*)0x0)->GetClass();
      BMCluster_TClassManip(theClass);
   return theClass;
   }

   static void BMCluster_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_BMCluster(void *p) {
      return  p ? new(p) ::BMCluster : new ::BMCluster;
   }
   static void *newArray_BMCluster(Long_t nElements, void *p) {
      return p ? new(p) ::BMCluster[nElements] : new ::BMCluster[nElements];
   }
   // Wrapper around operator delete
   static void delete_BMCluster(void *p) {
      delete ((::BMCluster*)p);
   }
   static void deleteArray_BMCluster(void *p) {
      delete [] ((::BMCluster*)p);
   }
   static void destruct_BMCluster(void *p) {
      typedef ::BMCluster current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BMCluster

namespace {
  void TriggerDictionaryInitialization_BMClusterDict_Impl() {
    static const char* headers[] = {
"BMCluster.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "BMClusterDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$BMCluster.hpp")))  BMCluster;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "BMClusterDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "BMCluster.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"BMCluster", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("BMClusterDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_BMClusterDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_BMClusterDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_BMClusterDict() {
  TriggerDictionaryInitialization_BMClusterDict_Impl();
}
