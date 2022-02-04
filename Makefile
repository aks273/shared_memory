CC=clang
CFLAGS= -g -Wall
OBJS=shared_memory.o
EXE=write_sh_mem.elf read_sh_mem.elf destroy_sh_mem.elf

all: $(EXE)

%.elf: %.o $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.dSYM *.o $(EXE)