# Programowanie grafiki 3D w OpenGL

## Jak zbudować

Na ubuntu
```sh
git clone https://gitlab.com/mdziemia/gl23_kanclerz_piotr.git --recurse-submodules
cd gl23_kanclerz_piotr
rm PreLoad.cmake
sudo apt-get install libwayland-dev pkg-config libxrandr-dev libxinerama-dev libxkbcommon-dev libxcursor-dev libxi-dev
mkdir build
cd build
cmake .. 
make
```

Na Windowsie
```
git clone https://gitlab.com/mdziemia/gl23_kanclerz_piotr.git --recurse-submodules
cd gl23_kanclerz_piotr
mkdir build
cd build
cmake ..
cmake --build .
```

## Jak uruchomić

Aplikacje budowane są np do build/src/labs/lab1

## Laboratorium 
[Laboratorium 1](./src/labs/lab1)

[Laboratorium 2](./src/labs/lab2)

[Laboratorium 3](./src/labs/lab3)

[Laboratorium 4](./src/labs/lab4)

## Projekt

[Projekt](./src/project/)

