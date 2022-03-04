vpath %.cpp src
vpath %.cpp src/frontend

CC :=g++
CPPFLAGS := -std=c++17 -O2
SOURCE := $(wildcard src/*.cpp src/frontend/*.cpp)
OBJECTS :=$(patsubst %.cpp,build/%.o,$(notdir $(SOURCE)))
DEPENDS :=$(patsubst %.o,%.d,$(OBJECTS))
TAEGETS := easycc

$(shell mkdir -p build)

.PHONY:all
all: $(TAEGETS)
	@echo build finish

$(TAEGETS) :$(OBJECTS)
	$(CC) $(CPPFLAGS) -lm $^ -o $@

scanner:src/frontend/parser.cpp src/frontend/token.cpp

src/frontend/parser.cpp:src/frontend/parser.y
	bison -o $@ -d $<

src/frontend/token.cpp:src/frontend/token.l
	flex -o $@ $<

build/%.o:%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

-include $(DEPENDS)

build/%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,build/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -r $@.$$$$

.PHONY:clean
clean:
	rm -r build/*
	# -rm ./src/frontend/token.cpp
	# -rm ./src/frontend/parser.hpp
	# -rm ./src/frontend/parser.cpp

