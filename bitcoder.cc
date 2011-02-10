#include "bitcoder.h"
#include <node_buffer.h>

using namespace bitcoder;
using namespace v8;
using namespace node;

const char* alphabet = "0123456789abcdefghjkmnpqrtuvwxyz";
const int bits = 5;

Encoder::Encoder() :
  skip(0), carry(0)
{
}

int Encoder::encode(const char* input, size_t len, char* output, bool flush)
{
  int i = 0, pos = 0;
  while (i < len) {
    if (skip < 0) { // we have carry-over
      carry |= (byte)input[i] >> (-skip);
    } else {
      carry = (byte)input[i] << skip;
    }
    if (skip > 8 - bits) {
      // need more input to produce output
      ++i;
      skip -= 8;
      continue;
    }
    if (skip <= 8 - bits) {
      // move on to next input character
      skip += bits;
      output[pos++] = alphabet[carry >> (8-bits)];
    }
    if (skip >= 8) {
      ++i;
      skip -= 8;
    }
  }
  if (flush && skip < 0) {
    output[pos++] = alphabet[carry >> (8-bits)];
  }
  return pos;
}

size_t Encoder::bytesNeeded(size_t len, bool flush)
{
  size_t bitlen = len * 8 - skip;
  if (flush) bitlen += 4;
  return bitlen / 5;
}

bool isTrue(Handle<Value> v) {
  return v->IsBoolean() && v->ToBoolean()->Value();
}

Handle<Value> Encoder::Encode(const Arguments& args) {
  HandleScope scope;
  Encoder* encoder = ObjectWrap::Unwrap<Encoder>(args.This());
  Local<Object> input_buffer = args[0]->ToObject();
  bool flush = args.Length() > 1 && isTrue(args[1]);
  size_t outlen = encoder->bytesNeeded(Buffer::Length(input_buffer), flush);
  Buffer* output_buffer = Buffer::New(outlen);
  encoder->encode(Buffer::Data(input_buffer), Buffer::Length(input_buffer), Buffer::Data(output_buffer), flush);
  return scope.Close(output_buffer->handle_);
}

Handle<Value> Encoder::New(const Arguments& args) {
  HandleScope scope;
  Encoder *r = new Encoder();
  r->Wrap(args.This());
  return scope.Close(args.This());
}

void Encoder::Initialize(Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  NODE_SET_PROTOTYPE_METHOD(t, "encode", Encode);
  target->Set(String::NewSymbol("Encoder"), t->GetFunction());
}
