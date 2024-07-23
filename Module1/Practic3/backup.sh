#! /bin/bash

read -p "Введите полный путь для папки, которую нужно скопировать: " main_folder
read -p "Введите полный путь папки, для копирования: " backup_folder
read -p "Введите периодичность для копирования в минутах: " mins


touch tmp_file
echo "*/$mins * * * * tar -cvzf $backup_folder/backup.tar.gzip" "$main_folder" > tmp_file
crontab tmp_file
rm tmp_file
