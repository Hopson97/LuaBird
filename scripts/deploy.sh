#!/bin/bash

sh scripts/build.sh release 

rm -rf -d LuaBird

mkdir LuaBird

cp bin/release/LuaBird LuaBird
cp -r res LuaBird

echo "Deploy build created."
echo "cd LuaBird to find it"