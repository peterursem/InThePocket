echo 'Delete raster ASM objects'
cd raster
Rm *.o
cd ..
echo 'Delete bitmap ASM objects'
cd bitmaps
Rm *.o
cd ..
echo 'Delete sound ASM objects'
cd sound
Rm *.o
cd ..
echo 'Delete C object files'
cd build
Rm *.o
cd ..
echo 'Delete program'
Rm *.tos