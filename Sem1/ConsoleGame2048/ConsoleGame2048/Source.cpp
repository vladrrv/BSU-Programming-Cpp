#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <ctime>
using namespace std;

int random_index(int x)
{
	int index;
	index = rand() % x;
	return index;
}

class GameAI
{
	int field[4][4];
public:
	GameAI()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				field[i][j] = 0;
		generateNew();
	}
	void save(ofstream &savefile)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				savefile << field[j][i] << " ";
			savefile << endl;
		}
	}
	void load(ifstream &savefile)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				savefile >> field[j][i];
	}
	void play()
	{
		printField();
		int ch = 0;
		while (ch != 27)
		{
			ch = _getch();
			if (ch == 0 || ch == 224)
			{
				int prev[4][4];
				memcpy(prev, field, 64);
				switch (_getch())
				{
				case 72: // up arrow
					up();
					break;
				case 80: // down arrow
					down();
					break;
				case 75: // left arrow
					left();
					break;
				case 77: // right arrow
					right();
					break;
				}
				if (memcmp(prev, field, 64))
				{
					random_spawn();
					printField();
				}
			}
			else
				continue;
		}
	}
private:
	void generateNew()
	{
		srand(time(NULL));
		int i = 0, j = 0;
		i = random_index(4);
		j = random_index(4);
		field[i][j] = 2;
		i = random_index(4);
		j = random_index(4);
		field[i][j] = 2;

	}
	void printField()
	{
		system("cls");
		int el_size = 1;
		int border_size = 7;
		int check = 10;
		for (int j = 0; j < 4; j++)
		{
			int i = 0;
			while (i < 4)
			{
				if (field[i][j] >= check)
				{
					check = check * 10;
					el_size += 1;
					border_size += 4;
					i--;
				}
				i++;
			}
		}
		int j = 0;
		while (j < 4)
		{
			cout << "|";
			for (int l = 0; l < border_size; l++)
				cout << "-";
			cout << "|" << endl;
			for (int i = 0; i < 4; i++)
			{
				if (field[i][j] == 0)
				{
					cout << "|";
					for (int l = 0; l < el_size; l++)
						cout << " ";
				}
				else
				{
					cout << "|" << field[i][j];
					int temp_el = field[i][j];
					int count = 0;
					while (temp_el)
					{
						temp_el /= 10;
						count++;
					}
					while (count < el_size)
					{
						cout << " ";
						count++;
					}
				}
			}
			cout << "|" << endl;
			j++;
		}
	}
	void fall(int *line)
	{
		int temp[4] = { 0,0,0,0 }, k = 0;
		for (int i = 0; i < 4; i++)
			if (line[i] != 0)
				temp[k++] = line[i];
		for (int i = 0; i < 4; i++)
			line[i] = temp[i];
	}
	void mov(int *line)
	{
		fall(line);
		for (int i = 0; i < 3; i++)
			if (line[i] == line[i + 1])
			{
				line[i] *= 2;
				line[i + 1] = 0;
				fall(line);
			}
	}
	void left()
	{
		int temp[4];
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				temp[j] = field[j][i];
			mov(temp);
			for (int j = 0; j < 4; j++)
				field[j][i] = temp[j];
		}
	}
	void right()
	{
		int temp[4];
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				temp[j] = field[3 - j][i];
			mov(temp);
			for (int j = 0; j < 4; j++)
				field[3 - j][i] = temp[j];
		}
	}
	void up()
	{
		for (int i = 0; i < 4; i++)
			mov(field[i]);
	}
	void down()
	{
		int temp[4];
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				temp[j] = field[i][3 - j];
			mov(temp);
			for (int j = 0; j < 4; j++)
				field[i][3 - j] = temp[j];
		}
	}
	void random_spawn()
	{
		int i, j, k;
		i = random_index(4);
		j = random_index(4);
		k = random_index(10);
		if (field[i][j] == 0)
		{
			if (k == 2)
				field[i][j] = 4;
			else
				field[i][j] = 2;
		}
		else
			random_spawn();
	}
};

class Game
{
	string name;
	GameAI g;
public:
	Game() : name("New Game")
	{ }
	Game(string s) : name(s)
	{ }
	void launch()
	{
		cout << "\n                           Greetings, player! "
			<< "\nThis game is my programming homework, "
			<< "\nI hope my programming teacher Anatoly will like it."
			<< "\nFeel free to add any fixes and special tasks!"
			<< "\n\nUse arrows to control the game";
		cout << "\nTo start a new game now, press 'enter' key. \nTo load previously saved game, press 'l' key. \nTo save and/or exit the game, press 'esc' key" << endl;
		switch (_getch())
		{
		case 'l': load(); start(); break;
		case 13: start(); break;
		default: cout << "\nIncorrect input!";
		}
	}
	void start()
	{
		g.play();
		cout << "\nDo you want to save the game? (if yes press 'enter', otherwise press any other key)";
		if (_getch() == 13)
			save();
		cout << "\nDo you want to exit? (if yes press 'enter', otherwise press any other key)";
		if (_getch() != 13)
			start();
	}
	void save()
	{
		ofstream savefile;
		savefile.open("save.txt");
		g.save(savefile);
		savefile.close();
		cout << "\nSaved!";
	}
	void load()
	{
		ifstream savefile;
		savefile.open("save.txt");
		g.load(savefile);
	}
};

int main()
{
	Game a;
	a.launch();
}