#! /bin/sh

cmake -Bbuild -DMY_VAR="ft_opengl"

echo "Cmake DONE!"

make -C ./build

echo "make DONE!"

mv ./build/ft_opengl ./

./ft_opengl