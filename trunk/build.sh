cd ReleaseStatic
make clean
make
cd ..
cd ReleaseDynamic
make clean
make
cd ..
doxygen ALNSlib.doxyfile
