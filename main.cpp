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
        int b;
        nod*prim;

    public:
        Stiva()
        {
            prim=NULL;
        }
        Stiva(Stiva&a);
        ~Stiva();
        void creareStiva();
        void afisareStiva();
        nod* extrageNod(nod*&p);
        void adaugaNod(int info);
        void conversieBaza10();
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
    int b,cif;
    fin>>b;
    while(fin>>cif)
        adaugaNod(cif);
}
void Stiva::afisareStiva()
{
    if(prim==NULL)
        fout<<"Nu sunt elemente in stiva. \n";
    else
    {
        fout<<"Stiva contine elementele: ";
        for(nod*p=prim;p!=NULL;p=p->urm)
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
    int nr=0,putereB=1;
    nod*p=extrageNod(p);
    do
    {
        nr=nr+p->info*putereB;
        putereB=putereB*b;
        //de continuat
    }
}
int main()
{
    Stiva a;
    nod*p;
    a.creareStiva();
    a.afisareStiva();
    a.conversieBaza10();
    return 0;
}
