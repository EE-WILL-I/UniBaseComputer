#include "convertationmodule.h"
#include<iostream>
#include<string>
#include<map>
#include<math.h>
using namespace std;


class ConvertationModule
{
public:
    map<int, char> HEXADECIMAL_FORMAT = { {10, 'A'}, {11, 'B'}, { 12, 'C' }, { 13, 'D' }, { 14, 'E' }, { 15, 'F' } };

    bool IsDigit(char c)
    {
        return c >= '0' && c <= '9';
    }
    bool IsReal(char c)
    {
        return c == ',' || c == '.';
    }

    string ConvertBaseInt(string input, int inBase, int outBase)
    {
        string result = "";

        if (inBase != 10)
        {
            string nBaseNumber = input;
            int digit = 0, sum = 0;
            for (int i = 0; i < (int)nBaseNumber.length(); ++i) {

                if (!IsDigit(nBaseNumber[i]))
                {
                    for (auto& it : HEXADECIMAL_FORMAT)
                        if (it.second == nBaseNumber[i])
                            digit = it.first;
                }
                else digit = stoi(to_string(nBaseNumber[i] - '0'));

                sum += (digit * pow(inBase, (nBaseNumber.length() - 1 - i)));
            }
            string t = to_string(sum);
            result = ConvertBaseInt(t, 10, outBase);
        }
        else
        {
            bool isDecimal = true;
            for (int i = 0; i < (int)input.length(); ++i) {
                if (!IsDigit(input[i])) {
                    isDecimal = false;
                    break;
                }
            }
            if (isDecimal)
            {
                int decimal = stoi(input);
                while (decimal > 0)
                {
                    int division_result = decimal % outBase;
                    string temp = to_string(division_result);
                    if (division_result >= 10)
                        temp = HEXADECIMAL_FORMAT[division_result];
                    temp += result;
                    result = temp;
                    decimal /= outBase;
                }
            }
        }
        return result;
    }

    string ConvertBaseReal(string input, int inBase, int outBase)
    {
        string leftPart, rightPart, result = "";
        string tmp = "";
        int radix = 0;
        for (radix; radix < (int)input.length(); ++radix) if ((input[radix] == '.') || (input[radix] == ',')) break;
        else tmp += input[radix];

        if (inBase != 10) leftPart = ConvertBaseInt(tmp, inBase, 10);
        else leftPart = ConvertBaseInt(tmp, 10, outBase);

        int lim = radix + 3;
        for (radix += 1; radix < lim; ++radix) rightPart += input[radix];
        if (inBase != 10)
        {
            double digit = 0, sum = 0;
            for (int i = 0; i < (int)rightPart.length(); ++i)
            {

                if (!IsDigit(rightPart[i]))
                {
                    for (auto& it : HEXADECIMAL_FORMAT)
                        if (it.second == rightPart[i])
                            digit = it.first;
                }
                else digit = stoi(to_string(rightPart[i] - '0'));

                sum += (double)(digit * pow(inBase, -(i + 1)));
            }
            int t = stoi(leftPart);
            sum += t;
            result = ConvertBaseReal(to_string(sum), 10, outBase);
        }
        else
        {
            int multiplication_result, rightPartInt = stoi(rightPart);
            rightPart = "";
            for (int i = 0; i < 3; i++)
            {
                int tmp = rightPartInt * outBase;
                multiplication_result = (int)(tmp / 100);
                rightPartInt = tmp % 100;
                if (multiplication_result >= 10)
                    rightPart += HEXADECIMAL_FORMAT[multiplication_result];
                else rightPart += to_string(multiplication_result);
            }
            result = leftPart + "." + rightPart;
        }

        return result;
    }
};

