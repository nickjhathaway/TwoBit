#!/usr/bin/env bash

# this should work
uname -a | grep -v Darwin >/dev/null && exit 0

if [ $# -lt 1 ]; then
	FILES=bin/*
else
	FILES="$@"
fi

for f in $FILES; do

	echo "fixing binary: $f"

	#cppcms
	install_name_tool -change libcppcms.1.dylib "$(pwd)"/external/local/cppcms/lib/libcppcms.1.dylib $f

	install_name_tool -change libbooster.0.dylib "$(pwd)"/external/local/cppcms/lib/libbooster.0.dylib $f

	#armadillo
	install_name_tool -change libarmadillo.4.dylib "$(pwd)"/external/local/armadillo/lib/libarmadillo.4.dylib $f

	#bamtools
	install_name_tool -change libbamtools.2.3.0.dylib "$(pwd)"/external/local/bamtools/lib/bamtools/libbamtools.2.3.0.dylib $f

	#boost libraries
	install_name_tool -change libboost_program_options.dylib "$(pwd)"/external/local/boost/lib/libboost_program_options.dylib $f
	install_name_tool -change libboost_thread.dylib "$(pwd)"/external/local/boost/lib/libboost_thread.dylib $f
	install_name_tool -change libboost_filesystem.dylib "$(pwd)"/external/local/boost/lib/libboost_filesystem.dylib $f
	install_name_tool -change libboost_iostreams.dylib "$(pwd)"/external/local/boost/lib/libboost_iostreams.dylib $f
	install_name_tool -change libboost_regex.dylib "$(pwd)"/external/local/boost/lib/libboost_regex.dylib $f
	install_name_tool -change libboost_serialization.dylib "$(pwd)"/external/local/boost/lib/libboost_serialization.dylib $f
	install_name_tool -change libboost_system.dylib "$(pwd)"/external/local/boost/lib/libboost_system.dylib $f

done

