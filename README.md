# Azalea #


<table>
	<tr>
		<td>linux</td>
		<td>windows</td>
		<td>coverity</td>
		<td>cmake</td>
	</tr>
	<tr>
		<td>
			<a title="travis" href="https://travis-ci.org/duguying/Azalea">
				<img src="https://api.travis-ci.org/duguying/Azalea.png" />
			</a>
		</td>
		<td>
			<a title="Build status" href="https://ci.appveyor.com/project/duguying/azalea">
				<img src="https://ci.appveyor.com/api/projects/status/c443id309jwrmb5t" />
			</a>
		</td>
		<td>
			<a title="coverity" href="https://scan.coverity.com/projects/1501">
				<img src="https://scan.coverity.com/projects/1501/badge.svg" />
			</a>
		</td>
		<td>
			<a title="cmake" href="http://www.cmake.org/">
				<img src="http://www.cmake.org/cmake/img/CMake-logo-triangle-download.jpg" />
			</a>2.8
		</td>
	</tr>
</table>


a chatting server

# design #

![design](https://rawgithub.com/duguying/Azalea/master/docs/design.svg)

# core #
![core](https://rawgithub.com/duguying/Azalea/master/docs/core.svg)

# build #

**linux**

```shell
mkdir build
cd build
cmake ..
make
```

**windows (MSVC 9+ build)**

```shell
mkdir build
cd build
cmake -G"NMake Makefiles" ..
nmake
```

# let's have a try #

start Azalea server in 1st terminal
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

:smile:


=======
# Azalea #


||linux||[![travis](https://api.travis-ci.org/duguying/Azalea.png)](https://travis-ci.org/duguying/Azalea)||
||windows||[![Build status](https://ci.appveyor.com/api/projects/status/c443id309jwrmb5t)](https://ci.appveyor.com/project/duguying/azalea)||
||coverity||[![coverity](https://scan.coverity.com/projects/1501/badge.svg)](https://scan.coverity.com/projects/1501)||
||cmake||[![cmake](http://www.cmake.org/cmake/img/CMake-logo-triangle-download.jpg)](http://www.cmake.org/)2.8||
<table>
<td>
	<tr>111</tr>
	<tr>222</tr>
	<tr>333</tr>
</td>
<td>
	<tr>111</tr>
	<tr>222</tr>
	<tr>333</tr>
</td>
</table>
a chatting server

# design #

![design](https://rawgithub.com/duguying/Azalea/master/docs/design.svg)

# core #
![core](https://rawgithub.com/duguying/Azalea/master/docs/core.svg)

# build #

**linux**

```shell
mkdir build
cd build
cmake ..
make
```

**windows (MSVC 9+ build)**

```shell
mkdir build
cd build
cmake -G"NMake Makefiles" ..
nmake
```

# let's have a try #

start Azalea server in 1st terminal
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

:smile:
