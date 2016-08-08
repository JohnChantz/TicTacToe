/*	Γιάννης Χαντζηγούλας 
	ΑΜ:21368
	email: it21368@hua.gr
	Edited in Ubuntu 14.04 LTS using gedit, compiled succesfully with gcc.	
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Το βασικο struct για το board
typedef struct{
	int **a;
	int size;
}_board;

// Το board ειναι δεικτης στο _board
typedef _board* board;

// Το struct για την θεση οπου τοποθετειται το 'Χ' η 'Ο'
typedef struct{
	int row;
	int col;
}position;

//Δηλωση των προτοτυπων των συναρτησεων για το σταδιο του Pre-Processor
void display_Board(int, int **, board);
void init_board(board, int, int**);
void get_1stplayer_move(position*, char,board,int);
void get_2ndplayer_move(position*,char,board,int);
int check_board(board,int,int **);
int check_winner(board,int,int **,char);
void free_memory(board,int,int **,position*,position*);

//Αρχη του κυριως κωδικα της main
int main(int argc, char** argv)
{
	//ελεγχος για σωστη επιλογη μεγεθους απο το χρηστη και αν εχει δωσει μεγεθος
	if(argc==1 || atoi(argv[1])<=2)
	{
		printf("\nSyntax Error. Give board size=>3.\n\tProgram Terminating...\n\n");
		return 0;
	}

	printf("\nHello players and\n\tWelcome to TicTacToe game!!!\n\n\n");

	//Αναθεση μνημης για το board,size,a**
	board myboard = (board)malloc(sizeof(board));
	if(myboard==NULL)
	{
		printf("ERROR!!! Memory allocation failed.\nProgram terminating...\n");	
		return 0;						//ελεγχος αν εγινε αναθεση μνημης,αλλιως τερματισμος
	}
	myboard->size = atoi(argv[1]);
	printf("The size you choosed for the board is %d\n\n", myboard->size);
	myboard->a = (int**)malloc(myboard->size*sizeof(int*));
	if(myboard->a==NULL)
	{
		printf("ERROR!!! Memory allocation failed.\nProgram terminating...\n");
		return 0;						//ελεγχος αν εγινε αναθεση μνημης,αλλιως τερματισμος
	}
	int i, j;
	for (i = 0; i < myboard->size; i++)
	{
		myboard->a[i] = (int*)malloc(myboard->size*sizeof(char));
		if(myboard->a[i]==NULL)
		{
			printf("ERROR!!! Memory allocation failed.\nProgram terminating...\n");
			return 0;					//ελεγχος αν εγινε αναθεση μνημης,αλλιως τερματισμος
		}
	}
	/**************/

	//Αρχικοποιηση του πινακα
	init_board(myboard, myboard->size, myboard->a);
	printf("Your board is :\n");
	display_Board(myboard->size, myboard->a, myboard);

	//Ενημερωση του χρηστη για επιλογη συμβολου
	printf("\t\t!!!...Let the game begin...!!!\n\n");
	printf("1st player: Choose your symbol X or O: ");
	char player1, player2;	
	//Ελεγχος για εγκυρη επιλογη συμβολων
	while(1)
	{
		scanf("%s",&player1);
		if(player1=='X' || player1=='x' || player1=='O' || player1=='o')
			break;
		printf("Wrong symbol. Try again: ");
	}

	if (player1 == 'X' || player1== 'x')
	{
		player1='X';
		player2 = 'O';
	}
	else if (player1 == 'O'|| player1 == 'o')
	{
		player1='O';
		player2 = 'X';
	}


	printf("1st player choosed %c, 2nd player must take %c.\n\n", player1, player2);
	printf("Player 1 please give the position you wish to play,ie. X,Y.\n");

	//Αναθεση μνημης για το stuct position
	position* position1=(position*)malloc(sizeof(position));
	if(position1==NULL)
	{
		printf("ERROR!!! Memory allocation failed.\nProgram terminating...\n");
		return 0; 						//ελεγχος αν εγινε αναθεση μνημης,αλλιως τερματισμος
	}
	position* position2=(position*)malloc(sizeof(position));
	if(position1==NULL)
	{
		printf("ERROR!!! Memory allocation failed.\nProgram terminating...\n");
		return 0;						//ελεγχος αν εγινε αναθεση μνημης,αλλιως τερματισμος
	}

	//Κυριως κοματι παιχνιδιου
	do
	{
		//Ελεγχος των κινησεων του παιχτη1
		do
		{
			get_1stplayer_move(position1,player1,myboard,myboard->size);
			if(myboard->a[position1->row][position1->col]=='X' || myboard->a[position1->row][position1->col]=='O')
			{
				printf("The position you choosed isn't available.\nGive position again.\n\t");
			}
			else
			{
				printf("\tValid positions given. Continue playing...\n\n");
				myboard->a[position1->row][position1->col] = player1;
				display_Board(myboard->size, myboard->a, myboard);
				break;
			}
		}while(1);
		//ελεγχος αν νικησε ο παιχτης1
		if(check_winner(myboard,myboard->size,myboard->a,player1))
		{	
			display_Board(myboard->size, myboard->a, myboard);
			printf("Congratz player1 you are the winner!!!\n\n\n\t\t~End_of_Game~\n\n");
			break;
		}
		if(!check_board(myboard, myboard->size, myboard->a))
			break;
		/*****************/
		//Ελεγχος των κινησεων του παιχτη2
		do
		{
			get_2ndplayer_move(position2,player2,myboard,myboard->size);
			if(myboard->a[position2->row][position2->col]=='X' || myboard->a[position2->row][position2->col]=='O')
			{
				printf("The position you choosed isn't available.\nGive position again.\n\t");
			}
			else
			{
				printf("\tValid positions given. Continue playing...\n\n");
				myboard->a[position2->row][position2->col] = player2;
				display_Board(myboard->size, myboard->a, myboard);
				break;
			}
		}while(1);
		//ελεγχος αν νικησε ο παιχτης2
		if(check_winner(myboard,myboard->size,myboard->a,player2))
		{
			display_Board(myboard->size, myboard->a, myboard);
			printf("Congratz player2 you are the winner!!!\n\n\n\t\t~End_of_Game~\n\n");
			break;
		}
		/****************/
	}while (check_board(myboard, myboard->size, myboard->a));//ελεγχος αν υπαρχουν κενες θεσεις στον πινακα

	//ελεγχος αν υπαρχη ισοπαλια, εφοσον δεν υπαρχουν κενες θεσεις ουτε νικητης
	if(!check_board(myboard,myboard->size,myboard->a)&&!check_winner(myboard,myboard->size,myboard->a,player2)&&!check_winner(myboard,myboard->size,myboard->a,player1))
	{
		printf("\n\tIt's a TIE...\n\n");
	}
	//απελευθερωση δεσμευμενης μνημης
	free_memory(myboard,myboard->size,myboard->a,position1,position2);
	return 0;
}//Τελος της main



//Κωδικας Συναρτησεων
void display_Board(int size, int **a, board myboard)	//εμφανιση-σχεδιασμος του πινακα
{
	int i, j;
	for (i = 0; i<myboard->size; i++)
	{

		for (j = 0; j<myboard->size; j++)
		{
			printf(" %c ", myboard->a[i][j]);
			if (j != ((myboard->size) - 1))
				printf("|");
		}
		printf("\n");
	
		for (j = 0; j<myboard->size; j++)
		{
			printf("---");
			if (j != ((myboard->size) - 1))
				printf("|");
		}
		printf("\n");
	}

	printf("\n");
}

void init_board(board myboard, int size, int **a)	//αρχηκοποιηση του πινακα με κενες θεσεις
{
	int i, j;
	for (i = 0; i<myboard->size; i++)
	{
		for (j = 0; j<myboard->size; j++)
		{
			myboard->a[i][j] = ' ';
		}
	}
}

void get_1stplayer_move(position* position1, char player1,board myboard,int size) 	//ελεγχος αν ο παιχτης1 κανει εγκυρη κινηση
{
	printf("Player1 choose position: ");
	scanf("%d%*c%d", &(position1->row), &(position1->col));//ενημερωση του παιχτη1 για να δωσει θεση
	printf("\nChecking row and column given...");
		while(position1->row<1 || position1->row>myboard->size || position1->col<1 || position1->col>myboard->size)	//ελεγχος οτι η θεση ειναι εγκυρη και δεν βγαινει εκτος πινακα
		{
		
			if(position1->row>=1 && position1->row<=myboard->size)
				printf("\n\tValid row given. Check for column...");
			else if(position1->col>=1 && position1->col<=myboard->size)
				printf("\n\tValid column given. Checking for row...");
			if(position1->row<1 || position1->row>myboard->size)
			{
				do
				{
					printf("\n\tWrong row given. Please try again: ");
					scanf("%d",&(position1->row));
				}while(position1->row<1 || position1->row>myboard->size);
			}

			if(position1->col<1 || position1->col>myboard->size)
			{
				do
				{
					printf("\n\tWrong column given. Please try again: ");
					scanf("%d",&(position1->col));
				}while(position1->col<1 || position1->col>myboard->size);		
			}
		}		/***************************/
	position1->row--;	//ο παιχτης1 δινει θεσεις τις μορφης 1.1 ή 3.2 κτλπ, στο σημειο αυτο γινετε μετατροπη ωστε η θεσεις να αντιστοιχουν στις πραγματικες συντεταγμενες του πινακα
	position1->col--;
	printf("\n\n");
}
void get_2ndplayer_move(position* position2, char player2,board myboard,int size)	//αντιστοιχοι ελεγχοι για τον παιχτη2
{
	printf("Player2 choose position: ");
	scanf("%d%*c%d", &(position2->row), &(position2->col));
	printf("\nChecking row and column given...");
		while(position2->row<1 || position2->row>myboard->size || position2->col<1 || position2->col>myboard->size)
		{
		
			if(position2->row>=1 && position2->row<=myboard->size)
				printf("\n\tValid row given. Check for column...");
			else if(position2->col>=1 && position2->col<=myboard->size)
				printf("\n\tValid column given. Checking for row...");
			if(position2->row<1 || position2->row>myboard->size)
			{
				do
				{
					printf("\n\tWrong row given. Please try again: ");
					scanf("%d",&(position2->row));
				}while(position2->row<1 || position2->row>myboard->size);
			}

			if(position2->col<1 || position2->col>myboard->size)
			{
				do
				{
					printf("\n\tWrong column given. Please try again: ");
					scanf("%d",&(position2->col));
				}while(position2->col<1 || position2->col>myboard->size);
			}
		}
	position2->row--;
	position2->col--;
	printf("\n\n");
}

int check_board(board myboard, int size, int **a)	//ελεγχος του πινακα αν εχει ελευθερες θεσεις 
{
	int i, j;
	int counter = (myboard->size)*(myboard->size);
	for (i = 0; i<myboard->size; i++)
	{
		for (j = 0; j<myboard->size; j++)
		{
			if (myboard->a[i][j] == 'X' || myboard->a[i][j] == 'O')
			{
				counter--;
			}
		}
	}
	if (counter == 0)
		return 0;
	else
		return 1;
}

int check_winner(board myboard,int size,int **a,char player)	//ελεγχος αν υπαρχει νικητης
{
	int i,j;
	int counter=0;
	int minus=0;
	
	for(i=0;i<myboard->size;i++)	//ελεγχος των οριζοντιων γραμμων του πινακα
	{
		for(j=0;j<myboard->size;j++)
		{
			if(myboard->a[i][j]==player)
			{
				counter++;
				if(counter==myboard->size)
					return 1;
			}
			
		}
		counter=0;
	}/***********/

	for(i=0;i<myboard->size;i++)	//ελεγχος των καθετων γραμμων του πινακα
	{
		for(j=0;j<myboard->size;j++)
		{
			if(myboard->a[j][i]==player)
			{
				counter++;
				if(counter==myboard->size)
					return 1;
			}
		}
		counter=0;
	}/*********/

	for(i=0;i<myboard->size;i++)	//ελεγχος της πρωτης διαφωνιου του πινακα
	{
		for(j=0;j<myboard->size;j++)
		{
			if(i==j)
			{
				if(myboard->a[i][j]==player)
					counter++;
				if(counter==myboard->size)
					return 1;
			}
		}
	}/*******/
	counter=0;

	for(i=0;i<myboard->size;i++)	//ελεγχος της δευτερης διαγωνιου του πινακα
	{
		for(j=0;j<myboard->size;j++)
		{
			if(j==(myboard->size)-1-minus)
			{
				if(myboard->a[i][j]==player)
					counter++;
				if(counter==myboard->size)
					return 1;
			}
		}
		minus++;	//το minus ειναι η μετατοπιση που απαιτειτε καθε φορα απο την γραμμη του πινακα ωστε να βρισκετε στη διαγωνιο
	}/********/
		

	return 0;

}

void free_memory(board myboard,int size,int **a,position* position1,position* position2)	//απελευθερωση της μνημης που εχει δεσμευτει κατα τη διαρκεια της εκτελεσης
{
	int i;
	for(i=0;i<myboard->size;i++)
	{
		free(myboard->a[i]);
	}
	
	free(myboard->a);
	
	free(position1);
	free(position2);
}
