// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME BMBeaminfoDict
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
#include "BMBeaminfo.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *BMBeaminfo_Dictionary();
   static void BMBeaminfo_TClassManip(TClass*);
   static void *new_BMBeaminfo(void *p = 0);
   static void *newArray_BMBeaminfo(Long_t size, void *p);
   static void delete_BMBeaminfo(void *p);
   static void deleteArray_BMBeaminfo(void *p);
   static void destruct_BMBeaminfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BMBeaminfo*)
   {
      ::BMBeaminfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BMBeaminfo));
      static ::ROOT::TGenericClassInfo 
         instance("BMBeaminfo", "BMBeaminfo.hpp", 9,
                  typeid(::BMBeaminfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &BMBeaminfo_Dictionary, isa_proxy, 0,
                  sizeof(::BMBeaminfo) );
      instance.SetNew(&new_BMBeaminfo);
      instance.SetNewArray(&newArray_BMBeaminfo);
      instance.SetDelete(&delete_BMBeaminfo);
      instance.SetDeleteArray(&deleteArray_BMBeaminfo);
      instance.SetDestructor(&destruct_BMBeaminfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BMBeaminfo*)
   {
      return GenerateInitInstanceLocal((::BMBeaminfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::BMBeaminfo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *BMBeaminfo_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::BMBeaminfo*)0x0)->GetClass();
      BMBeaminfo_TClassManip(theClass);
   return theClass;
   }

   static void BMBeaminfo_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_BMBeaminfo(void *p) {
      return  p ? new(p) ::BMBeaminfo : new ::BMBeaminfo;
   }
   static void *newArray_BMBeaminfo(Long_t nElements, void *p) {
      return p ? new(p) ::BMBeaminfo[nElements] : new ::BMBeaminfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_BMBeaminfo(void *p) {
      delete ((::BMBeaminfo*)p);
   }
   static void deleteArray_BMBeaminfo(void *p) {
      delete [] ((::BMBeaminfo*)p);
   }
   static void destruct_BMBeaminfo(void *p) {
      typedef ::BMBeaminfo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BMBeaminfo

namespace {
  void TriggerDictionaryInitialization_BMBeaminfoDict_Impl() {
    static const char* headers[] = {
"BMBeaminfo.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "BMBeaminfoDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$BMBeaminfo.hpp")))  BMBeaminfo;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "BMBeaminfoDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "BMBeaminfo.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"BMBeaminfo", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("BMBeaminfoDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_BMBeaminfoDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_BMBeaminfoDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_BMBeaminfoDict() {
  TriggerDictionaryInitialization_BMBeaminfoDict_Impl();
}
