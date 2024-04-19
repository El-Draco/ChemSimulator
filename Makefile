BACKEND		=	backend		#rename to simulator or engine
FRONTEND	=	GUI 		#rename to renderer or smthn

NVCC		=	nvcc
NVCCFLAGS	=	-lcublas -lcurand

RM			=	rm
INC 		= 	-Iinc/

SRC_DIR 	= srcs
BIN_DIR 	= bin
OBJ_DIR 	= obj

#relative to their respective directories
COMM_SRCS	= 	#
BACKEND_SRCS	=	main.cpp Bond.cpp Molecule.cpp Vector3.cpp
FRONTEND_SRCS	=	main.cpp#

BACKEND_SRCS	:= ${addprefix srcs/backend/, ${BACKEND_SRCS}}
FRONTEND_SRCS	:= ${addprefix srcs/frontend/, ${FRONTEND_SRCS}}

all: $(BIN_DIR)/$(BACKEND) $(BIN_DIR)/$(FRONTEND)

$(BIN_DIR)/$(BACKEND): ${BACKEND_SRCS} ${COMM_SRCS}
	${NVCC} ${NVCCFLAGS} ${INC} $(BACKEND_SRCS) $(COMM_SRCS) -o $(BIN_DIR)/$(BACKEND)

$(BIN_DIR)/$(FRONTEND):
							cmake -B "./srcs/GUI/" -H"./srcs/GUI"
							cmake --build "./srcs/GUI/"
							make -C ./srcs/GUI/
							cp -rf ./srcs/GUI/GUI ./bin/frontend 

clean:
	${RM} $(BIN_DIR)/*
	${RM} positions.txt
