#include <iostream>

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    int x = 1;
    int y = 2;
    int result = sum(x, y);
    std::cout << "Результат: " << result << std::endl;

    return 0;
}