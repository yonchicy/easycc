
all:
	@mkdir -p build
	@cd build && cmake .. && make -j 20
	@echo build finished

.PHONY:test
test:
	@cd test && ./test.sh

clean:
	@cd build && make clean
