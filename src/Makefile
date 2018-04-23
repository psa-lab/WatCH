#
# Makefile for WatCH

CC = gcc
COPTS = -O
#COPTS = -g
INCLUDES = -Iinc
CFLAGS = $(COPTS) $(INCLUDES)
LIBS =  -lm

OBJS =  basics.o read_input_file.o distance.o complete_link_clustering.o \
	output_cluster_points.o

cluster: $(OBJS) main_cluster.c
	$(CC) $(CFLAGS) -o cluster main_cluster.c $(OBJS) $(LIBS)

.c.o: 
	$(CC) $(CFLAGS) -c $< 

touch:  
	touch *.c

clean:
	rm *.o
