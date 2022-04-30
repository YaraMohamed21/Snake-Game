#include<iostream>
#include<windows.h>
#include<conio.h>
#include <limits>
#include <unordered_set>
using namespace std;
//Global variables decleration
double start, finish;
int height = 25;
int width = 100;
int gameover = 0, counter, gameover2 = 0, choice, counter2;
int lflag = 0, rflag = 0, uflag = 0, dflag = 0, hit_flag = 0;//flags for left,right,up and down keyboard keys pressed by player1
int lflag2 = 0, rflag2 = 0, uflag2 = 0, dflag2 = 0;//flags for left,right,up and down keyboard keys pressed by player2
short fcount; //number of '@' in case of 2 players

using namespace std;
class Snake
{

	int x, y, fx, fy, x2, y2;
	/*
	x--->position of x snake for player 1
	y--->position of y snake for player 1
	x2-->position of x snake for player 2
	y2-->position of y snake for player 2
	fx-->represents position x of '@'
	fy-->represents position y of '@'

	*/

	char playername[50], playername2[50];;

	struct node
	{
		int nx, ny;
		struct node* next;
		struct node* back;
	};

	struct node* head = NULL; //represents the snake for player 1
	struct node* head2 = NULL;//represents the snake for player 2

	void gotoxy(int x, int y) //fuction to set cursor position
	{
		COORD pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	void nameandscore()
	{
		gotoxy(101, 0);
		textcolour(10);
		cout << "WELCOME !!";
		textcolour(6);
		gotoxy(101, 2);
		cout << playername << "'s SCORE = " << counter * 100;
		if (choice == 2)
		{
			gotoxy(101, 4);
			cout << playername2 << "'s SCORE = " << counter2 * 100;
			gotoxy(101, 6);
			cout << "Remained Fruit :";
			gotoxy(117, 6);
			cout << "  ";
			gotoxy(117, 6);
			cout << fcount;
		}
	}



	void textcolour(int k)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//A handle is a pointer or index with no visible type attached to it.
		//GetStdHandle: Retrieves a handle to the specified standard device (standard input, standard output, or standard error).
		//msh fhma awy bs msh moshkla :D
		SetConsoleTextAttribute(hConsole, k);
	}

public:

	void window() //setting window layout
	{
		if (choice == 1)
			textcolour(4);
		else
			textcolour(1);
		for (int i = 0; i <= width; i++)//frame layout
		{
			gotoxy(i, 0);
			cout << "Û";
			gotoxy(i, height);
			cout << "Û";
		}

		for (int i = 0; i <= height; i++)
		{
			gotoxy(0, i);
			cout << "Û";
			gotoxy(width, i);
			cout << "Û";
		}
	}


	void setup()
	{
		counter = 0;
		gameover = 0;
		window();
		resetflag();
		nameandscore();
		head = new node;
		head->nx = width / 2;
		head->ny = height / 2;
		head->next = NULL;
		head->back = NULL;
		x = width / 2;
		y = height / 2;
	label1:
		fx = rand() % width;
		if (fx == 0 || fx == width)
			goto label1;// go to label1 if x position of '@' hits the side wall 
	label2:
		fy = rand() % height;
		if (fy == 0 || fy == height)
			goto label2;// go to label2 if y position of '@' hits the upper wall 
	}

	void setup2()
	{
		resetflag2();
		gameover2 = 0;
		counter2 = 0;
		fcount = 2;
		head2 = new node;
		head2->nx = width / 2 + 5;
		head2->ny = height / 2 + 5;
		head2->next = NULL;
		head2->back = NULL;
		x2 = width / 2 + 5;
		y2 = height / 2 + 5;

	}

	void drawlist(struct node* h, int k)// function to draw a snake
	{
		textcolour(k);
		struct node* ptr;
		ptr = h;
		while (ptr != NULL)
		{
			gotoxy(ptr->nx, ptr->ny);
			cout << "Û";
			ptr = ptr->next;
		}
	}


	void destroylist(struct node* h)
	{
		struct node* ptr;
		ptr = h;
		while (ptr != NULL)
		{
			gotoxy(ptr->nx, ptr->ny);
			cout << " ";
			ptr = ptr->next;
		}
	}



	void draw1()
	{

		drawlist(head, 2);//draw snake 1
		gotoxy(fx, fy);
		textcolour(4);
		cout << "@";
		Sleep(70);
		destroylist(head);
	}
	void draw2()
	{

		drawlist(head, 2);//draw snake 1
		drawlist(head2, 5);//draw snake 1
		gotoxy(fx, fy);
		textcolour(4);
		cout << "@";
		Sleep(70);
		destroylist(head);
		destroylist(head2);

	}

	void resetflag()
	{
		uflag = 0;
		dflag = 0;
		lflag = 0;
		rflag = 0;
		hit_flag = 0;
	}

	void resetflag2()
	{
		uflag2 = 0;
		dflag2 = 0;
		lflag2 = 0;
		rflag2 = 0;
		hit_flag = 0;
	}
	void play()
	{
		int h;
		char ch;
		if (_kbhit())// if a key is pressed
		{
			ch = _getch();// store the pressed key
			h = ch; // store the ascii code of the pressed key
			switch (h)
			{
			case 72:if (dflag != 1) { resetflag(); uflag = 1; }
				   break;
			case 80:if (uflag != 1) { resetflag(); dflag = 1; }
				   break;
			case 75:if (rflag != 1) { resetflag(); lflag = 1; }
				   break;
			case 77:if (lflag != 1) { resetflag(); rflag = 1; }
				   break;

			case 119:if (dflag2 != 1) { resetflag2(); uflag2 = 1; }
					break;
			case 115:if (uflag2 != 1) { resetflag2(); dflag2 = 1; }
					break;
			case 97:if (rflag2 != 1) { resetflag2(); lflag2 = 1; }
				   break;
			case 100:if (lflag2 != 1) { resetflag2(); rflag2 = 1; }
					break;

			default:break;
			}
		}
	}
	void box(int m1, int n1, int m2, int n2)
	{
		for (int i = m1; i <= m2; i++)
		{
			gotoxy(i, n1);
			cout << "//";
			gotoxy(i, n2);
			cout << "//";
		}

		for (int i = n1; i <= n2; i++)
		{
			gotoxy(m1, i);
			cout << "//";
			gotoxy(m2, i);
			cout << "//";
		}
	}

	void welcome()//Welcome page layout
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(10);
		gotoxy(width / 2 - 10, height / 2 - 10);
		cout << "*** WELCOME TO SNAKE GAME *** ";
		textcolour(9);
		gotoxy(width / 2 - 16, height / 2 - 3);
		cout << "Press 1 For Single player \n";
		gotoxy(width / 2 - 16, height / 2 - 1);
		cout << "Press 2 For 2-players \n";
		gotoxy(width / 2 - 16, height / 2);

		cin >> choice;
		if (choice != 1 && choice != 2)// test_case_1 handling: if the user entered any input but 1 or 2 the game will not crash, instead it will ask the user to enter valid input and the game will run again.
		{
			cin.clear();
			cin.ignore(1000, '\n');
			gotoxy(width / 2 - 16, height / 2 + 1);
			cout << "Please enter 1 or 2";
			Sleep(1000);
			system("cls");
			welcome();
		}
		system("cls");
	}



	void welcome1()
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(6);
		gotoxy(width / 2 - 18, height / 2 - 3);
		cout << "WELCOME TO SNAKE GAME SINGLE PLAYER MODE ";
		textcolour(8);
		gotoxy(width / 2 - 13, height / 2);
		cout << "Enter Your Name : ";
		cin >> playername;
		system("cls");
	}

	void welcome2()
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(6);
		gotoxy(width / 2 - 18, height / 2 - 3);
		cout << "WELCOME TO SNAKE GAME MULTIPLAYER MODE ";
		textcolour(8);
		gotoxy(width / 2 - 13, height / 2);
		cout << "Enter Player1 Name : ";
		gotoxy(width / 2 - 13, height / 2 + 2);
		cout << "Enter Player2 Name : ";
		gotoxy(width / 2 + 7, height / 2);
		cin >> playername;
		gotoxy(width / 2 + 7, height / 2 + 2);
		cin >> playername2;
		system("cls");
	}

	char end()//score reveal
	{
	en:
		char c;
		gotoxy(width / 2 - 5, height / 2 - 4);
		cout << "GAME OVER \n";
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4 + 1);
		if (hit_flag)  goto here;
		textcolour(1);
		gotoxy(width / 2 - 15, height / 2 - 2);
		cout << playername << " You Scored : " << counter * 100;
		if (choice == 2)
		{
			gotoxy(width / 2 - 15, height / 2);
			cout << playername2 << " You Scored : " << counter2 * 100;
			textcolour(4);
			if (gameover != 0 && fcount != 0)
			{
				gotoxy(width / 2 - 15, height / 2 + 2);
				cout << playername2 << " has WON !";
				gotoxy(width / 2 - 15, height / 2 + 3);
				cout << playername << " has lost !";
			}
			else if (gameover == 0 && fcount != 0)
			{
				gotoxy(width / 2 - 15, height / 2 + 2);
				cout << playername << " has WON !";
				gotoxy(width / 2 - 15, height / 2 + 3);
				cout << playername2 << " has lost !";
			}
			if (fcount == 0)
			{
				textcolour(4);
				if (counter > counter2)
				{
					gotoxy(width / 2 - 15, height / 2 + 2);
					cout << playername << " has WON !";
					gotoxy(width / 2 - 15, height / 2 + 3);
					cout << playername2 << " has lost !";
				}
				else if (counter < counter2)
				{
					gotoxy(width / 2 - 15, height / 2 + 2);
					cout << playername2 << " has WON !";
					gotoxy(width / 2 - 15, height / 2 + 3);
					cout << playername << " has lost !";
				}
				else {
					gotoxy(width / 2 - 15, height / 2 + 2);
					cout << "TIE !!";
				}
			}
		}
	here:
		textcolour(6);
		gotoxy(width / 2 - 15, height / 2 + 5);
		cout << "Want To Play Again ? (Y/N) : ";
		cin >> c;
		if (cin.peek() != '\n' || (c != 'y' && c != 'Y' && c != 'n' && c != 'N'))
		{

			cin.clear();
			cin.ignore(1000, '\n');
			gotoxy(width / 2 - 15, height / 2 + 6);
			cout << "Please enter Y or N";
			Sleep(1000);
			system("cls");
			goto en;
		}
		system("cls");
		return c;

	}


	void run() //Snake movement
	{
		if (uflag == 1)
			y--;
		else if (dflag == 1)
			y++;
		else if (lflag == 1)
			x--;
		else if (rflag == 1)
			x++;


		if (uflag2 == 1)
			y2--;
		else if (dflag2 == 1)
			y2++;
		else if (lflag2 == 1)
			x2--;
		else if (rflag2 == 1)
			x2++;

	}
	void dolist(struct node* h, int pp, int qq) //update head,next and back 
	{
		struct node* ptr, * prev;
		ptr = h;
		prev = h;

		while (ptr->next != NULL)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		while (prev != h)
		{
			ptr->nx = prev->nx;
			ptr->ny = prev->ny;
			prev = prev->back;
			ptr = ptr->back;
		}
		ptr->nx = prev->nx;
		ptr->ny = prev->ny;
		prev->nx = pp;
		prev->ny = qq;
	}




	void drawagain()
	{
		if (x == width)
		{
			x = 1;
		}
		if (x == 0)
		{
			x = width - 1;
		}
		if (y == 0)
		{
			y = height - 1;
		}
		if (y == height)
		{
			y = 1;
		}
	}


	void drawagain2()
	{
		if (x2 == width)
		{
			x2 = 1;
		}
		if (x2 == 0)
		{
			x2 = width - 1;
		}
		if (y2 == 0)
		{
			y2 = height - 1;
		}
		if (y2 == height)
		{
			y2 = 1;
		}
	}

	void generatefruit()
	{
	label1:
		fx = rand() % width;
		if (fx == 0 || fx == width)
			goto label1;
	label2:
		fy = rand() % height;
		if (fy == 0 || fy == height)
			goto label2;
	}

	void checkfcount()
	{
		if (fcount == 0)
		{
			gotoxy(fx, fy);
			cout << " ";
			gameover = 1;
			gameover2 = 1;
		}
	}

	void checkup()
	{
		if (x == width || x == 0)
		{
			gotoxy(fx, fy);
			cout << " ";
			gameover = 1;
		}
		if (y == height || y == 0)
		{
			gotoxy(fx, fy);
			cout << " ";
			gameover = 1;
		}
		struct node* current1 = head;
		struct node* current2 = head2;
		unordered_set<int> mapx;
		unordered_set<int> mapy;
		while (current1 != NULL)
		{
			mapx.insert(current1->nx);
			mapy.insert(current1->ny);
			current1 = current1->next;
		}
		while (current2 != NULL)
		{
			if ((mapx.find(current2->nx) != mapx.end()) && (mapy.find(current2->ny) != mapy.end()))
			{
				gotoxy(fx, fy);
				cout << " ";
				gameover = 1;
				gameover2 = 1;
				gameover = 1;
				hit_flag = true;
				break;
			}
			current2 = current2->next;
		}
		drawagain();
		struct node* h;
		h = head->next;
		while (h != NULL)
		{
			if (x == h->nx && y == h->ny)
			{
				gameover = 1;
				break;
			}
			h = h->next;
		}

		if (x == fx && y == fy)
		{
			if (choice == 2)
			{
				fcount--;
				checkfcount();
			}
			struct node* t, * ptr, * prev;
			t = new node;
			t->next = NULL;
			t->back = NULL;
			ptr = head;
			prev = head;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = t;
			t->back = ptr;
			generatefruit();
			counter++;
			nameandscore();
		}
		dolist(head, x, y);
	}


	void checkup2()
	{
		if (x2 == width || x2 == 0)
		{
			gotoxy(fx, fy);
			cout << " ";
			gameover2 = 1;
		}
		if (y2 == height || y2 == 0)
		{
			gotoxy(fx, fy);
			cout << " ";
			gameover2 = 1;
		}
		drawagain2();
		struct node* h;
		h = head2->next;
		while (h != NULL)
		{
			if (x2 == h->nx && y2 == h->ny)
			{
				gameover2 = 1;
				break;
			}
			h = h->next;
		}

		if (x2 == fx && y2 == fy)
		{
			fcount--;
			checkfcount();
			struct node* t, * ptr, * prev;
			t = new node;
			t->next = NULL;
			t->back = NULL;
			ptr = head2;
			prev = head2;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = t;
			t->back = ptr;
			generatefruit();
			counter2++;
			nameandscore();
		}
		dolist(head2, x2, y2);
	}


	char game1()
	{
		char ch;
		welcome1();
		setup();
		window();
		while (!gameover)
		{
			draw1();
			play();
			run();
			checkup();
		}
		ch = end();
		return ch;
	}

	char game2()
	{
		char ch;
		welcome2();
		setup2();
		setup();
		window();
		while (gameover != 1 && gameover2 != 1)
		{
			draw2();
			play();
			run();
			checkup();
			checkup2();
		}ch = end();
		return ch;
	}

};
int main()
{
	start = clock();
	Snake s;
again: s.welcome();
	if (choice == 1)
	{
		char ch;
		ch = s.game1();
		if (ch == 'y' || ch == 'Y')goto again;
	}
	if (choice == 2)
	{
		char ch;
		ch = s.game2();
		if (ch == 'y' || ch == 'Y') { choice = 0; goto again; }
	}
	finish = clock();
	system("exit");
}
