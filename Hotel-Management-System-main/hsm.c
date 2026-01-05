#include <stdio.h>
#include <time.h>
// #include<stdlib.h>
#include <windows.h>
#define full_this_room 4
void setcolor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xB0) + (ForgC & 0x0B);
        //	SetConsoleTextAttributes(hStdOut,wColor);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
typedef struct Student
{
    int room_no;
    char name[50];
    char cnic;
    char phone_no[20];
    char adderess[225];
    char Email[50];
    char period[30];
    char arivalDate[20];
    char nationality[30];

} Student;
int countMember[5000] = {0};
void menu()
{
    int choice;
    do
    {

        printf("Enter 1. for book room \n");
        printf("Enter 2. for view detail \n");
        printf("Enter 3. for find \n");
        printf("Enter 4. for remove \n");
        printf("Enter 5. for edit \n");
        printf("Enter 6. for Exit! \n");
        time_t t;
        time(&t);
        printf("\nCurrent date and time : %s", ctime(&t));
        printf("Enter Choice here : ");
        scanf("%d", &choice);
    } while (!(choice != 6 || choice != 5 || choice != 4 || choice != 3 || choice != 2 || choice != 1));
}
void BookRoom(Student *s)
{
    FILE *f;
    f = fopen("noteBook.txt", "a");
    printf("Enter Room number : ");
    scanf("%d", &s->room_no);
    if (countMember[s->room_no] == 1)
    {
        do
        {
            printf("This Room is Already full Please check other Room\n");
            scanf("%d", &s->room_no);
        } while (countMember[s->room_no] == 1);
    }
    printf("Enter name : ");
    scanf("%s", &s->name);
    printf("Enter Aderess : ");
    scanf("%s", &s->adderess);
    printf("Enter Nationality : ");
    scanf("%s", &s->nationality);
    printf("Enter Email : ");
    scanf("%s", &s->Email);
    printf("Enter Period : ");
    scanf("%s", &s->period);
    printf("Enter arival Date : ");
    scanf("%s", &s->arivalDate);
    printf("Enter Phone Number : ");
    scanf("%s", &s->phone_no);
    printf("Enter Cnic : ");
    scanf("%s", &s->cnic);
    fprintf(f, "Name : %s Room Number : %d,Adress : %s Nationality : %s Email : %s Period : %s Arival Date : %s Phone No : %sCNIC : %s", s->room_no,s->name,s->adderess,s->nationality,s->Email,s->period,s->arivalDate,s->phone_no,s->cnic);
    // while(fprintf(f,"Name : %s Room Number : %d,Adress : %s Nationality : %s Email : %s Period : %s Arival Date : %s Phone No : %sCNIC : %s",s)!=EOF)
    // {

    // }
    printf("Sucessfully Booked the room Numeber %d\n", s->room_no);
}
void view(Student *s)
{
    printf("Name\tRoom Number\tAderess\tEmail\tNationality\tPhone Number \t Arival Date \tCnic \t Period\n");
    printf("%s\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n", s->name, s->room_no, s->adderess, s->Email, s->nationality, s->phone_no, s->arivalDate, s->cnic, s->period);
    printf("%s\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n", s->name, s->room_no, s->adderess, s->Email, s->nationality, s->phone_no, s->arivalDate, s->cnic, s->period);
}

int main(void)
{
    setcolor(6);
    // perror("I am color\n");
    // setcolor(1);
    // perror("I am color\n");
    // setcolor(2);
    // perror("I am color\n");
    // setcolor(4);
    // perror("I am color\n");
    // setcolor(7);
    // perror("I am color\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("~~~~~~~~~~~~~~~~~~~  H O S T E L _ M A N A G E M E N T _ S Y S T E M  ~~~~~~~~~~~~~~~~~~~\n");
    printf("-----------------------------------------------------------------------------------------\n");
    Student s1;

    menu();
    // BookRoom(&s1);
    // view(&s1);
    return 0;
}