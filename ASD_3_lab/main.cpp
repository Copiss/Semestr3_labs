/* На вход дается одно число х, нужно вывести все числа от 1 до х, удовлетворяющие условию:
 *                           3^K*5^L*7^M = x
 * где K, L, M - натуральные числа или могут быть равны 0. */

#include <iostream>
#include <vector> //Работа с векторами
#include <algorithm> //Для алгоритмических операций (sort)

int main()
{
    long long x;
    std::cout << "What's the maximum x you want, cutie?" << std::endl;
    std::cin >> x;
    long long tx = 1;
    std::vector <long long> mass;
    while (tx <= x)
    { //Подбираем всевозможные K, L и M
        long long tf = tx;
        while (tf <= x)
        {
            long long ts = tf;
            while (ts <=x)
            {
                mass.push_back(ts);
                ts *= 7;
            }
            tf *= 5;
        }
        tx *= 3;
    }
    std::sort(mass.begin(), mass.end());
    std::cout << "Here are your wonderful possible x's:" << std::endl;
    for (int i = 0; i < mass.size(); i++)
    {
        std::cout << mass.at(i) << std::endl;
    }
    return 0;
}
