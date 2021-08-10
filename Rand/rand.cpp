#include <iostream>
#include <deque>
#include <algorithm>
#include <cmath>
#include <thread>
#include <chrono>

class MyRand
// Класс для реализации Линейного Конгруэнтного Метода
{
private:
    std::deque<uint> deque;
public:
    MyRand();
    ~MyRand() = default;
    uint next();
    std::deque<uint>& get_deque(); 
};

MyRand::MyRand()
{
    deque.push_back(157);
    deque.push_back(5054);
    deque.push_back(25789);
    deque.push_back(13214);
}

uint MyRand::next()
{
    deque.pop_front();
    deque.push_back((31 * deque.back() + 187) % 32768);

    return deque.back();
}
std::deque<uint>& MyRand::get_deque()
{
    return deque;
}

int mod_inv(int a, int m)
{
    int t, nt, r, nr, q, tmp;
    t = 0;  nt = 1;  r = m;  nr = a % m;
    while (nr != 0) {
        q = r/nr;
        tmp = nt;  nt = t - q*nt;  t = tmp;
        tmp = nr;  nr = r - q*nr;  r = tmp;
    }
    if (r > 1) return -1;
    if (t < 0) t += m;
    return t;
}

long get_next(std::deque<uint> deque)
{
    for (uint m = *std::max_element(deque.begin(), deque.end()); m <= 65535; ++m)
    {
        int diff0 = deque.at(1) - deque.at(0); if (diff0 < 0) diff0 += m;
        int diff1 = deque.at(2) - deque.at(1); if (diff1 < 0) diff1 += m;
        int diff2 = deque.at(3) - deque.at(2); if (diff2 < 0) diff2 += m;

        int inv_diff0 = mod_inv(diff0, m);
        if (inv_diff0 < 0) continue;
        int a = (diff1 * inv_diff0) % m;

        int my_diff1 = (a * diff0) % m;
        int my_diff2 = (a * diff1) % m;

        if (my_diff1 == diff1 && my_diff2 == diff2)
        {
            int c1 = deque.at(3) - (deque.at(2) * a) % m;
            int c2 = deque.at(2) - (deque.at(1) * a) % m;
            int c3 = deque.at(1) - (deque.at(0) * a) % m;
            // std::cout << "m = " << m << c1 << " " << c2 << " " << c3 << std::endl;
            if (c1 == c2 && c2 == c3 && c1 >= 0)
            {
                if ((deque.at(0) * a + c1) % m == deque.at(1) &&
                    (deque.at(1) * a + c1) % m == deque.at(2) &&
                    (deque.at(2) * a + c1) % m == deque.at(3)/* && (13214 * a + c1) % m == 16605*/)
                    // std::cout << ">>>" << inv_diff0;
                    return (deque.back() * a + c1) % m;
            }
        }
    }
    return -1;
}

int main()
{
    MyRand r;
    while (1)
    {
        std::cout << "Deque condition: ";
        for (auto var : r.get_deque())
            std::cout << var << "; ";
        // std::cout << std::endl;

        std::cout << "\tReceived: ";
        long res = get_next(r.get_deque());
        if (res == -1)
            std::cout << "Error";
        else
            std::cout << res;
        std::cout << ";\tExpected: " << r.next() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
    }

    return 0;
}