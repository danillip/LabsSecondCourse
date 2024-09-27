#!/bin/bash

# Функция для подсчета скрытых файлов в домашнем каталоге
count_hidden_files() {
    count=$(find ~/ -maxdepth 1 -type f -name ".*" | wc -l)
    echo "Количество скрытых файлов в домашнем каталоге: $count"
}

# Функция для создания скрытых файлов
create_hidden_files() {
    touch ~/.hidden_file1 ~/.hidden_file2 ~/.hidden_file3
    echo "Скрытые файлы созданы."
}

# Функция для установки приложения
install_app() {
    # Пути для установки
    bin_path="/usr/bin/"
    lib_path="/usr/lib/"
    doc_path="/usr/share/doc/алейников/"
    log_path="/var/log/"

    # Проверка и создание каталогов при необходимости
    if [ ! -d "$bin_path" ]; then
        sudo mkdir -p "$bin_path"
    fi
    if [ ! -d "$lib_path" ]; then
        sudo mkdir -p "$lib_path"
    fi
    if [ ! -d "$doc_path" ]; then
        sudo mkdir -p "$doc_path"
    elif [ -f "$doc_path" ]; then
        echo "Ошибка: $doc_path существует и является файлом, а не каталогом."
        exit 1
    fi

    # Копирование файлов в указанные каталоги
    sudo cp file_without_extension "$bin_path"
    sudo cp file_with_extension.lib "$lib_path"
    sudo cp file_with_extension.doc "$doc_path"

    # Установка прав на выполнение для файла без расширения
    sudo chmod +x "${bin_path}file_without_extension"
    sudo chown $(whoami):$(whoami) "${bin_path}file_without_extension"

    echo "Приложение установлено успешно."

    # Открытие каталогов после установки
    xdg-open "$bin_path"
    xdg-open "$lib_path"
    xdg-open "$doc_path"
    xdg-open "$log_path"
}

# Функция для создания трех файлов
create_files() {
    touch file_without_extension file_with_extension.lib file_with_extension.doc
    echo "Три файла созданы: file_without_extension, file_with_extension.lib, file_with_extension.doc"
}

# Функция для выполнения задания
perform_task() {
    # Получение от пользователя имени каталога, расширения файла и строки для поиска
    read -p "Введите имя каталога: " directory
    read -p "Введите расширение файла: " extension
    read -p "Введите строку для поиска: " search_string

    # Поиск файлов с указанным расширением и содержащих указанную строку
    find "$directory" -type f -name "*.$extension" -exec grep -l "$search_string" {} + > "/var/log/$(whoami).log"

    echo "Поиск завершен. Результаты записаны в файл /var/log/$(whoami).log."
}

# Меню
while true; do
    echo "Меню:"
    echo "1. Подсчитать скрытые файлы в домашнем каталоге(только без прав админа использовать, иначе он создает папку рут)"
    echo "2. Создать скрытые файлы в домашнем каталоге"
    echo "3. Установить приложение"
    echo "4. Создать три файла для приложения"
    echo "5. Открыть каталоги для приложения"
    echo "6. Выполнить задание"
    echo "7. Выйти"
    read -p "Выберите действие [1-7]: " choice

    case $choice in
        1) count_hidden_files ;;
        2) create_hidden_files ;;
        3) install_app ;;
        4) create_files ;;
        5) echo "Открываю каталоги для приложения..." ; sleep 1; install_app ;;
        6) perform_task ;;
        7) echo "Выход"; exit ;;
        *) echo "Некорректный выбор. Попробуйте еще раз." ;;
    esac
done

