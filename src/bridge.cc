#include <node.h>
#include <stdlib.h>  // calloc
#include "tesselator.h" // Libtess2 header file

namespace Bridge {
    // Helper functions
    v8::Handle<v8::Object> instanceObject()
    {
        static v8::Persistent<v8::ObjectTemplate> sObjectTemplate;
        if (sObjectTemplate.IsEmpty()) {
            sObjectTemplate = v8::Persistent<v8::ObjectTemplate>::New(v8::ObjectTemplate::New());
            sObjectTemplate->SetInternalFieldCount(1);
        }

        return sObjectTemplate->NewInstance();
    }

    TESStesselator* extractTesslator(v8::Handle<v8::Object> obj) {
        return reinterpret_cast<TESStesselator*>(obj->GetPointerFromInternalField(0));
    }

    int extractIntValue(const v8::Arguments & args, int index) {
        assert(args[index]->IsInt32());
        return args[index]->Int32Value();
    }

    v8::Handle<v8::Array> extractArrayValue(const v8::Arguments & args, int index) {
        assert(args[index]->IsArray());
        return v8::Handle<v8::Array>::Cast(args[index]);
    }

    // Exposed functions
    v8::Handle<v8::Value> _tessNewTess(const v8::Arguments & args)
    {
        v8::HandleScope handleScope;
        assert(args.Length() == 0);

        // Step 1 - Convert the V8 object to library C++ object.
        // There is no arguments. Skip this step.
        
        // Step 2 - Execute the library C++ function. 
        TESStesselator* tesslator = tessNewTess(NULL);
        
        // Step 3 - Convert the return value from library C++ object to V8 object.
        v8::Handle<v8::Object> v8object = instanceObject();
        v8object->SetPointerInInternalField(0, (void*)tesslator);

        // Step 4 - Return the V8 object.
        return v8object;
    }

    v8::Handle<v8::Value> _tessAddContour(const v8::Arguments & args)
    {
        v8::HandleScope handleScope;

        // Step 1 - Convert the V8 object to library C++ object.
        
        v8::Local<v8::Object> v8tesslator = v8::Local<v8::Object>::Cast(args[0]);
        TESStesselator* tesslator = extractTesslator(v8tesslator);

        int size = extractIntValue(args, 1);
        assert(size == 2 || size == 3);

        v8::Handle<v8::Array> v8array = extractArrayValue(args, 2);
        int numVertices = v8array->Length() / size;

        double* vertices = (double*)malloc(sizeof(double) * v8array->Length());
        for (unsigned int idx = 0; idx < v8array->Length(); ++idx ) {
            v8::Local<v8::Value> v8value = v8array->Get(v8::Int32::New(idx));
            vertices[idx] = v8value->NumberValue();
        }

        int stride = size * sizeof(double);
        
        // Step 2 - Execute the library C++ function. 
        tessAddContour(tesslator, size, vertices, stride, numVertices);
        free(vertices);

        // Step 3 - Convert the return value from library C++ object to V8 object.
        // There is no return value from the function. Skip this step.
        
        // Step 4 - Return the V8 object.
        return v8::Undefined();
    }
};

// Node.js Addon Module Initialization
void init(v8::Handle<v8::Object> target)
{
    v8::HandleScope scope;

    target->Set(v8::String::New("tessNewTess"), v8::FunctionTemplate::New(&Bridge::_tessNewTess)->GetFunction());
    target->Set(v8::String::New("tessAddContour"), v8::FunctionTemplate::New(&Bridge::_tessAddContour)->GetFunction());
}

NODE_MODULE(libtess2js, init);