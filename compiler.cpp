#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // для strcmp, strcpy_s

using namespace std;

// Элемент таблицы символов (связный список)
struct element
{
    char* name;
    char operation;
    char* value;
    int variable;
    element* next;
};

/////////////////////////////////////////////////
element* previous(element* top, element* current)
{
    element* p = top;
    while (p != nullptr && p->next != current)
    {
        p = p->next;
    }
    return p;
}

/////////////////////////////////////////////////
element* findElement(const char* name, element* top)
{
    element* p = top;
    while (p != nullptr)
    {
        if (strcmp(p->name, name) == 0)
            return p;
        p = p->next;
    }
    return nullptr;
}

//////////////////////////////////////////////////
void probel(int k, ofstream& f)
{
    for (int i = 0; i < k - 1; i++)
        f << " ";
}

//////////////////////////////////////////
void proverka(int k, ofstream& f)
{
    if (k == 1) f << "что первый символ будет A-Z" << endl;
    if (k == 2) f << "что второй символ будет A-Z или 0-9" << endl;
    if (k == 3) f << "что третий символ будет :" << endl;
    if (k == 4) f << "что четвертый символ будет =" << endl;
    if (k == 5) f << "что в конце будет ;" << endl;
    if (k == 6) f << "что после будет символ ! % - или 0-1" << endl;
    if (k == 7) f << "что будет последовательность из восьми цифр 0-1" << endl;
    if (k == 8) f << "что после ! % - будет 0-1 или A-Z" << endl;
    if (k == 9) f << "что в конце после A-Z будет A-Z " << endl;
}

//////////////////////////////////////////
int countOne(const string& bool_mass)
{
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        if (bool_mass[i] == '1')
            count++;
    }
    return count;
}

//////////////////////////////////////////
int differenceOneZero(const string& bool_mass)
{
    int one = 0, zero = 0;
    for (int i = 0; i < 8; i++)
    {
        if (bool_mass[i] == '1')
            one++;
        else
            zero++;
    }
    return one - zero;
}

/////////////////////////////////////////
int BinarySystem(const string& bool_mass)
{
    int result = 0;
    int power = 1;
    for (int i = 7; i >= 0; i--)
    {
        if (bool_mass[i] == '1')
        {
            result += power;
        }
        power *= 2;
    }
    return result;
}

////////////////////////////////////////////
class Compilator
{
private:
    element* top;
    string word;
public:
    Compilator(ifstream& f);
    ~Compilator();
    bool syntaxix(ofstream& f);
    void memory();
    bool calculate(ofstream& f);
    void show(ofstream& f);
};

Compilator::Compilator(ifstream& f)
{
    top = nullptr;
    getline(f, word);
}

Compilator::~Compilator()
{
    element* p = top;
    while (p != nullptr)
    {
        element* next = p->next;
        delete[] p->name;
        if (p->value != nullptr)
            delete[] p->value;
        delete p;
        p = next;
    }
}

// Конечный автомат для синтаксического анализа входной строки
bool Compilator::syntaxix(ofstream& f)
{
    int q = 0, k = 0, pr = 0, count = 0;
    for (int i = 0; i < (int)word.length() && q != 11; i++)
    {
        char x = word[i];
        switch (q)
        {
        case 0:
            if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
            {
                q = 1; pr++; f << x;
            }
            else
            {
                k = 1; q = 11; pr++; f << x;
            }
            break;
        case 1:
            if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
            {
                q = 6; pr++; f << x;
            }
            else if (x >= '0' && x <= '9')
            {
                q = 2; pr++; f << x;
            }
            else
            {
                k = 2; q = 11; pr++; f << x;
            }
            break;
        case 2:
            if (x == ':')
            {
                q = 3; pr++; f << x;
            }
            else
            {
                k = 3; q = 11; pr++; f << x;
            }
            break;
        case 3:
            if (x == '=')
            {
                q = 4; pr++; f << x;
            }
            else
            {
                k = 4; q = 11; pr++; f << x;
            }
            break;
        case 4:
            if (x == '!' || x == '%' || x == '-')
            {
                q = 7; pr++; f << x;
            }
            else if (x == '0' || x == '1')
            {
                count = 1; q = 5; pr++; f << x;
            }
            else
            {
                k = 6; q = 11; pr++; f << x;
            }
            break;
        case 5:
            if ((x == '0' || x == '1') && count < 8)
            {
                count++; pr++; f << x;
            }
            else if (x == ';' && count == 8)
            {
                q = 10; pr++; f << x;
            }
            else
            {
                k = 7; q = 11; pr++; f << x;
            }
            break;
        case 6:
            if (x == ':')
            {
                q = 12; pr++; f << x;
            }
            else
            {
                k = 8; q = 11; pr++; f << x;
            }
            break;
        case 7:
            if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
            {
                q = 8; pr++; f << x;
            }
            else if (x == '0' || x == '1')
            {
                count = 1; q = 5; pr++; f << x;
            }
            else
            {
                k = 8; q = 11; pr++; f << x;
            }
            break;
        case 8:
            if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
            {
                q = 9; pr++; f << x;
            }
            else
            {
                k = 9; q = 11; pr++; f << x;
            }
            break;
        case 9:
            if (x == ';')
            {
                q = 10; pr++; f << x;
            }
            else
            {
                k = 5; q = 11; pr++; f << x;
            }
            break;
        case 10:
            if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
            {
                q = 1; pr++; f << x;
            }
            else
            {
                k = 1; q = 11; pr++; f << x;
            }
            break;
        case 12:
            if (x == '=')
            {
                q = 5; pr++; f << x;
            }
            else
            {
                k = 4; q = 11; pr++; f << x;
            }
            break;
        default:
            break;
        }
    }

    if (q == 10)
    {
        f << endl;
        return true;
    }
    if (q == 11)
    {
        f << endl;
        probel(pr, f);
        f << "^" << endl;
        probel(pr, f);
        f << "|" << endl;
        f << "Ожидалось, ";
        proverka(k, f);
    }
    return false;
}

// Разбор строки на операторы и построение таблицы символов
void Compilator::memory()
{
    size_t start = 0;
    size_t end = word.find(';');
    while (end != string::npos)
    {
        string statement = word.substr(start, end - start);
        char identifier[3];
        identifier[0] = statement[0];
        identifier[1] = statement[1];
        identifier[2] = '\0';

        element* existing = findElement(identifier, top);
        if (existing == nullptr)
        {
            element* newElement = new element;
            newElement->name = new char[3];
            strcpy(newElement->name, identifier);

            if (statement[4] == '!' || statement[4] == '%' || statement[4] == '-')
                newElement->operation = statement[4];
            else
                newElement->operation = '+';

            string value_str;
            if (newElement->operation == '!' || newElement->operation == '%' || newElement->operation == '-')
                value_str = statement.substr(5, end - start - 5);
            else
                value_str = statement.substr(4, end - start - 4);

            newElement->value = new char[value_str.length() + 1];
            strcpy(newElement->value, value_str.c_str());

            newElement->variable = 0;
            newElement->next = top;
            top = newElement;
        }

        start = end + 1;
        end = word.find(';', start);
    }
}

// Вычисление значений всех переменных согласно семантике языка
bool Compilator::calculate(ofstream& f)
{
    bool hasErrors = false;
    element* p = top;
    while (p != nullptr)
    {
        if (p->value != nullptr)
        {
            string value_str(p->value);
            if (value_str.length() == 8)
            {
                if (p->operation == '+')
                {
                    p->variable = -1;
                }
                else if (p->operation == '!')
                {
                    p->variable = countOne(value_str);
                }
                else if (p->operation == '%')
                {
                    p->variable = differenceOneZero(value_str);
                }
                else if (p->operation == '-')
                {
                    p->variable = BinarySystem(value_str);
                }
            }
            else if (value_str.length() == 2)
            {
                element* source = findElement(value_str.c_str(), top);
                if (source != nullptr)
                {
                    if (source->variable == 0 && source->value != nullptr)
                    {
                        string source_value(source->value);
                        if (source_value.length() == 8)
                        {
                            source->variable = BinarySystem(source_value);
                        }
                    }

                    if (p->operation == '-')
                    {
                        p->variable = source->variable;
                    }
                    else if (p->operation == '!')
                    {
                        string binary_code = "";
                        int num = source->variable;
                        for (int j = 7; j >= 0; j--)
                        {
                            if (num & (1 << j))
                                binary_code += '1';
                            else
                                binary_code += '0';
                        }
                        p->variable = countOne(binary_code);
                    }
                    else if (p->operation == '%')
                    {
                        string binary_code = "";
                        int num = source->variable;
                        for (int j = 7; j >= 0; j--)
                        {
                            if (num & (1 << j))
                                binary_code += '1';
                            else
                                binary_code += '0';
                        }
                        p->variable = differenceOneZero(binary_code);
                    }
                }
                else
                {
                    f << "ОШИБКА: Переменная '" << value_str << "' не определена!" << endl;
                    hasErrors = true;
                }
            }
        }
        p = p->next;
    }
    return !hasErrors;
}

// Вывод итоговых значений всех переменных
void Compilator::show(ofstream& f)
{
    element* last = top;
    while (last != nullptr && last->next != nullptr)
        last = last->next;

    element* p = last;
    while (p != nullptr)
    {
        if (p->operation == '+')
            f << p->name << " = " << p->value;
        else
            f << p->name << " = " << p->variable;

        p = previous(top, p);
        if (p != nullptr) f << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    ifstream in("txt.txt");
    ofstream out("itog.txt");

    if (!in)
    {
        cout << "Ошибка открытия файлов!" << endl;
        exit(-1);
    }

    Compilator compiler(in);
    if (compiler.syntaxix(out))
    {
        compiler.memory();
        if (compiler.calculate(out))
        {
            compiler.show(out);
        }
    }

    in.close();
    out.close();
    return 0;
}
