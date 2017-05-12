#include <iostream>
#include <fstream>

using namespace std;
ifstream fin ("STIVA.IN");
ofstream fout ("STIVA.OUT");

struct nod
{
    nod*urm;
    int info;
};

class Stiva
{
private:
    nod*prim;
public:
    int baza;
    Stiva()
    {
        prim=NULL;
        baza=1;
    }
    Stiva(Stiva&a);
    ~Stiva();
    void creareStiva();
    void afisareStiva();
    nod* extrageNod(nod*&p);
    void adaugaNod(int info);
    void conversieBaza10();
    void conversieBazaB(int b );
    Stiva operator+(Stiva&a);
    Stiva operator-(Stiva&a);
    Stiva operator*(int cifra);
    bool operator>(Stiva&a);
    Stiva operator*(Stiva&a);
};

Stiva::Stiva(Stiva&a)
{
    nod*p,*q,*u;
    p=a.prim;
    prim=new nod;
    prim->info = p->info;
    p=p->urm;
    u=prim;
    while(p!=NULL)
    {
        q=new nod;
        q->info = p->info;
        u->urm = q;
        u=q;
        p=p->urm;
    }
    u->urm=NULL;
}
Stiva::~Stiva()
{
    nod*p=prim,*q;
    while(p!=NULL)
    {
        q=p;
        p=p->urm;
        delete q;
    }
    prim=NULL;
}
void Stiva::adaugaNod(int info)
{
    if(prim==NULL)
    {
        prim=new nod;
        prim->info = info;
        prim->urm=NULL;
    }
    else
    {
        nod*q;
        q=new nod;
        q->info=info;
        q->urm=prim;
        prim=q;
    }

}
void Stiva::creareStiva()
{
    int cif=0;
    fin>>baza;
    do
    {
        fin>>cif;
        if(cif>=0)
            adaugaNod(cif);
    }
    while(cif>=0);

}
void Stiva::afisareStiva()
{
    if(prim==NULL)
        fout<<"Nu sunt elemente in stiva. \n";
    else
    {
        fout<<"Stiva contine elementele: ";
        for(nod*p=prim; p!=NULL; p=p->urm)
        {
            fout<<p->info<<' ';
        }
        fout<<'\n';
    }
}
nod* Stiva::extrageNod(nod*&p)
{
    if(prim!=NULL)
    {
        p=prim;
        prim=prim->urm;
        return p;
    }

    return NULL;
}
void Stiva::conversieBaza10()
{
    int nr=0,putereB=1,cif;
    nod*p=extrageNod(p);
    while(p!=NULL)
    {
        cif=p->info;
        nr+=cif*putereB;
        putereB=putereB*baza;
        p=extrageNod(p);
    }
    int v[51],nr2=0;
    while(nr!=0)
    {
        v[++nr2]=nr%10;
        nr/=10;
    }
    for(int i=nr2; i>=1; i--)
        adaugaNod(v[i]);
    baza=10;
}
void Stiva::conversieBazaB(int b)
{
    int nr=0,cif;
    nod*p=extrageNod(p);
    int putereB=1;
    while(p!=NULL)
    {
        cif=p->info;
        nr+=cif*putereB;
        putereB=putereB*10;
        p=extrageNod(p);
    }

    int v[10],nr2=0;
    while(nr!=0)
    {
        v[++nr2]=nr%b;
        nr/=b;
    }
    for(int i=nr2; i>=1; i--)
        adaugaNod(v[i]);
    baza=b;

}
Stiva Stiva::operator+(Stiva&b)
{
    int baza_calcul = b.baza,c1,c2,x,t=0,nr=0,v[51];
    Stiva c;
    conversieBaza10();
    b.conversieBaza10();
    nod*p1,*p2;
    p1=prim;
    p2=b.prim;
    while(p1!=NULL&&p2!=NULL)
    {
        c1=p1->info;
        c2=p2->info;
        x=c1+c2+t;

        if(x<10)
            {
                //c.adaugaNod(x);
                v[++nr]=x;
                t=0;
            }
        else
            {
                //c.adaugaNod(x%10);
                v[++nr]=x%10;
                t=1;
            }
        p1=p1->urm;
        p2=p2->urm;
    }
    while(p1!=NULL)
    {
        c1=p1->info;
        x=c1+t;
        if(x<10)
        {
            //c.adaugaNod(x);
            v[++nr]=x;
            t=0;
        }
        else
        {
            //c.adaugaNod(x%10);
            v[++nr]=x%10;
            t=1;
        }
        p1=p1->urm;
    }
    while(p2!=NULL)
    {
        c1=p2->info;
        x=c1+t;
        if(x<10)
        {
            //c.adaugaNod(x);
            v[++nr]=x;
            t=0;
        }
        else
        {
            //c.adaugaNod(x%10);
            v[++nr]=x%10;
            t=1;
        }
        p2=p2->urm;
    }
    while(t)
    {
        //c.adaugaNod(t);
        v[++nr]=t;
        t=0;
    }
    c.baza=10;
    for(int i=nr;i>=1;i--)
        c.adaugaNod(v[i]);

    c.conversieBazaB(baza_calcul);
    return c;
}

int main()
{
    Stiva a,b,c;
    nod*p;
    a.creareStiva();
    b.creareStiva();
    a.afisareStiva();
    b.afisareStiva();
    c=a+b;
    c.afisareStiva();
    return 0;
}
