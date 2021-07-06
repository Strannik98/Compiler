#include "table_const.h"
#include "table_var.h"
#include <conio.h>
//Тестируем наличие зарезервированного слова в таблице
void contain_test(string type, table_const<string> A)
{
	cout << "Is '"<< type <<"' included in Table?";
	if (A.contains(type)) cout << "\nYes, it is\n" << endl;
	else cout << "\nNo, it isn't\n" << endl;
}
//Ищем номер в таблице по названию
void  num_test(string name, table_const<string> A) 
{
	int number;
	cout << "What number do the '" << name << "' have in Table?";
	if (A.get_num(name, number)) cout << "\nNumber of '" << name << "' is " << number + 1 << "\n\n";
	else cout << "\nSorry, '" << name << "' didn't found\n" << endl;
}
//Ищем название по номеру в таблице
void  val_test(int num, table_const<string> A)
{
	string name;
	cout << "What name does the " << num << " element have in Table?";
	if (A.get_val(num, name)) cout << "\nName of " << num << " element is '" << name << "'\n\n";
	else cout << "\nSorry, " << num << " element didn't found\n" << endl;
}




void main() {
	table_const<string> A;
	A.read_file("types.txt"); //чтение из файла таблица постоянных
	cout << "\tTest 1\n";
		//тест на наличие элемента в постоянной таблице
	contain_test("int", A); //верный
	contain_test("float", A); //неверный
	cout << "\tTest 2\n";
		//тест поиска номера указанному имени
	num_test("char", A); //верный
	num_test("string", A); //неверный
	cout << "\tTest 3\n";
		//тест поиска имени по указанному номеру
	val_test(3,A); //верный
	val_test(10, A); //неверный

	int hash, chain;
	table_var B; //переменная таблица
	B.add("dcba"); //
	B.add("cbad"); //
	B.add("badc"); // добавление элементов в переменную таблицу
	B.add("abcd"); //
	B.add("abce"); //
	cout << "\tTest 4\n";
	//тест на получение положения элемента по имени
	B.get_location("aaaa", hash, chain); //неверный
	B.get_location("abcd", hash, chain); //верный
	cout.setf(ios::boolalpha);
	cout << "Getting location of \"abcd\"\nHash: " << hash << "\nChain = " << chain << "\n" << endl;

	cout << "\tTest 5\n";
	//тест на установление типа по имени
	B.set_type("dddd", 2); //неверный
	B.set_type("abcd", 2); //верный
	//тест на установление типа по положению
	B.set_type(2, -1, 2); //неверный
	B.set_type(hash, chain, 2); //верный

	cout << "\n\tTest 6\n";
	//тест на установление инициализированности по имени
	B.set_is_init("dca", true);  //неверный
	B.set_is_init("abcd", true); //верный
	//тест на установление инициализированности по положению
	B.set_is_init(1, -1, true); //неверный
	B.set_is_init(hash, chain, true); //верный

	lexeme C;
	cout << "\n\tTest 7\n";
	//тест на полкчение иныормации о лексеме по имени
	B.get_lexeme("abcdd", C);
	B.get_lexeme("badc", C);
	cout << "\nGetting lexeme by name"<< endl;
	cout << "Name: " << C.name << endl;
	cout << "Type: " << C.type << endl;
	cout << "Is init: " << C.is_init << endl << endl;
	//тест на получение информации о лексеме по положению
	B.get_lexeme(hash, chain, C);
	B.get_lexeme(hash, -1, C);
	cout << "\nGetting lexeme by hash and chain" << endl;
	cout << "Name: " << C.name << endl;
	cout << "Type: " << C.type << endl;
	cout << "Is init: " << C.is_init << endl;	
	_getch();
}
