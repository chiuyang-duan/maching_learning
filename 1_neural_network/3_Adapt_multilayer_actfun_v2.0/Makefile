
TARGET     := myneural

CC	   := gcc  

CFLAG	   := -Wall  

INCLUDES   := -I. 

SRCS    = feedforward_neural.c Common.c  
INCLUDE = Common.h data_retrieval.h

OBJS    = $(SRCS:.c=.o)  

all:

	$(CC) $(SRCS) -o $(TARGET) -lm $^

clean:     
	rm -rf $(basename $(TARGET)) $(SRCS:.c=.o)

