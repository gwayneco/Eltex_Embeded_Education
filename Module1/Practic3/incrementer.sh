echo "$(date +%H:%M) I run $(($(tail -1 /home/user/Eltex/Scripts/Module1/Practic3/date_time.txt | awk -F ' ' '{print $4}')+1)) time" >> /home/user/Eltex/Scripts/Module1/Practic3/date_time.txt
