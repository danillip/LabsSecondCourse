#!/bin/bash

# Запрашиваем научное направление для удаления
read -p "Введите научное направление для удаления: " delete_direction

# Путь к папке с научным направлением
direction_folder="Научные направления/$delete_direction"

# Проверяем, существует ли папка с указанным научным направлением
if [ -d "$direction_folder" ]; then
    # Переходим в папку с научным направлением
    cd "$direction_folder" || exit

    # Перебираем все символьные ссылки внутри папки
    for link in *; do
        # Проверяем, является ли элемент символьной ссылкой
        if [ -L "$link" ]; then
            # Определяем путь, на который указывает символьная ссылка
            target=$(readlink "$link")
            # Переходим в родительский каталог и удаляем элемент, на который указывает символьная ссылка
            rm -rf "$target"
            echo "Удалены файлы из папки '$target'"
        fi
    done

    # Удаляем саму папку с научным направлением
    cd ..
    rm -rf "$delete_direction"
    echo "Папка с научным направлением '$delete_direction' успешно удалена."
else
    echo "Папка с научным направлением '$delete_direction' не найдена."
fi

