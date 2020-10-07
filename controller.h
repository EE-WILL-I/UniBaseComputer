#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<string>
#include<map>
#include"arithmeticalmodule.cpp"
#include"convertationmodule.cpp"


class controller
{
public:
    controller();
    int Convert();
    std::string Convert(std::string input, int inBase, int outBase);
    int Add();
    int Take();
    int Mult();
    int Div();
    int Select();
    std::string Print();
    void SetInput(string n1, string base);
    std::string GetInfo();

private:
    ConvertationModule* cm;
    ArithmeticalModule* am;
    string finfo, sinfo, num1, num2, num3, OUTPUT;
    int fcode;
    char sign = '0';
    std::map<char, int> signMap = {{'+', 2},{'-', 3},{'*', 4},{'/', 5}};
    std::map<char, std::string> typeInfoMap = {{'+', "сложение"},{'-', "вычетание"},{'*', "умножение"},{'/', "деление"}};
    void Reset();
};

#endif // CONTROLLER_H
