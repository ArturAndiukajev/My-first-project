#include "firstlib.h"

//---------------------------------------------------------
double rezultatasVidurkis(list <int>& namudarbai,int egz)
{
    int kiekis = namudarbai.size();
    double rez=0;
    try
    {
        if (kiekis == 0)
        {
            throw std::invalid_argument("Kiekis negali buti lygus nuliui");
        }}
    catch (const std::exception& e)
    {
        cout << "Dalyba is nulio. " << e.what() << endl;
    }
    double suma=0;
    for (auto it = namudarbai.begin(); it != namudarbai.end(); ++it)
    {
        suma += *it;
    }
    rez=0.4*(suma/kiekis*1.0)+0.6*egz;
    return rez;
}
//--------------------------------------------------------------

//--------------------------------------------------------------
double Med(list <int>& namudarbai)
{
    namudarbai.sort();
    size_t size = namudarbai.size();
    if (size % 2 == 0)
    {
        size_t middle = size / 2;
        auto it1 = std::next(namudarbai.begin(), middle - 1);
        auto it2 = std::next(namudarbai.begin(), middle);
        return (*it1 + *it2) / 2.0;
    }
    else
    {
        auto it = std::next(namudarbai.begin(), size / 2);
        return *it;
    }
}
//---------------------------------------------------------------

//---------------------------------------------------------------
double rezultatasMediana(double mediana, int egz)
{
    double rez=0;
    rez=0.4*mediana+0.6*egz;
    return rez;
}
//----------------------------------------------------------------

//----------------------------------------------------------------
bool palyginimasVardai(const Studentas& a, const Studentas& b)
{
    return a.vardas < b.vardas;
}
//-----------------------------------------------------------------

//-----------------------------------------------------------------
bool palyginimasPavardes(const Studentas& a, const Studentas& b)
{
    return a.pavarde < b.pavarde;
}
//------------------------------------------------------------------

//------------------------------------------------------------------
bool palyginimasVidurkis(const Studentas& a, const Studentas& b)
{
    return a.galutinis1 < b.galutinis1;
}
//-------------------------------------------------------------------

//--------------------------------------------------------------------
void generavimas(int studentu_skaicius, string fileName, int nd_kiekis)
{
    srand(time(NULL));
    auto pradzia=std::chrono::high_resolution_clock::now();
    ofstream outputFile(fileName);
    outputFile<<left<<"Vardas"<<setw(25)<<" "<<setw(13)<<right<<"Pavarde"<<setw(15)<<" ";
    for(int i=0;i<nd_kiekis;i++)
    {
        outputFile<<setw(3)<<right<<"ND"<<setw(3)<<left<<i+1<<setw(5)<<" ";
    }
    outputFile<<setw(7)<<left<<"Egz."<<endl;
    for(int i=0;i<studentu_skaicius;i++)
    {
        outputFile<<left<<"Vardas"<<setw(10)<<left<<i+1<<setw(15)<<" "<<setw(13)<<right<<"Pavarde"<<setw(10)<<left<<i+1;
        for(int j=0;j<nd_kiekis;j++)
        {
            outputFile<<setw(9)<<right<<rand()%10+1<<setw(2)<<right<<" ";
        }
        outputFile<<setw(9)<<right<<rand()%10+1<<endl;
    }
    outputFile.close();
    auto pabaiga=std::chrono::high_resolution_clock::now();
    auto uztruko=std::chrono::duration_cast<std::chrono::milliseconds>(pabaiga - pradzia);
    cout<<"Failo "<<fileName<<" generavimo laikas:"<<uztruko.count()<<" milisekundziu"<<endl;
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void isvedimas(list <Studentas> studentai, string fileName)
{
    ofstream outputFile(fileName);
    if (!outputFile.is_open())
    {
        cerr << "Failo atidarymo klaida: "<<fileName<<endl;
        return;
    }
    outputFile<<setw(20)<<left<<"Vardas"<<setw(20)<<"Pavarde"<<setw(20)<<"Galutinis(Vid.)"<<endl;
    outputFile<<"-------------------------------------------------------------------------------"<<endl;
    for(const auto& Studentas : studentai)
    {
        outputFile<<setw(20)<<left<<Studentas.vardas<<setw(20)<<Studentas.pavarde<<setw(20)<<fixed<<setprecision(2)<<Studentas.galutinis1<<endl;
    }
    outputFile.close();
}
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
void skaitymas(list <Studentas>& studentai, string Fname)
{
    studentai.clear();
    ifstream input_file(Fname);
    if (!input_file.is_open())
    {
        cout << "Failo atidarymas negalimas: " << Fname << endl;
        exit(1);
    }
    string header;
    int stulp_kiekis=0;
    getline(input_file, header);
    string v;
    string p;
    std::istringstream headerStream(header);
    string token;
    while (headerStream >> token)
    {
        stulp_kiekis++;
    }
    while (input_file >> v >> p)
    {
        Studentas naujas_st;
        naujas_st.vardas = v;
        naujas_st.pavarde = p;
        for(int i=0;i<stulp_kiekis-3;i++)
        {
            int nd;
            if (!(input_file >> nd)||(nd>10)||(nd<0))
            {
                cout << "Nepavyko perskaityti namu darbo rezultato is failo." << endl;
                cout << "Tarp duomenu yra netikslumu, pvz. namu darbo pazymys didesnis uz 10 arba vietoj pazymio irasyta raide." << endl;
                exit(1);
            }
            naujas_st.ND.push_back(nd);
        }
        int Egz;
        if (!(input_file >> Egz)||(Egz>10)||(Egz<0))
        {
            cout << "Nepavyko perskaityti egzamino rezultato is failo." << endl;
            cout << "Tarp duomenu yra netikslumu, pvz. egzamino pazymys didesnis uz 10 arba vietoj pazymio irasyta raide." << endl;
            exit(1);
        }
        naujas_st.Egz=Egz;
        naujas_st.galutinis1=rezultatasVidurkis(naujas_st.ND, naujas_st.Egz);
        double mediana;
        mediana=Med(naujas_st.ND);
        naujas_st.galutinis2=rezultatasMediana(mediana, naujas_st.Egz);
        studentai.push_back(naujas_st);
        naujas_st.ND.clear();
    }
}
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
bool Vargsiukai(const Studentas studentas, double riba)
{
    return studentas.galutinis1 < riba;
}
//-------------------------------------------------------------------------------------------------------