// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME DetClustersDict
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
#include "DetClusters.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *DetClusters_Dictionary();
   static void DetClusters_TClassManip(TClass*);
   static void *new_DetClusters(void *p = 0);
   static void *newArray_DetClusters(Long_t size, void *p);
   static void delete_DetClusters(void *p);
   static void deleteArray_DetClusters(void *p);
   static void destruct_DetClusters(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DetClusters*)
   {
      ::DetClusters *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::DetClusters));
      static ::ROOT::TGenericClassInfo 
         instance("DetClusters", "DetClusters.hpp", 10,
                  typeid(::DetClusters), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &DetClusters_Dictionary, isa_proxy, 0,
                  sizeof(::DetClusters) );
      instance.SetNew(&new_DetClusters);
      instance.SetNewArray(&newArray_DetClusters);
      instance.SetDelete(&delete_DetClusters);
      instance.SetDeleteArray(&deleteArray_DetClusters);
      instance.SetDestructor(&destruct_DetClusters);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DetClusters*)
   {
      return GenerateInitInstanceLocal((::DetClusters*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::DetClusters*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *DetClusters_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::DetClusters*)0x0)->GetClass();
      DetClusters_TClassManip(theClass);
   return theClass;
   }

   static void DetClusters_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_DetClusters(void *p) {
      return  p ? new(p) ::DetClusters : new ::DetClusters;
   }
   static void *newArray_DetClusters(Long_t nElements, void *p) {
      return p ? new(p) ::DetClusters[nElements] : new ::DetClusters[nElements];
   }
   // Wrapper around operator delete
   static void delete_DetClusters(void *p) {
      delete ((::DetClusters*)p);
   }
   static void deleteArray_DetClusters(void *p) {
      delete [] ((::DetClusters*)p);
   }
   static void destruct_DetClusters(void *p) {
      typedef ::DetClusters current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DetClusters

namespace {
  void TriggerDictionaryInitialization_DetClustersDict_Impl() {
    static const char* headers[] = {
"DetClusters.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "DetClustersDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$DetClusters.hpp")))  DetClusters;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "DetClustersDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "DetClusters.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"DetClusters", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DetClustersDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DetClustersDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_DetClustersDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_DetClustersDict() {
  TriggerDictionaryInitialization_DetClustersDict_Impl();
}
