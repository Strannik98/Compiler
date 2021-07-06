#include <string>
#include <vector>

using namespace std;

// Класс для хранения идентификаторов и констант
class lexeme
{
public:
    // Имя идентификатора или значение константы
    string name;
    // Тип, 0 - не определен, 1 - int, 2 - char
    int type;
    //Флаг инициализированности
    bool is_init;
	// Конструктор по умолчанию
	lexeme() {}
	// Конструктор с заданием имени идентификатора или значения константы
	lexeme(string new_name)
	{
		name = new_name;
		type = 0;
		is_init = false;
		//dimension = 1;
	}
	//Деструктор
	~lexeme()
	{
		is_init = false;
	}
    // Оператор присваивания
    lexeme &operator = (const lexeme &other)
    {
        if(this != &other)
        {
            name = other.name;
            type = other.type;
            is_init = other.is_init;
        }
        return *this;
    }
};
