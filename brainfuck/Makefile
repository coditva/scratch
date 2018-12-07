# compiler and other options
CC=bfc

# keep it empty
all: a hello

# spit out as .o file
%: %.bf
	-@echo
	-@echo " --- Compiling $<"
	$(CC) $<

# clean the working dir
.PHONY: clean
clean:
	rm -rf ./*.out
