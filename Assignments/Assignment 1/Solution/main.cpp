/* @Arpit Garg 
ADSA Assignment 1
School method for Integer Addition and Kasturba Multiplication
A1784072
 */

//Header Files
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>

//func declarations
unsigned int makeEqual(std::string& Num1, std::string& Num2);
std::string kartsuba(std::string Num1, std::string Num2, int Base);
std::string _multiply(std::string Num1, std::string Num2, int Base);
std::string _add(std::string Num1, std::string Num2, int B);
std::string _sub(std::string num1, std::string Num2, int B);
void optimizeString(std::string& str);
void reverseString(std::string& str);


//main function 
int main() {
    std::string n1, n2;
    int b = 10;
    std::cin >> n1 >> n2 >> b;
    std::cout << _add(n1, n2, b);
    std::cout << " ";
    std::cout << kartsuba(n1, n2, b);
    return 0;
}

//Addition Method
std::string _add(std::string Num1, std::string Num2, int B) {
    int sz = makeEqual(Num1, Num2);
    int rem = 0, carry = 0;
    std::string sum;
    int i = sz - 1;
    while (i >= 0)
    {
        int tmp = (Num1[i] - '0') + (Num2[i] - '0') + carry;
        int choice = 1;
        if (tmp >= B) {
            choice = 1;
        }
        else {
            choice = 0;
        }
        switch (choice) {
        case 0: sum = sum + std::to_string(tmp);
            carry = 0;
            break;
        case 1: rem = tmp % B;
            carry = tmp / B;
            sum = sum + std::to_string(rem);
            break;
        }
        i--;
    }
    if (carry != 0)
        sum = sum + std::to_string(carry);

    reverseString(sum);
    return sum;
}

//Making size equal 
unsigned int makeEqual(std::string& Num1, std::string& Num2)
{
    if (Num1.size() > Num2.size())
        Num2 = std::string(Num1.size() - Num2.size(), '0').append(Num2);
    else if (Num2.size() > Num1.size())
        Num1 = std::string(Num2.size() - Num1.size(), '0').append(Num1);

    return Num1.size();
}


//Subtracting method
std::string _sub(std::string Num1, std::string Num2, int B) {
    unsigned int sz = makeEqual(Num1, Num2);
    int c = 0; int d;
    std::string sb;
    int i = sz - 1;
    while (i >= 0) {
        int choice = 1;
        int n = Num1[i] - '0' - c;
        int m = Num2[i] - '0';
        if (m > n) {
            choice = 1;
        }
        else {
            choice = 0;
        }
        switch (choice) {
        case 0: d = n - m;
            c = 0;
            sb = sb + std::to_string(d);
            break;
        case 1: d = n + B - m;
            c = 1;
            sb = sb + std::to_string(d);
            break;
        }
        i--;
    }
    reverseString(sb);
    return sb;
}

//Multiplication method for one bit according to base
std::string _multiply(std::string Num1, std::string Num2, int B) {

    std::string result;
    int carry = 0;
    int i = Num1.size() - 1;

    while (i >= 0) {
        int mul = (Num1[i] - '0') * (Num2[0] - '0') + carry;
        int choice = 1;
        if (mul >= B) {
            choice = 1;
        }
        else {
            choice = 0;
        }
        switch (choice) {
        case 0: result.append(std::to_string(mul));
            carry = 0;
            break;
        case 1: result.append(std::to_string(mul % B));
            carry = mul / B;
            break;
        }
        i--;
    }
    if (carry != 0) result.append(std::to_string(carry));
    reverseString(result);
    return result;
}

//Kartsuba method for multiplication
std::string kartsuba(std::string numOne, std::string numTwo, int Base) {
    unsigned int sz = makeEqual(numOne, numTwo);

    if (sz == 1)
        return _multiply(numOne, numTwo, Base);
    std::string part0, part1;
    std::string xH = numOne.substr(0, sz / 2);
    std::string xL = numOne.substr(sz / 2, sz - sz / 2);
    std::string yH = numTwo.substr(0, sz / 2);
    std::string yL = numTwo.substr(sz / 2, sz - sz / 2);
    (xH.size() == 1) ? part0 = _multiply(xH, yH, Base) : part0 = kartsuba(xH, yH, Base);
    (xL.size() == 1) ? part1 = _multiply(xL, yL, Base) : part1 = kartsuba(xL, yL, Base);
    std::string part2 = kartsuba(_add(xH, xL, Base), _add(yH, yL, Base), Base);
    std::string part3 = _sub(part2, _add(part0, part1, Base), Base);

    for (unsigned int i = 0; i < 2 * (sz - sz / 2); i++)
        part0.append("0");
    for (unsigned int i = 0; i < sz - sz / 2; i++)
        part3.append("0");

    std::string result = _add(_add(part0, part1, Base), part3, Base);

    optimizeString(result);
    return result;
}
//remove leading zeros
void optimizeString(std::string& str)
{
    str = str.erase(0, std::min(str.find_first_not_of('0'), str.size() - 1));
}

//reverse string
void reverseString(std::string& str)
{
    std::reverse(str.begin(), str.end());
}
