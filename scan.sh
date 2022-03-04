#!/bin/bash
flex -o src/frontend/token.cpp src/frontend/token.l
bison -d -o src/frontend/parser.cpp src/frontend/parser.y
