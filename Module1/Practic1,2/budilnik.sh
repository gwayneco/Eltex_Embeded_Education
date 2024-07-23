#! /bin/bash

read -p "Время срабатывания в формате часы минуты:" hours mins
read -p "Файл с мелодией: " ringtone

touch tmp_file
echo "$mins $hours * * * aplay $ringtone" > tmp_file
crontab tmp_file
rm tmp_file
