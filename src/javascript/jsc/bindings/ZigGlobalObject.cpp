
#include "ZigGlobalObject.h"

#include "helpers.h"

#include "JavaScriptCore/AggregateError.h"
#include "JavaScriptCore/BytecodeIndex.h"
#include "JavaScriptCore/CallFrameInlines.h"
#include "JavaScriptCore/ClassInfo.h"
#include "JavaScriptCore/CodeBlock.h"
#include "JavaScriptCore/CodeCache.h"
#include "JavaScriptCore/Completion.h"
#include "JavaScriptCore/Error.h"
#include "JavaScriptCore/ErrorInstance.h"
#include "JavaScriptCore/Exception.h"
#include "JavaScriptCore/ExceptionScope.h"
#include "JavaScriptCore/FunctionConstructor.h"
#include "JavaScriptCore/HashMapImpl.h"
#include "JavaScriptCore/HashMapImplInlines.h"
#include "JavaScriptCore/Heap.h"
#include "JavaScriptCore/Identifier.h"
#include "JavaScriptCore/InitializeThreading.h"
#include "JavaScriptCore/IteratorOperations.h"
#include "JavaScriptCore/JSArray.h"

#include "JavaScriptCore/JSCallbackConstructor.h"
#include "JavaScriptCore/JSCallbackObject.h"
#include "JavaScriptCore/JSCast.h"
#include "JavaScriptCore/JSClassRef.h"
#include "JavaScriptCore/JSMicrotask.h"
#include "ZigConsoleClient.h"
// #include "JavaScriptCore/JSContextInternal.h"
#include "JavaScriptCore/CatchScope.h"
#include "JavaScriptCore/DeferredWorkTimer.h"
#include "JavaScriptCore/JSInternalPromise.h"
#include "JavaScriptCore/JSLock.h"
#include "JavaScriptCore/JSMap.h"
#include "JavaScriptCore/JSModuleLoader.h"
#include "JavaScriptCore/JSModuleRecord.h"
#include "JavaScriptCore/JSNativeStdFunction.h"
#include "JavaScriptCore/JSObject.h"
#include "JavaScriptCore/JSPromise.h"
#include "JavaScriptCore/JSSet.h"
#include "JavaScriptCore/JSSourceCode.h"
#include "JavaScriptCore/JSString.h"
#include "JavaScriptCore/JSValueInternal.h"
#include "JavaScriptCore/JSVirtualMachineInternal.h"
#include "JavaScriptCore/ObjectConstructor.h"
#include "JavaScriptCore/OptionsList.h"
#include "JavaScriptCore/ParserError.h"
#include "JavaScriptCore/ScriptExecutable.h"
#include "JavaScriptCore/SourceOrigin.h"
#include "JavaScriptCore/StackFrame.h"
#include "JavaScriptCore/StackVisitor.h"
#include "JavaScriptCore/VM.h"
#include "JavaScriptCore/VMEntryScope.h"
#include "JavaScriptCore/WasmFaultSignalHandler.h"
#include "wtf/Gigacage.h"
#include "wtf/URL.h"
#include "wtf/text/ExternalStringImpl.h"
#include "wtf/text/StringCommon.h"
#include "wtf/text/StringImpl.h"
#include "wtf/text/StringView.h"
#include "wtf/text/WTFString.h"

#include "wtf/text/Base64.h"
// #include "JavaScriptCore/CachedType.h"
#include "JavaScriptCore/JSCallbackObject.h"
#include "JavaScriptCore/JSClassRef.h"

#include "BunClientData.h"

#include "ZigSourceProvider.h"

#include "JSDOMURL.h"
#include "JSURLSearchParams.h"
#include "JSDOMException.h"
#include "JSEventTarget.h"
#include "EventTargetConcrete.h"
#include "JSAbortSignal.h"
#include "JSCustomEvent.h"
#include "JSAbortController.h"
#include "JSEvent.h"
#include "JSErrorEvent.h"
#include "JSFetchHeaders.h"

#include "Process.h"

#include "JavaScriptCore/RemoteInspectorServer.h"
#include "WebCoreJSBuiltinInternals.h"
#include "JSBuffer.h"
#include "JSFFIFunction.h"
#include "JavaScriptCore/InternalFunction.h"
#include "JavaScriptCore/LazyClassStructure.h"
#include "JavaScriptCore/LazyClassStructureInlines.h"
#include "JavaScriptCore/FunctionPrototype.h"
#include "napi.h"
#include "JSZigGlobalObjectBuiltins.h"
#include "JSSQLStatement.h"
#include "ReadableStreamBuiltins.h"

using JSGlobalObject = JSC::JSGlobalObject;
using Exception = JSC::Exception;
using JSValue = JSC::JSValue;
using JSString = JSC::JSString;
using JSModuleLoader = JSC::JSModuleLoader;
using JSModuleRecord = JSC::JSModuleRecord;
using Identifier = JSC::Identifier;
using SourceOrigin = JSC::SourceOrigin;
using JSObject = JSC::JSObject;
using JSNonFinalObject = JSC::JSNonFinalObject;
namespace JSCastingHelpers = JSC::JSCastingHelpers;
using JSBuffer = WebCore::JSBuffer;
#include <dlfcn.h>

#include "IDLTypes.h"

#include "JSAbortAlgorithm.h"
#include "JSDOMAttribute.h"
#include "JSByteLengthQueuingStrategy.h"
#include "JSCountQueuingStrategy.h"
#include "JSReadableByteStreamController.h"
#include "JSReadableStream.h"
#include "JSReadableStreamBYOBReader.h"
#include "JSReadableStreamBYOBRequest.h"
#include "JSReadableStreamDefaultController.h"
#include "JSReadableStreamDefaultReader.h"
#include "JSTransformStream.h"
#include "JSTransformStreamDefaultController.h"
#include "JSWritableStream.h"
#include "JSWritableStreamDefaultController.h"
#include "JSWritableStreamDefaultWriter.h"
#include "JavaScriptCore/BuiltinNames.h"
#include "JSTextEncoder.h"
#include "StructuredClone.h"

// #include <iostream>

static bool has_loaded_jsc = false;

extern "C" void JSCInitialize()
{
    if (has_loaded_jsc)
        return;
    has_loaded_jsc = true;
    JSC::Config::enableRestrictedOptions();

    std::set_terminate([]() { Zig__GlobalObject__onCrash(); });
    WTF::initializeMainThread();
    JSC::initialize();
    {
        JSC::Options::AllowUnfinalizedAccessScope scope;

        JSC::Options::useConcurrentJIT() = true;
        JSC::Options::useSigillCrashAnalyzer() = true;
        JSC::Options::useWebAssembly() = true;
        JSC::Options::useSourceProviderCache() = true;
        // JSC::Options::useUnlinkedCodeBlockJettisoning() = false;
        JSC::Options::exposeInternalModuleLoader() = true;
        JSC::Options::useSharedArrayBuffer() = true;
        JSC::Options::useJIT() = true;
        JSC::Options::useBBQJIT() = true;

        JSC::Options::ensureOptionsAreCoherent();
    }
}

extern "C" JSC__JSGlobalObject* Zig__GlobalObject__create(JSClassRef* globalObjectClass, int count,
    void* console_client)
{
    auto heapSize = JSC::HeapType::Large;

    JSC::VM& vm = JSC::VM::create(heapSize).leakRef();
    JSC::Wasm::enableFastMemory();

    // This must happen before JSVMClientData::create
    vm.heap.acquireAccess();

    WebCore::JSVMClientData::create(&vm);

    JSC::JSLockHolder locker(vm);
    Zig::GlobalObject* globalObject = Zig::GlobalObject::create(vm, Zig::GlobalObject::createStructure(vm, JSC::JSGlobalObject::create(vm, JSC::JSGlobalObject::createStructure(vm, JSC::jsNull())), JSC::jsNull()));
    globalObject->setConsole(globalObject);

    if (count > 0) {
        globalObject->installAPIGlobals(globalObjectClass, count, vm);
    }

    JSC::gcProtect(globalObject);

    vm.ref();
    return globalObject;
}

extern "C" void* Zig__GlobalObject__getModuleRegistryMap(JSC__JSGlobalObject* arg0)
{
    if (JSC::JSObject* loader = JSC::jsDynamicCast<JSC::JSObject*>(arg0->moduleLoader())) {
        JSC::JSMap* map = JSC::jsDynamicCast<JSC::JSMap*>(
            loader->getDirect(arg0->vm(), JSC::Identifier::fromString(arg0->vm(), "registry"_s)));

        JSC::JSMap* cloned = map->clone(arg0, arg0->vm(), arg0->mapStructure());
        JSC::gcProtect(cloned);

        return cloned;
    }

    return nullptr;
}

extern "C" bool Zig__GlobalObject__resetModuleRegistryMap(JSC__JSGlobalObject* globalObject,
    void* map_ptr)
{
    if (map_ptr == nullptr)
        return false;
    JSC::JSMap* map = reinterpret_cast<JSC::JSMap*>(map_ptr);
    JSC::VM& vm = globalObject->vm();
    if (JSC::JSObject* obj = JSC::jsDynamicCast<JSC::JSObject*>(globalObject->moduleLoader())) {
        auto identifier = JSC::Identifier::fromString(globalObject->vm(), "registry"_s);

        if (JSC::JSMap* oldMap = JSC::jsDynamicCast<JSC::JSMap*>(
                obj->getDirect(globalObject->vm(), identifier))) {

            vm.finalizeSynchronousJSExecution();

            obj->putDirect(globalObject->vm(), identifier,
                map->clone(globalObject, globalObject->vm(), globalObject->mapStructure()));

            // vm.deleteAllLinkedCode(JSC::DeleteAllCodeEffort::DeleteAllCodeIfNotCollecting);
            // JSC::Heap::PreventCollectionScope(vm.heap);
            oldMap->clear(globalObject);
            JSC::gcUnprotect(oldMap);
            // vm.heap.completeAllJITPlans();

            // vm.forEachScriptExecutableSpace([&](auto &spaceAndSet) {
            //   JSC::HeapIterationScope heapIterationScope(vm.heap);
            //   auto &set = spaceAndSet.set;
            //   set.forEachLiveCell([&](JSC::HeapCell *cell, JSC::HeapCell::Kind) {
            //     if (JSC::ModuleProgramExecutable *executable =
            //           JSC::jsDynamicCast<JSC::ModuleProgramExecutable *>(cell)) {
            //       executable->clearCode(set);
            //     }
            //   });
            // });

            // globalObject->vm().heap.deleteAllUnlinkedCodeBlocks(
            //   JSC::DeleteAllCodeEffort::PreventCollectionAndDeleteAllCode);
        }
    }
    // map
    // }
    return true;
}

namespace Zig {

using namespace WebCore;

const JSC::ClassInfo GlobalObject::s_info = { "GlobalObject"_s, &Base::s_info, nullptr, nullptr,
    CREATE_METHOD_TABLE(GlobalObject) };

extern "C" JSClassRef* Zig__getAPIGlobals(size_t* count);
extern "C" const JSC__JSValue* Zig__getAPIConstructors(size_t* count, JSC__JSGlobalObject*);

static JSGlobalObject* deriveShadowRealmGlobalObject(JSGlobalObject* globalObject)
{
    auto& vm = globalObject->vm();
    Zig::GlobalObject* shadow = Zig::GlobalObject::create(vm, Zig::GlobalObject::createStructure(vm, JSC::JSGlobalObject::create(vm, JSC::JSGlobalObject::createStructure(vm, JSC::jsNull())), JSC::jsNull()));
    shadow->setConsole(shadow);
    size_t count = 0;
    JSClassRef* globalObjectClass = Zig__getAPIGlobals(&count);

    shadow->setConsole(shadow);
    if (count > 0) {
        shadow->installAPIGlobals(globalObjectClass, count, vm);
    }

    return shadow;
}

extern "C" JSC__JSValue JSC__JSValue__makeWithNameAndPrototype(JSC__JSGlobalObject* globalObject, void* arg1, void* arg2, const ZigString* visibleInterfaceName)
{
    auto& vm = globalObject->vm();
    JSClassRef jsClass = reinterpret_cast<JSClassRef>(arg1);
    JSClassRef protoClass = reinterpret_cast<JSClassRef>(arg2);
    JSObjectRef objectRef = JSObjectMakeConstructor(reinterpret_cast<JSContextRef>(globalObject), protoClass, jsClass->callAsConstructor);
    JSObjectRef wrappedRef = JSObjectMake(reinterpret_cast<JSContextRef>(globalObject), jsClass, nullptr);
    JSC::JSObject* object = JSC::JSValue::decode(reinterpret_cast<JSC__JSValue>(objectRef)).getObject();
    JSC::JSObject* wrapped = JSC::JSValue::decode(reinterpret_cast<JSC__JSValue>(wrappedRef)).getObject();
    object->setPrototypeDirect(vm, wrapped);
    JSString* nameString = JSC::jsNontrivialString(vm, Zig::toString(*visibleInterfaceName));
    object->putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    object->putDirect(vm, vm.propertyNames->toStringTagSymbol,
        nameString, JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::ReadOnly);

    return JSC::JSValue::encode(JSC::JSValue(object));
}

const JSC::GlobalObjectMethodTable GlobalObject::s_globalObjectMethodTable = {
    &supportsRichSourceInfo,
    &shouldInterruptScript,
    &javaScriptRuntimeFlags,
    &queueMicrotaskToEventLoop, // queueTaskToEventLoop
    nullptr, // &shouldInterruptScriptBeforeTimeout,
    &moduleLoaderImportModule, // moduleLoaderImportModule
    &moduleLoaderResolve, // moduleLoaderResolve
    &moduleLoaderFetch, // moduleLoaderFetch
    &moduleLoaderCreateImportMetaProperties, // moduleLoaderCreateImportMetaProperties
    &moduleLoaderEvaluate, // moduleLoaderEvaluate
    &promiseRejectionTracker, // promiseRejectionTracker
    &reportUncaughtExceptionAtEventLoop,
    &currentScriptExecutionOwner,
    &scriptExecutionStatus,
    nullptr, // defaultLanguage
    nullptr, // compileStreaming
    nullptr, // instantiateStreaming
    nullptr,
    &Zig::deriveShadowRealmGlobalObject
};

GlobalObject::GlobalObject(JSC::VM& vm, JSC::Structure* structure)
    : JSC::JSGlobalObject(vm, structure, &s_globalObjectMethodTable)
    , m_constructors(makeUnique<WebCore::DOMConstructors>())
    , m_world(WebCore::DOMWrapperWorld::create(vm, WebCore::DOMWrapperWorld::Type::Normal))
    , m_worldIsNormal(true)
    , m_builtinInternalFunctions(vm)

{

    m_scriptExecutionContext = new WebCore::ScriptExecutionContext(&vm, this);
}

GlobalObject::~GlobalObject() = default;

void GlobalObject::destroy(JSCell* cell)
{
    static_cast<GlobalObject*>(cell)->GlobalObject::~GlobalObject();
}

WebCore::ScriptExecutionContext* GlobalObject::scriptExecutionContext()
{
    return m_scriptExecutionContext;
}

WebCore::ScriptExecutionContext* GlobalObject::scriptExecutionContext() const
{
    return m_scriptExecutionContext;
}

void GlobalObject::reportUncaughtExceptionAtEventLoop(JSGlobalObject* globalObject,
    JSC::Exception* exception)
{
    Zig__GlobalObject__reportUncaughtException(globalObject, exception);
}

void GlobalObject::promiseRejectionTracker(JSGlobalObject* obj, JSC::JSPromise* prom,
    JSC::JSPromiseRejectionOperation reject)
{
    Zig__GlobalObject__promiseRejectionTracker(
        obj, prom, reject == JSC::JSPromiseRejectionOperation::Reject ? 0 : 1);
}

static Zig::ConsoleClient* m_console;

void GlobalObject::setConsole(void* console)
{
    m_console = new Zig::ConsoleClient(console);
    this->setConsoleClient(m_console);
}

#pragma mark - Globals

JSC_DECLARE_CUSTOM_GETTER(JSBuffer_getter);

JSC_DEFINE_CUSTOM_GETTER(JSBuffer_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSBuffer::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSTextEncoder_getter);

JSC_DEFINE_CUSTOM_GETTER(JSTextEncoder_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSTextEncoder::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSDOMURL_getter);

JSC_DEFINE_CUSTOM_GETTER(JSDOMURL_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSDOMURL::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSURLSearchParams_getter);

JSC_DEFINE_CUSTOM_GETTER(JSURLSearchParams_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSURLSearchParams::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSErrorEvent_getter);

JSC_DEFINE_CUSTOM_GETTER(JSErrorEvent_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSErrorEvent::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSEvent_getter);

JSC_DEFINE_CUSTOM_GETTER(JSEvent_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSEvent::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSCustomEvent_getter);

JSC_DEFINE_CUSTOM_GETTER(JSCustomEvent_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSCustomEvent::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSFetchHeaders_getter);

JSC_DEFINE_CUSTOM_GETTER(JSFetchHeaders_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSFetchHeaders::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSEventTarget_getter);

JSC_DEFINE_CUSTOM_GETTER(JSEventTarget_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSEventTarget::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSDOMAbortController_getter);

JSC_DEFINE_CUSTOM_GETTER(JSDOMAbortController_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSAbortController::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSDOMAbortSignal_getter);

JSC_DEFINE_CUSTOM_GETTER(JSDOMAbortSignal_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSAbortSignal::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

JSC_DECLARE_CUSTOM_GETTER(JSDOMException_getter);

JSC_DEFINE_CUSTOM_GETTER(JSDOMException_getter,
    (JSC::JSGlobalObject * lexicalGlobalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* thisObject = JSC::jsCast<Zig::GlobalObject*>(lexicalGlobalObject);
    return JSC::JSValue::encode(
        WebCore::JSDOMException::getConstructor(JSC::getVM(lexicalGlobalObject), thisObject));
}

static JSC_DECLARE_CUSTOM_SETTER(property_lazyProcessSetter);
static JSC_DECLARE_CUSTOM_GETTER(property_lazyProcessGetter);

JSC_DEFINE_CUSTOM_SETTER(property_lazyProcessSetter,
    (JSC::JSGlobalObject * globalObject, JSC::EncodedJSValue thisValue,
        JSC::EncodedJSValue value, JSC::PropertyName))
{
    return false;
}

static JSClassRef dot_env_class_ref;
JSC_DEFINE_CUSTOM_GETTER(property_lazyProcessGetter,
    (JSC::JSGlobalObject * _globalObject, JSC::EncodedJSValue thisValue,
        JSC::PropertyName))
{
    Zig::GlobalObject* globalObject = reinterpret_cast<Zig::GlobalObject*>(_globalObject);

    JSC::VM& vm = globalObject->vm();
    auto clientData = WebCore::clientData(vm);
    JSC::JSValue processPrivate = globalObject->getIfPropertyExists(globalObject, clientData->builtinNames().processPrivateName());
    if (LIKELY(processPrivate)) {
        return JSC::JSValue::encode(processPrivate);
    }

    auto* process = Zig::Process::create(
        vm, Zig::Process::createStructure(vm, globalObject, globalObject->objectPrototype()));

    {
        auto jsClass = dot_env_class_ref;

        JSC::JSCallbackObject<JSNonFinalObject>* object = JSC::JSCallbackObject<JSNonFinalObject>::create(
            globalObject, globalObject->callbackObjectStructure(), jsClass, nullptr);
        if (JSObject* prototype = jsClass->prototype(globalObject))
            object->setPrototypeDirect(vm, prototype);

        process->putDirect(vm, JSC::Identifier::fromString(vm, "env"_s),
            JSC::JSValue(object),
            JSC::PropertyAttribute::DontDelete | 0);

        JSC::gcProtect(JSC::JSValue(object));
    }
    globalObject->putDirect(vm, clientData->builtinNames().processPrivateName(), JSC::JSValue(process), 0);
    JSC::gcProtect(JSC::JSValue(process));

    return JSC::JSValue::encode(JSC::JSValue(process));
}

static JSC_DECLARE_HOST_FUNCTION(functionQueueMicrotask);

static JSC_DEFINE_HOST_FUNCTION(functionQueueMicrotask,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    JSC::VM& vm = globalObject->vm();

    if (callFrame->argumentCount() == 0) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "queueMicrotask requires 1 argument (a function)"_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    JSC::JSValue job = callFrame->argument(0);

    if (!job.isObject() || !job.getObject()->isCallable()) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "queueMicrotask expects a function"_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    // This is a JSC builtin function
    globalObject->queueMicrotask(JSC::createJSMicrotask(vm, job, JSC::JSValue {}, JSC::JSValue {},
        JSC::JSValue {}, JSC::JSValue {}));

    return JSC::JSValue::encode(JSC::jsUndefined());
}

static JSC_DECLARE_HOST_FUNCTION(functionSetTimeout);

static JSC_DEFINE_HOST_FUNCTION(functionSetTimeout,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    JSC::VM& vm = globalObject->vm();

    if (callFrame->argumentCount() == 0) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "setTimeout requires 1 argument (a function)"_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    JSC::JSValue job = callFrame->argument(0);

    if (!job.isObject() || !job.getObject()->isCallable()) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "setTimeout expects a function"_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    if (callFrame->argumentCount() == 1) {
        globalObject->queueMicrotask(JSC::createJSMicrotask(vm, job, JSC::JSValue {}, JSC::JSValue {},
            JSC::JSValue {}, JSC::JSValue {}));
        return JSC::JSValue::encode(JSC::jsNumber(Bun__Timer__getNextID()));
    }

    JSC::JSValue num = callFrame->argument(1);
    return Bun__Timer__setTimeout(globalObject, JSC::JSValue::encode(job), JSC::JSValue::encode(num));
}

static JSC_DECLARE_HOST_FUNCTION(functionSetInterval);

static JSC_DEFINE_HOST_FUNCTION(functionSetInterval,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    JSC::VM& vm = globalObject->vm();

    if (callFrame->argumentCount() == 0) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "setInterval requires 2 arguments (a function)"_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    JSC::JSValue job = callFrame->argument(0);

    if (!job.isObject() || !job.getObject()->isCallable()) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "setInterval expects a function"_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    JSC::JSValue num = callFrame->argument(1);
    return Bun__Timer__setInterval(globalObject, JSC::JSValue::encode(job),
        JSC::JSValue::encode(num));
}

static JSC_DECLARE_HOST_FUNCTION(functionClearInterval);

static JSC_DEFINE_HOST_FUNCTION(functionClearInterval,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    JSC::VM& vm = globalObject->vm();

    if (callFrame->argumentCount() == 0) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "clearInterval requires 1 argument (a number)"_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    JSC::JSValue num = callFrame->argument(0);

    return Bun__Timer__clearInterval(globalObject, JSC::JSValue::encode(num));
}

static JSC_DECLARE_HOST_FUNCTION(functionClearTimeout);

static JSC_DEFINE_HOST_FUNCTION(functionClearTimeout,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    JSC::VM& vm = globalObject->vm();

    if (callFrame->argumentCount() == 0) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "clearTimeout requires 1 argument (a number)"_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    JSC::JSValue num = callFrame->argument(0);

    return Bun__Timer__clearTimeout(globalObject, JSC::JSValue::encode(num));
}

static JSC_DECLARE_HOST_FUNCTION(functionBTOA);

static JSC_DEFINE_HOST_FUNCTION(functionBTOA,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    JSC::VM& vm = globalObject->vm();

    if (callFrame->argumentCount() == 0) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "btoa requires 1 argument (a string)"_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    const String& stringToEncode = callFrame->argument(0).toWTFString(globalObject);

    if (!stringToEncode || stringToEncode.isNull()) {
        return JSC::JSValue::encode(JSC::jsString(vm, WTF::String()));
    }

    if (!stringToEncode.isAllLatin1()) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        // TODO: DOMException
        JSC::throwTypeError(globalObject, scope, "The string contains invalid characters."_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    return JSC::JSValue::encode(JSC::jsString(vm, WTF::base64EncodeToString(stringToEncode.latin1())));
}

static JSC_DECLARE_HOST_FUNCTION(functionATOB);

static JSC_DEFINE_HOST_FUNCTION(functionATOB,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    JSC::VM& vm = globalObject->vm();

    if (callFrame->argumentCount() == 0) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "atob requires 1 argument (a string)"_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    const WTF::String& encodedString = callFrame->argument(0).toWTFString(globalObject);

    if (encodedString.isNull()) {
        return JSC::JSValue::encode(JSC::jsString(vm, ""));
    }

    auto decodedData = WTF::base64Decode(encodedString, {
                                                            WTF::Base64DecodeOptions::ValidatePadding,
                                                            WTF::Base64DecodeOptions::IgnoreSpacesAndNewLines,
                                                            WTF::Base64DecodeOptions::DiscardVerticalTab,
                                                        });
    if (!decodedData) {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        // TODO: DOMException
        JSC::throwTypeError(globalObject, scope, "The string contains invalid characters."_s);
        return JSC::JSValue::encode(JSC::JSValue {});
    }

    return JSC::JSValue::encode(JSC::jsString(vm, WTF::String(decodedData->data(), decodedData->size())));
}

extern "C" JSC__JSValue Bun__resolve(JSC::JSGlobalObject* global, JSC__JSValue specifier, JSC__JSValue from);
extern "C" JSC__JSValue Bun__resolveSync(JSC::JSGlobalObject* global, JSC__JSValue specifier, JSC__JSValue from);

static JSC_DECLARE_HOST_FUNCTION(functionImportMeta__resolve);

static JSC_DEFINE_HOST_FUNCTION(functionImportMeta__resolve,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    JSC::VM& vm = globalObject->vm();

    switch (callFrame->argumentCount()) {
    case 0: {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        // not "requires" because "require" could be confusing
        JSC::throwTypeError(globalObject, scope, "import.meta.resolve needs 1 argument (a string)"_s);
        scope.release();
        return JSC::JSValue::encode(JSC::JSValue {});
    }
    default: {
        JSC::JSValue moduleName = callFrame->argument(0);

        if (moduleName.isUndefinedOrNull()) {
            auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
            JSC::throwTypeError(globalObject, scope, "import.meta.resolve expects a string"_s);
            scope.release();
            return JSC::JSValue::encode(JSC::JSValue {});
        }

        JSC__JSValue from;

        if (callFrame->argumentCount() > 1) {
            from = JSC::JSValue::encode(callFrame->argument(1));
        } else {
            JSC::JSObject* thisObject = JSC::jsDynamicCast<JSC::JSObject*>(callFrame->thisValue());
            if (UNLIKELY(!thisObject)) {
                auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
                JSC::throwTypeError(globalObject, scope, "import.meta.resolve must be bound to an import.meta object"_s);
                return JSC::JSValue::encode(JSC::JSValue {});
            }

            auto clientData = WebCore::clientData(vm);

            from = JSC::JSValue::encode(thisObject->get(globalObject, clientData->builtinNames().pathPublicName()));
        }

        return Bun__resolve(globalObject, JSC::JSValue::encode(moduleName), from);
    }
    }
}

static JSC_DECLARE_HOST_FUNCTION(functionImportMeta__resolveSync);

static JSC_DEFINE_HOST_FUNCTION(functionImportMeta__resolveSync,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    JSC::VM& vm = globalObject->vm();

    switch (callFrame->argumentCount()) {
    case 0: {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        // not "requires" because "require" could be confusing
        JSC::throwTypeError(globalObject, scope, "import.meta.resolveSync needs 1 argument (a string)"_s);
        scope.release();
        return JSC::JSValue::encode(JSC::JSValue {});
    }
    default: {
        JSC::JSValue moduleName = callFrame->argument(0);

        if (moduleName.isUndefinedOrNull()) {
            auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
            JSC::throwTypeError(globalObject, scope, "import.meta.resolveSync expects a string"_s);
            scope.release();
            return JSC::JSValue::encode(JSC::JSValue {});
        }

        JSC__JSValue from;

        if (callFrame->argumentCount() > 1) {
            JSC::JSValue fromValue = callFrame->argument(1);

            // require.resolve also supports a paths array
            // we only support a single path
            if (!fromValue.isUndefinedOrNull() && fromValue.isObject()) {
                if (JSC::JSArray* array = JSC::jsDynamicCast<JSC::JSArray*>(fromValue.getObject()->getIfPropertyExists(globalObject, JSC::Identifier::fromString(vm, "paths"_s)))) {
                    if (array->length() > 0) {
                        fromValue = array->getIndex(globalObject, 0);
                    }
                }
            }
            from = JSC::JSValue::encode(fromValue);
        } else {
            JSC::JSObject* thisObject = JSC::jsDynamicCast<JSC::JSObject*>(callFrame->thisValue());
            if (UNLIKELY(!thisObject)) {
                auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
                JSC::throwTypeError(globalObject, scope, "import.meta.resolveSync must be bound to an import.meta object"_s);
                return JSC::JSValue::encode(JSC::JSValue {});
            }

            auto clientData = WebCore::clientData(vm);

            from = JSC::JSValue::encode(thisObject->get(globalObject, clientData->builtinNames().pathPublicName()));
        }

        auto result = Bun__resolveSync(globalObject, JSC::JSValue::encode(moduleName), from);
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());

        if (!JSC::JSValue::decode(result).isString()) {
            JSC::throwException(globalObject, scope, JSC::JSValue::decode(result));
            return JSC::JSValue::encode(JSC::JSValue {});
        }

        scope.release();
        return result;
    }
    }
}

extern "C" void Bun__reportError(JSC__JSGlobalObject*, JSC__JSValue);

static JSC_DECLARE_HOST_FUNCTION(functionReportError);
static JSC_DEFINE_HOST_FUNCTION(functionReportError,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
    switch (callFrame->argumentCount()) {
    case 0: {
        return JSC::JSValue::encode(JSC::jsUndefined());
    }
    default: {
        Bun__reportError(globalObject, JSC::JSValue::encode(callFrame->argument(0)));
    }
    }

    return JSC::JSValue::encode(JSC::jsUndefined());
}

JSC_DEFINE_HOST_FUNCTION(functionNoop, (JSC::JSGlobalObject*, JSC::CallFrame*))
{
    return JSC::JSValue::encode(JSC::jsUndefined());
}

JSC_DEFINE_CUSTOM_GETTER(noop_getter, (JSGlobalObject*, EncodedJSValue, PropertyName))
{
    return JSC::JSValue::encode(JSC::jsUndefined());
}

JSC_DEFINE_CUSTOM_SETTER(noop_setter,
    (JSC::JSGlobalObject*, JSC::EncodedJSValue,
        JSC::EncodedJSValue, JSC::PropertyName))
{
    return true;
}

// we're trying out a new way to do this lazy loading
static JSC_DECLARE_HOST_FUNCTION(functionLazyLoad);
static JSC_DEFINE_HOST_FUNCTION(functionLazyLoad,
    (JSC::JSGlobalObject * globalObject, JSC::CallFrame* callFrame))
{
JSC:
    VM& vm = globalObject->vm();
    switch (callFrame->argumentCount()) {
    case 0: {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        JSC::throwTypeError(globalObject, scope, "lazyLoad needs 1 argument (a string)"_s);
        scope.release();
        return JSC::JSValue::encode(JSC::JSValue {});
    }
    default: {
        static NeverDestroyed<const String> sqliteString(MAKE_STATIC_STRING_IMPL("sqlite"));
        static NeverDestroyed<const String> noopString(MAKE_STATIC_STRING_IMPL("noop"));
        JSC::JSValue moduleName = callFrame->argument(0);
        if (moduleName.isNumber()) {
            switch (moduleName.toInt32(globalObject)) {
            case 0: {
                auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
                JSC::throwTypeError(globalObject, scope, "lazyLoad expects a string"_s);
                scope.release();
                return JSC::JSValue::encode(JSC::JSValue {});
            }

            case 1: {
                return ByteBlob__JSReadableStreamSource__load(globalObject);
            }
            case 2: {
                return FileBlobLoader__JSReadableStreamSource__load(globalObject);
            }
            default: {
                auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
                JSC::throwTypeError(globalObject, scope, "lazyLoad expects a string"_s);
                scope.release();
                return JSC::JSValue::encode(JSC::JSValue {});
            }
            }
        }

        auto string = moduleName.toWTFString(globalObject);
        if (string.isNull()) {
            auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
            JSC::throwTypeError(globalObject, scope, "lazyLoad expects a string"_s);
            scope.release();
            return JSC::JSValue::encode(JSC::JSValue {});
        }

        if (string == sqliteString) {
            return JSC::JSValue::encode(JSSQLStatementConstructor::create(vm, globalObject, JSSQLStatementConstructor::createStructure(vm, globalObject, globalObject->m_functionPrototype.get())));
        }

        if (UNLIKELY(string == noopString)) {
            auto* obj = constructEmptyObject(globalObject);
            obj->putDirectCustomAccessor(vm, JSC::PropertyName(JSC::Identifier::fromString(vm, "getterSetter"_s)), JSC::CustomGetterSetter::create(vm, noop_getter, noop_setter), 0);
            Zig::JSFFIFunction* function = Zig::JSFFIFunction::create(vm, reinterpret_cast<Zig::GlobalObject*>(globalObject), 0, String(), functionNoop, JSC::NoIntrinsic);
            obj->putDirect(vm, JSC::PropertyName(JSC::Identifier::fromString(vm, "function"_s)), function, JSC::PropertyAttribute::Function | 0);
            return JSC::JSValue::encode(obj);
        }

        return JSC::JSValue::encode(JSC::jsUndefined());

        break;
    }
    }
}

static inline JSValue jsServiceWorkerGlobalScope_ByteLengthQueuingStrategyConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSByteLengthQueuingStrategy::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_ByteLengthQueuingStrategyConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_ByteLengthQueuingStrategyConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_CountQueuingStrategyConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSCountQueuingStrategy::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_CountQueuingStrategyConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_CountQueuingStrategyConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_ReadableByteStreamControllerConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSReadableByteStreamController::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_ReadableByteStreamControllerConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_ReadableByteStreamControllerConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_ReadableStreamConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSReadableStream::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_ReadableStreamConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_ReadableStreamConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_ReadableStreamBYOBReaderConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSReadableStreamBYOBReader::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_ReadableStreamBYOBReaderConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_ReadableStreamBYOBReaderConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_ReadableStreamBYOBRequestConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSReadableStreamBYOBRequest::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_ReadableStreamBYOBRequestConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_ReadableStreamBYOBRequestConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_ReadableStreamDefaultControllerConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSReadableStreamDefaultController::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_ReadableStreamDefaultControllerConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_ReadableStreamDefaultControllerConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_ReadableStreamDefaultReaderConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSReadableStreamDefaultReader::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_ReadableStreamDefaultReaderConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_ReadableStreamDefaultReaderConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_TransformStreamConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSTransformStream::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_TransformStreamConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_TransformStreamConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_TransformStreamDefaultControllerConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSTransformStreamDefaultController::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_TransformStreamDefaultControllerConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_TransformStreamDefaultControllerConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_WritableStreamConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSWritableStream::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_WritableStreamConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_WritableStreamConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_WritableStreamDefaultControllerConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSWritableStreamDefaultController::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_WritableStreamDefaultControllerConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_WritableStreamDefaultControllerConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsServiceWorkerGlobalScope_WritableStreamDefaultWriterConstructorGetter(JSGlobalObject& lexicalGlobalObject, Zig::GlobalObject& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSWritableStreamDefaultWriter::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsServiceWorkerGlobalScope_WritableStreamDefaultWriterConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<Zig::GlobalObject>::get<jsServiceWorkerGlobalScope_WritableStreamDefaultWriterConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

JSC_DECLARE_HOST_FUNCTION(makeThisTypeErrorForBuiltins);
JSC_DECLARE_HOST_FUNCTION(makeGetterTypeErrorForBuiltins);
JSC_DECLARE_HOST_FUNCTION(makeDOMExceptionForBuiltins);
JSC_DECLARE_HOST_FUNCTION(createWritableStreamFromInternal);
JSC_DECLARE_HOST_FUNCTION(getInternalWritableStream);
JSC_DECLARE_HOST_FUNCTION(whenSignalAborted);
JSC_DECLARE_HOST_FUNCTION(isAbortSignal);
JSC_DEFINE_HOST_FUNCTION(makeThisTypeErrorForBuiltins, (JSGlobalObject * globalObject, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 2);
    VM& vm = globalObject->vm();
    DeferTermination deferScope(vm);
    auto scope = DECLARE_CATCH_SCOPE(vm);

    auto interfaceName = callFrame->uncheckedArgument(0).getString(globalObject);
    scope.assertNoException();
    auto functionName = callFrame->uncheckedArgument(1).getString(globalObject);
    scope.assertNoException();
    return JSValue::encode(createTypeError(globalObject, makeThisTypeErrorMessage(interfaceName.utf8().data(), functionName.utf8().data())));
}

JSC_DEFINE_HOST_FUNCTION(makeGetterTypeErrorForBuiltins, (JSGlobalObject * globalObject, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 2);
    VM& vm = globalObject->vm();
    DeferTermination deferScope(vm);
    auto scope = DECLARE_CATCH_SCOPE(vm);

    auto interfaceName = callFrame->uncheckedArgument(0).getString(globalObject);
    scope.assertNoException();
    auto attributeName = callFrame->uncheckedArgument(1).getString(globalObject);
    scope.assertNoException();

    auto error = static_cast<ErrorInstance*>(createTypeError(globalObject, JSC::makeDOMAttributeGetterTypeErrorMessage(interfaceName.utf8().data(), attributeName)));
    error->setNativeGetterTypeError();
    return JSValue::encode(error);
}

JSC_DEFINE_HOST_FUNCTION(makeDOMExceptionForBuiltins, (JSGlobalObject * globalObject, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 2);

    auto& vm = globalObject->vm();
    DeferTermination deferScope(vm);
    auto scope = DECLARE_CATCH_SCOPE(vm);

    auto codeValue = callFrame->uncheckedArgument(0).getString(globalObject);
    scope.assertNoException();

    auto message = callFrame->uncheckedArgument(1).getString(globalObject);
    scope.assertNoException();

    ExceptionCode code { TypeError };
    if (codeValue == "AbortError")
        code = AbortError;
    auto value = createDOMException(globalObject, code, message);

    EXCEPTION_ASSERT(!scope.exception() || vm.hasPendingTerminationException());

    return JSValue::encode(value);
}

JSC_DEFINE_HOST_FUNCTION(getInternalWritableStream, (JSGlobalObject*, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 1);

    auto* writableStream = jsDynamicCast<JSWritableStream*>(callFrame->uncheckedArgument(0));
    if (UNLIKELY(!writableStream))
        return JSValue::encode(jsUndefined());
    return JSValue::encode(writableStream->wrapped().internalWritableStream());
}

JSC_DEFINE_HOST_FUNCTION(createWritableStreamFromInternal, (JSGlobalObject * globalObject, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 1);
    ASSERT(callFrame->uncheckedArgument(0).isObject());

    auto* jsDOMGlobalObject = JSC::jsCast<JSDOMGlobalObject*>(globalObject);
    auto internalWritableStream = InternalWritableStream::fromObject(*jsDOMGlobalObject, *callFrame->uncheckedArgument(0).toObject(globalObject));
    return JSValue::encode(toJSNewlyCreated(globalObject, jsDOMGlobalObject, WritableStream::create(WTFMove(internalWritableStream))));
}

JSC_DEFINE_HOST_FUNCTION(whenSignalAborted, (JSGlobalObject * globalObject, CallFrame* callFrame))
{
    ASSERT(callFrame);
    ASSERT(callFrame->argumentCount() == 2);

    auto& vm = globalObject->vm();
    auto* abortSignal = jsDynamicCast<JSAbortSignal*>(callFrame->uncheckedArgument(0));
    if (UNLIKELY(!abortSignal))
        return JSValue::encode(JSValue(JSC::JSValue::JSFalse));

    Ref<AbortAlgorithm> abortAlgorithm = JSAbortAlgorithm::create(vm, callFrame->uncheckedArgument(1).getObject());

    bool result = AbortSignal::whenSignalAborted(abortSignal->wrapped(), WTFMove(abortAlgorithm));
    return JSValue::encode(result ? JSValue(JSC::JSValue::JSTrue) : JSValue(JSC::JSValue::JSFalse));
}

JSC_DEFINE_HOST_FUNCTION(isAbortSignal, (JSGlobalObject*, CallFrame* callFrame))
{
    ASSERT(callFrame->argumentCount() == 1);
    return JSValue::encode(jsBoolean(callFrame->uncheckedArgument(0).inherits<JSAbortSignal>()));
}

extern "C" JSC__JSValue ZigGlobalObject__createNativeReadableStream(Zig::GlobalObject* globalObject, JSC__JSValue nativeID, JSC__JSValue nativeTag);
extern "C" JSC__JSValue ZigGlobalObject__createNativeReadableStream(Zig::GlobalObject* globalObject, JSC__JSValue nativeID, JSC__JSValue nativeTag)
{
    auto& vm = globalObject->vm();
    auto scope = DECLARE_THROW_SCOPE(vm);

    auto clientData = WebCore::clientData(vm);
    auto& builtinNames = WebCore::builtinNames(vm);

    auto function = globalObject->getDirect(vm, builtinNames.createNativeReadableStreamPrivateName()).getObject();
    JSC::MarkedArgumentBuffer arguments = JSC::MarkedArgumentBuffer();
    arguments.append(JSValue::decode(nativeID));
    arguments.append(JSValue::decode(nativeTag));

    auto callData = JSC::getCallData(function);
    return JSC::JSValue::encode(call(globalObject, function, callData, JSC::jsUndefined(), arguments));
}

void GlobalObject::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(info()));

    addBuiltinGlobals(vm);

    RELEASE_ASSERT(classInfo());
}

void GlobalObject::addBuiltinGlobals(JSC::VM& vm)
{
    m_builtinInternalFunctions.initialize(*this);

    auto clientData = WebCore::clientData(vm);
    auto& builtinNames = WebCore::builtinNames(vm);

    WTF::Vector<GlobalPropertyInfo> extraStaticGlobals;
    extraStaticGlobals.reserveCapacity(26);

    JSC::Identifier queueMicrotaskIdentifier = JSC::Identifier::fromString(vm, "queueMicrotask"_s);
    extraStaticGlobals.uncheckedAppend(
        GlobalPropertyInfo { queueMicrotaskIdentifier,
            JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject()), 0,
                "queueMicrotask"_s, functionQueueMicrotask),
            JSC::PropertyAttribute::Function | JSC::PropertyAttribute::DontDelete | 0 });

    JSC::Identifier setTimeoutIdentifier = JSC::Identifier::fromString(vm, "setTimeout"_s);
    extraStaticGlobals.uncheckedAppend(
        GlobalPropertyInfo { setTimeoutIdentifier,
            JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject()), 0,
                "setTimeout"_s, functionSetTimeout),
            JSC::PropertyAttribute::Function | JSC::PropertyAttribute::DontDelete | 0 });

    JSC::Identifier clearTimeoutIdentifier = JSC::Identifier::fromString(vm, "clearTimeout"_s);
    extraStaticGlobals.uncheckedAppend(
        GlobalPropertyInfo { clearTimeoutIdentifier,
            JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject()), 0,
                "clearTimeout"_s, functionClearTimeout),
            JSC::PropertyAttribute::Function | JSC::PropertyAttribute::DontDelete | 0 });

    JSC::Identifier setIntervalIdentifier = JSC::Identifier::fromString(vm, "setInterval"_s);
    extraStaticGlobals.uncheckedAppend(
        GlobalPropertyInfo { setIntervalIdentifier,
            JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject()), 0,
                "setInterval"_s, functionSetInterval),
            JSC::PropertyAttribute::Function | JSC::PropertyAttribute::DontDelete | 0 });

    JSC::Identifier clearIntervalIdentifier = JSC::Identifier::fromString(vm, "clearInterval"_s);
    extraStaticGlobals.uncheckedAppend(
        GlobalPropertyInfo { clearIntervalIdentifier,
            JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject()), 0,
                "clearInterval"_s, functionClearInterval),
            JSC::PropertyAttribute::Function | JSC::PropertyAttribute::DontDelete | 0 });

    JSC::Identifier atobIdentifier = JSC::Identifier::fromString(vm, "atob"_s);
    extraStaticGlobals.uncheckedAppend(
        GlobalPropertyInfo { atobIdentifier,
            JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject()), 0,
                "atob"_s, functionATOB),
            JSC::PropertyAttribute::Function | JSC::PropertyAttribute::DontDelete | 0 });

    JSC::Identifier btoaIdentifier = JSC::Identifier::fromString(vm, "btoa"_s);
    extraStaticGlobals.uncheckedAppend(
        GlobalPropertyInfo { btoaIdentifier,
            JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject()), 0,
                "btoa"_s, functionBTOA),
            JSC::PropertyAttribute::Function | JSC::PropertyAttribute::DontDelete | 0 });
    JSC::Identifier reportErrorIdentifier = JSC::Identifier::fromString(vm, "reportError"_s);
    extraStaticGlobals.uncheckedAppend(
        GlobalPropertyInfo { reportErrorIdentifier,
            JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject()), 0,
                "reportError"_s, functionReportError),
            JSC::PropertyAttribute::DontDelete | 0 });

    static NeverDestroyed<const String> BunLazyString(MAKE_STATIC_STRING_IMPL("Bun.lazy"));
    JSC::Identifier BunLazyIdentifier = JSC::Identifier::fromUid(vm.symbolRegistry().symbolForKey(BunLazyString));
    extraStaticGlobals.uncheckedAppend(
        GlobalPropertyInfo { BunLazyIdentifier,
            JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject()), 0,
                BunLazyString, functionLazyLoad),
            JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::Function | 0 });

    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.makeThisTypeErrorPrivateName(), JSFunction::create(vm, this, 2, String(), makeThisTypeErrorForBuiltins), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.makeGetterTypeErrorPrivateName(), JSFunction::create(vm, this, 2, String(), makeGetterTypeErrorForBuiltins), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.makeDOMExceptionPrivateName(), JSFunction::create(vm, this, 2, String(), makeDOMExceptionForBuiltins), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.whenSignalAbortedPrivateName(), JSFunction::create(vm, this, 2, String(), whenSignalAborted), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.cloneArrayBufferPrivateName(), JSFunction::create(vm, this, 3, String(), cloneArrayBuffer), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.structuredCloneForStreamPrivateName(), JSFunction::create(vm, this, 1, String(), structuredCloneForStream), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(vm.propertyNames->builtinNames().ArrayBufferPrivateName(), arrayBufferConstructor(), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.streamClosedPrivateName(), jsNumber(1), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.streamClosingPrivateName(), jsNumber(2), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.streamErroredPrivateName(), jsNumber(3), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.streamReadablePrivateName(), jsNumber(4), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.streamWaitingPrivateName(), jsNumber(5), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.streamWritablePrivateName(), jsNumber(6), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.isAbortSignalPrivateName(), JSFunction::create(vm, this, 1, String(), isAbortSignal), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.getInternalWritableStreamPrivateName(), JSFunction::create(vm, this, 1, String(), getInternalWritableStream), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));
    extraStaticGlobals.uncheckedAppend(GlobalPropertyInfo(builtinNames.createWritableStreamFromInternalPrivateName(), JSFunction::create(vm, this, 1, String(), createWritableStreamFromInternal), PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly));

    this->addStaticGlobals(extraStaticGlobals.data(), extraStaticGlobals.size());

    extraStaticGlobals.releaseBuffer();

    putDirectBuiltinFunction(vm, this, builtinNames.createNativeReadableStreamPrivateName(), readableStreamCreateNativeReadableStreamCodeGenerator(vm), PropertyAttribute::Builtin | PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "process"_s), JSC::CustomGetterSetter::create(vm, property_lazyProcessGetter, property_lazyProcessSetter),
        JSC::PropertyAttribute::CustomAccessor | 0);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "URL"_s), JSC::CustomGetterSetter::create(vm, JSDOMURL_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | 0);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "URLSearchParams"_s), JSC::CustomGetterSetter::create(vm, JSURLSearchParams_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "DOMException"_s), JSC::CustomGetterSetter::create(vm, JSDOMException_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "Event"_s), JSC::CustomGetterSetter::create(vm, JSEvent_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "EventTarget"_s), JSC::CustomGetterSetter::create(vm, JSEventTarget_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "AbortController"_s), JSC::CustomGetterSetter::create(vm, JSDOMAbortController_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "AbortSignal"_s), JSC::CustomGetterSetter::create(vm, JSDOMAbortSignal_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "CustomEvent"_s), JSC::CustomGetterSetter::create(vm, JSCustomEvent_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "Headers"_s), JSC::CustomGetterSetter::create(vm, JSFetchHeaders_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "ErrorEvent"_s), JSC::CustomGetterSetter::create(vm, JSErrorEvent_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "Buffer"_s), JSC::CustomGetterSetter::create(vm, JSBuffer_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "TextEncoder"_s), JSC::CustomGetterSetter::create(vm, JSTextEncoder_getter, nullptr),
        JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().TransformStreamPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_TransformStreamConstructor, nullptr), attributesForStructure(static_cast<unsigned>(JSC::PropertyAttribute::DontEnum)));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().TransformStreamPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_TransformStreamConstructor, nullptr), attributesForStructure(static_cast<unsigned>(JSC::PropertyAttribute::DontEnum)));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().TransformStreamDefaultControllerPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_TransformStreamDefaultControllerConstructor, nullptr), attributesForStructure(static_cast<unsigned>(JSC::PropertyAttribute::DontEnum)));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().TransformStreamDefaultControllerPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_TransformStreamDefaultControllerConstructor, nullptr), attributesForStructure(static_cast<unsigned>(JSC::PropertyAttribute::DontEnum)));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableByteStreamControllerPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableByteStreamControllerConstructor, nullptr), attributesForStructure(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableStreamPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableStreamConstructor, nullptr), attributesForStructure(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableStreamBYOBReaderPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableStreamBYOBReaderConstructor, nullptr), attributesForStructure(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableStreamBYOBRequestPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableStreamBYOBRequestConstructor, nullptr), attributesForStructure(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableStreamDefaultControllerPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableStreamDefaultControllerConstructor, nullptr), attributesForStructure(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableStreamDefaultReaderPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableStreamDefaultReaderConstructor, nullptr), attributesForStructure(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().WritableStreamPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_WritableStreamConstructor, nullptr), attributesForStructure(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().WritableStreamDefaultControllerPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_WritableStreamDefaultControllerConstructor, nullptr), attributesForStructure(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().WritableStreamDefaultWriterPrivateName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_WritableStreamDefaultWriterConstructor, nullptr), attributesForStructure(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().AbortSignalPrivateName(), CustomGetterSetter::create(vm, JSDOMAbortSignal_getter, nullptr), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().TransformStreamDefaultControllerPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_TransformStreamDefaultControllerConstructor, nullptr), static_cast<unsigned>(JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DontEnum));
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableByteStreamControllerPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableByteStreamControllerConstructor, nullptr), JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableStreamPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableStreamConstructor, nullptr), JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableStreamBYOBReaderPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableStreamBYOBReaderConstructor, nullptr), JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableStreamBYOBRequestPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableStreamBYOBRequestConstructor, nullptr), JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableStreamDefaultControllerPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableStreamDefaultControllerConstructor, nullptr), JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().ReadableStreamDefaultReaderPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ReadableStreamDefaultReaderConstructor, nullptr), JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().WritableStreamPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_WritableStreamConstructor, nullptr), JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().WritableStreamDefaultControllerPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_WritableStreamDefaultControllerConstructor, nullptr), JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().WritableStreamDefaultWriterPublicName(), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_WritableStreamDefaultWriterConstructor, nullptr), JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "ByteLengthQueuingStrategy"_s), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_ByteLengthQueuingStrategyConstructor, nullptr), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);
    putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "CountQueuingStrategy"_s), CustomGetterSetter::create(vm, jsServiceWorkerGlobalScope_CountQueuingStrategyConstructor, nullptr), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    // putDirect(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().nativeReadableStreamPrototypePrivateName(), jsUndefined(), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::DontEnum | 0);
}

// This is not a publicly exposed API currently.
// This is used by the bundler to make Response, Request, FetchEvent,
// and any other objects available globally.
void GlobalObject::installAPIGlobals(JSClassRef* globals, int count, JSC::VM& vm)
{
    auto clientData = WebCore::clientData(vm);
    size_t constructor_count = 0;
    JSC__JSValue const* constructors = Zig__getAPIConstructors(&constructor_count, this);
    WTF::Vector<GlobalPropertyInfo> extraStaticGlobals;
    extraStaticGlobals.reserveCapacity((size_t)count + constructor_count + 3 + 1);
    int i = 0;
    for (; i < constructor_count; i++) {
        auto* object = JSC::jsDynamicCast<JSC::JSCallbackConstructor*>(JSC::JSValue::decode(constructors[i]).asCell()->getObject());

        extraStaticGlobals.uncheckedAppend(
            GlobalPropertyInfo { JSC::Identifier::fromString(vm, object->get(this, vm.propertyNames->name).toWTFString(this)),
                JSC::JSValue(object), JSC::PropertyAttribute::DontDelete | 0 });
    }
    int j = 0;
    for (; j < count - 1; j++) {
        auto jsClass = globals[j];

        JSC::JSCallbackObject<JSNonFinalObject>* object = JSC::JSCallbackObject<JSNonFinalObject>::create(this, this->callbackObjectStructure(),
            jsClass, nullptr);
        if (JSObject* prototype = object->classRef()->prototype(this))
            object->setPrototypeDirect(vm, prototype);

        extraStaticGlobals.uncheckedAppend(
            GlobalPropertyInfo { JSC::Identifier::fromString(vm, jsClass->className()),
                JSC::JSValue(object), JSC::PropertyAttribute::DontDelete | 0 });
    }

    // The last one must be "process.env"
    // Runtime-support is for if they change
    dot_env_class_ref = globals[j];

    // // The last one must be "process.env"
    // // Runtime-support is for if they change
    // {
    //   auto jsClass = globals[i];

    //   JSC::JSCallbackObject<JSNonFinalObject> *object =
    //     JSC::JSCallbackObject<JSNonFinalObject>::create(this, this->callbackObjectStructure(),
    //                                                     jsClass, nullptr);
    //   if (JSObject *prototype = jsClass->prototype(this)) object->setPrototypeDirect(vm,
    //   prototype);

    //   process->putDirect(this->vm, JSC::Identifier::fromString(this->vm, "env"),
    //                      JSC::JSValue(object), JSC::PropertyAttribute::DontDelete | 0);
    // }

    this->addStaticGlobals(extraStaticGlobals.data(), extraStaticGlobals.size());

    m_NapiClassStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            init.setStructure(Zig::NapiClass::createStructure(init.vm, init.global, init.global->m_functionPrototype.get()));
        });

    m_JSFFIFunctionStructure.initLater(
        [](LazyClassStructure::Initializer& init) {
            init.setStructure(Zig::JSFFIFunction::createStructure(init.vm, init.global, init.global->m_functionPrototype.get()));
        });

    // putDirectCustomAccessor(vm, JSC::Identifier::fromString(vm, "SQL"_s), JSC::CustomGetterSetter::create(vm, JSSQLStatement_getter, nullptr),
    //     JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly);

    extraStaticGlobals.releaseBuffer();

    this->setRemoteDebuggingEnabled(true);
    // auto& server = Inspector::RemoteInspectorServer::singleton();
    // if (server.start("localhost", 9222)) {
    // }
}

template<typename Visitor>
void GlobalObject::visitChildrenImpl(JSCell* cell, Visitor& visitor)
{
    GlobalObject* thisObject = jsCast<GlobalObject*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    Base::visitChildren(thisObject, visitor);

    {
        // The GC thread has to grab the GC lock even though it is not mutating the containers.
        Locker locker { thisObject->m_gcLock };

        for (auto& structure : thisObject->m_structures.values())
            visitor.append(structure);

        for (auto& guarded : thisObject->m_guardedObjects)
            guarded->visitAggregate(visitor);
    }

    for (auto& constructor : thisObject->constructors().array())
        visitor.append(constructor);

    thisObject->m_builtinInternalFunctions.visit(visitor);
    thisObject->m_JSFFIFunctionStructure.visit(visitor);
    ScriptExecutionContext* context = thisObject->scriptExecutionContext();
    visitor.addOpaqueRoot(context);
}

DEFINE_VISIT_CHILDREN(GlobalObject);

// void GlobalObject::destroy(JSCell* cell)
// {
//     static_cast<Zig::GlobalObject*>(cell)->Zig::GlobalObject::~Zig::GlobalObject();
// }

// template<typename Visitor>
// void GlobalObject::visitChildrenImpl(JSCell* cell, Visitor& visitor)
// {
//     Zig::GlobalObject* thisObject = jsCast<Zig::GlobalObject*>(cell);
//     ASSERT_GC_OBJECT_INHERITS(thisObject, info());
//     Base::visitChildren(thisObject, visitor);

//     {
//         // The GC thread has to grab the GC lock even though it is not mutating the containers.
//         Locker locker { thisObject->m_gcLock };

//         for (auto& structure : thisObject->m_structures.values())
//             visitor.append(structure);

//         for (auto& guarded : thisObject->m_guardedObjects)
//             guarded->visitAggregate(visitor);
//     }

//     for (auto& constructor : thisObject->constructors().array())
//         visitor.append(constructor);

//     thisObject->m_builtinInternalFunctions.visit(visitor);
// }

// DEFINE_VISIT_CHILDREN(Zig::GlobalObject);

JSC::Identifier GlobalObject::moduleLoaderResolve(JSGlobalObject* globalObject,
    JSModuleLoader* loader, JSValue key,
    JSValue referrer, JSValue origin)
{
    ErrorableZigString res;
    res.success = false;
    ZigString keyZ = toZigString(key, globalObject);
    ZigString referrerZ = referrer.isString() ? toZigString(referrer, globalObject) : ZigStringEmpty;
    Zig__GlobalObject__resolve(&res, globalObject, &keyZ, &referrerZ);

    if (res.success) {
        return toIdentifier(res.result.value, globalObject);
    } else {
        auto scope = DECLARE_THROW_SCOPE(globalObject->vm());
        throwException(scope, res.result.err, globalObject);
        return globalObject->vm().propertyNames->emptyIdentifier;
    }
}

JSC::JSInternalPromise* GlobalObject::moduleLoaderImportModule(JSGlobalObject* globalObject,
    JSModuleLoader*,
    JSString* moduleNameValue,
    JSValue parameters,
    const SourceOrigin& sourceOrigin)
{
    JSC::VM& vm = globalObject->vm();
    auto scope = DECLARE_THROW_SCOPE(vm);

    auto* promise = JSC::JSInternalPromise::create(vm, globalObject->internalPromiseStructure());
    RETURN_IF_EXCEPTION(scope, promise->rejectWithCaughtException(globalObject, scope));

    auto sourceURL = sourceOrigin.url();
    ErrorableZigString resolved;
    auto moduleNameZ = toZigString(moduleNameValue, globalObject);
    auto sourceOriginZ = sourceURL.isEmpty() ? ZigStringCwd : toZigString(sourceURL.fileSystemPath());
    resolved.success = false;
    Zig__GlobalObject__resolve(&resolved, globalObject, &moduleNameZ, &sourceOriginZ);
    if (!resolved.success) {
        throwException(scope, resolved.result.err, globalObject);
        return promise->rejectWithCaughtException(globalObject, scope);
    }

    auto result = JSC::importModule(globalObject, toIdentifier(resolved.result.value, globalObject),
        parameters, JSC::jsUndefined());
    RETURN_IF_EXCEPTION(scope, promise->rejectWithCaughtException(globalObject, scope));

    return result;
}

JSC::JSInternalPromise* GlobalObject::moduleLoaderFetch(JSGlobalObject* globalObject,
    JSModuleLoader* loader, JSValue key,
    JSValue value1, JSValue value2)
{
    JSC::VM& vm = globalObject->vm();
    JSC::JSInternalPromise* promise = JSC::JSInternalPromise::create(vm, globalObject->internalPromiseStructure());

    auto scope = DECLARE_THROW_SCOPE(vm);

    auto rejectWithError = [&](JSC::JSValue error) {
        promise->reject(globalObject, error);
        return promise;
    };

    auto moduleKey = key.toWTFString(globalObject);
    RETURN_IF_EXCEPTION(scope, promise->rejectWithCaughtException(globalObject, scope));
    if (moduleKey.endsWith(".node")) {
        return rejectWithError(createTypeError(globalObject, "To load Node-API modules, use require() or process.dlopen instead of import."_s));
    }

    auto moduleKeyZig = toZigString(moduleKey);
    auto source = Zig::toZigString(value1, globalObject);
    ErrorableResolvedSource res;
    res.success = false;
    res.result.err.code = 0;
    res.result.err.ptr = nullptr;

    Zig__GlobalObject__fetch(&res, globalObject, &moduleKeyZig, &source);

    if (!res.success) {
        throwException(scope, res.result.err, globalObject);
        RETURN_IF_EXCEPTION(scope, promise->rejectWithCaughtException(globalObject, scope));
    }

    if (res.result.value.tag == 1) {
        auto buffer = Vector<uint8_t>(res.result.value.source_code.ptr, res.result.value.source_code.len);
        auto source = JSC::SourceCode(
            JSC::WebAssemblySourceProvider::create(WTFMove(buffer),
                JSC::SourceOrigin(WTF::URL::fileURLWithFileSystemPath(Zig::toString(res.result.value.source_url))),
                WTFMove(moduleKey)));

        auto sourceCode = JSSourceCode::create(vm, WTFMove(source));
        RETURN_IF_EXCEPTION(scope, promise->rejectWithCaughtException(globalObject, scope));

        promise->resolve(globalObject, sourceCode);
        scope.release();

        globalObject->vm().drainMicrotasks();
        return promise;
    } else {
        auto provider = Zig::SourceProvider::create(res.result.value);
        auto jsSourceCode = JSC::JSSourceCode::create(vm, JSC::SourceCode(provider));
        promise->resolve(globalObject, jsSourceCode);
    }

    // if (provider.ptr()->isBytecodeCacheEnabled()) {
    //     provider.ptr()->readOrGenerateByteCodeCache(vm, jsSourceCode->sourceCode());
    // }

    scope.release();

    globalObject->vm().drainMicrotasks();
    return promise;
}

JSC::JSObject* GlobalObject::moduleLoaderCreateImportMetaProperties(JSGlobalObject* globalObject,
    JSModuleLoader* loader,
    JSValue key,
    JSModuleRecord* record,
    JSValue val)
{

    JSC::VM& vm = globalObject->vm();
    auto scope = DECLARE_THROW_SCOPE(vm);

    JSC::JSObject* metaProperties = JSC::constructEmptyObject(vm, globalObject->nullPrototypeObjectStructure());
    RETURN_IF_EXCEPTION(scope, nullptr);

    auto clientData = WebCore::clientData(vm);
    JSString* keyString = key.toStringOrNull(globalObject);
    if (UNLIKELY(!keyString)) {
        return metaProperties;
    }
    auto view = keyString->value(globalObject);
    auto index = view.reverseFind('/', view.length());
    if (index != WTF::notFound) {
        metaProperties->putDirect(vm, clientData->builtinNames().dirPublicName(),
            JSC::jsSubstring(globalObject, keyString, 0, index));
        metaProperties->putDirect(
            vm, clientData->builtinNames().filePublicName(),
            JSC::jsSubstring(globalObject, keyString, index + 1, keyString->length() - index - 1));
    } else {
        metaProperties->putDirect(vm, clientData->builtinNames().filePublicName(), keyString);
        metaProperties->putDirect(vm, clientData->builtinNames().dirPublicName(), jsEmptyString(vm));
    }

    metaProperties->putDirect(vm, clientData->builtinNames().resolvePublicName(),
        JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject), 0,
            clientData->builtinNames().resolvePublicName().string(), functionImportMeta__resolve),
        JSC::PropertyAttribute::Function | 0);
    metaProperties->putDirect(vm, clientData->builtinNames().resolveSyncPublicName(),
        JSC::JSFunction::create(vm, JSC::jsCast<JSC::JSGlobalObject*>(globalObject), 0,
            clientData->builtinNames().resolveSyncPublicName().string(), functionImportMeta__resolveSync),
        JSC::PropertyAttribute::Function | 0);

    metaProperties->putDirectBuiltinFunction(vm, globalObject, clientData->builtinNames().requirePublicName(),
        jsZigGlobalObjectRequireCodeGenerator(vm),
        JSC::PropertyAttribute::Builtin | 0);

    metaProperties->putDirect(vm, clientData->builtinNames().pathPublicName(), key);
    metaProperties->putDirect(vm, clientData->builtinNames().urlPublicName(), JSC::JSValue(JSC::jsString(vm, WTF::URL::fileURLWithFileSystemPath(view).string())));

    RETURN_IF_EXCEPTION(scope, nullptr);

    return metaProperties;
}

JSC::JSValue GlobalObject::moduleLoaderEvaluate(JSGlobalObject* globalObject,
    JSModuleLoader* moduleLoader, JSValue key,
    JSValue moduleRecordValue, JSValue scriptFetcher,
    JSValue sentValue, JSValue resumeMode)
{

    if (UNLIKELY(scriptFetcher && scriptFetcher.isObject())) {
        return scriptFetcher;
    }

    JSC::JSValue result = moduleLoader->evaluateNonVirtual(globalObject, key, moduleRecordValue,
        scriptFetcher, sentValue, resumeMode);

    return result;
}

void GlobalObject::queueMicrotaskToEventLoop(JSC::JSGlobalObject& global,
    Ref<JSC::Microtask>&& task)
{

    Zig__GlobalObject__queueMicrotaskToEventLoop(
        &global, &JSMicrotaskCallback::create(global, WTFMove(task)).leakRef());
}

} // namespace Zig
