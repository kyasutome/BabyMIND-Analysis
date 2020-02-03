// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME WMDQDataDict
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
#include "WMDQData.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *WMDQData_Dictionary();
   static void WMDQData_TClassManip(TClass*);
   static void *new_WMDQData(void *p = 0);
   static void *newArray_WMDQData(Long_t size, void *p);
   static void delete_WMDQData(void *p);
   static void deleteArray_WMDQData(void *p);
   static void destruct_WMDQData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WMDQData*)
   {
      ::WMDQData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::WMDQData));
      static ::ROOT::TGenericClassInfo 
         instance("WMDQData", "WMDQData.hpp", 9,
                  typeid(::WMDQData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &WMDQData_Dictionary, isa_proxy, 0,
                  sizeof(::WMDQData) );
      instance.SetNew(&new_WMDQData);
      instance.SetNewArray(&newArray_WMDQData);
      instance.SetDelete(&delete_WMDQData);
      instance.SetDeleteArray(&deleteArray_WMDQData);
      instance.SetDestructor(&destruct_WMDQData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WMDQData*)
   {
      return GenerateInitInstanceLocal((::WMDQData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::WMDQData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *WMDQData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::WMDQData*)0x0)->GetClass();
      WMDQData_TClassManip(theClass);
   return theClass;
   }

   static void WMDQData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_WMDQData(void *p) {
      return  p ? new(p) ::WMDQData : new ::WMDQData;
   }
   static void *newArray_WMDQData(Long_t nElements, void *p) {
      return p ? new(p) ::WMDQData[nElements] : new ::WMDQData[nElements];
   }
   // Wrapper around operator delete
   static void delete_WMDQData(void *p) {
      delete ((::WMDQData*)p);
   }
   static void deleteArray_WMDQData(void *p) {
      delete [] ((::WMDQData*)p);
   }
   static void destruct_WMDQData(void *p) {
      typedef ::WMDQData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::WMDQData

namespace {
  void TriggerDictionaryInitialization_WMDQDataDict_Impl() {
    static const char* headers[] = {
"WMDQData.hpp",
0
    };
    static const char* includePaths[] = {
"/Users/kenji/local/root/root-6.18.02/built/include",
"/Users/kenji/Dropbox/wagasci/babymind/software/BabyMIND-Analysis/lib/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "WMDQDataDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$WMDQData.hpp")))  WMDQData;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "WMDQDataDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "WMDQData.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"WMDQData", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("WMDQDataDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_WMDQDataDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_WMDQDataDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_WMDQDataDict() {
  TriggerDictionaryInitialization_WMDQDataDict_Impl();
}
