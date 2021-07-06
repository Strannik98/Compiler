#include <fstream>
#include <string>
#include <vector>
#include "lexeme.h"
using namespace std;

const int default_hashnum = 100;
// Класс переменных таблиц
class table_var
{
private:
	int i;
    // Размер таблицы
    int hashnum;
    // Указатель на массив цепочек
    vector<lexeme> *table;

    // Подсчет хэша
    int get_hash(string name);
    // Подсчет номера в цепочке
    int get_chain(string name);
public:
    // Конструктор с размером таблицы по умолчанию
    table_var();
    // Конструктор с пользовательским размером таблицы
    table_var(int new_hashnum);
    // Деструктор
    ~table_var();

    // Определение хэша и номера в цепочке
    bool get_location(string name, int &hash, int &chain);
    // Проверка есть ли элемент в таблице
    inline bool contains(string name);
    // Добавление нового имени идентификатора или значения константы
    bool add(string name);

    // Задание типа по хэшу и номеру в цепочке
    bool set_type(int hash, int chain, int type);
    // Задание типа по имени идентификатора или значению константы
    bool set_type(string name, int type);
   
    // Задание флага инициализациипо хэшу и номеру в цепочке
    bool set_is_init(int hash, int chain, bool is_init);
    // Задание флага инициализациипо имени идентификатора или значению константы
    bool set_is_init(string name, bool is_init);

    // Получение структуры lexeme по хэшу и номеру в цепочке
    bool get_lexeme(int hash, int chain, lexeme &lexeme);
    // Получение структуры lexeme по имени идентификатора или значению константы
    bool get_lexeme(string name, lexeme &lexeme);
	
};


// Подсчет хэша
	int table_var::get_hash(string name)
	{
		int hash = 0;
		for (i = 0; i < name.size(); i++)
			hash += name[i];
		return hash % hashnum;
	}

	// Подсчет номера в цепочке
	int table_var::get_chain(string name)
	{
		int h = get_hash(name);
		for (i = 0 ; i < table[h].size(); i++)
			if (name == table[h][i].name) return i;
		return -1;
	}

	// Конструктор с размером таблицы по умолчанию
	table_var::table_var()
	{
		hashnum = default_hashnum;
		table = new vector<lexeme>[default_hashnum];
	}

	// Конструктор с пользовательским размером таблицы
	table_var::table_var(int new_hashnum)
	{
		hashnum = new_hashnum;
		table = new vector<lexeme>[hashnum];
	}

	// Деструктор
	table_var::~table_var()
	{
		for (i = 0; i < hashnum; i++)
			table[i].clear();
		delete[] table;
	}

	// Проверка есть ли элемент в таблице
	inline bool table_var::contains(string name)
	{
		if (get_chain(name) != -1) return true;
		return false;
	}

	// Добавление нового имени идентификатора или значения константы
	bool table_var::add(string name)
	{
		if (contains(name)) return false;
		int h = get_hash(name);
		table[h].push_back(lexeme(name));
		return true;
	}

	// Задание типа по хэшу и номеру в цепочке
	bool table_var::set_type(int hash, int chain, int type)
	{
		if (chain == -1) { cout << "Can't set type, hash: " << hash << " or chain: " << chain << " doesn't exist\n"; return false; }
		table[hash][chain].type = type;
		return true;
	}

	// Задание типа по имени идентификатора или значению константы
	bool table_var::set_type(string name, int type)
	{
		if (!contains(name)) { cout << "Can't set type, " << name << " doesn't exist\n"; return false; }
		int hash = get_hash(name), chain = get_chain(name);
		return set_type(hash, chain, type);
	}

	// Задание флага инициализации для массивов по хэшу и номеру в цепочке
	bool table_var::set_is_init(int hash, int chain, bool is_init)
	{
		if (chain == -1) { cout << "Can't set init, hash: " << hash << " or chain: " << chain << " doesn't exist\n"; return false; }
		table[hash][chain].is_init = is_init;
		return true;
	}

	// Задание флага инициализации для массивов по имени идентификатора или значению константы
	bool table_var::set_is_init(string name, bool is_init)
	{
		if (!contains(name)) { cout << "Can't set init, " << name << " doesn't exist\n"; return false; }
		int hash = get_hash(name), chain = get_chain(name);
		return set_is_init(hash, chain, is_init);
	}


	// Определение хэша и номера в цепочке
	bool table_var::get_location(string name, int &hash, int &chain)
	{
		if (!contains(name)) { cout << "Can't get location, " << name << " doesn't exist\n"; return false; }
		int h = get_hash(name),c = get_chain(name);
		if (chain == -1) return false;
		hash = h;
		chain = c;
		return true;
	}

	// Получение структуры lexeme по хэшу и номеру в цепочке
	bool table_var::get_lexeme(int hash, int chain, lexeme &lexeme)
	{
		if (chain == -1) { cout << "Can't get lexeme, hash: " << hash <<" or chain: "<< chain << " doesn't exist\n"; return false; }
		lexeme = table[hash][chain];
		return true;
	}

	// Получение структуры lexeme по имени идентификатора или значению константы
	bool table_var::get_lexeme(string name, lexeme &lexeme)
	{
		if (!contains(name)) { cout << "Can't get lexeme, " << name << " doesn't exist\n"; return false; }
		int hash = get_hash(name), chain = get_chain(name);
		return get_lexeme(hash, chain, lexeme);
	}
