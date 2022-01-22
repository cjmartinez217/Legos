#include <iomanip>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Lego
{
	int number;
	string theme;
	string name;
	int minifigs;
	int pieces;
	double price;

	Lego()
	{
		number = 0;
		theme = "";
		name = "";
		minifigs = 0;
		pieces = 0;
		price = 0.0;
	}

	Lego(int number, string theme, string name, int minifigs, int pieces, double price)
	{
		this->number = number;
		this->theme = theme;
		this->name = name;
		this->minifigs = minifigs;
		this->pieces = pieces;
		this->price = price;
	}
};

void readFromFile(string fileName, vector<Lego>& legos);
void mostExpensive(const vector<Lego>& legos);
void printLego(Lego lego);
void largestPieceCount(const vector<Lego>& legos);
void searchName(const vector<Lego>& legos);
void searchTheme(const vector<Lego>& legos);
void averagePartInfo(const vector<Lego>& legos);
void priceInfo(const vector<Lego>& legos);
void minifigInfo(const vector<Lego>& legos);
void oneOfEverything(const vector<Lego>& legos);

int main()
{
	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;

	/*======= Load data from file(s) =======*/
	vector<Lego> legos;
	switch (option)
	{
	case 1:
		readFromFile("lego1.csv", legos);
		break;
	case 2:
		readFromFile("lego2.csv", legos);
		break;
	case 3:
		readFromFile("lego3.csv", legos);
		break;
	case 4:
		readFromFile("lego1.csv", legos);
		readFromFile("lego2.csv", legos);
		readFromFile("lego3.csv", legos);
		break;
	}

	cout << "1. Most Expensive set" << endl;
	cout << "2. Largest piece count" << endl;
	cout << "3. Search for set name containing..." << endl;
	cout << "4. Search themes..." << endl;
	cout << "5. Part count information" << endl;
	cout << "6. Price information" << endl;
	cout << "7. Minifigure information" << endl;
	cout << "8. If you bought one of everything..." << endl;
	cout << "0. Exit" << endl;

	int choice;
	cin >> choice;
	cin.get();  // Clear newline character for any later input

	/*======= Print out how many sets were loaded =======*/
	int sets = legos.size();
	cout << "Total number of sets: " << sets << endl << endl;

	/*======= Based on the choice, execute the appropriate task and show the results =======*/

	switch (choice)
	{
	case 0:
		break;
	case 1:
		mostExpensive(legos);
		break;
	case 2:
		largestPieceCount(legos);
		break;
	case 3:
		searchName(legos);
		break;
	case 4:
		searchTheme(legos);
		break;
	case 5:
		averagePartInfo(legos);
		break;
	case 6:
		priceInfo(legos);
		break;
	case 7:
		minifigInfo(legos);
		break;
	case 8:
		oneOfEverything(legos);
		break;
	}

	return 0;
}

void printLego(Lego lego)
{
	cout << "Name: " << lego.name << endl;
	cout << "Number: " << lego.number << endl;
	cout << "Theme: " << lego.theme << endl;
	cout << "Price: $" << lego.price << endl;
	cout << "Minifigures: " << lego.minifigs << endl;
	cout << "Piece count: " << lego.pieces << endl;
}

void readFromFile(string fileName, vector<Lego>& legos)
{
	ifstream inFile(fileName);

	if (inFile.is_open())
	{
		string temp;
		getline(inFile, temp); //reads title from file

		//for one lego
		while (getline(inFile, temp))
		{
			istringstream stream(temp);
			string tempNumber, theme, name, tempMinifigs, tempPieces, tempPrice;
			getline(stream, tempNumber, ',');
			int number = stoi(tempNumber);
			getline(stream, theme, ',');
			getline(stream, name, ',');
			getline(stream, tempMinifigs, ',');
			int minifigs = stoi(tempMinifigs);
			getline(stream, tempPieces, ',');
			int pieces = stoi(tempPieces);
			getline(stream, tempPrice);
			double price = stod(tempPrice);

			Lego newLego = Lego(number, theme, name, minifigs, pieces, price); // creates new lego object
			legos.push_back(newLego); // adds new object to legos vector
		}
	}
	else
		cout << "Could not open " << fileName << endl;
}

void mostExpensive(const vector<Lego>& legos)
{
	Lego mostExpensiveLego = legos[0];
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		if (legos[i].price > mostExpensiveLego.price)
			mostExpensiveLego = legos[i];
	}
	cout << "The most expensive set is:\n";
	printLego(mostExpensiveLego);
}

void largestPieceCount(const vector<Lego>& legos)
{
	Lego mostPieces = legos[0];
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		if (legos[i].pieces > mostPieces.pieces)
			mostPieces = legos[i];
	}
	cout << "The set with the highest parts count:\n";
	printLego(mostPieces);
}

void searchName(const vector<Lego>& legos)
{
	int count = 0;
	string name;
	getline(cin, name);
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		if (legos[i].name.find(name) != string::npos)
		{
			count++;
		}
	}
	if (count == 0)
		cout << "No sets found matching that search term\n";
	else
	{
		cout << "Sets matching \"" << name << "\":\n\n";
		for (unsigned int i = 0; i < legos.size(); i++)
		{
			if (legos[i].name.find(name) != string::npos)
			{
				cout << legos[i].number << " " << legos[i].name << " $" << legos[i].price << endl;
			}
		}
	}
}

void searchTheme(const vector<Lego>& legos)
{
	int count = 0;
	string theme;
	getline(cin, theme);
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		if (legos[i].theme.find(theme) != string::npos)
			count++;
	}
	if (count == 0)
	{
		cout << "No sets found matching that search term\n";
	}
	else 
	{
		cout << "Sets matching \"" << theme << "\":\n\n";
		for (unsigned int i = 0; i < legos.size(); i++)
		{
			if (legos[i].theme.find(theme) != string::npos)
			{
				cout << legos[i].number << " " << legos[i].name << " $" << legos[i].price << endl;
			}
		}
	}
}

void averagePartInfo(const vector<Lego>& legos)
{
	int sum = 0;
	cout << "Average part count for " << legos.size() << " sets: ";
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		sum += legos[i].pieces;
	}
	int average = sum / legos.size();
	cout << average << endl;
}

void priceInfo(const vector<Lego>& legos)
{
	cout << "Average price for " << legos.size() << " sets: $";
	double sum = 0;
	Lego max = legos[0];
	Lego min = legos[0];
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		sum += legos[i].price;
		if (legos[i].price > max.price)
			max = legos[i];
		if (legos[i].price < min.price)
			min = legos[i];
	}
	double average = sum / legos.size();
	cout << average << endl << endl;

	//print out least expensive set
	cout << "Least expensive set:\n";
	printLego(min);
	cout << endl;

	//print out most expensive set
	cout << "Most expensive set:\n";
	printLego(max);
}

void minifigInfo(const vector<Lego>& legos)
{
	cout << "Average number of minifigures: ";
	int sum = 0;
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		sum += legos[i].minifigs;
	}
	int average = sum / legos.size();
	cout << average << endl;
	cout << "Set with the most minifigures:\n";
	Lego most = legos[0];
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		if (legos[i].minifigs > most.minifigs)
			most = legos[i];
	}
	printLego(most);
}

void oneOfEverything(const vector<Lego>& legos)
{
	cout << "If you bought one of everything...\n";
	double cost = 0.0;
	int pieces = 0, minifigs = 0;
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		cost += legos[i].price;
		pieces += legos[i].pieces;
		minifigs += legos[i].minifigs;
	}
	cout << "It would cost: $" << cost << endl;
	cout << "You would have " << pieces << " pieces in your collection\n";
	cout << "You would have an army of " << minifigs << " minifigures!\n";
}

