#include <iostream>
#include <string>
#include <cstdint>

void HelloWorld()
{
    std::cout << "startup" << std::endl;
    std::cout << "Input two numbers:" <<std::endl;
    uint8_t n1 = 0, n2 = 0;
    std::cin >> n1 >> n2;
    std::cout << "sum is " << n1 + n2 << std::endl;
}

void Cin()
{
    int val = 0, sum = 0;
    while(std::cin >> val)
    {
        sum += val;
    }
    std::cout << "the sum is: " << sum << std::endl;
}

void Comment()
{
    std::cout << "/*";
    std::cout <<"*/";
    // std::cout <</* "*/" */;          //error 不能嵌套
    std::cout <</* "*/" /* "/*" */;
}

void Test()
{
    int i = 100, sum = 0;
    for(int i = 0; i != 10; ++i)
        sum += i;
    std::cout << i << "," << sum << std::endl;
}

int main()
{   
    Test();

    return 0;
}
