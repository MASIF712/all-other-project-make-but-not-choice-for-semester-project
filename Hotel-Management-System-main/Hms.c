#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
struct member
{
    int Room;
    char name[50];
} s;

void Add()
{
    FILE *f;
    f = fopen("noteBook.txt", "a");
    printf("Enter Room no :");
    scanf("%d", &s.Room);
    printf("Enter Name : ");
    scanf("%s", s.name);
    fprintf(f, "Name : %s\t Room No : %d\n", s.name, s.Room);
    printf("Sucessfully Booked Room\n");
    fclose(f);
}
void save()
{
    FILE *f;
    f = fopen("noteBook.txt", "a");
    char str[55];
    while (fread(str, sizeof(str), sizeof(f), f))
    {
        fwrite(str, sizeof(str), sizeof(f), stdout);
    }
    fclose(f);
}
void view()
{
    FILE *f;
    // printf("Name \t Room No \t\n");
    f = fopen("noteBook.txt", "r");
    char s;
    int ch;
    while ((ch = fgetc(f)) != EOF)
    {
        putchar(ch);
    }
    printf("complete printed");
    fclose(f);
}
void menu()
{
    printf("````````````````WELLCOME````````````````\n");
    printf("Enter 1-> Book Room \n");
    printf("Enter 2-> View Details \n");
    printf("Enter 3-> remove member \n");
    printf("Enter 4-> clean room \n");
    printf("Enter 5-> edit room \n");
    printf("Enter 6-> Exit! \n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        // bookroom();
        Add();
        save();
        break;
    case 2:
        view();
        break;
    case 3:
        // remove();
        break;
    case 4:
        // remove_all_room();
        break;
    case 5:
        // edit();
        break;
    case 6:
        // return 0;
        break;
    default:
        break;
    }
}
int main()
{
    printf("Well Come\n");
    int i=0;
	
	time_t t;
	time(&t);
	char customername;
	char choice;

	system("cls");   // FOR CLEARING SCREEN
	// SetBkColor(hdc,255);
	printf(" -------------------------------------------------------------------------\n");
    printf("|                                                                         |\n");
    printf("|                                                                         |\n");
    printf("|  O   O   OOO    OOOO  OOOOO  OOOOO  O           O   O   OOOO            |\n");
    printf("|  O   O  O   O  O        O    O      O           OO OO  O                |\n");
    printf("|  OOOOO  O   O   OOOO    O    OOOO   O           O O O   OOOO            |\n");
    printf("|  O   O  O   O      O    O    O      O           O   O      O            |\n");
    printf("|  O   O   OOO    OOOO    O    OOOOO  OOOOO       O   O   OOOO            |\n");
    printf("|                                                                         |\n");
    printf("|                                                                         |\n");                  
	printf(" -------------------------------------------------------------------------\n");
 	printf("\t\t*************************************************\n");
	printf("\t\t*                                               *\n");
	printf("\t\t*       -----------------------------           *\n");
	printf("\t\t*        WELCOME TO HOTEL DESERT CAVE           *\n");
	printf("\t\t*       -----------------------------           *\n");
	printf("\t\t*                                               *\n");
	printf("\t\t*                                               *\n");
	printf("\t\t*                                               *\n");
	printf("\t\t*    Brought To You By code-projects.org        *\n");
	printf("\t\t*                 ESP,XYZ                       *\n");
	printf("\t\t*   Made By: Shanza Arshid & Muzammil Asif      *\n");
	printf("\t\t*     CONTACT US:18-88888555533,035598852       *\n");
	printf("\t\t*************************************************\n\n\n");
		for(i=0;i<80;i++)
		printf("-");
	    printf("\nCurrent date and time : %s",ctime(&t));
	    for(i=0;i<80;i++)
		printf("-");
	printf(" \n Press any key to continue:");
	
	// getch();	
    menu();
    
    return 0;
}