CC         = g++
CC_FLAGS   = -std=c++0x
TARGET     = avl
INC_DIR    = include

.PHONY: all

all: $(TARGET).bin

$(TARGET).bin: $(TARGET).o
	$(CC) $(CC_FLAGS) -o $@ $?

$(TARGET).o: src/$(TARGET).cc $(INC_DIR)/*
	$(CC) -I$(INC_DIR) $(CC_FLAGS) -c $<

clean:
	rm -rf $(TARGET).bin $(TARGET).o
