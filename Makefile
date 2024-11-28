# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++11 -Wall

# Source Files
SRCS = question2.cpp

# Object Files
OBJS = $(SRCS:.cpp=.o)

# Output Binaries
DEBUG_BIN = admin_debug.exe
OPT_BIN = admin_optimized.exe

# Default Target (All)
all: debug optimized

# Debug Build
debug: CXXFLAGS += -g
debug: $(DEBUG_BIN)

$(DEBUG_BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Optimized Build
optimized: CXXFLAGS += -O2
optimized: $(OPT_BIN)

$(OPT_BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean rule to remove generated files (Windows version)
clean:
	del /Q *.o $(DEBUG_BIN) $(OPT_BIN)
