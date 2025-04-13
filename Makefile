CC = g++
CFLAGS = -g -Wall 
TARGET = server
TARGET2 = client

all: $(TARGET) $(TARGET2)

$(TARGET): server.o serverMain.o user.o
	$(CC) $(CFLAGS) -o $(TARGET) $^

$(TARGET2): client.o clientMain.o
	$(CC) $(CFLAGS) -o $(TARGET2) $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f server.o client.o serverMain.o clientMain.o user.o $(TARGET) $(TARGET2) 