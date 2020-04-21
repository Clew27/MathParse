MAIN_PRG  = parse_test.cpp
MAIN_SRCS = lex exception parse
ALL_SRCS  = $(patsubst %, ../../src/%.cpp, ${MAIN_SRCS}) ${MAIN_PRG}
OBJECTS   = ${ALL_SRCS:.cpp=.o}
EXEC_BIN  = ${MAIN_PRG:.cpp=.exe}

GPP       = g++ -std=c++17 -g -O0
WARNING   = -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast
GPP_WARN  = ${GPP} ${WARNING} 

all : ${EXEC_BIN}

${EXEC_BIN} : ${OBJECTS}
	${GPP_WARN} ${OBJECTS} -o ${EXEC_BIN}

%.o : %.cpp
	${GPP_WARN} -c $< -o $@

run : ${EXEC_BIN}
	./${EXEC_BIN}

clean :
	-rm ${OBJECTS}

spotless : clean
	-rm ${EXEC_BIN}
