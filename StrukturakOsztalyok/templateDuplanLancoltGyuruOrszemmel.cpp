#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

template <typename T>
class Lista;

template <typename T>
class Node
{
    T adat;
    Node<T> *next;
    Node<T> *prev;

public:
    Node(T adat = T(), Node<T> *next = 0, Node<T> *prev = 0){
        this->adat = adat;
        this->prev = prev;
        this->next = next;
    }
    friend class Lista<T>;
};

template <typename T>
class Lista{
    Node<T> *s; ///sentinel

public:
    Lista(){
        s = new Node<T>();
        s->next = s;
        s->prev = s;
    }
    //masolo konstruktor
    Lista(const Lista &lista)
    {
        s = new Node<T>();
        s->next = s;
        s->prev = s;
        for(Node<T> *i = lista.s->next; i != lista.s; i = i->next)
        {
            beszur_hatul(i->adat);
        }
    }
    //kiuriti a listat
    void clear(){
        Node<T> *p = s->next;
        while(p != s){
            Node<T> *tmp = p;
            p = p->next;
            delete tmp;
        }

        s->next = s;
        s->prev = s;
    }
    //destruktor
    ~Lista(){
        clear();
        delete s;
    }
    void kiir()
    {
        for(Node<T> *i = s->next; i != s; i = i->next)
        {
            cout << i->adat << " ";
        }
        cout << endl;
    }
    void beszur_elol(T adat)
    {
        Node<T> *uj = new Node<T>(adat, s->next, s);
        s->next->prev = uj;
        s->next = uj;
    }
    void beszur_hatul(T adat)
    {
        Node<T> *uj = new Node<T>(adat, s, s->prev);
        s->prev->next = uj;
        s->prev = uj;
    }
    void rendezett_beszur(T adat)
    {
        Node<T> *i = s->next;
        //megkeressuk a helyet
        while(i != s && i->adat < adat)
        {
            i = i->next;
        }

        Node<T> *uj = new Node<T>(adat, i, i->prev);
        i->prev->next = uj;
        i->prev = uj;
    }
    void torol(T torlendoElem)
    {
        //kereses
        Node<T> *i = s->next;
        while(i != s)
        {
            //torles
            if(i->adat == torlendoElem)
            {
                Node<T> *next = i->next;
                Node<T> *prev = i->prev;

                i->next->prev = prev;
                i->prev->next = next;
                delete i;

                i = next;
            }
            else
            {
                i = i->next;
            }
        }
    }
    static Lista<T> osszefesul(Lista<T> &a, Lista<T> &b)
    {
        Lista c;
        Node<T> *i = a.s -> next;
        Node<T> *j = b.s -> next;
        while(i != a.s && j != b.s){
            if(i->adat <= j->adat)
            {
                c.beszur_hatul(i->adat);
                i = i->next;
            }
            else
            {
                c.beszur_hatul(j->adat);
                j = j->next;
            }
        }
        while(i != a.s)
        {
            c.beszur_hatul(i->adat);
            i = i->next;
        }
        while(j != b.s)
        {
            c.beszur_hatul(j->adat);
            j = j->next;
        }
        return c;
    }
    //= operator tulterhelese
    Lista<T>& operator=(const Lista<T> &other)
    {
        //kivedem azt amikor onmagat kene bemasolni
        if(this != &other)
        {
            clear();
            for(Node<T> *i = other.s->next; i != other.s; i = i->next)
            {
                beszur_hatul(i->adat);
            }
        }
        return *this;
    }
};


class Tort{
private:
    int szamlalo;
    int nevezo;

    static int mod(int x)
    {
        if(x < 0) return -x;
        else return x;
    }
    //legnagyobb kozos oszto
    static int lnko(int a, int b)
    {
        while(b != 0)
        {
            int maradek = a % b;
            a = b;
            b = maradek;
        }
        return mod(a);
    }
    void egyszerusit()
    {
        int oszto = lnko(szamlalo, nevezo);
        szamlalo /= oszto;
        nevezo /= oszto;

        if(nevezo < 0) {
            szamlalo = -szamlalo;
            nevezo = -nevezo;
        }
    }
public:
    //Konstruktorok
    Tort()
    {
        szamlalo = 0;
        nevezo = 1;
    }
    Tort(int szamlalo)
    {
        this->szamlalo = szamlalo;
        this->nevezo = 1;
    }
    Tort(int szamlalo, int nevezo)
    {
        //hiba
        if(nevezo == 0)
            nevezo = 1;
        this->szamlalo = szamlalo;
        this->nevezo = nevezo;
        this->egyszerusit();
    }
    //getter setter metodusok
    void setSzamlalo(int szamlalo)
    {
        this->szamlalo = szamlalo;
    }
    int getSzamlalo() const
    {
        return szamlalo;
    }
    void setNevezo(int nevezo)
    {
        this->nevezo = nevezo;
    }
    int getNevezo() const
    {
        return nevezo;
    }
    void kiir() const
    {
        cout << this->szamlalo << "/" << this->nevezo << endl;
    }
    //muveletek
    Tort szorzas(Tort b)
    {
        Tort c;
        c.szamlalo = this->szamlalo * b.szamlalo;
        c.nevezo = this->nevezo * b.nevezo;
        c.egyszerusit();
        return c;
    }
    Tort osztas(Tort b)
    {
        Tort c;
        c.szamlalo = this->szamlalo * b.nevezo;
        c.nevezo = this->nevezo * b.szamlalo;
        c.egyszerusit();
        return c;
    }
    Tort osszeadas(Tort b)
    {
        Tort c;
        c.szamlalo = this->szamlalo * b.nevezo + b.szamlalo * this->nevezo;
        c.nevezo = this->nevezo * b.nevezo;
        c.egyszerusit();
        return c;
    }
    Tort kivonas(Tort b)
    {
        Tort c;
        c.szamlalo = this->szamlalo * b.nevezo - b.szamlalo * this->nevezo;
        c.nevezo = this->nevezo * b.nevezo;
        c.egyszerusit();
        return c;
    }
    //operator tulterhelesek
    Tort operator+(const Tort &t) const
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.nevezo + t.szamlalo * this->nevezo;
        c.nevezo = this->nevezo * t.nevezo;
        c.egyszerusit();
        return c;
    }
    Tort operator-(const Tort &t) const
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.nevezo - t.szamlalo * this->nevezo;
        c.nevezo = this->nevezo * t.nevezo;
        c.egyszerusit();
        return c;
    }
    Tort operator*(const Tort &t) const
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.szamlalo;
        c.nevezo = this->nevezo * t.nevezo;
        c.egyszerusit();
        return c;
    }
    Tort operator/(const Tort &t) const
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.nevezo;
        c.nevezo = this->nevezo * t.szamlalo;
        c.egyszerusit();
        return c;
    }
    //osszehasonlitas operatorok tulterhelese
    bool operator<(const Tort &t) const
    {
        return this->szamlalo * t.nevezo < t.szamlalo * this->nevezo;
    }
    bool operator>(const Tort &t) const
    {
        return this->szamlalo * t.nevezo > t.szamlalo * this->nevezo;
    }
    bool operator<=(const Tort &t) const
    {
        return this->szamlalo * t.nevezo <= t.szamlalo * this->nevezo;
    }
    bool operator>=(const Tort &t) const
    {
        return this->szamlalo * t.nevezo >= t.szamlalo * this->nevezo;
    }
    bool operator==(const Tort &t) const
    {
        return this->szamlalo == t.szamlalo && this->nevezo == t.nevezo;
    }
    bool operator!=(const Tort &t) const
    {
        return this->szamlalo != t.szamlalo || this->nevezo != t.nevezo;
    }

    // Overload << and >> operators as friend functions
    friend ostream &operator<<(ostream &out, const Tort &t);
    friend istream &operator>>(istream &in, Tort &t);
};
// Overload << for output
ostream &operator<<(ostream &out, const Tort &t)
{
    out << t.szamlalo << "/" << t.nevezo;
    return out;
}
// Overload >> for input
istream &operator>>(istream &in, Tort &t)
{
    in >> t.szamlalo >> t.nevezo;
    //hiba
    if(t.nevezo == 0)
        t.nevezo = 1;
    t.egyszerusit();
    return in;
}

int main()
{
    int n = 20;
    Lista<Tort> a, b;
    srand(time(0));
    for(int i = 0; i < n; i++)
    {
        Tort t1(rand()%100, rand()%100 + 1);
        a.rendezett_beszur(t1);
        Tort t2(rand()%100, rand()%100 + 1);
        b.rendezett_beszur(t2);

    }
    cout << "a:" << endl;
    a.kiir();
    cout << "b:" << endl;
    b.kiir();
    cout<< "osszefesulve: "<< endl;
    Lista<Tort> c = Lista<Tort>::osszefesul(a, b);
    c.kiir();

    return 0;
}
