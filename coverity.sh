#!/bin/bash
		
wget https://scan.coverity.com/download/Linux -O cov-build-tools.gz --post-data "project=azalea&token=FgaZPLkFHxZOZXrOFUJm6Q"
tar -zxvf cov-build-tools.gz
export PATH=$PATH:$PWD/cov-build-tools/bin
cov-build --dir cov-int make
tar czvf azalea.tgz cov-int
curl --form project=duguying/Azalea \
  --form token=FgaZPLkFHxZOZXrOFUJm6Q \
  --form email=duguying2008@gmail.com \
  --form file=@azalea.tgz \
  --form version=Version \
  --form description=Description \
  http://scan5.coverity.com/cgi-bin/upload.py