#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstring>

using namespace std;

ofstream out("IstoricComenzi.txt");

int cheltuieli=30,profit=20,vanzari=3;

void CodClearConsole(HANDLE hConsole){
    //https://docs.microsoft.com/ro-ro/windows/console/clearing-the-screen
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;
    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}


void ClearConsole(){
    //https://docs.microsoft.com/ro-ro/windows/console/clearing-the-screen
    HANDLE hStdout;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CodClearConsole(hStdout);
}


class Produs{

private:

    int id;
    static int id_actual;
    char* nume;
    string descriere;
    int discount;

public:

    Produs(char* nume, string descriere, int discount):id(id_actual++){

    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->descriere = descriere;
    this->discount = discount;

    }

    Produs():id(id_actual++){}

    Produs& operator =(const Produs& produs){
        if(this!=&produs){

                if(this->nume!=NULL)
                                delete[] this->nume;
                this->nume=new char[strlen(produs.nume)+1];
                strcpy(this->nume,produs.nume);
                this->descriere = produs.descriere;
                this->discount = produs.discount;

        }

        return *this;

    }

    virtual void afisareProdus() = 0;

    string getNume(){

    return this->nume;

    }

    string getDescriere(){

    return this->descriere;

    }

    int getDiscount(){

    return this->discount;

    }

    friend bool operator== (const Produs&, const Produs&);

    ~Produs(){
        if(this->nume!=NULL)
            delete[] this->nume;
    }
};

int Produs:: id_actual=1000;

bool operator== (const Produs& x, const Produs& y) {
    if (x.id == y.id)
    {
        return true;
    }
    else {
        return false;
    }
 }

class Pizza: public Produs {

private:

    string toping;

public:

    Pizza(string toping, char* nume, string descriere, int discount):Produs(nume, descriere, discount){

        this->toping =  toping;

    }

    Pizza():Produs(){

    }

    void afisareProdus(){

        cout<<endl<<"Nume : "<<this->getNume();
        cout<<endl<<"Descriere : "<<this->getDescriere();
        cout<<endl<<"Discount : "<<this->getDiscount();
        cout<<endl<<"Toping : "<<this->toping;

    }

    friend ofstream& operator<< (ofstream& out,  Pizza pizza){

        out<<endl<<"Nume : "<<pizza.getNume();
        out<<endl<<"Descriere : "<<pizza.getDescriere();
        out<<endl<<"Discount : "<<pizza.getDiscount();
        out<<endl<<"Toping : "<<pizza.toping;

        return out;
    }

    Pizza& operator =(const Pizza& pizza){
        if(this!=&pizza){

                this->toping = pizza.toping;
                Produs::operator=(pizza);

        }
        return *this;
    }

    ~Pizza(){

    }

};


class Paste: public Produs {

private:

    string tip_paste;

public:

    Paste(string tip_paste, char* nume, string descriere, int discount):Produs(nume, descriere, discount){

        this->tip_paste = tip_paste;

    }

    Paste():Produs(){

    }

    void afisareProdus(){

        cout<<endl<<"Nume : "<<this->getNume();
        cout<<endl<<"Descriere : "<<this->getDescriere();
        cout<<endl<<"Discount : "<<this->getDiscount();
        cout<<endl<<"Tip de paste : "<<this->tip_paste;

    }

    friend ofstream& operator<< (ofstream& out,  Paste paste){

        out<<endl<<"Nume : "<<paste.getNume();
        out<<endl<<"Descriere : "<<paste.getDescriere();
        out<<endl<<"Discount : "<<paste.getDiscount();
        out<<endl<<"Toping : "<<paste.tip_paste;

        return out;
    }

    ~Paste(){

    }

};


class Hamburger: public Produs {

private:

    string tip_carne;

public:

    Hamburger(string tip_carne, char* nume, string descriere, int discount):Produs(nume, descriere, discount){

        this->tip_carne = tip_carne;

    }

    Hamburger():Produs(){

    }

    void afisareProdus(){

        cout<<endl<<"Nume : "<<this->getNume();
        cout<<endl<<"Descriere : "<<this->getDescriere();
        cout<<endl<<"Discount : "<<this->getDiscount();
        cout<<endl<<"Tip de carne : "<<this->tip_carne;

    }

    friend ofstream& operator<< (ofstream& out,  Hamburger hamburger){

        out<<endl<<"Nume : "<<hamburger.getNume();
        out<<endl<<"Descriere : "<<hamburger.getDescriere();
        out<<endl<<"Discount : "<<hamburger.getDiscount();
        out<<endl<<"Toping : "<<hamburger.tip_carne;

        return out;
    }

    ~Hamburger(){

    }

};

class Comanda{

private:

    Pizza *listaPizza[20];
    Paste *listaPaste[20];
    Hamburger *listaHamburger[20];
    int indexPizza;
    int indexPaste;
    int indexHamburger;
    bool neplasata;
    bool in_procesare;
    bool livrata;

public:

    Comanda(){

    this->indexPizza = 0;
    this->indexPaste = 0;
    this->indexHamburger = 0;
    this->neplasata = 0;
    this->in_procesare = 0;
    this->livrata = 0;

    }

    void adaugarePizza(Pizza &pizza){

    listaPizza[this->indexPizza] = new Pizza();
    *listaPizza[this->indexPizza] = pizza;
    this->indexPizza++;

    }

    void adaugarePaste(Paste &paste){

    listaPaste[this->indexPaste] = new Paste();
    *listaPaste[this->indexPaste] = paste;
    this->indexPaste++;

    }

    void adaugareHamburger(Hamburger &hamburger){

    listaHamburger[this->indexHamburger] = new Hamburger();
    *listaHamburger[this->indexHamburger] = hamburger;
    this->indexHamburger++;

    }

    void Stergere(int ind){

        if(ind <= indexPizza){

            for (int i=ind-1;i<this->indexPizza-1;++i){
                listaPizza[i] = new Pizza();
                *listaPizza[i] = *listaPizza[i+1];

        }

        listaPizza[indexPizza] = new Pizza();
        this->indexPizza = this->indexPizza - 1;

        }

        else if(ind <= indexPizza + indexPaste){

                ind = ind - indexPizza - 1;

                for (int i=ind;i<this->indexPaste-1;++i){

                    listaPaste[i] = new Paste();
                    *listaPaste[i] = *listaPaste[i+1];

                }

                listaPaste[indexPizza] = new Paste();
                this->indexPaste = this->indexPaste - 1;

        }


             else if(ind <= indexPizza + indexPaste + indexHamburger){

                    ind = ind - indexPizza - indexPaste - 1;

                    for (int i=ind;i<this->indexHamburger-1;++i){

                        listaHamburger[i] = new Hamburger();
                        *listaHamburger[i] = *listaHamburger[i+1];

                }

                listaHamburger[indexHamburger] = new Hamburger();
                this->indexHamburger = this->indexHamburger - 1;

             }


    }

    void setStare(int stare){

    if(stare == 1){

        this->neplasata = 1;

    }

    if(stare == 2){

        this->in_procesare = 1;

    }

    if(stare == 3){

        this->livrata = 1;

    }

    }

    int getStare(){
    if(neplasata == 1){

        return 1;

    }

    if(in_procesare == 1){

        return 2;

    }

    if(this->livrata == 1){

        return 3;

    }
    }

    Pizza getIndexPizza(int index){

        return *listaPizza[index];

    }

    Paste getIndexPaste(int index){

        return *listaPaste[index];

    }

    Hamburger getIndexHamburger(int index){

        return *listaHamburger[index];

    }

    int getIndexPizza(){

        return this->indexPizza;

    }

    int getIndexPaste(){

        return this->indexPaste;

    }

    int getIndexHamburger(){

        return this->indexHamburger;

    }

    void afisareComanda(){

    for (int i=0;i<this->indexPizza;++i){

        cout<<endl<<endl<<i+1<<": ";
        (*listaPizza[i]).afisareProdus();

    }

    for (int i=0;i<this->indexPaste;++i){

        cout<<endl<<endl<<i+1+indexPizza<<": ";
        (*listaPaste[i]).afisareProdus();

    }

    for (int i=0;i<this->indexHamburger;++i){

        cout<<endl<<endl<<i+1+indexPizza+indexPaste<<": ";
        (*listaHamburger[i]).afisareProdus();

    }
    }

    friend ofstream& operator<< (ofstream& out,  Comanda comanda){
        out<<endl<<endl<<"---------------------------";

        for (int i=0;i<comanda.getIndexPizza();++i){

        out<<endl<<endl<<i+1<<": ";
        out<<comanda.getIndexPizza(i);

        }

        for (int i=0;i<comanda.getIndexPaste();++i){

        out<<endl<<endl<<i+1+comanda.getIndexPizza()<<": ";
        out<<comanda.getIndexPaste(i);

        }

        for (int i=0;i<comanda.getIndexHamburger();++i){

        out<<endl<<endl<<i+1+comanda.getIndexPizza()+comanda.getIndexPaste()<<": ";
        out<<comanda.getIndexHamburger(i);

    }
        out<<endl<<"Comanda este in stadiul:";
        if(comanda.getStare() == 1)out<<"Returnata";
        if(comanda.getStare() == 2)out<<"In procesare";
        if(comanda.getStare() == 3)out<<"Livrat";


        out<<endl<<"---------------------------"<<endl<<endl;

        return out;
    }

};

void CreareComanda(){
    Comanda com;
    ClearConsole();
    bool truee = 1;
    int y;
    while (truee) {
        ClearConsole();
        cout<<endl<<"Ce doriti sa comandati?";
        cout<<endl<<"1.Pizza";
        cout<<endl<<"2.Paste";
        cout<<endl<<"3.Hamburger";
        cout<<endl<<"4.Nimic in plus";
        cin>>y;

        if(y==1){
            ClearConsole();
            cheltuieli+=10;
            profit+=5;
            char* sir=new char[strlen("Pizza")+1];
            strcpy(sir,"Pizza");
            string str1,str2;
            cout<<endl<<"Ce doriti pe pizza?"<<endl;
            cin>>str2;

            cout<<endl<<"Doriti alte lucruri la pizza?"<<endl;
            cin>>str1;

            ClearConsole();

            Pizza piz(str1,sir,str2,4);
            com.adaugarePizza(piz);
            delete [] sir;
        }

        if(y==2){
                cheltuieli+=12;
            profit+=7;
                ClearConsole();
            char* sir=new char[strlen("Paste")+1];
            strcpy(sir,"Paste");
            string str1,str2;
            cout<<endl<<"Ce doriti pe Paste?"<<endl;
            cin>>str2;

            cout<<endl<<"Doriti alte lucruri la paste?"<<endl;
            cin>>str1;

            ClearConsole();

            Paste past(str1,sir,str2,10);
            com.adaugarePaste(past);
            delete [] sir;
        }

        if(y==3){

                ClearConsole();
                cheltuieli+=7;
            profit+=15;
            char* sir=new char[strlen("Hamburger")+1];
            strcpy(sir,"Hamburger");
            string str1,str2;
            cout<<endl<<"Ce doriti pe Hamburger?"<<endl;
            cin>>str2;

            cout<<endl<<"Doriti alte lucruri la Hamburger?"<<endl;
            cin>>str1;

            ClearConsole();

            Hamburger ham(str1,sir,str2,1);
            com.adaugareHamburger(ham);
            delete [] sir;
        }

        if(y==4) {ClearConsole();
                cout<<"In ce stadiu este comanda?";
            cout<<endl<<"1.Nelivrata";
            cout<<endl<<"2.In asteptare";
            cout<<endl<<"3.Livrata";
        int pi;cin>>pi;
        if(pi!=1)vanzari++;
                com.setStare(pi);
                truee=0;out<<com;}
    }

}

void AfisareRapoarte(){

    ClearConsole();
    int p;
        cout<<endl<<"Istoricul comenzilor este in Text Document-ul cu numele IstoricComenzi";
        cout<<endl<<"Cheltuieli:"<<cheltuieli;
        cout<<endl<<"Profit:"<<profit;
        cout<<endl<<"Vanzari:"<<vanzari;
        cout<<endl<<endl<<"Alegeti optiunea:";
        cout<<endl<<"1.Iesire";
        cin>>p;

    }

void MeniuPrincipal(){

    ClearConsole();

    cout<<endl<<"Alegeti optiunea:";
    cout<<endl<<"1.Faceti o comanda.";
    cout<<endl<<"2.Rapoarte";
    cout<<endl<<"3.Iesire";
    cout<<endl<<"Ce optiune doriti?:";
    int x;cin>>x;
    bool l=1;

    while(l){

    switch(x){

    case 1:

        CreareComanda();
        break;

    case 2:

        AfisareRapoarte();
        break;

    case 3:

        l=0;
        break;

    }

    if(l==1&&x<=3){

    ClearConsole();

    cout<<endl<<"Alegeti optiunea:";
    cout<<endl<<"1.Faceti o comanda.";
    cout<<endl<<"2.Rapoarte";
    cout<<endl<<"3.Iesire";
    cout<<endl<<"Ce optiune doriti?:";
    cin>>x;}

    if(l==1&&x>3){

    ClearConsole();
    cout<<endl<<"Nu aveti aceasta optiune, alegeti optiunea:";
    cout<<endl<<"1.Faceti o comanda.";
    cout<<endl<<"2.Rapoarte";
    cout<<endl<<"3.Iesire";
    cout<<endl<<"Ce optiune doriti?:";
    cin>>x;

    }


    }

}


int main(){

    MeniuPrincipal();

    out.close();
    return 0;
}
