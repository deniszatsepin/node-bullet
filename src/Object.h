#pragma once

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
using namespace v8;
using namespace node;

#define OBJECT_DEF_START(CLASS) \
	class CLASS : public node::ObjectWrap { \
		public: \
			static Persistent<FunctionTemplate> constructor; \
			static void Initialize(Handle<Object> target); \
			static Handle<Value> New(const Arguments &args); \
		private: \
			~CLASS(); \
		public:

#define OBJECT_DEF_END() \
	};

#define OBJECT_DEF_FUNCTION(NAME) \
	static Handle<Value> NAME(const Arguments &args)

#define OBJECT_FUNCTION_START(CLASS,NAME) \
	Handle<Value> CLASS::NAME(const Arguments &args) { \
		HandleScope scope; \
		CLASS* self = ObjectWrap::Unwrap<CLASS>(args.This());

#define OBJECT_FUNCTION_END() \
	}

#define OBJECT_INIT_START(CLASS) \
	Persistent<FunctionTemplate> CLASS::constructor; \
	void CLASS::Initialize(Handle<Object> target) { \
		Local<String> __classname = String::NewSymbol( #CLASS ); \
		HandleScope scope; \
		constructor = Persistent<FunctionTemplate>::New(FunctionTemplate::New(CLASS::New)); \
		constructor->InstanceTemplate()->SetInternalFieldCount(1); \
		constructor->SetClassName(__classname);

#define OBJECT_INIT_END(CLASS) \
		target->Set(__classname, constructor->GetFunction()); \
	}

#define OBJECT_NEW_START(CLASS) \
	Handle<Value> CLASS::New(const Arguments &args) { \
		HandleScope scope; \
		CLASS* self = new CLASS();

#define OBJECT_NEW_END() \
		self->Wrap(args.This()); \
		return args.This(); \
	}

#define OBJECT_DELETE_START(CLASS) \
	CLASS::~CLASS() {

#define OBJECT_DELETE_END() \
	}
