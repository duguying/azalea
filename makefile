iChat:ichat.c
	gcc ichat.c -lpthread -o iChat
clean:
	rm ./iChat
test:
	./iChat

