#! /bin/bash

BROWSER_PROJECT_ROOT=$(pwd)

mkdir -p out/build
mkdir -p bin

cmake -S $BROWSER_PROJECT_ROOT -B $BROWSER_PROJECT_ROOT/out/build

cd $BROWSER_PROJECT_ROOT/out/build
make
cp ./Browser $BROWSER_PROJECT_ROOT/bin
