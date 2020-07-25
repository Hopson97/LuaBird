#!/bin/bash

if [ "$1" = "release" ]
then
    ./bin/release/LuaBird 
else
    ./bin/debug/LuaBird 
fi