test: clean default
	node test.js

default:
	node-waf configure build

clean:
	rm -rf build/
