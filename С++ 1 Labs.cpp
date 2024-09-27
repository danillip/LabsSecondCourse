#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>

using namespace std;

struct Address {
	string street;
	int houseNumber;
	int apartmentNumber;
};

struct Record {
	string fullName;
	Address address;
	string phoneNumber;
	double balance;
};

class HashTable {
private:
	// Ввести три состояния в used
    enum class State { FREE, BUSY, REMOVED };
    
    struct HashItem {
        Record record;
        State state; // Теперь здесь используется перечисление State
    };


	vector<HashItem> table;
	int size; // текущий размер таблицы
	int capacity; // текущая ёмкость таблицы

	// Хеш-функция для адреса
	size_t hashFunction(const Address& address) {
		return address.houseNumber + address.apartmentNumber;
	}

	// Вторая хеш-функция для двойного хеширования
	size_t hashFunction2(const Address& address) {
	// Добавить getNextPrime
    return getNextPrime(address.street.length());
    }

	// Проверка на простое число
	bool isPrime(int n) {
		if (n <= 1) return false;
		if (n <= 3) return true;
		if (n % 2 == 0 || n % 3 == 0) return false;
		for (int i = 5; i * i <= n; i += 6) {
			if (n % i == 0 || n % (i + 2) == 0) return false;
		}
		return true;
	}

	// Нахождение ближайшего простого числа большего или равного n
	int getNextPrime(int n) {
		if (n <= 1) return 2;
		int prime = n;
		bool found = false;
		while (!found) {
			prime++;
			if (isPrime(prime)) {
				found = true;
			}
		}
		return prime;
	}

	// Увеличение размера таблицы
	void resizeTable() {
        int newCapacity = getNextPrime(capacity * 2);
        vector<HashItem> newTable(newCapacity, { Record(), State::FREE }); // Создаем новый вектор с пустыми записями
        for (const auto& item : table) {
            if (item.state == State::BUSY) {
                // Переписываем в новый вектор
                size_t index, step;
                for (index = hashFunction(item.record.address), step = hashFunction2(item.record.address);
                     newTable[index].state != State::FREE;
                     index = (index + step) % newCapacity) {}
    
                newTable[index].record = item.record;
                newTable[index].state = State::BUSY;
            }
        }
        table = move(newTable);
        capacity = newCapacity;
    }

public:
	HashTable(int initialCapacity = 200) : size(0), capacity(initialCapacity) {
    table.resize(capacity); // Изменяем размер вектора до начальной ёмкости
    for (auto& item : table) {
        item.state = State::FREE; // Заполняем состоянием FREE
    }
    }

	// Метод вставки элемента в таблицу
	void insert(const Record& record) {
    // Проверка на заполненность таблицы
    bool needResize = (size >= capacity / 2);
    if (needResize) {
        resizeTable();
    }

    // Находим индекс для вставки записи
    size_t index = hashFunction(record.address);
    size_t step = hashFunction2(record.address);
    while (table[index].state == State::BUSY) {
        index = (index + step) % capacity;
    }

    // Вставляем запись
    table[index].record = record;
    table[index].state = State::BUSY;
    size++;
    }
    
    bool isEqual(const Record& rec1, const Record& rec2) {
        return rec1.address.street == rec2.address.street &&
               rec1.address.houseNumber == rec2.address.houseNumber &&
               rec1.address.apartmentNumber == rec2.address.apartmentNumber;
    }
    
	// Метод удаления элемента из таблицы
	void remove(const Address& address) {
        size_t index = hashFunction(address);
        size_t step = hashFunction2(address);
        while (table[index].state != State::FREE) { // Проверка на состояние ячейки
            if (isEqual(table[index].record, { "", address.street, address.houseNumber, address.apartmentNumber })) {
                table[index].state = State::REMOVED; // Помечаем как удаленное
                size--;
                return;
            }
            index = (index + step) % capacity;
        }
    }

void printFullNameByAddress(const Address& address) {
    size_t index = hashFunction(address);
    size_t step = hashFunction2(address);
    while (table[index].state != State::FREE && table[index].state != State::REMOVED) { // Проверка на состояние ячейки
        if (table[index].record.address.street == address.street &&
            table[index].record.address.houseNumber == address.houseNumber &&
            table[index].record.address.apartmentNumber == address.apartmentNumber) {
            cout << "ФИО: " << table[index].record.fullName << endl;
            return;
        }
        index = (index + step) % capacity;
    }
    cout << "Нет записей для данного адреса" << endl;
}

void printTable() {
    for (size_t i = 0; i < capacity; ++i) {
        if (table[i].state == State::BUSY) { // Проверка на состояние ячейки
            cout << "Адрес: " << table[i].record.address.street << ", "
                 << table[i].record.address.houseNumber << ", "
                 << table[i].record.address.apartmentNumber << ", ";
            cout << "ФИО: " << table[i].record.fullName << endl;
        }
    }
}

void writeToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи" << endl;
        return;
    }

    for (size_t i = 0; i < capacity; ++i) {
        if (table[i].state == State::BUSY) { // Проверка на состояние ячейки
            file << table[i].record.fullName << "," << table[i].record.address.street << ","
                 << table[i].record.address.houseNumber << "," << table[i].record.address.apartmentNumber << ","
                 << table[i].record.phoneNumber << "," << table[i].record.balance << endl;
        }
    }

    file.close();
}

void clear() {
    table.clear(); // Очищаем вектор
    size = 0;
}


	// Метод чтения данных из файла
	void readFromFile(const string& filename) {
	    clear(); // Чистим таблицу перед чтением новых данных
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Ошибка при открытии файла для чтения" << endl;
			return;
		}

		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string fullName, street, phoneNumber;
			int houseNumber, apartmentNumber;
			double balance;

			getline(ss, fullName, ',');
			getline(ss, street, ',');
			ss >> houseNumber;
			ss.ignore();
			ss >> apartmentNumber;
			ss.ignore();
			getline(ss, phoneNumber, ',');
			ss >> balance;

			Record record = { fullName, {street, houseNumber, apartmentNumber}, phoneNumber, balance };
			insert(record);
		}

		file.close();
	}
};

void printMenu() {
	cout << "1. Вставить запись" << endl;
	cout << "2. Удалить запись" << endl;
	cout << "3. Найти запись по адресу и вывести ФИО" << endl;
	cout << "4. Вывести все записи" << endl;
	cout << "5. Записать данные в файл" << endl;
	cout << "6. Прочитать данные из файла" << endl;
	cout << "7. Очистить таблицу" << endl;
	cout << "8. Выйти" << endl;
	cout << "9. Рандомная генерация человека" << endl;
}

// Функция для генерации случайных данных по одному человеку
Record generateRecord() {
	static const string streets[] = { "ул. Ленина", "пр. Победы", "пер. Садовый", "пр. Гагарина", "ул. Пушкина" };
	static const string names[] = { "Иванов Иван Иванович", "Петров Петр Петрович", "Сидоров Сидор Сидорович", "Кузнецов Кузьма Кузьмич", "Николаев Николай Николаевич" };
	static const string phones[] = { "111-111", "222-222", "333-333", "444-444", "555-555" };

	string fullName = names[rand() % 5]; // Генерация случайного ФИО
	string street = streets[rand() % 5]; // Генерация случайной улицы
	int houseNumber = rand() % 100 + 1; // Генерация случайного номера дома от 1 до 100
	int apartmentNumber = rand() % 100 + 1; // Генерация случайного номера квартиры от 1 до 100
	string phoneNumber = phones[rand() % 5]; // Генерация случайного номера телефона
	double balance = (rand() % 10000) / 100.0; // Генерация случайного баланса от 0 до 9999.99

	return { fullName, {street, houseNumber, apartmentNumber}, phoneNumber, balance };
}

int main() {
	setlocale(LC_ALL, "RU");
	HashTable hashTable;

	int choice;
	do {
		printMenu();
		cout << "Выберите операцию: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			string fullName, street, phoneNumber;
			int houseNumber, apartmentNumber;
			double balance;

			cout << "Введите ФИО: ";
			cin.ignore();
			getline(cin, fullName);
			cout << "Введите улицу: ";
			getline(cin, street);
			cout << "Введите номер дома: ";
			cin >> houseNumber;
			cout << "Введите номер квартиры: ";
			cin >> apartmentNumber;
			cout << "Введите номер телефона: ";
			cin.ignore();
			getline(cin, phoneNumber);
			cout << "Введите баланс: ";
			cin >> balance;

			Record record = { fullName, {street, houseNumber, apartmentNumber}, phoneNumber, balance };
			hashTable.insert(record);
			break;
		}
		case 2: {
			string street;
			int houseNumber, apartmentNumber;

			cout << "Введите улицу: ";
			cin.ignore();
			getline(cin, street);
			cout << "Введите номер дома: ";
			cin >> houseNumber;
			cout << "Введите номер квартиры: ";
			cin >> apartmentNumber;

			Address address = { street, houseNumber, apartmentNumber };
			hashTable.remove(address);
			break;
		}
		case 3: {
			string street;
			int houseNumber, apartmentNumber;

			cout << "Введите улицу: ";
			cin.ignore();
			getline(cin, street);
			cout << "Введите номер дома: ";
			cin >> houseNumber;
			cout << "Введите номер квартиры: ";
			cin >> apartmentNumber;

			Address address = { street, houseNumber, apartmentNumber };
			hashTable.printFullNameByAddress(address);
			break;
		}
		case 4: {
			hashTable.printTable();
			break;
		}
		case 5: {
			string filename;
			cout << "Введите имя файла для записи: ";
			cin >> filename;
			hashTable.writeToFile(filename);
			break;
		}
		case 6: {
			string filename;
			cout << "Введите имя файла для чтения: ";
			cin >> filename;
			hashTable.readFromFile(filename);
			break;
		}
		case 7: {
			hashTable.clear();
			break;
		}
		case 8:
			cout << "Выход из программы." << endl;
			break;
		case 9: {
			// Генерация данных и добавление их в таблицу
			Record record = generateRecord();
			hashTable.insert(record);
			cout << "Сгенерирована запись:" << endl;
			cout << "ФИО: " << record.fullName << ", Адрес: " << record.address.street << ", " << record.address.houseNumber << ", " << record.address.apartmentNumber << ", Телефон: " << record.phoneNumber << ", Баланс: " << record.balance << endl;
			break;
		}
		default:
			cout << "Неверный выбор. Пожалуйста, введите число от 1 до 9." << endl;
		}
	} while (choice != 8);

	return 0;
}