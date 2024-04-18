BACKEND		=	backend		#rename to simulator or engine
FRONTEND	=	frontend	#rename to renderer or smthn

NVCC		=	nvcc
NVCCFLAGS	=	-lcublas -lcurand

RM			=	rm
INC 		= 	inc/

SRC_DIR 	= srcs
BIN_DIR 	= bin
OBJ_DIR 	= obj

#relative to their respective directories
COMM_SRCS	= 	#
BACKEND_SRCS	=	main.cpp
FRONTEND_SRCS	=	main.cpp#

BACKEND_SRCS	:= ${addprefix srcs/backend/, ${BACKEND_SRCS}}
FRONTEND_SRCS	:= ${addprefix srcs/frontend/, ${FRONTEND_SRCS}}

all: setup $(BIN_DIR)/$(BACKEND) $(BIN_DIR)/$(FRONTEND)

$(BIN_DIR)/$(BACKEND): ${BACKEND_SRCS} ${COMM_SRCS}
	${NVCC} ${NVCCFLAGS} $(BACKEND_SRCS) $(COMM_SRCS) -o $(BIN_DIR)/$(BACKEND)

$(BIN_DIR)/$(FRONTEND):	${FRONTEND_SRCS} ${COMM_SRCS}
	${NVCC} ${NVCCFLAGS} $(FRONTEND_SRCS) $(COMM_SRCS) -o $(BIN_DIR)/$(FRONTEND)


clean:
	${RM} $(BIN_DIR)/*

setup: