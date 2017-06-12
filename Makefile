.PHONY: build test

build:
	@mkdir -p build; cd build; cmake -DCMAKE_BUILD_TYPE=Debug ../ && make

clean:
	@rm -rf build

test: build
	@cd build; make test
