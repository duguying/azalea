#!/bin/bash

mkdir build
cd build
cmake ..

case `uname -m` in
	i?86)				BITS=32 ;;
	amd64|x86_64)	BITS=64 ;;
esac

if [ "$CC"x = "gcc"x ]; then
	wget https://scan.coverity.com/download/linux-${BITS} -O cov-build-tools.tar.gz --post-data "project=duguying/Azalea&token=$COVERITY_SCAN_TOKEN"
	tar -zxf cov-build-tools.tar.gz

	COV_DIR=`find ./ -type d -name 'cov-analysis*'`
	export PATH=$PATH:$COV_DIR/bin

	cov-build --dir cov-int make
	tar czvf azalea.tgz cov-int
	curl --form project=duguying/Azalea \
	  --form token=$COVERITY_SCAN_TOKEN \
	  --form email=duguying2008@gmail.com \
	  --form file=@azalea.tgz \
	  --form version=Version \
	  --form description=Description \
	  http://scan5.coverity.com/cgi-bin/upload.py
else
	make
fi

make test