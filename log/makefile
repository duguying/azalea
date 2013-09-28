log:liblog.so
	gcc test.c -Lbin -llog -o bin/log
liblog.so:
	gcc -fpic -shared log.c -o bin/liblog.so
clean:
	rm -rf bin/*
debug:
	gcc test.c -D _DEBUG_ -o bin/log
test:
	bin/log
