#include <iostream> 
#include <stdio.h>
#include <string>

using namespace std;


int main() {
    setlocale(LC_ALL, "Rus");

    bool flag = 0;

    do
    {
        string value;
        value.resize(5);
        cout << "Введите размерность графа ( 1 < размер < 500 ): ";

        getline(cin, value);

        flag = 0;

        if (value[0] == '0')
            flag = 1;

        for (int i = 0; i < value.size(); i++)
        {
            if (!isdigit(value[i]) || isspace(value[i]))
                flag = 1;
        }

        if (!flag)
        {
            if (value.size() == 1 && std::atoi(value.c_str()) == 1)
                flag = 1;
            if (std::atoi(value.c_str()) > 500)
                flag = 1;
        }

        if (flag == 1)
        {
            std::cout << "!!! Введите корректные данные!" << std::endl << endl;
            std::cout << "> Нажмите любую клавишу, чтобы продолжить...";
            getchar();
            system("cls");
        }
        else
        {
            value = std::atoi(value.c_str());
            break;
        }
    } while (flag);
}