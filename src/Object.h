#pragma once

#include "Util.h"

/*******************************
	DEFINITION
*******************************/

#define OBJECT_DEF_START(CLASS) \
	class CLASS : public node::ObjectWrap { \
		public: \
			static Persistent<FunctionTemplate> constructor; \
			static CLASS* Unwrap(Handle<Value> handle); \
			static bool HasInstance(Handle<Value> handle); \
			static void Initialize(Handle<Object> target); \
			static Handle<Value> New(const Arguments &args); \
		private: \
			~CLASS(); \
		public:

#define OBJECT_DEF_END() \
	};

#define OBJECT_DEF_FUNCTION(NAME) \
	static Handle<Value> func_ ## NAME (const Arguments &args);

#define OBJECT_DEF_ACCESSOR(NAME) \
	static Handle<Value> func_get_ ## NAME (Local<String> property, const AccessorInfo &info); \
	static void func_set_ ## NAME (Local<String> property, Local<Value> value, const AccessorInfo &info);

/*******************************
	INIT
*******************************/

#define OBJECT_INIT_START(CLASS) \
	Persistent<FunctionTemplate> CLASS::constructor; \
	CLASS* CLASS::Unwrap(Handle<Value> handle) { \
		Local<Object> obj = handle->ToObject(); \
		return ObjectWrap::Unwrap<CLASS>(obj); \
	} \
	bool CLASS::HasInstance(Handle<Value> handle) { \
		return CLASS::constructor->HasInstance(handle); \
	} \
	void CLASS::Initialize(Handle<Object> target) { \
		HandleScope scope; \
		Local<String> __classname = String::NewSymbol( #CLASS ); \
		constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(CLASS::New)); \
		constructor->InstanceTemplate()->SetInternalFieldCount(1); \
		constructor->SetClassName(__classname);

#define OBJECT_INIT_END(CLASS) \
		target->Set(__classname, constructor->GetFunction()); \
	}

#define OBJECT_INIT_FUNCTION(NAME) \
	constructor->PrototypeTemplate()->Set( \
		String::NewSymbol( #NAME ), \
		FunctionTemplate::New( func_ ## NAME ) \
	);

#define OBJECT_INIT_ACCESSOR(NAME) \
	constructor->PrototypeTemplate()->SetAccessor( \
		String::NewSymbol( #NAME ), \
		func_get_ ## NAME, func_set_ ## NAME );

/********************************
	NEW
********************************/

#define OBJECT_NEW_START(CLASS) \
	Handle<Value> CLASS::New(const Arguments &args) { \
		HandleScope scope; \
		CLASS* self = new CLASS();

#define OBJECT_NEW_END() \
		self->Wrap(args.This()); \
		return args.This(); \
	}

/*******************************
	DELETE
*******************************/

#define OBJECT_DELETE_START(CLASS) \
	CLASS::~CLASS() {

#define OBJECT_DELETE_END() \
	}

/*******************************
	FUNCTIONS
*******************************/

#define OBJECT_FUNCTION_START(CLASS,NAME) \
	Handle<Value> CLASS::func_ ## NAME (const Arguments &args) { \
		HandleScope scope; \
		CLASS* self = ObjectWrap::Unwrap<CLASS>(args.This()); \
		Handle<Value> result = Undefined();

#define OBJECT_FUNCTION_END() \
		return scope.Close(result); \
	}

#define OBJECT_GETTER_START(CLASS,NAME) \
	Handle<Value> CLASS::func_get_ ## NAME (Local<String> property, const AccessorInfo &info) { \
		HandleScope scope; \
		CLASS* self = ObjectWrap::Unwrap<CLASS>(info.This()); \
		Handle<Value> result = Undefined();

#define OBJECT_GETTER_END() \
		return scope.Close(result); \
	}

#define OBJECT_SETTER_START(CLASS,NAME) \
	void CLASS::func_set_ ## NAME (Local<String> property, Local<Value> value, const AccessorInfo &info) { \
		HandleScope scope; \
		CLASS* self = ObjectWrap::Unwrap<CLASS>(info.This());

#define OBJECT_SETTER_END() \
	}






