CC = gcc
PROGRAMS = block block2 gethtml polling polling2 talk_client talk_server tcp_c tcp_s

block: block.c
	$(CC) -Wall -o $@ $^
block2: block2.c
	$(CC) -Wall -o $@ $^
gethtml: gethtml.c
	$(CC) -Wall -o $@ $^
polling: polling.c
	$(CC) -Wall -o $@ $^
polling2: polling2.c
	$(CC) -Wall -o $@ $^
talk_client: talk_client.c
	$(CC) -Wall -o $@ $^
talk_server: talk_server.c
	$(CC) -Wall -o $@ $^
tcp_c: tcp_c.c
	$(CC) -Wall -o $@ $^
tcp_s: tcp_s.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
