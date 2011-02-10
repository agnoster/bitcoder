#include <v8.h>
#include <node.h>

#include "bitcoder.h"

using namespace node;
using namespace v8;

extern "C" {
  void init (Handle<Object> target)
  {
    HandleScope scope;
    target->Set(String::New("hello"), String::New("world"));
    bitcoder::Encoder::Initialize(target);
  }
  NODE_MODULE(bitcoder,init);
}


