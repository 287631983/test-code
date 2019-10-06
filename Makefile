all:server client
.PHONEY:all
.PHONEY:clean
CFLAGS=-g -Wall -o0
OBJS1=server.c
OBJS2=client.c
server:$(OBJS1)
	@$(CC) $(CFLAGS) $^ -o $@
client:$(OBJS2)
	@$(CC) $(CFLAGS) $^ -o $@
clean:
	@$(RM) -rf server client