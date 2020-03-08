// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME DetHitClusterDict
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
#include "DetHitCluster.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *DetHitCluster_Dictionary();
   static void DetHitCluster_TClassManip(TClass*);
   static void *new_DetHitCluster(void *p = 0);
   static void *newArray_DetHitCluster(Long_t size, void *p);
   static void delete_DetHitCluster(void *p);
   static void deleteArray_DetHitCluster(void *p);
   static void destruct_DetHitCluster(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DetHitCluster*)
   {
      ::DetHitCluster *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::DetHitCluster));
      static ::ROOT::TGenericClassInfo 
         instance("DetHitCluster", "DetHitCluster.hpp", 9,
                  typeid(::DetHitCluster), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &DetHitCluster_Dictionary, isa_proxy, 0,
                  sizeof(::DetHitCluster) );
      instance.SetNew(&new_DetHitCluster);
      instance.SetNewArray(&newArray_DetHitCluster);
      instance.SetDelete(&delete_DetHitCluster);
      instance.SetDeleteArray(&deleteArray_DetHitCluster);
      instance.SetDestructor(&destruct_DetHitCluster);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DetHitCluster*)
   {
      return GenerateInitInstanceLocal((::DetHitCluster*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::DetHitCluster*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *DetHitCluster_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::DetHitCluster*)0x0)->GetClass();
      DetHitCluster_TClassManip(theClass);
   return theClass;
   }

   static void DetHitCluster_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_DetHitCluster(void *p) {
      return  p ? new(p) ::DetHitCluster : new ::DetHitCluster;
   }
   static void *newArray_DetHitCluster(Long_t nElements, void *p) {
      return p ? new(p) ::DetHitCluster[nElements] : new ::DetHitCluster[nElements];
   }
   // Wrapper around operator delete
   static void delete_DetHitCluster(void *p) {
      delete ((::DetHitCluster*)p);
   }
   static void deleteArray_DetHitCluster(void *p) {
      delete [] ((::DetHitCluster*)p);
   }
   static void destruct_DetHitCluster(void *p) {
      typedef ::DetHitCluster current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DetHitCluster

namespace {
  void TriggerDictionaryInitialization_DetHitClusterDict_Impl() {
    static const char* headers[] = {
"DetHitCluster.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "DetHitClusterDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$DetHitCluster.hpp")))  DetHitCluster;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "DetHitClusterDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "DetHitCluster.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"DetHitCluster", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DetHitClusterDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DetHitClusterDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_DetHitClusterDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_DetHitClusterDict() {
  TriggerDictionaryInitialization_DetHitClusterDict_Impl();
}
