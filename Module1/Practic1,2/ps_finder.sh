#! /bin/bash

read -p "Введите имя процесса:" process
read -p "Введите периодичность проверки в секундах:" period

while true
do
	ps aux | grep -e $process > temp.txt
	if [[ $process != "grep" ]]
	then
		temp_var=`grep -v "grep" temp.txt`
	fi
	if [[ $temp_var == "" ]]
	then 
		echo "Процесс не запущен"
		echo "Запуск процесса"
		$process
	else
		echo "Процесс запущен"
	fi
	echo "Следующая проверка через:" $period "секунд"
	sleep $period
done
