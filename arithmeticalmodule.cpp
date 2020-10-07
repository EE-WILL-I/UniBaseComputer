#include "arithmeticalmodule.h"
#include<iostream>
#include<string>
#include<map>
#include<math.h>
#include<vector>

using namespace std;

class ArithmeticalModule
{
private:
    int num1_pointPos = 0, num2_pointPos = 0;
    map<int, char> HEXADECIMAL_FORMAT = { {10, 'A'}, {11, 'B'}, { 12, 'C' }, { 13, 'D' }, { 14, 'E' }, { 15, 'F' } };

    void Reset()
    {
        num1_pointPos = 0, num2_pointPos = 0;
    }

    string Dispoint(string num, int* radix)
    {
        string out = "";
        int tradix = *radix;
        for (int i = tradix; i < (int)num.length(); ++i) if ((num[i] == '.') || (num[i] == ',')) break;
        else
        {
            out += num[i];
            tradix++;
        }
        if (tradix < (int)num.length()) {
            ++tradix;
        }
        if(*radix == 0) *radix = tradix;
        return out;
    }

    enum NumberPart { Left, Right };

    void Equalize(string* num1Part, string* num2Part, NumberPart part)
    {
        string t1 = *num1Part, t2 = *num2Part;
        int num1Len = t1.length(), num2Len = t2.length();
        if (num1Len != num2Len)
            switch (part)
            {
            case ArithmeticalModule::Left:
            {
                string tmp = "";
                for (int i = 0; i < abs(num1Len - num2Len); i++)
                    tmp += "0";
                if (num1Len < num2Len)
                {
                    tmp += *num1Part;
                    *num1Part = tmp;
                }
                else
                {
                    tmp += *num2Part;
                    *num2Part = tmp;
                }
                break;
            }
            case ArithmeticalModule::Right:
            {
                string tmp = "";
                for (int i = 0; i < abs(num1Len - num2Len); i++)
                    tmp += "0";
                if (num1Len < num2Len)
                    *num1Part += tmp;
                else
                    *num2Part += tmp;
                break;
            }
            default:
                break;
            }
    }
    bool IsDigit(char c)
    {
        return c >= '0' && c <= '9';
    }
    string Sum(string num1, string num2, int base)
    {
        int digit1 = 0, digit2 = 0, buffer = 0, len = num1.length() - 1;
        string result = "";
        for (int i = len; i >= 0; --i)
        {
            if (num1[i] != ',' && num1[i] != '.')
            {
                char digit_char1 = num1[i], digit_char2 = num2[i];
                if (!IsDigit(digit_char1))
                {
                    for (auto& it : HEXADECIMAL_FORMAT)
                        if (it.second == digit_char1)
                            digit1 = it.first;
                }
                else digit1 = stoi(to_string(digit_char1 - '0'));

                if (!IsDigit(digit_char2))
                {
                    for (auto& it : HEXADECIMAL_FORMAT)
                        if (it.second == digit_char2)
                            digit2 = it.first;
                }
                else digit2 = stoi(to_string(digit_char2 - '0'));

                int sum = digit1 + digit2 + buffer;
                buffer = 0;
                if (sum >= base)
                {
                    buffer = sum / base;
                    sum %= base;
                }
                string tmp = "";
                if (sum >= 10)
                    tmp = HEXADECIMAL_FORMAT[sum];
                else tmp = to_string(sum);
                tmp += result;
                result = tmp;
                if ((i == 0) && (buffer != 0))
                {
                    tmp = to_string(buffer);
                    tmp += result;
                    result = tmp;
                }
            }
            else
            {
                string tmp = ".";
                tmp += result;
                result = tmp;
            }
        }
        return result;
    }
    string Substract(string num1, string num2, int base)
    {
        int digit1 = 0, digit2 = 0, buffer = 0, len = num1.length() - 1;
        bool isNegative = false;

        if(num1_pointPos < num2_pointPos)
        {
            swap(num1, num2);
            isNegative = true;
        }
        else
        {
            int i = 0;
            while(stoi(to_string(num1[i] - '0')) == stoi(to_string(num2[i] - '0'))) i++;
            if(stoi(to_string(num1[i] - '0')) < stoi(to_string(num2[i] - '0')))
            {
                swap(num1, num2);
                isNegative = true;
            }
        }

        string result = "";
        for (int i = len; i >= 0; --i)
        {
            if (num1[i] != ',' && num1[i] != '.')
            {
                char digit_char1 = num1[i], digit_char2 = num2[i];

                if (!IsDigit(digit_char1))
                {
                    for (auto& it : HEXADECIMAL_FORMAT)
                        if (it.second == digit_char1)
                            digit1 = it.first;
                }
                else digit1 = stoi(to_string(digit_char1 - '0'));

                if (!IsDigit(digit_char2))
                {
                    for (auto& it : HEXADECIMAL_FORMAT)
                        if (it.second == digit_char2)
                            digit2 = it.first;
                }
                else digit2 = stoi(to_string(digit_char2 - '0'));

                int sum = digit1 - buffer - digit2;
                buffer = 0;
                if (sum < 0)
                {
                    if (i != 0)
                    {
                        buffer = 1;
                        sum += base;
                    }
                }
                string tmp = "";
                if (sum >= 10)
                    tmp = HEXADECIMAL_FORMAT[sum];
                else tmp = to_string(sum);
                tmp += result;
                result = tmp;
            }
            else
            {
                string tmp = ".";
                tmp += result;
                result = tmp;
            }
        }
        int k = 0;
        while(result[k]=='0')
        {
            k++;
        }
        string out = "";
        for(k;k<(int)result.length();k++) out += result[k];
        return (isNegative ? "-" : "") + out;
    }
    string Multiply(string num1, string num2, int base)
    {

        string bigger, lesser, t1 = num1, t2 = num2;
        if (t1.length() >= t2.length())
        {
            bigger = t1;
            lesser = t2;
        }
        else
        {
            bigger = t2;
            lesser = t1;
        }

        //cout << "\nb = " << bigger << "l = " << lesser <<'\n';
        vector<string> buffer;
        string sum = "";
        int sumBias = 0;

        for (int i = lesser.length() - 1; i >= 0; --i)
        {
            char digit = lesser[i];
            int digit_int = 0;
            if (!IsDigit(digit))
            {
                for (auto& it : HEXADECIMAL_FORMAT)
                    if (it.second == digit)
                        digit_int = it.first;
            }
            else digit_int = stoi(to_string(digit - '0'));
            //cout << "\nd = " << digit_int << '\n';

            string tBigger = bigger, nSum = tBigger;
            for (int n = 1; n < digit_int; n++)
            {
                Equalize(&nSum, &tBigger, Left);
                nSum = this->Sum(nSum, tBigger, base);
            }

            for (int k = 0; k < sumBias; k++)
                nSum += "0";
            buffer.push_back(nSum);
            //cout << nSum;
            sumBias++;
        }
        sum = buffer[0];
        for (int k = 1; k < sumBias; k++)
        {
            Equalize(&sum, &buffer[k], Left);
            sum = Sum(sum, buffer[k].c_str(), base);
            //cout << "\nk = " << buffer[k] << '\n';
        }

        return sum;
    }

    string num1_left, num1_right, num2_left, num2_right;

    void Build(string *num1, string *num2)
    {
        num1_left = Dispoint(*num1, &num1_pointPos);
        num2_left = Dispoint(*num2, &num2_pointPos);
        num1_right = Dispoint(*num1, &num1_pointPos);
        num2_right = Dispoint(*num2, &num2_pointPos);

        Equalize(&num1_left, &num2_left, Left);
        Equalize(&num1_right, &num2_right, Right);

        *num1 = num1_left + ((num1_right != "") ? "." : "") + num1_right;
        *num2 = num2_left + ((num1_right != "") ? "." : "") + num2_right;
    }

public:
    string Add(string num1, string num2, int base)
    {
        string n1temp = num1, n2temp = num2;
        Build(&n1temp, &n2temp);
        cout << n1temp << '\n' << "+\n" << n2temp << "\n=\n";
        string out = Sum(n1temp, n2temp, base);

        Reset();
        return out;
    }
    string Take(string num1, string num2, int base)
    {
        string n1temp = num1, n2temp = num2;
        Build(&n1temp, &n2temp);
        cout << n1temp << '\n' << "-\n" << n2temp << "\n=\n";
        string out = Substract(n1temp, n2temp, base);
        cout << out << endl;

        Reset();
        return out;
    }
    string Mult(string num1, string num2, int base)
    {
        string num1_left, num1_right, num2_left, num2_right;

        num1_left = Dispoint(num1, &num1_pointPos);
        num2_left = Dispoint(num2, &num2_pointPos);
        num1_right = Dispoint(num1, &num1_pointPos);
        num2_right = Dispoint(num2, &num2_pointPos);

        string num1_whole = num1_left + num1_right, num2_whole = num2_left + num2_right;

        string tempOut = Multiply(num1_whole, num2_whole, base);
        string out = "";
        int dotPos = num1_right.length() + num2_right.length();
        for (int i = 0; i < (int)tempOut.length(); i++)
        {
            if (i == ((int)tempOut.length() - dotPos))
                out += ".";
            out += tempOut[i];
        }

        Reset();
        return out;
    }
    string Div(string num1, string num2)
    {
        double real_1 = atof(num1.c_str()),
               real_2 = atof(num2.c_str());
        string out = to_string((double)(real_1 / real_2));

        Reset();
        return out;
    }
};

