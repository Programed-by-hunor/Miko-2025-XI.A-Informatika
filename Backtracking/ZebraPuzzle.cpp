#include <iostream>
#include <iomanip>

using namespace std;

enum Szin { SARGA, KEK, PIROS, ZOLD, FEHER };
enum Nemzet { NORVEG, UKRAN, BRIT, SPANYOL, JAPAN };
enum Ital { VIZ, TEA, TEJ, NARANCSLE, KAVE };
enum Cigi { KOOLS, CHESTERFIELD, OLDGOLD, LUCKYSTRIKE, PARLIMENTS };
enum Allat { ROKA, LO, CSIGA, KUTYA, ZEBRA };

string szinNev[] =
{
    "sarga", "kek", "piros", "zold", "feher"
};

string nemzetNev[] =
{
    "norveg", "ukran", "brit", "spanyol", "japan"
};

string italNev[] =
{
    "viz", "tea", "tej", "narancsle", "kave"
};

string cigiNev[] =
{
    "Kools", "Chesterfield", "Old Gold", "Lucky Strike", "Parliments"
};

string allatNev[] =
{
    "roka", "lo", "csiga", "kutya", "zebra"
};

int hol(int t[], int ertek)
{
    for(int i=0;i<5;i++)
        if(t[i]==ertek)
            return i;

    return -1;
}

void kiir(int szin[],
          int nemzet[],
          int ital[],
          int cigi[],
          int allat[])
{
    const int W = 15;

    cout << setw(W) << " ";
    for(int i=1;i<=5;i++)
        cout << setw(W) << i;
    cout << endl;

    cout << setw(W) << "Szin";
    for(int i=0;i<5;i++)
        cout << setw(W) << szinNev[szin[i]];
    cout << endl;

    cout << setw(W) << "Nemzet";
    for(int i=0;i<5;i++)
        cout << setw(W) << nemzetNev[nemzet[i]];
    cout << endl;

    cout << setw(W) << "Ital";
    for(int i=0;i<5;i++)
        cout << setw(W) << italNev[ital[i]];
    cout << endl;

    cout << setw(W) << "Cigaretta";
    for(int i=0;i<5;i++)
        cout << setw(W) << cigiNev[cigi[i]];
    cout << endl;

    cout << setw(W) << "Allat";
    for(int i=0;i<5;i++)
        cout << setw(W) << allatNev[allat[i]];
    cout << endl;

    int zebraHaz = hol(allat, ZEBRA);

    cout << endl << "A zebrat a "
         << nemzetNev[nemzet[zebraHaz]]
         << " tartja." << endl;
}

bool kovPerm(int a[], int n){
    int piv;
    int i;
    for(i=n-1; i>0; i--){
        if(a[i]>a[i-1]){
            piv=i - 1;
            break;
        }
    }
    if(i==0)
    {
        int j = n - 1;
        while(i < j)
        {
            swap(a[i++], a[j--]);
        }
        return false;
    }

    for(i=n-1; i>piv; i--){
        if(a[i]>a[piv]){
            swap(a[i], a[piv]);
            break;
        }
    }
    i = piv+1;
    int j = n - 1;
    while(i < j)
    {
        swap(a[i++], a[j--]);
    }

    return true;
}

int main()
{
    int szin[]   = {0,1,2,3,4};
    int nemzet[] = {0,1,2,3,4};
    int ital[]   = {0,1,2,3,4};
    int cigi[]   = {0,1,2,3,4};
    int allat[]  = {0,1,2,3,4};

    do //szin
    {
        int piros = hol(szin, PIROS);
        int zold = hol(szin, ZOLD);
        int feher = hol(szin, FEHER);
        int sarga = hol(szin, SARGA);
        int kek = hol(szin, KEK);

        if(zold-feher!=1)
            continue;


        do //nemzet
        {
            int brit= hol(nemzet, BRIT);
            int spanyol = hol(nemzet, SPANYOL);
            int ukran = hol(nemzet, UKRAN);
            int norveg = hol(nemzet, NORVEG);
            int japan = hol(nemzet, JAPAN);

            if(norveg!=0)
                continue;
            if(brit!=piros)
                continue;
            if(abs(norveg-kek)!=1)
                continue;

            do //ital
            {
                int tea= hol(ital, TEA);
                int kave= hol(ital, KAVE);
                int viz= hol(ital, VIZ);
                int narancsle= hol(ital, NARANCSLE);
                int tej= hol(ital, TEJ);

                if(tej!=2)
                    continue;
                if(kave!=zold)
                    continue;
                if(tea!=ukran)
                    continue;

                do // cigi
                {
                    int kools = hol(cigi, KOOLS);
                    int chesterfield = hol(cigi, CHESTERFIELD);
                    int oldgold = hol(cigi, OLDGOLD);
                    int luckystrike = hol(cigi, LUCKYSTRIKE);
                    int parliments = hol(cigi, PARLIMENTS);

                    if(kools!=sarga)
                        continue;
                    if(luckystrike!=narancsle)
                        continue;
                    if(japan!=parliments)
                        continue;
                    do //allat
                    {
                        int roka = hol(allat, ROKA);
                        int lo = hol(allat, LO);
                        int csiga = hol(allat, CSIGA);
                        int kutya = hol(allat, KUTYA);
                        int zebra = hol(allat, ZEBRA);

                        if(spanyol!=kutya)
                            continue;
                        if(oldgold!=csiga)
                            continue;
                        if(abs(chesterfield-roka)!=1)
                            continue;
                        if(abs(kools-lo)!=1)
                            continue;

                        kiir(szin, nemzet, ital, cigi, allat);

                    }while(kovPerm(allat, 5));
                }while(kovPerm(cigi, 5));
            }while(kovPerm(ital, 5));
        }while(kovPerm(nemzet, 5));
    }while(kovPerm(szin, 5));

    return 0;
}
