/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSTextEncoder.h"

#include "ActiveDOMObject.h"
#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructor.h"
#include "JSDOMConvertBufferSource.h"
#include "JSDOMConvertInterface.h"
#include "JSDOMConvertNumbers.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObject.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSDestructibleObjectHeapCellType.h>
#include <JavaScriptCore/ObjectConstructor.h>
#include <JavaScriptCore/SlotVisitorMacros.h>
#include <JavaScriptCore/SubspaceInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>

namespace WebCore {
using namespace JSC;

template<> TextEncoder::EncodeIntoResult convertDictionary<TextEncoder::EncodeIntoResult>(JSGlobalObject& lexicalGlobalObject, JSValue value)
{
    VM& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    bool isNullOrUndefined = value.isUndefinedOrNull();
    auto* object = isNullOrUndefined ? nullptr : value.getObject();
    if (UNLIKELY(!isNullOrUndefined && !object)) {
        throwTypeError(&lexicalGlobalObject, throwScope);
        return {};
    }
    TextEncoder::EncodeIntoResult result;
    JSValue readValue;
    if (isNullOrUndefined)
        readValue = jsUndefined();
    else {
        readValue = object->get(&lexicalGlobalObject, Identifier::fromString(vm, "read"_s));
        RETURN_IF_EXCEPTION(throwScope, {});
    }
    if (!readValue.isUndefined()) {
        result.read = convert<IDLUnsignedLongLong>(lexicalGlobalObject, readValue);
        RETURN_IF_EXCEPTION(throwScope, {});
    }
    JSValue writtenValue;
    if (isNullOrUndefined)
        writtenValue = jsUndefined();
    else {
        writtenValue = object->get(&lexicalGlobalObject, Identifier::fromString(vm, "written"_s));
        RETURN_IF_EXCEPTION(throwScope, {});
    }
    if (!writtenValue.isUndefined()) {
        result.written = convert<IDLUnsignedLongLong>(lexicalGlobalObject, writtenValue);
        RETURN_IF_EXCEPTION(throwScope, {});
    }
    return result;
}

JSC::JSObject* convertDictionaryToJS(JSC::JSGlobalObject& lexicalGlobalObject, JSDOMGlobalObject& globalObject, const TextEncoder::EncodeIntoResult& dictionary)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);

    auto result = constructEmptyObject(&lexicalGlobalObject, globalObject.objectPrototype());

    if (!IDLUnsignedLongLong::isNullValue(dictionary.read)) {
        auto readValue = toJS<IDLUnsignedLongLong>(lexicalGlobalObject, throwScope, IDLUnsignedLongLong::extractValueFromNullable(dictionary.read));
        RETURN_IF_EXCEPTION(throwScope, {});
        result->putDirect(vm, JSC::Identifier::fromString(vm, "read"_s), readValue);
    }
    if (!IDLUnsignedLongLong::isNullValue(dictionary.written)) {
        auto writtenValue = toJS<IDLUnsignedLongLong>(lexicalGlobalObject, throwScope, IDLUnsignedLongLong::extractValueFromNullable(dictionary.written));
        RETURN_IF_EXCEPTION(throwScope, {});
        result->putDirect(vm, JSC::Identifier::fromString(vm, "written"_s), writtenValue);
    }
    return result;
}

// Functions

static JSC_DECLARE_HOST_FUNCTION(jsTextEncoderPrototypeFunction_encode);
static JSC_DECLARE_HOST_FUNCTION(jsTextEncoderPrototypeFunction_encodeInto);

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsTextEncoderConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsTextEncoder_encoding);

class JSTextEncoderPrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTextEncoderPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTextEncoderPrototype* ptr = new (NotNull, JSC::allocateCell<JSTextEncoderPrototype>(vm)) JSTextEncoderPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::GCClient::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTextEncoderPrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTextEncoderPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTextEncoderPrototype, JSTextEncoderPrototype::Base);

using JSTextEncoderDOMConstructor = JSDOMConstructor<JSTextEncoder>;

template<> EncodedJSValue JSC_HOST_CALL_ATTRIBUTES JSTextEncoderDOMConstructor::construct(JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame)
{
    VM& vm = lexicalGlobalObject->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* castedThis = jsCast<JSTextEncoderDOMConstructor*>(callFrame->jsCallee());
    ASSERT(castedThis);
    auto object = TextEncoder::create();
    if constexpr (IsExceptionOr<decltype(object)>)
        RETURN_IF_EXCEPTION(throwScope, {});
    static_assert(TypeOrExceptionOrUnderlyingType<decltype(object)>::isRef);
    auto jsValue = toJSNewlyCreated<IDLInterface<TextEncoder>>(*lexicalGlobalObject, *castedThis->globalObject(), throwScope, WTFMove(object));
    if constexpr (IsExceptionOr<decltype(object)>)
        RETURN_IF_EXCEPTION(throwScope, {});
    setSubclassStructureIfNeeded<TextEncoder>(lexicalGlobalObject, callFrame, asObject(jsValue));
    RETURN_IF_EXCEPTION(throwScope, {});
    return JSValue::encode(jsValue);
}
JSC_ANNOTATE_HOST_FUNCTION(JSTextEncoderDOMConstructorConstruct, JSTextEncoderDOMConstructor::construct);

template<> const ClassInfo JSTextEncoderDOMConstructor::s_info = { "TextEncoder"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTextEncoderDOMConstructor) };

template<> JSValue JSTextEncoderDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTextEncoderDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "TextEncoder"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSTextEncoder::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSTextEncoderPrototypeTableValues[] = {
    { "constructor"_s, static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t) static_cast<PropertySlot::GetValueFunc>(jsTextEncoderConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "encoding"_s, static_cast<unsigned>(JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute), NoIntrinsic, { (intptr_t) static_cast<PropertySlot::GetValueFunc>(jsTextEncoder_encoding), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "encode"_s, static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t) static_cast<RawNativeFunction>(jsTextEncoderPrototypeFunction_encode), (intptr_t)(0) } },
    { "encodeInto"_s, static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t) static_cast<RawNativeFunction>(jsTextEncoderPrototypeFunction_encodeInto), (intptr_t)(2) } },
};

const ClassInfo JSTextEncoderPrototype::s_info = { "TextEncoder"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTextEncoderPrototype) };

void JSTextEncoderPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTextEncoder::info(), JSTextEncoderPrototypeTableValues, *this);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSTextEncoder::s_info = { "TextEncoder"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTextEncoder) };

JSTextEncoder::JSTextEncoder(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TextEncoder>&& impl)
    : JSDOMWrapper<TextEncoder>(structure, globalObject, WTFMove(impl))
{
}

void JSTextEncoder::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(info()));

    // static_assert(!std::is_base_of<ActiveDOMObject, TextEncoder>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");
}

JSObject* JSTextEncoder::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTextEncoderPrototype::create(vm, &globalObject, JSTextEncoderPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTextEncoder::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTextEncoder>(vm, globalObject);
}

JSValue JSTextEncoder::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTextEncoderDOMConstructor, DOMConstructorID::TextEncoder>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTextEncoder::destroy(JSC::JSCell* cell)
{
    JSTextEncoder* thisObject = static_cast<JSTextEncoder*>(cell);
    thisObject->JSTextEncoder::~JSTextEncoder();
}

JSC_DEFINE_CUSTOM_GETTER(jsTextEncoderConstructor, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTextEncoderPrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTextEncoder::getConstructor(JSC::getVM(lexicalGlobalObject), prototype->globalObject()));
}

static inline JSValue jsTextEncoder_encodingGetter(JSGlobalObject& lexicalGlobalObject, JSTextEncoder& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLDOMString>(lexicalGlobalObject, throwScope, impl.encoding())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTextEncoder_encoding, (JSGlobalObject * lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTextEncoder>::get<jsTextEncoder_encodingGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

extern "C" JSC::EncodedJSValue TextEncoder__encode(JSC::JSGlobalObject* lexicalGlobalObject, const ZigString*);
extern "C" JSC::EncodedJSValue TextEncoder__encodeInto(JSC::JSGlobalObject* lexicalGlobalObject, const ZigString*, void* ptr, size_t len);

static inline JSC::EncodedJSValue jsTextEncoderPrototypeFunction_encodeBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTextEncoder>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->wrapped();
    EnsureStillAliveScope argument0 = callFrame->argument(0);
    if (argument0.value().isUndefined()) {
        return JSValue::encode(JSC::JSUint8Array::createUninitialized(lexicalGlobalObject, lexicalGlobalObject->m_typedArrayUint8.get(lexicalGlobalObject), 0));
    }
    auto input = argument0.value().toWTFString(lexicalGlobalObject);
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    auto str = Zig::toZigString(WTFMove(input));
    auto res = TextEncoder__encode(lexicalGlobalObject, &str);
    if (UNLIKELY(JSC::JSValue::decode(res).isObject() && JSC::JSValue::decode(res).getObject()->isErrorInstance())) {
        throwScope.throwException(lexicalGlobalObject, JSC::JSValue::decode(res));
        return encodedJSValue();
    }
    RELEASE_AND_RETURN(throwScope, res);
}

JSC_DEFINE_HOST_FUNCTION(jsTextEncoderPrototypeFunction_encode, (JSGlobalObject * lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTextEncoder>::call<jsTextEncoderPrototypeFunction_encodeBody>(*lexicalGlobalObject, *callFrame, "encode");
}

static inline JSC::EncodedJSValue jsTextEncoderPrototypeFunction_encodeIntoBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTextEncoder>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->wrapped();
    if (UNLIKELY(callFrame->argumentCount() < 2))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto source = argument0.value().toWTFString(lexicalGlobalObject);
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    EnsureStillAliveScope argument1 = callFrame->uncheckedArgument(1);
    auto destination = convert<IDLAllowSharedAdaptor<IDLUint8Array>>(*lexicalGlobalObject, argument1.value(), [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwArgumentTypeError(lexicalGlobalObject, scope, 1, "destination", "TextEncoder", "encodeInto", "Uint8Array"); });
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    auto str = Zig::toZigString(WTFMove(source));
    auto res = TextEncoder__encodeInto(lexicalGlobalObject, &str, destination->data(), destination->length());
    if (UNLIKELY(JSC::JSValue::decode(res).isObject() && JSC::JSValue::decode(res).getObject()->isErrorInstance())) {
        throwScope.throwException(lexicalGlobalObject, JSC::JSValue::decode(res));
        return encodedJSValue();
    }

    RELEASE_AND_RETURN(throwScope, res);
}

JSC_DEFINE_HOST_FUNCTION(jsTextEncoderPrototypeFunction_encodeInto, (JSGlobalObject * lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTextEncoder>::call<jsTextEncoderPrototypeFunction_encodeIntoBody>(*lexicalGlobalObject, *callFrame, "encodeInto");
}

JSC::GCClient::IsoSubspace* JSTextEncoder::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<JSTextEncoder, UseCustomHeapCellType::No>(
        vm,
        [](auto& spaces) { return spaces.m_clientSubspaceForTextEncoder.get(); },
        [](auto& spaces, auto&& space) { spaces.m_clientSubspaceForTextEncoder = WTFMove(space); },
        [](auto& spaces) { return spaces.m_subspaceForTextEncoder.get(); },
        [](auto& spaces, auto&& space) { spaces.m_subspaceForTextEncoder = WTFMove(space); });
}

void JSTextEncoder::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTextEncoder*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTextEncoderOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTextEncoderOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTextEncoder = static_cast<JSTextEncoder*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTextEncoder->wrapped(), jsTextEncoder);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable : 4483)
extern "C" {
extern void (*const __identifier("??_7TextEncoder@WebCore@@6B@")[])();
}
#else
extern "C" {
extern void* _ZTVN7WebCore11TextEncoderE[];
}
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TextEncoder>&& impl)
{

    if constexpr (std::is_polymorphic_v<TextEncoder>) {
#if ENABLE(BINDING_INTEGRITY)
        const void* actualVTablePointer = getVTablePointer(impl.ptr());
#if PLATFORM(WIN)
        void* expectedVTablePointer = __identifier("??_7TextEncoder@WebCore@@6B@");
#else
        void* expectedVTablePointer = &_ZTVN7WebCore11TextEncoderE[2];
#endif

        // If you hit this assertion you either have a use after free bug, or
        // TextEncoder has subclasses. If TextEncoder has subclasses that get passed
        // to toJS() we currently require TextEncoder you to opt out of binding hardening
        // by adding the SkipVTableValidation attribute to the interface IDL definition
        RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    }
    return createWrapper<TextEncoder>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TextEncoder& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TextEncoder* JSTextEncoder::toWrapped(JSC::VM&, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTextEncoder*>(value))
        return &wrapper->wrapped();
    return nullptr;
}

}
