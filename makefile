CXX = g++
CXXFLAGS = -std=c++17 -I"/opt/homebrew/Cellar/sfml@2/2.6.2_1/include"
LDFLAGS = -L"/opt/homebrew/Cellar/sfml@2/2.6.2_1/lib" -lsfml-graphics -lsfml-window -lsfml-system
SRC = timber.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = timber-app

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
