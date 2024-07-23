#!/bin/bash
master_directory="master"


for i in {1..50}
do
    mkdir $master_directory/submaster_directory_$i
    for j in {1..100}
    do
        mkdir $master_directory/submaster_directory_$i/slave_directory_$j
        for n in {1..200}
        do
        touch $master_directory/submaster_directory_$i/slave_directory_$j/sublsave_file_$n
        done
    done
done
