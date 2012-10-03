# bitcoder

> **STATUS: DEFUNCT** - To be honest, I'm not sure why I ever thought writing a C++ module was a good idea. I hate C++, but I wanted to play around with writing native code for Node, and encoding buffers seemed like an obvious case where you could get some considerable speedup. That did happen, but it's just not worth maintaining, I mean, who would want to base32-encode large chunks of data?

It's a streaming C++ Node addon for encoding/decoding byte streams to alternate bases.

Right now it only supports [Base 32][] encoding. An example `test.js`:

    var bitcoder = require('bitcoder')
    var encoder = new bitcoder.Encoder()
    // Encoder::encode(chunk, flush) - set flush=true for the final chunk
    var base32 = encoder.encode(new Buffer("Hello World"), true)
    console.log(base32.toString('ascii'))var encoder = new require('bitcoder').Encoder()

Result:

    $ node test.js
    91jprv3f41bpywkccg

## Install

    $ npm install bitcoder

## WHY?

Mostly to learn the Node C++ API, partially because [Base 32][] using only JS is slow as a dog, if that dog were a quadruple amputee. Aww, now I made myself sad.

## Formalia

Do whatever you want with the code, and I like pull requests, failing tests, and issue tickets.

[Base 32]: https://github.com/agnoster/base32-js/
