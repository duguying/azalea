test:liblog.so
	gcc test.c -Lbin -llog -o bin/test
liblog.so:
	gcc -fpic -shared log.c -o bin/liblog.so
clean:
	rm -rf bin/*
