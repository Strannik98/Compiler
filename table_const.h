#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <stdio.h>
using namespace std;

// Класс постоянных таблиц
template <typename T> class table_const
{
private:
	set<T> table;
public:
	// Конструктор по умолчанию
	table_const() {}
	// Деструктор
	inline ~table_const() { table.clear(); }
	// Добавление элемента в таблицу
	inline void add(T elem) { table.insert(elem); }
	// Чтение таблицы из файла
	bool read_file(string name)
	{
		ifstream f(name);
		if (!f.is_open()) return false;
		T elem;
		while (!f.eof())
		{
			f >> elem;
			add(elem);
		}
		return true;
	}
	// Проверка есть ли элемент в таблице
	bool contains(T elem)
	{
		typename set<T>::iterator it = table.find(elem);
		if (it == table.end()) return false;
		return true;
	}
	// Поиск номера по значению
	bool get_num(T elem, int &num)
	{
		if (!contains(elem)) return false;
		num = distance(table.begin(), table.find(elem));
		return true;
	}
	// Поиск значения по номеру
	bool get_val(int num, T &elem)
	{
		if (num < 0 || num >= table.size()) return false;
		typename set<T>::iterator it = table.begin();
		for (int i = 0; i < num; i++)
			it++;
		elem = *it;
		return true;
	}
};
