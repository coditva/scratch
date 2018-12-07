CC         = g++
CC_FLAGS   = -std=c++0x -g
TARGET     = avl
INC_DIR    = include

.PHONY: all

all: $(TARGET).bin

$(TARGET).bin: src/$(TARGET).o
	$(CC) $(CC_FLAGS) -o $@ $<

src/$(TARGET).o: src/$(TARGET).cc $(INC_DIR)/*
	$(CC) -I$(INC_DIR) $(CC_FLAGS) -o $@ -c $<

clean:
	rm `find \
        -name "*.bin"   -o \
        -name "*.o"     -o \
        -name "*.gch" `
