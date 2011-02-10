#include <v8.h>
#include <node.h>
#include <string.h>

namespace bitcoder {

using namespace v8;
using namespace node;

typedef unsigned char byte;

class Encoder : ObjectWrap {
  public:
    Encoder();

    static void Initialize(Handle<Object> target);
    static Handle<Value> New(const Arguments& args);
    static Handle<Value> Encode(const Arguments& args);

    int encode(const char* input, size_t len, char* output, bool flush);
    size_t bytesNeeded(size_t len, bool flush);

  private:
    int skip;
    byte carry;
};

};
