#include <iostream>
#include <random>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
int powmod (int a, int b, int p);
bool witness(int a, int n);
int random_int(int a, int b);
bool miller_rabin(int n, int s);
int generate_prime_candidate(int b);
int generate_prime(int b);

int main(void)
{
    cout << "Apartado 1:\n"; 
    int tem= 0,con = 0,j = 0, s = 2, n;
    for (int a = 101; a < 1000; a+=2)
    {
        if (!miller_rabin(a, s)) {
            con++;
            if (tem == 11) {
                cout << a<< "\n";
                tem = 0;
                continue; }
            else
                cout << a << " - ";
            tem++; } }
    cout << "\n" << con << " Numbers detected. (101 - 999) (s = " << s << ")" << "\n";
    cout << "\nApartado 2:" << "\n";
    con = 0;
   vector<int> res;
   while (res.size() != 100){
       n = generate_prime(10);
       if (n % 2 != 0)
       {
           if (!(find(res.begin(), res.end(), n) != res.end())){
               res.push_back(n);
               con++;}
       }}
   for (int i = 0; i < res.size(); i++){
       if (j == 20)
       {
           cout << "\n";
           j = 0; 
       }j++;
       cout << res[i] << "-"; } 
   cout << "\n" << con << " Numbers found.";
}
int generate_prime(int b)
{
    int s = 32;
    int n = generate_prime_candidate(b);
    while (miller_rabin(n, s))
        n += 2;
    return n;
}
int generate_prime_candidate(int b)
{
    int n = random_int(0, pow(2, b));
    int m = pow(2, (b - 5)) + 1;
    n = n | m;
    return n;
}
int random_int(int a, int b)
{
   random_device rd; 
   mt19937 gen(rd()); 
   uniform_int_distribution<> distr(a, b);
    return distr(gen);
}

bool miller_rabin(int n, int s)
{
    int a;
    for (int i = 1; i <= s; i++)
    {
        a = random_int(1, n - 1);
        if (witness(a, n))
            return 1;
    }
    return false;
}
bool witness(int a, int n)
{
    int sup = 1,t = 0, u = 1;
    bool found = 0;
    while (sup*2 <= n - 1){
        t++;sup = sup*2;
        while (sup*u <= n - 1){
            if (sup*u == n - 1 && u % 2 != 0){
                found = 1;
                break;}
            u++; }
        if (found)
            break;
        u = 0;}
    if (!found)
        return 0;
    int pre_x = powmod(a, u, n), x; 
    if (pre_x == 1 || pre_x == n-1)
        return 0;
    for (int i = 1; i < t; i++){
        x = powmod(pre_x, 2, n);
        if (x == n - 1)
            return 0;
        pre_x = x; }
    return 1;
}
int powmod (int a, int b, int p) {
    int res = 1;
    while (b)
    {
        if (b & 1){
            res = int (res * 1ll * a % p);
            --b; }
        else {
            a = int (a * 1ll * a % p);
            b >>= 1; }
    }  
    return res;}