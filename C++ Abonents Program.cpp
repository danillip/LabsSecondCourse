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

struct Record { //Вынеси мне IsEqual в struct record
	string fullName;
	Address address;
	string phoneNumber;
	double balance;
	size_t hashCode;

	Record() : fullName(""), address(Address()), phoneNumber(""), balance(0.0), hashCode(0) {}

	Record(const string& fullName, const Address& address, const string& phoneNumber, double balance) :
		fullName(fullName), address(address), phoneNumber(phoneNumber), balance(balance) {
		hashCode = calculateHashCode();
	}

	size_t calculateHashCode() const {
		size_t hash = 0;
		hash = address.houseNumber + address.apartmentNumber;
		hash += hash_string(fullName);
		hash += hash_string(phoneNumber);
		return hash;
	}

	size_t hash_string(const string& str) const {
		size_t hash = 0;
		for (char ch : str) {
			hash = hash * 31 + ch;
		}
		return hash;
	}

	// Метод для проверки равенства двух записей по адресу
	bool isEqual(const Address& otherAddress) const {
		return address.street == otherAddress.street &&
			address.houseNumber == otherAddress.houseNumber &&
			address.apartmentNumber == otherAddress.apartmentNumber;
	}
};

template<typename T>
class HashTable {
private:
	enum class State { FREE, BUSY, REMOVED };

	struct HashItem {
		Record record;
		State state;

		void print() {
			cout << "Адрес: " << record.address.street << ", "
				<< record.address.houseNumber << ", "
				<< record.address.apartmentNumber << ", ";
			cout << "ФИО: " << record.fullName << endl;
		}
	};

	vector<HashItem> table;
	int size;
	int capacity;

	size_t hashFunction(const Record& item) {
		return item.hashCode % capacity;
	}

	size_t hashFunction2(const Record& item) {
		return getNextPrime(item.address.street.length());
	}

	bool isPrime(int n) {
		if (n <= 1) return false;
		if (n <= 3) return true;
		if (n % 2 == 0 || n % 3 == 0) return false;
		for (int i = 5; i * i <= n; i += 6) {
			if (n % i == 0 || n % (i + 2) == 0) return false;
		}
		return true;
	}

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

	void resizeTable() {
		int newCapacity = getNextPrime(capacity * 2);
		vector<HashItem> newTable(newCapacity, { Record(), State::FREE });
		for (const auto& item : table) {
			if (item.state == State::BUSY) {
				size_t index, step; //Insert
				for (index = hashFunction(item.record), step = hashFunction2(item.record);
					newTable[index].state != State::FREE;
					index = (index + step) % newCapacity) {
				}

				newTable[index].record = item.record;
				newTable[index].state = State::BUSY;
			}
		}
		table = move(newTable);
		capacity = newCapacity;
	}

public:
	HashTable(int initialCapacity = 200) : size(0), capacity(initialCapacity) {
		table.resize(capacity);
		for (auto& item : table) {
			item.state = State::FREE;
		}
	}

	void insert(const Record& record) {
		bool needResize = (size >= capacity / 2);
		if (needResize) {
			resizeTable();
		}

		size_t index = hashFunction(record);
		size_t step = hashFunction2(record);
		while (table[index].state == State::BUSY) {
			index = (index + step) % capacity;
		}

		table[index].record = record;
		table[index].state = State::BUSY;
		size++;
	}

	//bool isEqual(const Record& rec1, const Record& rec2) {
	//	return rec1.address.street == rec2.address.street &&
	//		rec1.address.houseNumber == rec2.address.houseNumber &&
	//		rec1.address.apartmentNumber == rec2.address.apartmentNumber;
	//}

void remove(const Address& address) {
    for (size_t i = 0; i < capacity; ++i) {
        if (table[i].state == State::BUSY && table[i].record.isEqual(address)) {
            table[i].state = State::REMOVED;
            size--;
            return;
        }
    }
}


void printFullNameByAddress(const Address& address) {
    for (size_t i = 0; i < capacity; ++i) {
        if (table[i].state == State::BUSY && table[i].record.isEqual(address)) {
            table[i].print();
            return;
        }
    }
    cout << "Нет записей для данного адреса" << endl;
}



	void printTable() {
		for (size_t i = 0; i < capacity; ++i) {
			if (table[i].state == State::BUSY) {
				table[i].print();
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
			if (table[i].state == State::BUSY) {
				file << table[i].record.fullName << "," << table[i].record.address.street << ","
					<< table[i].record.address.houseNumber << "," << table[i].record.address.apartmentNumber << ","
					<< table[i].record.phoneNumber << "," << table[i].record.balance << endl;
			}
		}

		file.close();
	}

	void clear() {
		table.clear();
		size = 0;
	}

	void readFromFile(const string& filename) {
		clear();
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
}

Record generateRecord() {
	static const string streets[] = { "ул. Ленина", "пр. Победы", "пер. Садовый", "пр. Гагарина", "ул. Пушкина" };
	static const string names[] = { "Иванов Иван Иванович", "Петров Петр Петрович", "Сидоров Сидор Сидорович", "Кузнецов Кузьма Кузьмич", "Николаев Николай Николаевич" };
	static const string phones[] = { "111-111", "222-222", "333-333", "444-444", "555-555" };

	string fullName = names[rand() % 5];
	string street = streets[rand() % 5];
	int houseNumber = rand() % 100 + 1;
	int apartmentNumber = rand() % 100 + 1;
	string phoneNumber = phones[rand() % 5];
	double balance = (rand() % 10000) / 100.0;

	return { fullName, {street, houseNumber, apartmentNumber}, phoneNumber, balance };
}

int main() {
	setlocale(LC_ALL, "RU");
	HashTable<Record> hashTable;

	string filename;
	cout << "Введите имя файла: ";
	cin >> filename;

	hashTable.readFromFile(filename);

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
