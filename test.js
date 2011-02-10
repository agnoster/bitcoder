var bitcoder = require('bitcoder')
var encoder = new bitcoder.Encoder()
// Encoder::encode(chunk, flush) - set flush=true for the final chunk
var base32 = encoder.encode(new Buffer("Hello World"), true)
console.log(base32.toString('ascii'))
