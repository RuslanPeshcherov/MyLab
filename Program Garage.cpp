//Программа "Гараж". Даёт возможность пользователю добавить транспорт,
//посмотреть, что есть в гараже, и очистить гараж.

#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

void getLine(string& str);
char getChar();
void tableline();

//Описание классов

class transport
{
  private:
  string model;
  int year;

  public:
  transport (string m, int y);
  ~transport();
  friend ostream& operator << (ostream&, const transport&);
};

class transportList
{
  private:
  set<transport*> setPtrsTrans;
  set<transport*>::iterator iter;
  public:
  ~transportList();
  void inserttransport(transport*);
  void display();
};

class transportScreen
{
  private:
  transportList* ptrtransportList;
  string tmodel;
  int tyear;
  public:
  transportScreen(transportList* ptrTL) : ptrtransportList(ptrTL)
    {}
  void gettransport();
};

class Interface
{
  private:
  transportList* ptrtransportList;
  transportScreen* ptrtransportScreen;
  char ch;
  public:
  Interface();
  ~Interface();
  void interact();
};

int main()
  {
  Interface UserInterface;
  UserInterface.interact();
  return 0;
  }

//Описание методов

void getLine(string& str)
{
  char s[21];
  cin.get(s, 20, '\n');
  cin.ignore(20, '\n');
  str = s;
}

char getChar()
{
  char ch = cin.get();
  cin.ignore(80, '\n');
  return ch;
}

void tableline()
{
    for (int i=0; i<20; i++)
        cout << "=";
    cout << endl;
}

transport::transport(string m, int y) : model (m), year(y)
  { }

transport::~transport()
  { }

ostream& operator << (ostream& s, const transport& t)
  { s << t.model << '\t' << t.year << endl;  return s; }

void transportScreen::gettransport()
  {
  cout << "Please, input model: ";
  getLine(tmodel);
  cout << "Please, input year of issue: ";
  cin >> tyear;
  cin.ignore(80, '\n');
  transport* ptrtransport = new transport(tmodel, tyear);
  ptrtransportList->inserttransport(ptrtransport);
  }

transportList::~transportList()
  {
  while( !setPtrsTrans.empty() )
    {
    iter = setPtrsTrans.begin();
    delete *iter;
    setPtrsTrans.erase(iter);
    }
  }

void transportList::inserttransport(transport* ptrT)
  {
  setPtrsTrans.insert(ptrT);
  }

void transportList::display()
  {
  if( setPtrsTrans.empty() )
    cout << "Garage is empty now!\n";
  else
    {
    tableline();
    cout << "Model\tYear\n";
    tableline();
    iter = setPtrsTrans.begin();
    while( iter != setPtrsTrans.end() )
    cout << **iter++;
    tableline();
    }
  }

Interface::Interface()
  {
  ptrtransportList     = new transportList;
  }

Interface::~Interface()
  {
  delete ptrtransportList;
  }

void Interface::interact()
  {
  while(true)
    {
    cout << "____________Menu___________\n"
         << "'n' - for add new transport\n"
         << "'o' - for observe garage\n"
         << "'c' - for clean out garage\n"
         << "'q' - for quit\n";
    ch = getChar();
      switch (ch)
      {
        case 'n':
          ptrtransportScreen = new transportScreen(ptrtransportList);
          ptrtransportScreen->gettransport();
          delete ptrtransportScreen;
          break;
        case 'o':
          ptrtransportList->display();
          break;
        case 'c':
          delete ptrtransportList;
          break;
        case 'q':
          return;
          break;
        default:
          cout << "Unlegal symbol\n";
      }
    }
  }







