#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

class Polinom
{
    float egyutthato[100];
    int n;
public:
    Polinom(float egyutthato[], int n)
    {
        for(int i = 0; i <= n; i++)
        {
           this->egyutthato[i] = egyutthato[i];
        }
        this->n = n;
    }
    Polinom()
    {
        this->n = 0;
    }
    Polinom operator+(const Polinom &x)
    {
        Polinom osszeg;
        if(this->n > x.n)
        {
            osszeg.n = this->n;
            for(int i = 0; i <= this->n; i++)
            {
               osszeg.egyutthato[i] = this->egyutthato[i];
               if(i <= x.n)
                osszeg.egyutthato[i] += x.egyutthato[i];
            }
        }
        else
        {
            osszeg.n = x.n;
            for(int i = 0; i <= x.n; i++)
            {
               osszeg.egyutthato[i] = x.egyutthato[i];
               if(i <= this->n)
                osszeg.egyutthato[i] += this->egyutthato[i];
            }
        }
        return osszeg;
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
            if(irtunkMar)
                cout << " + ";

            irtunkMar = true;

            if(i == 0)
                out<<x.egyutthato[i];
            else if(i == 1)
                out<<x.egyutthato[i]<<"x";
            else
                out<<x.egyutthato[i]<<"x^"<<i;
        }
    }
    return out;
}

int main()
{
    srand(time(0));
    float tomb[10];
    float tomb2[10];
    for(int i = 0; i <= 5; i++)
    {
        tomb[i] = rand()%10;
    }
    for(int i = 0; i <= 7; i++)
    {
        tomb2[i] = rand()%10;
    }
    Polinom a(tomb, 5);
    Polinom b(tomb2, 7);
    cout << a << endl;
    cout << b << endl;
    cout << a + b << endl;
    return 0;
}
