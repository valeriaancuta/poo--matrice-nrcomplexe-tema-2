#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

class complexi
{
    double real, imaginar;

public:
    complexi(double, double);
    complexi(const complexi&);
    ~complexi();
    friend ifstream& operator>>(ifstream&, complexi&);
    friend ostream& operator<<(ostream&,const complexi&);
    friend const complexi operator +(complexi&, complexi&);
    friend const complexi operator +(complexi&,const complexi&);
    friend const complexi operator -(const complexi&,const complexi&);
    friend const complexi operator *(const complexi&, const complexi&);
    friend bool operator==(const complexi&,const complexi&);
    double get_imaginar();
    double get_real();
    void set_imaginar(double);
    void set_real(double);
    bool is_null();
};
//constructor
complexi::complexi(double real=0, double imaginar=0)
{
    this->real=real;
    this->imaginar=imaginar;
}
//constructor copiere
complexi::complexi(const complexi &nr)
{
    real=nr.real;
    imaginar=nr.imaginar;
}
//destructor
complexi::~complexi()
{
    real=0;
    imaginar=0;
}
//adunare nr complexe
const complexi operator+( complexi &nr1, complexi &nr2)
{
    complexi suma;
    suma.real=nr1.real+nr2.real;
    suma.imaginar=nr1.imaginar+nr2.imaginar;
    return suma;
}
//adunare nr complexe
const complexi operator+( complexi &nr1,const  complexi &nr2)
{
    complexi suma;
    suma.real=nr1.real+nr2.real;
    suma.imaginar=nr1.imaginar+nr2.imaginar;
    return suma;
}
//scadere nr complexe
const complexi operator-(const complexi &nr1,const complexi &nr2)
{
    complexi dif;
    dif.real=nr1.real-nr2.real;
    dif.imaginar=nr1.imaginar-nr2.imaginar;
    return dif;
}
//inmultire nr complexe
const complexi operator*(const complexi &nr1, const complexi &nr2)
{
    complexi produs;
    produs.real=nr1.real*nr2.real-nr1.imaginar*nr2.imaginar;
    produs.imaginar=nr1.real*nr2.imaginar+ nr2.real*nr1.imaginar;
    return produs;
}
//comparatie nr complexe
bool operator==(const complexi &nr1, const complexi &nr2)
{
    return (nr1.real==nr2.real)&&(nr1.imaginar==nr2.imaginar);
}
//citire fisier
ifstream& operator>>(ifstream &fin, complexi &nr)
{
    fin>>nr.real>>nr.imaginar;
    return fin;
}
//afisare fisier
ostream& operator<<(ostream &fout, const complexi &nr)
{
    fout<<nr.real<<"."<<nr.imaginar;
    return fout;
}

double complexi::get_imaginar()
{
    return imaginar;
}

double complexi::get_real()
{
    return real;
}

void complexi::set_imaginar(double x)
{
    imaginar=x;
}

void complexi::set_real(double x)
{
    real=x;
}
bool complexi::is_null()
{
    if(get_real()==0 && get_imaginar()==0)
        return true;
    return false;
}
class matrice
{
    friend class complexi;
protected:
    struct nod
    {
        complexi valoare;
        nod* linie;
        nod* coloana;
        int indice;

    };
    nod *first, *p;

public:
    matrice();
    matrice(int,int);
    ~matrice();
    virtual void adauga_linie()=0;
    virtual void adauga_coloana(int, complexi, int)=0;
    complexi valoare_intre(int,int);
    bool operator ==(matrice &);
    virtual void citire()=0;
    virtual void afisare()=0;

};
//constructor
matrice::matrice()
{
    first=new nod;
    first->linie=NULL;
    first->coloana=NULL;
    p=NULL;
    first->valoare.set_imaginar(0);
    first->valoare.set_real(0);
}
//destructor
matrice::~matrice()
{
    delete first;
    delete p;
}
complexi matrice::valoare_intre(int x,int y)
{
    int i,j;
    p=first;
    for (i=0; i<x; i++)
        p=p->linie;

    for (j=0; j<y; j++)
    {
        if (p->indice==y)
            return p->valoare;
        else if (p->coloana)
            p=p->coloana;
    }
    if (p->indice==y)
        return p->valoare;
    complexi a;
    a.set_imaginar(0);
    a.set_real(0);
    return a;
}

class matrice_oarecare:public matrice
{
    int nr_linii, nr_coloane;
public:
    matrice_oarecare(int, int);
    ~matrice_oarecare();
    friend ifstream &operator>>(ifstream&, matrice_oarecare&);
    friend ostream &operator<<(ostream&, matrice_oarecare&);
    void citire();
    void afisare();
    void adauga_coloana(int, complexi, int);
    void adauga_linie();



};

matrice_oarecare::matrice_oarecare(int n=0, int m=0)
{
    nr_linii=n;
    nr_coloane=m;
}

matrice_oarecare::~matrice_oarecare()
{
    nr_linii=0;
    nr_coloane=0;
}
ifstream&operator>>(ifstream &fin, matrice_oarecare &matr)
{
    matr.citire();
    return fin;
}

ostream&operator<<(ostream &fout, matrice_oarecare &matr)
{
    matr.afisare();
    return fout;
}

void matrice_oarecare::citire()
{
    complexi nr;
    int i,j;
    if((*this).nr_linii || (*this).nr_coloane)
        while ((*this).first->linie && (*this).first->coloana)
        {
            for ((*this).p=(*this).first; (*this).p->linie; (*this).p=(*this).p->linie);
            for ((*this).p=(*this).first; (*this).p->coloana; (*this).p=(*this).p->coloana)
                delete (*this).p;
        }
    fin>>(*this).nr_linii;
    fin>>(*this).nr_coloane;

    if ((*this).nr_linii<1&&(*this).nr_coloane<1)
    {
        (*this).nr_linii=0;
        (*this).nr_coloane=0;
        return ;
    }

    for (i=1; i<(*this).nr_linii; i++)
        (*this).adauga_linie();

    for (i=0; i<(*this).nr_linii; i++)
        for (j=0; j<(*this).nr_coloane; j++)
        {
            fin>>nr;
            (*this).adauga_coloana(i,nr,j);
        }
}

void matrice_oarecare::afisare()
{
    int i,j;
    for(i=0; i<(*this).nr_linii; i++)
    {
        for (j=0; j<(*this).nr_coloane; j++)
            fout<<(*this).valoare_intre(i,j)<<"  ";
        fout<<"\n";
    }
}

void matrice_oarecare::adauga_coloana(int nr_linie,complexi val, int nr_coloana)
{
    int i;
    p=first;
    for(i=0; i<nr_linie; i++)
        p=p->linie;
    if(p->coloana==NULL && p->valoare.get_real()==0 && p->valoare.get_imaginar()==0)
    {
        p->valoare=val;
        p->indice=nr_coloana;
        return;
    }

    for(; p->coloana; p=p->coloana);
    nod*q = new nod;
    p->coloana=q;
    p=p->coloana;
    q->linie=NULL;
    q->valoare=val;
    q->indice=nr_coloana;
    q->coloana=NULL;
}

void matrice_oarecare::adauga_linie()
{
    nod* q=new nod;
    for(p=first; p->linie; p=p->linie);
    q->linie=NULL;
    q->coloana=NULL;
    q->indice=0;
    q->valoare.set_real(0);
    q->valoare.set_imaginar(0);
    p->linie=q;
}

class matrice_patratica:public matrice
{
    int dimensiune;
    complexi determinant();
public:
    matrice_patratica(int);
    ~matrice_patratica();
    friend ifstream &operator>>(ifstream&, matrice_patratica&);
    friend ostream &operator<<(ostream&, matrice_patratica&);
    void citire();
    void afisare();
    void adauga_coloana(int, complexi, int);
    void adauga_linie();
    void diagonala();
};

matrice_patratica::matrice_patratica(int n=0)
{
    dimensiune=n;
}

matrice_patratica::~matrice_patratica()
{
    dimensiune=0;
}
ifstream&operator>>(ifstream &fin, matrice_patratica &matr)
{
    matr.citire();
    return fin;
}

ostream&operator<<(ostream &fout, matrice_patratica &matr)
{
    matr.afisare();
    return fout;
}

void matrice_patratica::citire()
{
    complexi nr;
    int i,j;
    if((*this).dimensiune)
        while ((*this).first->linie && (*this).first->coloana)
        {
            for ((*this).p=(*this).first; (*this).p->linie; (*this).p=(*this).p->linie);
            for ((*this).p=(*this).first; (*this).p->coloana; (*this).p=(*this).p->coloana)
                delete (*this).p;
        }
    fin>>(*this).dimensiune;

    if ((*this).dimensiune<1)
    {
        (*this).dimensiune=0;
        return ;
    }

    for (i=1; i<(*this).dimensiune; i++)
        (*this).adauga_linie();

    for (i=0; i<(*this).dimensiune; i++)
        for (j=0; j<(*this).dimensiune; j++)
        {
            fin>>nr;
            (*this).adauga_coloana(i,nr,j);
        }
}

void matrice_patratica::afisare()
{
    int i,j;
    for(i=0; i<(*this).dimensiune; i++)
    {
        for (j=0; j<(*this).dimensiune; j++)
            fout<<(*this).valoare_intre(i,j)<<"  ";
        fout<<"\n";
    }
    fout<<(*this).determinant();
}

complexi matrice_patratica:: determinant()
{
    if(dimensiune==2)
    {
        return (first->valoare*first->linie->coloana->valoare)-(first->linie->valoare*first->coloana->valoare);
    }
    else
    {
        complexi det;
        matrice_patratica submatrice(dimensiune);
        for(int i=0; i<dimensiune; i++)
        {
            int subi=0;
            for(int j=1; j<dimensiune; j++)
            {
                int subj=0;
                for(int x=0; x<dimensiune; x++)
                {
                    if(i!=x)
                    {
                        submatrice.adauga_coloana(subi,valoare_intre(j,x),subj);
                        subj++;
                    }
                }
                subi++;
            }
            submatrice.dimensiune--;
            det = det + (pow(-1,i)*valoare_intre(0,i)*submatrice.determinant());
        }
        return det;
    }
}
void matrice_patratica::adauga_coloana(int nr_linie,complexi val, int nr_coloana)
{
    int i;
    p=first;
    for(i=0; i<nr_linie; i++)
        p=p->linie;
    if(p->coloana==NULL && p->valoare.get_real()==0 && p->valoare.get_imaginar()==0)
    {
        p->valoare=val;
        p->indice=nr_coloana;
        return;
    }

    for(; p->coloana; p=p->coloana);
    nod*q = new nod;
    p->coloana=q;
    p=p->coloana;
    q->linie=NULL;
    q->valoare=val;
    q->indice=nr_coloana;
    q->coloana=NULL;
}

void matrice_patratica::adauga_linie()
{
    nod* q=new nod;
    for(p=first; p->linie; p=p->linie);
    q->linie=NULL;
    q->coloana=NULL;
    q->indice=0;
    q->valoare.set_real(0);
    q->valoare.set_imaginar(0);
    p->linie=q;
}

void matrice_patratica::diagonala()
{
    int i,j,e=0;
    for(i=0; i<dimensiune; i++)
        for(j=0; j<dimensiune; j++)
        {
            if((i==j && valoare_intre(i,j).is_null()==true) || (i!=j && valoare_intre(i,j).is_null()==false))
                e=1;

        }
    if(e==0)
        fout<<"Matricea e diagonala"<<endl;
    else
        fout<<"Matricea nu e diagonala"<<endl;
}

int main()
{
    matrice_patratica *v1;
    matrice_oarecare *v2;
    int nr, op, i1=0,i2=0,care;
    fin>>nr;
    v1=new matrice_patratica[nr+1];
    v2=new matrice_oarecare[nr+1];
    fin>>op;
    while(op)
    {
        switch(op)
        {
            case 1://citeste matrice patratica
            {
                fin>>v1[i1];
                i1++;
                break;
            }
            case 2://citeste matrice oarecare
            {
                fin>>v2[i2];
                i2++;
                break;
            }
            case 3://verificare matrice diagonala
            {
                fin>>care;
                v1[care-1].diagonala();
                break;
            }
            case 4://afisare matrice patratica
            {
                fin>>care;
                fout<<v1[care-1]<<endl;
                break;
            }
            case 5://afisare matrice oarecare
            {
                fin>>care;
                fout<<v2[care-1]<<endl;
                break;
            }
        }
        fin>>op;
    }
    return 0;
}
