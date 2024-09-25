﻿/*
 * Tencent is pleased to support the open source community by making Puerts available.
 * Copyright (C) 2020 THL A29 Limited, a Tencent company.  All rights reserved.
 * Puerts is licensed under the BSD 3-Clause License, except for the third-party components listed in the file 'LICENSE' which may
 * be subject to their corresponding license terms. This file is subject to the terms and conditions defined in file 'LICENSE',
 * which is part of this source code package.
 */

#pragma once
namespace puerts
{
struct PObjectRefInfo
{
    pesapi_env_ref EnvRef;
    pesapi_value_ref ValueRef;
    void* ExtraData;
    std::weak_ptr<int> EnvLifeCycleTracker; // TODO: 增加pesapi_env_ref有效性判断后去掉
};

#if defined(USE_OUTSIZE_UNITY)

typedef void (*MethodPointer)();
typedef void* (*ObjectAllocateFunc)(const void* type);
typedef void (*ValueTypeDeallocateFunc)(void* ptr);
typedef void* (*DelegateAllocateFunc)(const void* type, MethodPointer methodPointer, struct PObjectRefInfo** outDelegateInfo);
typedef void MethodType;
typedef bool (*WrapFuncPtr)(MethodType* method, MethodPointer methodPointer, const v8::FunctionCallbackInfo<v8::Value>& info, bool checkArgument, struct WrapData* wrapData);
typedef v8::FunctionCallback FunctionCallbackFunc;

typedef void (*FieldWrapFuncPtr)(const v8::FunctionCallbackInfo<v8::Value>& info, void* fieldInfo, size_t offset, void* typeInfo);

typedef void TypeIdType;

typedef void (*SetNativePtrFunc)(v8::Object* obj, void* ptr, void* type_id);

typedef v8::Value* (*CreateJSArrayBufferFunc)(v8::Context* env, void* buffer, size_t length);

typedef void (*UnrefJsObjectFunc)(struct PObjectRefInfo* objectInfo);

typedef const void* (*CSharpTypeToTypeIdFunc)(const void *type);

typedef v8::Value* (*GetModuleExecutorFunc)(v8::Context* env);

#else

#define MethodPointer Il2CppMethodPointer

typedef void* (*ObjectAllocateFunc)(Il2CppClass *klass);
typedef void (*ValueTypeDeallocateFunc)(void* ptr);
typedef void* (*DelegateAllocateFunc)(Il2CppClass* klass, MethodPointer methodPointer, struct PObjectRefInfo** outDelegateInfo);
typedef MethodInfo MethodType;
typedef bool (*WrapFuncPtr)(MethodType* method, Il2CppMethodPointer methodPointer, pesapi_callback_info info, bool checkArgument, struct WrapData* wrapData);
typedef pesapi_callback FunctionCallbackFunc;
typedef pesapi_constructor InitializeFunc;
typedef void (*FieldWrapFuncPtr)(pesapi_callback_info info, FieldInfo* field, size_t offset, Il2CppClass* fieldType);

typedef Il2CppClass TypeIdType;

typedef void (*SetNativePtrFunc)(pesapi_value obj, void* ptr, const void* type_id);

typedef pesapi_value (*CreateJSArrayBufferFunc)(pesapi_env env, void* buffer, size_t length);

typedef void (*UnrefJsObjectFunc)(struct PObjectRefInfo* delegateInfo);

typedef const void* (*CSharpTypeToTypeIdFunc)(Il2CppObject *type);

typedef pesapi_value (*GetModuleExecutorFunc)(pesapi_env env);

#endif

typedef void* (*FunctionToDelegateFunc)(pesapi_env env, pesapi_value pvalue, const void* TypeId, bool throwIfFail);

typedef void* (*GetRuntimeObjectFromPersistentObjectFunc)(pesapi_env env, pesapi_value pvalue);

typedef void (*SetRuntimeObjectToPersistentObjectFunc)(pesapi_env env, pesapi_value pvalue, void* runtimeObject);

typedef WrapFuncPtr (*FindWrapFuncFunc)(const char* signature);

typedef struct FieldWrapFuncInfo * (*FindFieldWrapFuncInfoFunc)(const char* signature);

typedef MethodPointer (*FindBridgeFuncFunc)(const char* signature);

typedef void(*LogCallbackFunc)(const char* value);

typedef void (*SetExtraDataFunc)(pesapi_env env, struct PObjectRefInfo* objectInfo);

struct WrapData 
{
    WrapFuncPtr Wrap;
    MethodType* Method;
    MethodPointer MethodPointer;
    bool IsStatic;
    bool IsExtensionMethod;
    bool HasParamArray;
    int OptionalNum;
    TypeIdType* TypeInfos[0];
};

struct JsClassInfoHeader
{
    const void* TypeId;
    const void* SuperTypeId;
    TypeIdType* Class;
    bool IsValueType;
    MethodPointer DelegateBridge;
    WrapData** CtorWrapDatas;
};

struct UnityExports
{
    //.cpp api
    ObjectAllocateFunc ObjectAllocate = nullptr;
    DelegateAllocateFunc DelegateAllocate = nullptr;
    ValueTypeDeallocateFunc ValueTypeDeallocate = nullptr;
    FunctionCallbackFunc MethodCallback = nullptr;
    InitializeFunc ConstructorCallback = nullptr;
    InitializeFunc DelegateConstructorCallback = nullptr;
    CSharpTypeToTypeIdFunc CSharpTypeToTypeId = nullptr;
    WrapFuncPtr ReflectionWrapper = nullptr;
    FieldWrapFuncPtr ReflectionGetFieldWrapper = nullptr;
    FieldWrapFuncPtr ReflectionSetFieldWrapper = nullptr;

    FindWrapFuncFunc FindWrapFunc = nullptr;
    FindFieldWrapFuncInfoFunc FindFieldWrapFuncInfo = nullptr;
    FindBridgeFuncFunc FindBridgeFunc = nullptr;

    //plugin api
    
    SetNativePtrFunc SetNativePtr = nullptr;
    CreateJSArrayBufferFunc CreateJSArrayBuffer = nullptr;
    UnrefJsObjectFunc UnrefJsObject = nullptr;
    FunctionToDelegateFunc FunctionToDelegate = nullptr;

    GetModuleExecutorFunc GetModuleExecutor = nullptr;

    GetRuntimeObjectFromPersistentObjectFunc GetRuntimeObjectFromPersistentObject = nullptr;
    SetRuntimeObjectToPersistentObjectFunc SetRuntimeObjectToPersistentObject = nullptr;
    
    SetExtraDataFunc SetExtraData = nullptr;
    
    LogCallbackFunc LogCallback = nullptr;
};

}