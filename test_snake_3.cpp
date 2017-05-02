#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>

// Dinh nghia cac phim di chuyen tren ban phim: a, d, w, s
#define    KEY_A    0x41
#define    KEY_D    0x44
#define    KEY_W    0x57
#define    KEY_S    0x53

using namespace std;

// duong bien gioi han con ran co the di chuyen
const int TUNG_DO = 20;
const int HOANG_DO = 60;


// tao vi tri moi
struct viTri {
	int x;
	int y;
};

// danh sach lien ket cac nut cua con ran
struct snake{
	viTri data;
	snake * next;
};

void gotoxy(short x, short y);												// ham gotoxy: dua con tro toi vi tri (x, y)
viTri newNoc (int x, int y);												// tao vi tri cua 1 nut
void addHead (snake *& head, int x, int y);									// tao nut con ran moi
void addEnd (snake *& head, int x, int y);									// chep du lieu vi tri vao nut moi cua con ran ( khi an duoc thuc an)
int length (snake *& head);													// do dai cua ran
void copy (snake *& head1, snake *& head2);									// sao chep vi tri nut 2 vao nut 1
void background (snake *& head); 											// tao phong nen de choi game
void atime (long & doKho, int & control1, int & control2);					// thoi gian dung cua con ran, nut con control la A, W, S, D de chi huong di chuyen
void movieSnake (snake *& head, int & control1, int & control2)	;			// di chuyen con ran = di chuyen lan luot tung nut cua con ran (*)
void print (snake *& head);													// in ca con ran sau khi xoa man hinh
bool checkKey(int key);														// trong time chay kiem tra co an nut di chuyen hay ko
void xoaMH ();																// xoa man hinh
bool isMovie(snake *& head, snake *& ghost, int & score);					// dieu kien di chuyen: ko dam trung duoi, ko dam trung tuong
void theEnd (snake *& head, int & score);									// in man hinh ket thuc game
bool newFood (viTri & food);												// tao thuc an moi
void checkEat (snake *& head, snake *& ghost, viTri & food, int & score);	// Kiem tra ran co an duoc thuc an hay khong
void level (long & doKho);													// Chia do kho cua game, tuy theo toc do di chuyen cua con ran
void ghost (snake *& ghost, int & runGhost);								// tao chuong ngai vat di chuyen tu tren xuong, ran dam trung thi se thua
void printGhost (snake *& ghost);											// in chuong ngai vat
void deleteSnake (snake *& head);											// xoa con ran sau khi game ket thuc, ham nay dang hoan thien

int main ()
{
	int playAgain = 0;
	int control1 ;			// lenh dieu khien truoc do
	int control2;			// lenh dieu khien sau
	int i = 0, end = 0, score = 0, runGhost = 0;
	viTri food;
	long doKho;
	int bestScore = 0;
	do
	{
		snake *Snake;			// con ran
		snake *Ghost;			// chuong ngai vat
		Snake = NULL;
		Ghost = NULL;
		addHead (Snake, 2, 5);
		addHead (Snake, 3, 5);
		addHead (Snake, 4, 5);
		addHead (Snake, 5, 5);
		addHead (Snake, 6, 5);

		background (Snake);			// tao khung nen cua chuong trinh

		score = length(Snake);
		control1 = control2 = 3;
		xoaMH ();
		level (doKho);
		print (Snake);
		newFood (food);
		while (1) {
			if (isMovie (Snake, Ghost, score)) {
				gotoxy(1, 23);
				system ("pause");
				break;
			}

			checkEat (Snake, Ghost, food, score);
			atime (doKho, control1, control2);
			movieSnake (Snake, control2, control1);
			control1 = control2;
			xoaMH ();
			print (Snake);
			ghost (Ghost, runGhost);
			printGhost (Ghost);
			runGhost++;
		}
		xoaMH ();
		gotoxy (20, 5);
		cout << "1. Play again";
		gotoxy (20, 6);
		cout << "2. Back";
		gotoxy (14, 8);
		cout << "Please choose number (1->2): ";
		cin >> playAgain;

		if ( playAgain == 1)	{
			deleteSnake(Snake);
			deleteSnake(Ghost);
		}
	}
	while ( playAgain == 1);

	gotoxy(1, 23);
	system("pause");
	return 0;
}



// ham gotoxy: dua con tro toi vi tri (x, y)
void gotoxy(short x, short y)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x-1;
    pos.Y = y-1;
    SetConsoleCursorPosition(hCon, pos);
}

// tao vi tri cua 1 nut
viTri newNoc (int x, int y) {
	viTri result;
	result.x = x;
	result.y = y;
	return result;
}

// tao nut con ran moi
void addHead (snake *& head, int x, int y)	{
	snake *tmp = new snake;
	(tmp->data).x = x;
	(tmp->data).y = y;
	if (head == NULL)	{
		head = tmp;
	}
	else {
		tmp->next = head;
		head = tmp;
	}
	tmp = NULL;
}

// chep du lieu vi tri vao nut moi cua con ran ( khi an duoc thuc an)
void addEnd (snake *& head, int x, int y)	{
	snake *tmp = new snake;
	snake *copy = new snake;
	copy = head;
	(tmp->data).x = x;
	(tmp->data).y = y;
	tmp->next = NULL;
	if (head == NULL)	{
		head = tmp;
	}
	else	{
		while (copy->next != NULL)
			copy = copy->next;
		copy->next = tmp;
	}
}

// do dai cua ran
int length (snake *& head)	{
	int i = 0;
	snake *q = new snake;
	q = head;
	while (q != NULL)	{
		q = q->next;
		i++;
	}
	return i;
}

// sao chep vi tri nut 2 vao nut 1
void copy (snake *& head1, snake *& head2)	{
	(head1->data).x = (head2->data).x;
	(head1->data).y = (head2->data).y;
}

// tao phong nen de choi game
void background (snake *& head)	{
	//tao khung tuong
	for (int k = 1; k <= TUNG_DO; k++)	{
		gotoxy(1, k);
		cout << "+";
	}
	for (int k = 1; k <= HOANG_DO; k++)	{
		gotoxy(k, 1);
		cout << "+";
	}
	for (int k = 1; k <= TUNG_DO; k++)	{
		gotoxy(HOANG_DO, k);
		cout << "+";
	}
	for (int k = 1; k <= HOANG_DO; k++)	{
		gotoxy(k, TUNG_DO);
		cout << "+";
	}

	gotoxy (62, 3);
	cout << "SNAKE GAME";
	gotoxy(62, 5);
	cout << "Score:";
	gotoxy(69, 5);
	cout << length (head);
}

// thoi gian dung cua con ran, nut con control la A, W, S, D de chi huong di chuyen
void atime (long & doKho, int & control1, int & control2)	{
//	cin.ignore();
	int mid = control2;
	for (int j = 0; j < doKho; j++)	{
		if (checkKey(VK_LEFT) || checkKey(KEY_A))
			control2 = 1;
		if (checkKey(VK_UP) || checkKey(KEY_W))
			control2 = 2;
		if (checkKey(VK_RIGHT) || checkKey(KEY_D))
			control2 = 3;
		if (checkKey(VK_DOWN) || checkKey(KEY_S))
			control2 = 4;
	}
	if (control2 == (control1 - 2) || control2 == (control1 + 2))
		control2 = mid;
}

// di chuyen con ran = di chuyen lan luot tung nut cua con ran (*)
void movieSnake (snake *& head, int & control1, int & control2)	{
// di chuyen cac nut sau
	snake *q = new snake;
	q = head;
	while ( q->next != NULL )	{
		q = q->next;
	}
	(q->data).y = 1;

	// copy data cua nut sau vao nut truoc
	snake *k = new snake;
	while ( 1 ) {
		k = head;
		while (q != k->next)	{
			k = k->next;
		}
		copy(q, k);
		q = k;
		if (q == head) break;
		k = NULL;
	}
	q = NULL;

// di chuyen nut 1, theo huong a, w, d, s
	if (control2 == 1)			// a
		(head->data).x -= 1;
	if (control2 == 2)			// w
		(head->data).y -= 1;
	if (control2 == 3)			// d
		(head->data).x += 1;
	if (control2 == 4)			// s
		(head->data).y += 1;
}

// in ca con ran sau khi xoa man hinh
void print (snake *& head)	{
	snake *q = new snake;
	q = head;

	// nut 1
	gotoxy ((q->data).x, (q->data).y);
	cout << "*";
	q = q->next;

	// cac nut sau
	while ( q != NULL)	{
		gotoxy ((q->data).x, (q->data).y);
		cout << "+";
		q = q->next;
	}
	q = NULL;
}

// trong time chay kiem tra co an nut di chuyen hay ko
bool checkKey(int key)
{
    return GetAsyncKeyState(key);
}


// xoa man hinh
void xoaMH ()	{
	for (int i = 2; i < TUNG_DO; i++)	{
			gotoxy (2, i);
			cout << "                                                          ";
		}
}

// dieu kien di chuyen: ko dam trung duoi, ko dam trung tuong
bool isMovie(snake *& head, snake *& ghost, int & score)	{
	snake *q = new snake;
	q = head;

	while (q->next != NULL)	{
		// xem co dam trung ghost hay ko
		if (ghost != NULL)	{
			snake *k = new snake;
			k = ghost;
			while (k->next != NULL)	{
				if ((q->data).x == (k->data).x && (q->data).y == (k->data).y)	{
					theEnd (head, score);
					return 1;
				}
				k = k->next;
			}
			k = NULL;
		}

		q = q->next;
		if ((q->data).x == (head->data).x && (q->data).y == (head->data).y)	{
			theEnd (head, score);
			return 1;
		}


	}

	if ((head->data).x == 1)	{
		theEnd (head, score);
		return 1;
	}

	if ((head->data).y == 1)	{
		theEnd (head, score);
		return 1;
	}
	if ((head->data).x == HOANG_DO)	{
		theEnd (head, score);
		return 1;
	}

	if ((head->data).y == TUNG_DO)	{
		theEnd (head, score);
		return 1;
	}

	return 0;
}

// in man hinh ket thuc game
void theEnd (snake *& head, int & score)	{
	system("cls");
	gotoxy (30, 5);
	cout << "GAME OVER";
	gotoxy(29, 8);
	cout << "Score:";
	gotoxy(38, 8);
	cout << score;
}

// tao thuc an moi
bool newFood (viTri & food)	{
	srand (time (0));
	food.x = (rand())%(HOANG_DO - 2) + 2;
	food.y = (rand())%(TUNG_DO - 2) + 2;
	gotoxy(food.x, food.y);
	cout << "O";
	return 1;
}

void checkEat (snake *& head, snake *& ghost, viTri & food, int & score)	{
	// truong hop an duoc food
	if ((head->data).x == food.x && (head->data).y == food.y)
	{
		newFood (food);					// tao new food
		// tao nut moi o duoi con ran
		snake *q = new snake;
		q = head;
		while (q->next != NULL)
			q = q->next;
		addEnd(head, (q->data).x, (q->data).y);

		// them diem so
		gotoxy(69, 5);
		score += 15;
		cout << score;

		//tao ghost
		int ghost_x = (rand())%(HOANG_DO - 2) + 2;
		addHead(ghost, ghost_x, 2);
	}

	else {
		gotoxy(food.x, food.y);
		cout << "O";
	}
}

// Chia do kho cua game, tuy theo toc do di chuyen cua con ran
void level (long & doKho)	{
	int result;
	do {
		gotoxy (20, 5);
		cout << "1. Easy";
		gotoxy (20, 6);
		cout << "2. Medium";
		gotoxy (20, 7);
		cout << "3. Dificult";
		gotoxy (14, 9);
		cout << "Please choose level (1->3): ";
		cin >> result;
	}
	while (result > 3 || result < 0);
	if (result == 1) doKho = 8e4;
	if (result == 2) doKho = 4e4;
	if (result == 3) doKho = 2e4;
}

// tao chuong ngai vat di chuyen tu tren xuong, ran dam trung thi se thua
void ghost (snake *& ghost, int & runGhost)	{
	if ( ghost == NULL) return;
	//xoa ghost neu ra khoi man hinh
	if ((ghost->data).y >= TUNG_DO)
		ghost = ghost->next;

	snake *q = new snake;
	q = ghost;
	while ( q->next != NULL )	{
		if ((q->next->data).y >= TUNG_DO)	{
			q->next = q->next->next;
			break;
		}
		q = q->next;
	}

	// cho ghost di xuong
	q = ghost;

	if (runGhost%4 == 0) {
		while ( q->next != NULL )	{
			(q->data).y += 1;
			q = q->next;
		}
		q = NULL;
	}
}

// in chuong ngai vat
void printGhost (snake *& ghost)	{
	if ( ghost == NULL) return;
	snake *q = new snake;
	q = ghost;
	while ( q->next != NULL )	{
		gotoxy ((q->data).x, (q->data).y);
		cout << "*";
		q = q->next;
	}
}

// xoa con ran sau khi game ket thuc, ham nay dang hoan thien
void deleteSnake (snake *& head)	{
	delete [] head;
}
