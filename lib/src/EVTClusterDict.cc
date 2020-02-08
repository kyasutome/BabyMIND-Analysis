// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME EVTClusterDict
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
#include "EVTCluster.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *EVTCluster_Dictionary();
   static void EVTCluster_TClassManip(TClass*);
   static void *new_EVTCluster(void *p = 0);
   static void *newArray_EVTCluster(Long_t size, void *p);
   static void delete_EVTCluster(void *p);
   static void deleteArray_EVTCluster(void *p);
   static void destruct_EVTCluster(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EVTCluster*)
   {
      ::EVTCluster *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::EVTCluster));
      static ::ROOT::TGenericClassInfo 
         instance("EVTCluster", "EVTCluster.hpp", 9,
                  typeid(::EVTCluster), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &EVTCluster_Dictionary, isa_proxy, 0,
                  sizeof(::EVTCluster) );
      instance.SetNew(&new_EVTCluster);
      instance.SetNewArray(&newArray_EVTCluster);
      instance.SetDelete(&delete_EVTCluster);
      instance.SetDeleteArray(&deleteArray_EVTCluster);
      instance.SetDestructor(&destruct_EVTCluster);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EVTCluster*)
   {
      return GenerateInitInstanceLocal((::EVTCluster*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EVTCluster*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *EVTCluster_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::EVTCluster*)0x0)->GetClass();
      EVTCluster_TClassManip(theClass);
   return theClass;
   }

   static void EVTCluster_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_EVTCluster(void *p) {
      return  p ? new(p) ::EVTCluster : new ::EVTCluster;
   }
   static void *newArray_EVTCluster(Long_t nElements, void *p) {
      return p ? new(p) ::EVTCluster[nElements] : new ::EVTCluster[nElements];
   }
   // Wrapper around operator delete
   static void delete_EVTCluster(void *p) {
      delete ((::EVTCluster*)p);
   }
   static void deleteArray_EVTCluster(void *p) {
      delete [] ((::EVTCluster*)p);
   }
   static void destruct_EVTCluster(void *p) {
      typedef ::EVTCluster current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EVTCluster

namespace {
  void TriggerDictionaryInitialization_EVTClusterDict_Impl() {
    static const char* headers[] = {
"EVTCluster.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "EVTClusterDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$EVTCluster.hpp")))  EVTCluster;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "EVTClusterDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "EVTCluster.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"EVTCluster", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("EVTClusterDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_EVTClusterDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_EVTClusterDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_EVTClusterDict() {
  TriggerDictionaryInitialization_EVTClusterDict_Impl();
}
