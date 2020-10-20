#include "controller.h"

using namespace std;

controller::controller()
{
    cm = new ConvertationModule();
    am = new ArithmeticalModule();

    finfo = "Enter a numbers and their base: \n";
    sinfo = "\n Select a function by typing it's code: \n 1) Convert a number to another base. \n "
          "2) Sum two numbers. \n 3) Substract two numbers. \n 4) Multiply two numbers. \n "
          "5) Divide two numbers. \n 0) Stop execution. \n";
}
string controller::Convert(string input, int inBase, int outBase)
{
    bool isReal = false;
    for (size_t i = 0; i < input.length(); ++i)
    {
        if (cm->IsReal(input[i]))
        {
            isReal = true;
            break;
        }
    }
    string out;
    out = (isReal) ? cm->ConvertBaseReal(input, inBase, outBase) : cm->ConvertBaseInt(input, inBase, outBase);
    if(input[0] == '-')
    {
        num1 = out, num2 = to_string(1), num3 = to_string(2);
        Add();
        return OUTPUT;
    }

    return out;
}
void controller::Reset()
{
    num1 = "";
    num2 = "";
    num3 = "";
    sign = '0';
    OUTPUT = "";
}
void controller::SetInput(string n1, string base)
{
    char signs[] = {'+', '-', '*', '/'};
    int i = 0;
    for(i; i < (int)n1.length(); i++)
    {
        for(char s : signs) {
            if(n1[i] == s)
            {
                sign = s;
                break;
            }
        }
        if(sign != '0') break;
    }
    for(int j = 0; j < i; j++)
        num1 += n1[j];
    for(i=i+1; i < (int)n1.length(); i++)
        num2 += n1[i];
    num3 = base;
    fcode = signMap[sign];
}
string controller::GetInfo()
{
    return typeInfoMap[sign];
}
int controller::Convert()
{
    cout << "Enter a number it's base and a new base: \n";

    string out;

    out = Convert(num1, stoi(num2), stoi(num3));

    OUTPUT = num1 + "(" + num2 + ") = " + out + "(" + num3 + ")" + '\n';
    return 0;
}
string controller::ConvertToDouble(string input, int base)
{
    string sign, binary, out;
    if(input[0] == '-')
    {
        sign = "1";
        input[0] = '0';
    }
    else sign = "0";

    binary = Convert(input, base, 2);
    out = cm->ConvertToDouble(binary, sign);

    return out;
}
string controller::ConvertFromDouble(string input)
{
    string out;
    out = cm->ConvertFromDouble(input);
    return out;
}
int controller::Add()
{
    cout << finfo;

    string out;
    out = am->Add(num1, num2, stoi(num3));
    OUTPUT = out;

    return 0;
}
int controller::Take()
{
    cout << finfo;
    string out;

    out = am->Take(num1, num2, stoi(num3));
    OUTPUT = out;

    return 0;
}
int controller::Mult()
{
    cout << finfo;
    string out;

    out = am->Mult(num1, num2, stoi(num3));
    OUTPUT = out;

    return 0;
}
int controller::Div()
{
    cout << finfo;
    string out, dec1, dec2;
    dec1 = Convert(num1, stoi(num3), 10);
    dec2 = Convert(num2, stoi(num3), 10);
    out = am->Div(dec1, dec2);
    out = Convert(out, 10, stoi(num3));
    OUTPUT = out;

    return 0;
}

int controller::Select()
{
    int code = -1;
    switch (fcode)
    {
    case 0:
    {
        code = -1;
        break;
    }
    case 1:
    {
        code = Convert();
        break;
    }
    case 2:
    {
        code = Add();
        break;
    }
    case 3:
    {
        code = Take();
        break;
    }
    case 4:
    {
        code = Mult();
        break;
    }
    case 5:
    {
        code = Div();
        break;
    }
    default:
    {
        cout << "Invalid code";
        Select();
        break;
    }
    }
    return code;
}
string controller::Print()
{
    string out = OUTPUT;
    Reset();
    return out;
}

