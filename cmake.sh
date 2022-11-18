#! /bin/sh

cmake -Bbuild -DMY_VAR="FT_OPENGL"

echo "Cmake DONE!"

make -C ./build

echo "make DONE!"

mv ./build/FT_OPENGL ./
