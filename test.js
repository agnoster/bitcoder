bitcoder = require('./bitcoder')

console.log(bitcoder)

var e = new bitcoder.Encoder()
var b = new Buffer("Hello World")
console.log(e.encode(b, true).toString('ascii'))
