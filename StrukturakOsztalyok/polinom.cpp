#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

class Polinom
{
    float egyutthato[100] = {0};
    int n;
public:
    Polinom()
    {
        this->n = 0;
    }
    Polinom(float egyutthato[], int n)
    {
        for(int i = 0; i <= n; i++)
        {
           this->egyutthato[i] = egyutthato[i];
        }
        this->n = n;
    }
    Polinom operator+(const Polinom &x) const
    {
        const Polinom &kisebb = this->n < x.n ? *this : x;
        const Polinom &nagyobb = this->n >= x.n ? *this : x;

        Polinom osszeg;
        osszeg.n = nagyobb.n;
        for(int i = 0; i <= nagyobb.n; i++)
        {
            osszeg.egyutthato[i] = nagyobb.egyutthato[i];
            if(i <= kisebb.n)
                osszeg.egyutthato[i] += kisebb.egyutthato[i];
        }
        return osszeg;
    }
    Polinom operator-(const Polinom &x) const
    {
        return *this + (x * -1);
    }
    Polinom operator*(const float &s) const
    {
        Polinom szorzat;
        szorzat.n = n;
        for(int i = 0; i <= n; i++){
            szorzat.egyutthato[i] = egyutthato[i] * s;
        }
        return szorzat;
    }
    Polinom operator*(const Polinom &x) const
    {
        Polinom szorzat;
        szorzat.n = n + x.n;
        for(int i = 0; i <= n; i++)
        {
            for(int j = 0; j <= x.n; j++)
            {
                 szorzat.egyutthato[i + j] += egyutthato[i] * x.egyutthato[j];
            }
        }
        return szorzat;
    }
    friend ostream& operator<<(ostream &out, const Polinom &x);
};

ostream& operator<<(ostream &out, const Polinom &x)
{
    bool irtunkMar = false;
    for(int i = x.n; i >= 0; i--)
    {
        if(x.egyutthato[i] != 0)
        {
            float a = x.egyutthato[i];

            if(irtunkMar)
            {
                if(a > 0)
                    out << " + ";
                else
                    out << " - ";
            }
            else
            {
                if(a < 0)
                    out << "-";
            }

            irtunkMar = true;

            float b = abs(a);

            if(i == 0)
                out << b;
            else if(i == 1)
            {
                if(b == 1)
                    out << "x";
                else
                    out << b << "x";
            }
            else
            {
                if(b == 1)
                    out << "x^" << i;
                else
                    out << b << "x^" << i;
            }
        }
    }
    //minden egyutthato 0
    if(!irtunkMar)
        out << 0;
    return out;
}
int main()
{
    srand(time(0));
    float tomb[10];
    float tomb2[10];
    for(int i = 0; i <= 5; i++)
    {
        tomb[i] = rand() % 20 - 10;
    }
    for(int i = 0; i <= 7; i++)
    {
        tomb2[i] = rand() % 20 - 10;
    }
    Polinom a(tomb, 5);
    Polinom b(tomb2, 7);
    cout << "a: " << endl << a << endl;
    cout << "b: " << endl << b << endl;
    cout << "a + b: " << endl << a + b << endl;
    cout << "a - b: " << endl << a - b << endl;
    cout << "a * b: " << endl << a * b << endl;
    return 0;
}
