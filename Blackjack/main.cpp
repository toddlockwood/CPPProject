#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;
#include <streambuf>


class Kolor{
private:
		int liczby[13];

	public:
		Kolor(){
			wypelnijKolorKartami();
		};

		int wyswietlLiczbe(int liczbaLosowa){
            return liczby[liczbaLosowa];
		}
		int setLiczba(int liczba){
            this->liczby[liczba] = 0;
		}


	private:
		wypelnijKolorKartami(){
			for(int i = 0; i<13;i++){
				liczby[i] = i+2;
			}
		}
};

class Talia{
    private:
        Kolor Kier,Pik,Karo,Trefl;
    public:
    Kolor zwrocKolor(int i){
        switch( i )
            {
                case 0:
                    return Kier;
                    break;
                case 1:
                    return Pik;
                    break;
                case 2:
                    return Karo;
                    break;
                case 3:
                    return Trefl;
                    break;
            }
        }

};

class RNG{
    public:
    int zwrocLiczbe(int zakres){
        int wylosowana_liczba =( std::rand() % zakres ) + 0;
        return wylosowana_liczba;
    }
};

class Gracz{
    private:
        int numerGracza;
        int wynik;
        string imie;
    public:
        int setNumerGracza(int nr){
            this->numerGracza = nr;
        }
        int getNumerGracza(){
            return numerGracza;
        }
        int setWynikGracza(int wynik){
            this->wynik = wynik;
        }
        int getWynikGracza(){
            return wynik;
        }
        string setImieGracza(string imie){
            this->imie = imie;
        }
        string getImieGracza(){
            return imie;
        }

};

class Krupier : public Gracz{
        private:
        int wynik;
        public:
        int setWynikGracza(int wynik){
            this->wynik = wynik;
        }
        int getWynikGracza(){
            return wynik;
        }
};

class Gra{
    private:
        int iluGraczy;
        Gracz tablicaGraczy[4];
    public:
        Gra(){
            cout<<  "*** Blackjack Edition Super 2018 ***" << endl;
            cout<<  "*** Wprowadz liczbe graczy od 1 - 4*" <<endl;
            cin>>iluGraczy;
            iluGraczy = walidacjaIlosciGraczy(iluGraczy);
            utworzenieListyGraczy(iluGraczy);
            rozgrywka();
        }
    private:
    int walidacjaIlosciGraczy(int ile){
        int gracze = ile;
        bool blokada = true;
        do{


				    if (cin.good())
				    {
						blokada=true;
				    }
				    else
				    {
				        cout << "*** To nie jest liczba *********"<<endl;
				        cin.clear();
				        cin.ignore();
				    }
                    if(gracze <1 || gracze >4 ){
                    blokada = false;
                    cout<<  "*** Blad wprowadzenia ilosci graczy*" <<endl;
                    cout<<  "*** Wprowadz poprawna liczbe *******" <<endl;
                    cout<<  "*** Wprowadz liczbe graczy od 1 - 4*" <<endl;
                    cin>>gracze;
                }


        }while(blokada==false);
        return gracze;
    }

    void utworzenieListyGraczy(int iloscGraczy){
        string imie;
        for(int i = 0;i<iloscGraczy;i++){
            tablicaGraczy[i].setNumerGracza(i);
        cout<<"Prosze wprowadzic imie gracza nr: " << tablicaGraczy[i].getNumerGracza() +1<<endl;
        cin>>imie;
        tablicaGraczy[i].setImieGracza(imie);
        //TODO Weryfikacja imienia
        }
    }

    void rozgrywka(){
                    Krupier kr;
            for(int i = 0; i<iluGraczy;i++){
                cout << "*** Wybrano gracza numer: " << tablicaGraczy[i].getNumerGracza() +1 << " *** " << tablicaGraczy[i].getImieGracza()<< endl;
                int wynik = losujKarte();
                string wybor;
                tablicaGraczy[i].setWynikGracza(wynik);
                do{ wynik += losujKarte();
                    tablicaGraczy[i].setWynikGracza(wynik);
                    cout<<"Obecny wynik gracza: " << tablicaGraczy[i].getWynikGracza() << endl;
                    if(tablicaGraczy[i].getWynikGracza()>21){
                        cout << "*** Gracz: " <<tablicaGraczy[i].getNumerGracza() +1 << " o imieniu: " << tablicaGraczy[i].getImieGracza() << " przegrywa :(" <<endl;
                        tablicaGraczy[i].setWynikGracza(0);
                        break;
                    }
                    cout <<endl;
                    cout << "Czy chcesz dobrac karte? T/N" <<endl;
                    cin >> wybor;
                    cout <<endl;
                    if(wybor=="n" || wybor =="N"){
                        break;
                    }
                    else
                        continue;
                }while(tablicaGraczy[i].getWynikGracza()<22);
            cout<<"Koncowy wynik gracza: " << tablicaGraczy[i].getWynikGracza() << endl;
            cout <<endl;
            cout <<endl;
            }
            cout<<"**** Gre rozpoczyna krupier ****" << endl;

            int wynik = 0;
            while(wynik <17){
            cout <<"Krupier dobiera karte " << endl;
            wynik += losujKarte();
            kr.setWynikGracza(wynik);
            if(kr.getWynikGracza()>21){
                 cout << "*** Krupier " << " przegrywa :(" <<endl;
                 kr.setWynikGracza(0);
                 break;
            }
            cout<<"Obecny wynik Krupiera: " << kr.getWynikGracza() << endl;
            }
            cout<<"Koncowy wynik Krupiera: " << kr.getWynikGracza() << endl;
            cout<<"************************"<<endl;
            cout<<"*PODSUMOWANIE ROZGRYWKI*"<<endl;
            cout<<"************************"<<endl;

            for(int i = 0; i<iluGraczy;i++){
                if(tablicaGraczy[i].getWynikGracza()>=kr.getWynikGracza()){
                    cout << "*** Gracz: " <<tablicaGraczy[i].getNumerGracza() << " o imieniu: " << tablicaGraczy[i].getImieGracza() << " wygrywa z Krupierem i zgarnia pule :)" <<endl;
                }else{
                    cout << "*** Gracz: " <<tablicaGraczy[i].getNumerGracza() << " o imieniu: " << tablicaGraczy[i].getImieGracza() << " przegrywa z Krupierem i Krupier zgarnia pule :((" <<endl;

                }
            }
                        cout<<"************************"<<endl;
                                    cout<<"************************"<<endl;
    }

    int losujKarte(){
        RNG rg;
        Talia tal;
        int karta;

        do{
            int kolorKarty = rg.zwrocLiczbe(4);
            int numerKarty = rg.zwrocLiczbe(13);
            karta = tal.zwrocKolor(kolorKarty).wyswietlLiczbe(numerKarty);
            tal.zwrocKolor(kolorKarty).setLiczba(numerKarty);
        }while(karta==0);

        return sprawdzWynikKarty(karta);

    }

    int sprawdzWynikKarty(int karta){

        if(karta==2){
            return 2;
        }
        if(karta == 3){
            return 3;
        }
        if(karta == 4){
            return 4;
        }
        if(karta==5){
            return 5;
        }
        if(karta == 6){
            return 6;
        }
        if(karta == 7){
            return 7;
        }
        if(karta==8){
            return 8;
        }
        if(karta == 9){
            return 9;
        }
        if(karta == 10){
            return 10;
        }
        if(karta==11){
            return 10;
        }
        if(karta == 12){
            return 10;
        }
        if(karta == 13){
            return 10;
        }
        if(karta == 14){
            return 11;
        }
    }

};


int main()
{
    string x;
    ifstream inFile;
    int wybor;
    inFile.open("ASCI.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    while (getline(inFile,x)) {
        cout << x << endl ;
}

    inFile.close();
    srand( time( NULL ) );
    bool exit = false;


    while(exit == false)
    {   cout<<"************************"<<endl;
        cout<<"@1.Wybierz '1' Aby zagrac"<<endl;
        cout<<"@2.Wybierz inny przycisk ABY WYJSC "<<endl;
        cout<<"************************"<<endl;
        cin>>wybor;
        switch(wybor)
            {
                case 1:{
                    Gra gr;
                    break;
                }
                default:{
                exit = true;
            }
            }
        }



    cout<<"exited: "<<endl;




    return 0;
}
