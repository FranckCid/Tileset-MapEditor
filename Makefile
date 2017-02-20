cc = g++ #					# Compiler
src = source/*.cpp #				# Source
cv = -std=c++11 #				# C++ version
in = -I./include -lSDL2 -lSDL2_image -lSDL2_ttf # Includes
w = -w #					# Warning
o = -o o #					# Output

all :
	$(cc) $(src) $(cv) $(in) $(w) $(o)

