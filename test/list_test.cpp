#include <iostream>
#include <cstdio>
#include <list>

int main(void)
{
    std::list<int> numbers;
    numbers.push_back(1);

    std::list<int>::iterator iter = numbers.begin();
    printf("%d \n", *iter);
    ++iter;
    printf("%d \n", *iter);
}