
ubuntu@ubuntu:~$ sleep 60
^Z
[1]+  Остановлен    sleep 60
ubuntu@ubuntu:~$ bg
[1]+ sleep 60 &
ubuntu@ubuntu:~$ fg 1
sleep 60


# Задача 4
# Создание именованного канала
mkfifo mychannel

# Передача списка файлов домашнего каталога вместе с подкаталогами в канал
ls -R ~/ > mychannel &

# Передача одного каталога вместе с файлами и подкаталогами в канал
ls -R /etc/ > mychannel &

# Чтение данных из канала
cat < mychannel

# Удаление именованного канала
rm mychannel

# Полный листинг процессов текущего пользователя
ps -ef | awk '{print $2, $3, $7, $8, $10}'

# Приостановка выполнения процесса и его возобновление
ubuntu@ubuntu:~$ sleep 200 &
[1] 9130
ubuntu@ubuntu:~$ kill -SIGSTOP 9130
ubuntu@ubuntu:~$ kill -SIGCONT 9130
ubuntu@ubuntu:~$ fg 1
sleep 200



# Определение идентификатора и имени последнего процесса, созданного пользователем root
ps -eo user,pid,cmd --sort=start_time | grep root | tail -n 1

