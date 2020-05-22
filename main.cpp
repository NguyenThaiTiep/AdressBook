#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;
const char SAVE    = 'S';
const char REMOVE  = 'R';
const char FIND    = 'F';
const char EDIT    = 'E';
const char DISPLAY = 'D';
const char GROUP   = 'G';

struct Person
{
    string Name;
    string PhoneNumber;
};

Person GetPerson (Person &New);
void PrintPerson (Person &One);
void OutPut (vector <Person> &LIST);
void RemovePerson (vector <Person> &LIST, int Number);
void RepairInfor (vector <Person> &LIST, int Number);
bool CheckSTT (vector <int> &LIST, int &Number);
void FindPerson (vector <Person> &LIST, string &words);
void OutFile();
void LoadFile();
void Groupatc();
string LastName (string &NAME);
string FrontName (string &NAME);
int  CompareName (string NAME1, string NAME2);
void SortAlphabet (vector <Person> &LIST );

int     STT;
int     choose = 0;
Person  Dem;
char    flag;
string  Keywords;
vector  <Person> Infor;
vector  <int>    STTDS;
vector  <Person> Group;

int main()
{
    cout << "\t *** ADRESSBOOK ***\n";
    cout << " S - Save                R - Remove\n" ;
    cout << " E - Edit                F - Find  \n" ;
    cout << " D - Display             G - Gruop \n" ;
    cout << "-------------------------------------\n";
    bool notBack = true;
    LoadFile();
    while ( notBack )
    {
        cout << "You want: \n";
        cin >> flag;
        switch (flag)
        {
            case SAVE   :{
                Infor.push_back(GetPerson(Dem));
                SortAlphabet (Infor);
                break;
            }
            case REMOVE :{
                cout << "Do you want to delete?\n";
                cout << "1 - Yes         0 - No\n";
                cin >> choose;
                if (choose != 1) continue;
                RemovePerson (Infor, STT);
                cout << "Deleled\n";
                break;
            }
            case FIND   :{
                cout << "KeyWords : ";
                fflush (stdin);
                getline (cin,Keywords);
                FindPerson (Infor, Keywords);
                break;
            }
            case EDIT   :{
                RepairInfor (Infor, STT);
                SortAlphabet (Infor);
                OutPut (Infor);
                }
            case DISPLAY : {
                OutPut(Infor);
                break;
            }
            case GROUP :{
                Groupatc();
                break;
            }
            default :
                notBack = false;
                break;
            }
    }
    cout << "Saved To File AddressBook.txt\n";
    OutFile();
    return 0;
}
//SAVE
Person GetPerson(Person &New)
{
    cout << "Name        : " ;
    fflush (stdin);
    getline (cin , New.Name);
    cout << "Phonenumber : ";
    cin >> New.PhoneNumber;
    return New;
}
//Display
void PrintPerson(Person &One)
{   cout << setw(2) << STT << " ";
    cout << One.Name ;
    cout << setw(40 - One.Name.size() + One .PhoneNumber.size()) << One.PhoneNumber <<endl;
}
void OutPut(vector<Person> &LIST)
{
    STT = 1;
    for(auto i : LIST)
    {
        PrintPerson(i);
        STT ++;
    }
}
//EDIT
void RepairInfor(vector <Person> &LIST , int Number)
{
    cout << "Name        : ";
    fflush (stdin);
    getline (cin , LIST[Number-1].Name);
    cout << "Phonenumber : ";
    cin >> LIST[Number-1].PhoneNumber;
}
//REMOVE
void RemovePerson(vector <Person> &LIST , int Number)
{
    LIST.erase(LIST.begin() + Number - 1);
    STTDS.clear();
}
//FIND
bool CheckSTT(vector<int> &LIST , int &Number)
{
    for(auto i : LIST)
    {
        if(i == Number) return true;
    }
    cout << "Not Found\n";
    return false;
}
void FindPerson(vector<Person> &LIST , string &words)
{
    bool check = false;
    STT = 1;
    for(auto i : LIST)
    {
        if((i.Name).find(words) != -1 || (i.PhoneNumber).find(words) != -1)
        {
        PrintPerson(i);
        STTDS. push_back (STT);
        check = true;
        }
        STT ++;
    }
    if(check)
    {
    system ("pause");
    do{
        cout << "\nSTT - Choose\t\t\t 0 - Continue\n";
        cin >> STT;
    }
    while (!CheckSTT(STTDS , STT));
    }
    else cout << "\tNot Found\n";
}

//FILE
void LoadFile()
{
    ifstream file;
    file.open("AddressBook.txt");
    while(!file.eof())
    {
        string line;
        getline(file,line);
        if(line.empty()) break;
        Dem.PhoneNumber = LastName(line);
        Dem.Name = FrontName(line);
        Infor . push_back(Dem);
    }
    file.close();
}

void OutFile()
{
    ofstream FILE;
    FILE.open("AddressBook.txt");
    for( auto i : Infor)
    {
        FILE << i.Name ;
        FILE << setw(47 - i.Name.size() +  i.PhoneNumber.length()) << i.PhoneNumber <<endl;
    }
    FILE.close();
}
//GROUP
void Groupatc()
{
    char pick;
    cout << "In GROUP\n You want:";
    cin >> pick;
    switch (pick)
    {
        case SAVE   :{
            Group.push_back( Infor[STT - 1] );
            break;
        }
        case REMOVE :{
            cout << "Do you want to delete?\n";
            cout << "1 - Yes         0 - No\n";
            RemovePerson (Group, STT);
            cout << "Deleled\n";
            break;
        }
        case FIND   :{
            cout << "KeyWords : ";
            fflush (stdin);
            getline (cin,Keywords);
            FindPerson (Group,Keywords);
            break;
        }
    }
    OutPut(Group);
}
//SORTNAME
string LastName (string &NAME)
{
    if (NAME.find (" ") == -1) return NAME;
    for(int i = NAME.size() - 1 ; i >= 0 ; i --)
        if(NAME[i] == ' ') return NAME.substr(i + 1 , NAME.size());
}
string FrontName (string &NAME)
{
    for(int i = NAME.size() - 1 ; i >= 0 ; i --)
        if(NAME[i] == ' '&& NAME[i-1] != ' ') return NAME.substr(0 , i );
}
int CompareName (string NAME1 , string NAME2)
{
    transform(NAME1.begin() , NAME1.end() , NAME1.begin() , :: toupper);
    transform(NAME2.begin() , NAME2.end() , NAME2.begin() , :: toupper);

	bool check = true;;
	while(check)
	{
        if(LastName(NAME1).compare(LastName(NAME2)) > 0) return 1;
        if(LastName(NAME1).compare(LastName(NAME2)) < 0) return -1;
        if(NAME1.find(" ") != -1) NAME1 = FrontName(NAME1);
        else check = false;
        if(NAME2.find(" ") != -1) NAME2 = FrontName(NAME2);
        else check = false;
    }
    return -1;
}
void SortAlphabet(vector <Person> &LIST)
{
    for(int i = 0 ; i < LIST.size() ; i++)
        for(int j = i +1 ; j < LIST.size() ; j ++) if (CompareName(LIST[i].Name , LIST[j].Name) == 1) swap(LIST[i] , LIST[j]);
}


