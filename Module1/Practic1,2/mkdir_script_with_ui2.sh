#!/bin/bash
RED='\033[0;31m'
NC='\033[0m' # No Color
echo -e "${RED}"

read -p "Введите директорию для расположения папок: " master_directory
read -p "Введите шаблон для наименования файлов: " name_template
read -p "Введите через пробел количество папок в главной директории, заглавной, количество файлов: " number_of_master_dirs number_of_submaster_dirs number_of_files

mkdir -p $master_directory

for i in $( seq 1 $number_of_master_dirs)
do
    mkdir $master_directory/$name_template$i
    for j in $( seq 1 $number_of_submaster_dirs)
    do
        mkdir $master_directory/$name_template$i/sub$name_template$j
        for n in $(seq 1 $number_of_files)
        do
        touch $master_directory/$name_template$i/sub$name_template$j/subsub$name_template$n
        done
    done
done

