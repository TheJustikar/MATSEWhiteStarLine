OBJS =  main.o Output.o CurrentField.o RoutePart.o Segment.o Vector2D.o  Input.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all : matse

matse : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o matse

RoutePart.o : MATSEWhiteStarLine/RoutePart.h MATSEWhiteStarLine/RoutePart.cpp MATSEWhiteStarLine/CurrentField.h MATSEWhiteStarLine/CurrentField.cpp MATSEWhiteStarLine/Segment.h MATSEWhiteStarLine/Segment.cpp MATSEWhiteStarLine/Vector2D.h MATSEWhiteStarLine/Vector2D.cpp
	$(CC) $(CFLAGS) MATSEWhiteStarLine/RoutePart.cpp

CurrentField.o : MATSEWhiteStarLine/CurrentField.h MATSEWhiteStarLine/CurrentField.cpp MATSEWhiteStarLine/Segment.h MATSEWhiteStarLine/Segment.cpp MATSEWhiteStarLine/Vector2D.h MATSEWhiteStarLine/Vector2D.cpp
	$(CC) $(CFLAGS) MATSEWhiteStarLine/CurrentField.cpp

Segment.o : MATSEWhiteStarLine/Segment.h MATSEWhiteStarLine/Segment.cpp MATSEWhiteStarLine/Vector2D.h MATSEWhiteStarLine/Vector2D.cpp
	$(CC) $(CFLAGS) MATSEWhiteStarLine/Segment.cpp

Vector2D.o : MATSEWhiteStarLine/Vector2D.h MATSEWhiteStarLine/Vector2D.cpp
	$(CC) $(CFLAGS) MATSEWhiteStarLine/Vector2D.cpp

Input.o : MATSEWhiteStarLine/Input.h MATSEWhiteStarLine/Input.cpp MATSEWhiteStarLine/CurrentField.h MATSEWhiteStarLine/CurrentField.cpp MATSEWhiteStarLine/Segment.h MATSEWhiteStarLine/Segment.cpp MATSEWhiteStarLine/Vector2D.h MATSEWhiteStarLine/Vector2D.cpp
	$(CC) $(CFLAGS)  MATSEWhiteStarLine/Input.cpp

Output.o : MATSEWhiteStarLine/Output.h MATSEWhiteStarLine/Output.cpp MATSEWhiteStarLine/Input.h MATSEWhiteStarLine/Input.cpp MATSEWhiteStarLine/RoutePart.h MATSEWhiteStarLine/RoutePart.cpp
	$(CC) $(CFLAGS)  MATSEWhiteStarLine/Output.cpp

main.o : MATSEWhiteStarLine/main.cpp MATSEWhiteStarLine/Output.h MATSEWhiteStarLine/Output.cpp MATSEWhiteStarLine/Input.h MATSEWhiteStarLine/Input.cpp MATSEWhiteStarLine/RoutePart.h MATSEWhiteStarLine/RoutePart.cpp MATSEWhiteStarLine/CurrentField.h MATSEWhiteStarLine/CurrentField.cpp MATSEWhiteStarLine/Segment.h MATSEWhiteStarLine/Segment.cpp MATSEWhiteStarLine/Vector2D.h MATSEWhiteStarLine/Vector2D.cpp
	$(CC) $(CFLAGS) MATSEWhiteStarLine/RoutePart.cpp

clean:
	\rm *.o *~ matse 
