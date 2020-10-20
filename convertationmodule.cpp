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
        bool isNegative = false;
        if(input[0] == '-')
        {
            isNegative = true;
            input[0] = '0';
        }

        if (inBase != 10)
        {
            string nBaseNumber = input;
            int digit = 0, sum = 0;
            for (size_t i = 0; i < nBaseNumber.length(); ++i) {

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
        if((isNegative)&&(result.length() <= 7))
        {
                string tmp = "", temp_result;;
                for(size_t i = 0; i < (8 - result.length()); i++)
                    tmp += '0';
                temp_result = tmp + result;
                result = InvertBinary(temp_result);
        }
        return result;
    }

    string InvertBinary(string input)
    {
        for(int i = 0; i < (int)(input.length()); i++)
            input[i] = (input[i] == '0') ? '1' : '0';
        return input;
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

        //int lim = radix + 10;
        for (radix += 1; radix < (int)input.length(); ++radix) rightPart += input[radix];
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
            int multiplication_result, rightPartInt = stoi(rightPart),  rpl = (int)rightPart.length();
            rightPart = "";
            for (int i = 0; i < rpl; i++)
            {
                int tmp = rightPartInt * outBase;
                multiplication_result = (int)(tmp / (int)(pow(10, rpl)));
                rightPartInt = tmp % (int)(pow(10, rpl));
                if (multiplication_result >= 10)
                    rightPart += HEXADECIMAL_FORMAT[multiplication_result];
                else rightPart += to_string(multiplication_result);
            }
            result = leftPart + "." + rightPart;
        }

        return result;
    }
    string ConvertToDouble(string input, string sign)
    {
        int pointPos = 1;
        string normal_form = "", power, computed, result = "";
        for(pointPos; pointPos < (int)input.length(); pointPos++)
        {
            if((input[pointPos] == ',')||(input[pointPos] == '.')) break;
            normal_form += input[pointPos];
        }
        for(int i = pointPos + 1; i < (int)input.length(); i++) normal_form += input[i];
        input = normal_form;
        pointPos += 1023 - 1;
        power = ConvertBaseInt(to_string(pointPos), 10, 2);

        computed = sign + power + normal_form;
        int len = (int)computed.length();
        for(int i = 0; i < 64 - len; i++) computed += "0";

        for(int i = 0; i < 64; i++)
        {
            string quartet = "";
            if((i > 0)&&(i % 4 == 0))
            {
                for(int j = i - 4; j < i; j++) quartet += computed[j];
                result += (quartet != "0000") ? ConvertBaseInt(quartet, 2, 16) : "0";
            }
        }
        return result;
    }
    string ConvertFromDouble(string input)
    {
        string binary = "", sign, power = "", mantissa = "", result;
        int exponent;
        for(int i = 0; i < (int)input.length(); i++)
        {
            string binary_raw = "";
            binary_raw = (input[i] != '0') ? ConvertBaseInt(string{input[i]}, 16, 2) : "0000";

            if(binary_raw.length() < 4)
            {
                string tmp = "";
                for(int j = 4 - (int)binary_raw.length(); j > 0; j--) tmp += "0";
                binary_raw = (tmp += binary_raw);
            }
            binary += binary_raw;
        }
        sign = string{binary[0]};
        for(int i = 1; i < 12; i ++) power += string{binary[i]};
        exponent = stoi(ConvertBaseInt(power, 2, 10)) - 1023;

        int i;
        for(i = 63; binary[i] != '1'; i--)
        for(int j = 12; j <= i; j++)
        {
            if(j == 12 + exponent) mantissa += ".";
            mantissa += string{binary[j]};
        }
        mantissa = "1" + mantissa;

        result = ((sign == "1") ? "-" : "") + ConvertBaseReal(mantissa, 2, 10);
        return result;
    }
};

