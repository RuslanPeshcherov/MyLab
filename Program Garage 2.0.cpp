//Program "Garage". User can to add a transport, to observe the garage and to clean out the garage.

#include <iostream>
#include <vector>
#include <set>
#include <string>

void getLine(std::string& str);
char getChar();
void tableLine();

//Classes description

class Transport
{
public:
	Transport(std::string model, int year);
	~Transport();
	friend std::ostream& operator << (std::ostream&, const Transport&);

private:
	std::string model_;
	int year_;
};

class TransportList
{
public:
	~TransportList();
	void insertTransport(Transport*);
	void display();

private:
	std::set<Transport*> setPtrsTrans;
};

class TransportScreen
{
public:
	TransportScreen(TransportList* ptrTL) :pTSTransportList_(ptrTL) {}
	void getTransport();

private:
	TransportList* pTSTransportList_;
};

class Interface
{
public:
	Interface();
	~Interface();
	void interact();

private:
	TransportList* pITransportList_;
};

int main()
{
	Interface UserInterface;
	UserInterface.interact();
	return 0;
}

///////////////////////////////////////////////////////////////////

//Methods description

void getLine(std::string& str)
{
	char s[20];
	std::cin.get(s, 20, '\n');
	std::cin.ignore(20, '\n');
	str = s;
}

char getChar()
{
	char ch = std::cin.get();
	std::cin.ignore(80, '\n');
	return ch;
}

void tableLine()
{
	for (int i = 0; i < 20; i++)
	{
		std::cout << "=";
	}

	std::cout << std::endl;
}

Transport::Transport(std::string model, int year) : model_(model), year_(year)
{ }

Transport::~Transport()
{ }

std::ostream& operator << (std::ostream& stream, const Transport& transport)
{
	stream << transport.model_ << '\t' << transport.year_ << std::endl;
	return stream;
}

void TransportScreen::getTransport()
{
	std::string model;
	std::cout << "Please, input model: ";
	getLine(model);

	int year;
	std::cout << "Please, input year of issue: ";
	std::cin >> year;
	std::cin.ignore(80, '\n');

	Transport* pTransport = new Transport(model, year);
	pTSTransportList_->insertTransport(pTransport);
}

TransportList::~TransportList()
{
	while (!setPtrsTrans.empty())
	{
        auto iter = setPtrsTrans.begin();
		delete *iter;
		setPtrsTrans.erase(iter);
	}
}

void TransportList::insertTransport(Transport* ptrT)
{
	setPtrsTrans.insert(ptrT);
}

void TransportList::display()
{
	if (setPtrsTrans.empty())
	{
		std::cout << "Garage is empty now!\n";
	}
	else
	{
		tableLine();

		std::cout << "Model\tYear\n";

		tableLine();

		auto iter = setPtrsTrans.begin();
		while (iter != setPtrsTrans.end())
		{
			std::cout << **iter++;
		}

		tableLine();
	}
}

Interface::Interface()
{
	pITransportList_ = new TransportList;
}

Interface::~Interface()
{
	delete pITransportList_;
}

void Interface::interact()
{
	char ch;
	TransportScreen* pTransportScreen;

	while (true)
	{
		std::cout << "____________Menu___________\n"
			<< "'n' - for add new Transport\n"
			<< "'o' - for observe garage\n"
			<< "'c' - for clean out garage\n"
			<< "'q' - for quit\n";

		ch = getChar();
		switch (ch)
		{
		case 'n':
			pTransportScreen = new TransportScreen(pITransportList_);
			pTransportScreen->getTransport();
			delete pTransportScreen;
			break;

		case 'o':
			pITransportList_->display();
			break;

		case 'c':
			delete pITransportList_;
			pITransportList_ = new TransportList;
			break;

		case 'q':
			return;

		default:
			std::cout << "Unlegal symbol\n";
		}
	}
}
