#!/bin/bash

# Установка зависимостей
sudo apt update
sudo apt install wget

# Загрузка Google Chrome
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb

# Установка Google Chrome
sudo dpkg -i google-chrome-stable_current_amd64.deb
sudo apt install -f

# Удаление загруженного файла
rm google-chrome-stable_current_amd64.deb

