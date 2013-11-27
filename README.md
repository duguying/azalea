# Azalea #

[![travis](https://api.travis-ci.org/duguying/Azalea.png)](https://travis-ci.org/duguying/Azalea)
[![cmake](http://www.cmake.org/cmake/img/CMake-logo-triangle-download.jpg)](http://www.cmake.org/)

a chatting server

# design #

![design](https://rawgithub.com/duguying/Azalea/master/docs/design.svg)

# core #
![core](https://rawgithub.com/duguying/Azalea/master/docs/core.svg)

# build #

```shell
mkdir build
cd build
cmake ..
make
```

# let's have a try #

start OpenChat server in 1st terminal
>
```shell
./ichat
```

connect the server from the tcper in 2nd terminal
>
```shell
./bin/tcper
$lijun
```

open another connection in 3rd terminal
>
```shell
./tcper
$rex
*lijun
hello, this is a message send to lijun from rex
```

and then, the 2nd terminal will received the message `hello, this is a message send to lijun from rex`.

okay,the `tcper` have not finished. but you can try it by this [TCP/UDP Tester](http://pan.baidu.com/s/1cgtSA), if you are in Windows.

:smile:




