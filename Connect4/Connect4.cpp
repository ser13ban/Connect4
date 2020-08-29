#include <iostream>
#include<Windows.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

//truying to center everything:
void MoveWindow(int posx, int posy)
{
	RECT rectClient, rectWindow;
	HWND hWnd = GetConsoleWindow();
	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);
	MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void MoveCenter()
{
	RECT rectClient, rectWindow;
	HWND hWnd = GetConsoleWindow();
	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);
	int posx, posy;
	posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2,
		posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2,

		MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void ini(char table[8][15]) {
	int i, j, aux=1;
	for (i = 0; i <= 7; ++i) {
		for (j = 0; j <= 14; ++j) {
			table[i][j] = ' ';
		}
	}
	for (i = 0; i <= 5; ++i) {
		for (j = 0; j <= 14; j += 2) {
			table[i][j] = '|';
		}
	}
	/*
	for (j = 0; j <= 14; j += 2) {
		table[6][j] = '.';
	}
	for (j = 1; j <= 13; j += 2) {
		table[6][j] = '_';
	}
	*/
	for (j = 1; j <= 13; j += 2) {

		table[6][j] = aux+'0';
		aux++;
	}
}
void display(char table[8][15]) {
	int i, j;
	for (i = 0; i <= 7; ++i) {
		for (j = 0; j <= 14; ++j) {
			//cout << table[i][j]<<' ';
			if (table[i][j] == '@')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 );
				cout << table[i][j] << ' ';
			}
			else if (table[i][j] == '#')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
				cout << table[i][j] << ' ';
			}
			else if (table[i][j] >= 49 && table[i][j] <= 55)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << table[i][j] << ' ';
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << table[i][j] << ' ';
			}
		}
		cout << '\n';
	}
}
int translatePositon(int pos) {
	return pos + pos - 1;
}
void move(char table[8][15],int pos,int player) {
	int i = 0;
	while (table[i][pos] == ' ' && i<6) {
		system("cls");
		if (i == 0) {
			if (player == 1) { table[i][pos] = '@'; }
			else{ table[i][pos] = '#'; }
			display(table);

		}
		else {
			if(player==1){ table[i - 1][pos] = ' '; table[i][pos] = '@'; }
			else{ table[i - 1][pos] = ' '; table[i][pos] = '#';}
			display(table);
		}
		++i;
	}

}
bool checkGameOver(char table[8][15],int player) {
	int i, j,k, count=0,aux;
	char pl;
	if (player == 1) { pl = '@'; }
	else{pl = '#';}
	//verificam vertical:
	for (j = 1; j <= 13; ++j) {
		for(i=5;i>=3;i--){
		count = 1;
		while (i >= 0 && table[i][j]==pl && (table[i][j] == table[i - 1][j])) {
			count++;
			if (count == 4) {
				return false;
			}
			i--;
		}
		}
	}
	//verificam orizontal:
	for (i = 5; i >= 0; i--) {
		for (j = 1; j <= 7; j += 2) {
			count = 1;
			while (j <= 13 && table[i][j] == pl && (table[i][j] == table[i][j + 2])) {
				count++;
				if (count == 4) {
					return false;
				}
				j += 2;
			}
		}
	}
	//verificare diagonal

	//directia: din stanga spre dreapta:
	i = 5; j = 1;
	for (int k = 5; k >= 3; k--)
	{
		aux = k * 2 + 1;
		i = k; j = 1; count = 0;
		count = 0;
		while (i >= 0 && j <= aux && table[i][j]==pl) {
			count++;
			if (count == 4) {
				return false;
			}
			i--;
			j += 2;
		}
		//cout<<'\n';
	}
	for (int k = 3; k <= 7; k = k + 2)
	{
		j = k; i = 5;
		count = 0;
		while (i >= 0 && j <= 13 && table[i][j]==pl) {
			count++;
			if (count == 4) {
				return false;
			}
			i--;
			j += 2;
		}
		//cout<<'\n';
	}

	//directia: din stanga spre dreapta:
	//aprape la fel ca mai sus doar ca terbuie sa plec cu j-ul in mod descrescator su sa ma uit la alte valori pentru atribuire
	aux = 5;
	for (int k = 3; k <= 7; k += 2) {
		i = aux;
		aux--;
		j = 13;
		count = 0;
		while (i >= 0 && j >= k && table[i][j] == pl) {
			count++;
			if (count == 4) {
				return false;
			}
			i--;
			j -= 2;
		}
		//cout << '\n';
	}
	aux = 0;
	for (int k = 11; k >= 7; k -= 2) {
		i = 5;
		j = k;
		count = 0;
		while (j >= 1 && i >= aux && table[i][j] == pl) {
			count++;
			if (count == 4) {
				return false;
			}
			i--;
			j -= 2;
		}
		aux++;
		//cout << '\n';
	}


	return true;
}
int main() {

	MoveWindow(10, 10);
	MoveCenter();
	int x, y,gameMode=0;
	bool gameOver = 1;
	char table[8][15];
	cout << "CONNECT4"<<'\n';
	cout << "Selectati una din optuinii:"<<'\n';
	cout << "1) Multiplayer (jucati contra un prieten)"<<'\n';
	cout << "2) Single player, contra calculatorlui ( nivel usor, calculatorul alege un loc aleator)" << '\n';
	cout << "3) Single player, contra calculatorlui ( nivel greu, calculatorul alege intotdeauna cea mai bune pozitie" << '\n';
	while (gameMode < 1 || gameMode>3) {
		cout << "Va rugam sa alegeti un mod de joc valabil: "<<'\n';
		cin >> gameMode;
	}
	ini(table);
	display(table);
	if(gameMode==1){
	while (gameOver) {
		cout << "Player 1: pe ce coloana vreti sa plasati piesa? ";
		cin >> x;
		if (x < 1 || x>7) {
			cout << "Muatarea trebuie facuta pe o coloana valabila (un numar intreg intre 1 si 7), introduceti alta valuare: ";
			cin >> x;
		}
		x = translatePositon(x); // aduca positia lui x de la player la coloana matricei
		if (table[0][x] != ' ') {// verificam daca am ajuns la marginea tabelei astgel incat player 1 sa nu poata sa modifice piesa lui plyer 2 de pe primul rand si viceversa(il vom obliga sa aleaga alta coloana)
			cout << "Ati ajuns la marginea tablei de joc, alegeti alta pozitie:  ";
			cin >> x;
			x = translatePositon(x);
		}
		move(table, x,1); //aplicam mutarea lui x
		//imediat dupa mutare se verifica daca nu este gameOver(daca aici este gameOver inseamna ca player 1 a castigat)
		if (checkGameOver(table,1) == 0) {
			cout << "Player 1 wins";
			gameOver = 0;
			break;
		}
		
		//Aproape acelasi lucruri se fac si pentru player 2;
		cout << "Player 2: pe ce coloana vreti sa plasati piesa? ";
		cin >> y;
		if (y < 1 || y>7) {
			cout << "Muatarea trebuie facuta pe o coloana valabila (un numar intreg intre 1 si 7), introduceti alta valuare: ";
			cin >> y;
		}
		y = translatePositon(y);
		if (table[0][y] != ' ') {
			cout << "Ati ajuns la marginea tablei de joc, alegeti alta pozitie:  ";
			cin >> y;
			y = translatePositon(y);
		}
		move(table, y, 2);
		if (checkGameOver(table,2) == 0) {
			cout << "Player 2 wins";
			gameOver = 0;
			break;
		}

	}
	}
	else if (gameMode == 2) {
		while (gameOver) {
			cout << "Player 1: pe ce coloana vreti sa plasati piesa? ";
			cin >> x;
			if (x < 1 || x>7) {
				cout << "Muatarea trebuie facuta pe o coloana valabila (un numar intreg intre 1 si 7), introduceti alta valuare: ";
				cin >> x;
			}
			x = translatePositon(x); // aduca positia lui x de la player la coloana matricei
			if (table[0][x] != ' ') {// verificam daca am ajuns la marginea tabelei astgel incat player 1 sa nu poata sa modifice piesa lui plyer 2 de pe primul rand si viceversa(il vom obliga sa aleaga alta coloana)
				cout << "Ati ajuns la marginea tablei de joc, alegeti alta pozitie:  ";
				cin >> x;
				x = translatePositon(x);
			}
			move(table, x, 1); //aplicam mutarea lui x
			//imediat dupa mutare se verifica daca nu este gameOver(daca aici este gameOver inseamna ca player 1 a castigat)
			if (checkGameOver(table, 1) == 0) {
				cout << "Player 1 wins";
				gameOver = 0;
				break;
			}
			int mov = 0;
			mov = rand() % 7 + 1;
			mov = translatePositon(mov);
			move(table, mov, 2);
			if (checkGameOver(table, 2) == 0) {
				cout << "You lost";
				gameOver = 0;
				break;
			}
		}
	}
	else if (gameMode == 3) { cout << "Ne pare rau inca nu am dezvoltat acest mod de joc (COMING SOON)"<<'\n'<<'\n'; }
}