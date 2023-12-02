#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <ctime>

using namespace std;

void League_Simulator();
void StartMenu();
void SingleP_MultiP(bool& Single_Multi);
void NamePlayers(string& P1, string& P2, bool Multiplayer);
void Choose_Characters(int& counter, string Player, int& Choice, bool Multiplayer);
void Overall_Shop(string P1, string P2, int P1_choice, int& P2_choice, bool Multiplayer, string P1_Items[], string P2_Items[], int array_size, int& counter);
void makeFightScene(int P1_choice, int P2_choice, string P1_Items[], string P2_Items[], int array_size, string fightarray[][160]);
bool Turn_Possible(int Health, int exp, bool& alive, int array_size, string Items[]);
void Take_Item_Input(string items[], int exp, string& item_used);
void Change_Exp_Health(string item_used, int& MainP_hp, int& MainP_exp, int& OtherP_hp, int& OtherP_exp, int exp_restored, int health_restored, int& thSword_dmg, int dagger_dmg, int& gun_dmg);
void Item_animation(string Player, string item_used, int thSword_dmg, int dagger_dmg, int gun_dmg);
void new_background(string fightarray[][160], int P1_hp, int P2_hp, int P1_exp, int P2_exp);
void Usable(string Items[], int choice, bool& valid, int exp);
void Alternate_Turns(string P1, string P2, string P1_Items[], string P2_Items[], int array_size, int& P1_hp, int& P1_exp, int& P2_hp, int& P2_exp, bool& P1_alive, bool& P2_alive, string fightarray[][160]);
void Overall_Fighting(string P1_items[], string P2_items[], int array_size, string player1, string player2, string fightarray[][160]);

int main()
{
    League_Simulator();
    return 0;
}

void League_Simulator()
{
    StartMenu();

    bool Single_Multi;  //true if multiplayer
    SingleP_MultiP(Single_Multi);

    if(Single_Multi == false)
    {
        return;
    }

    string Player1, Player2;
    NamePlayers(Player1, Player2, Single_Multi);

    int counter, P1_choice, P2_choice;
    counter = 1;
    Choose_Characters(counter, Player1, P1_choice, Single_Multi);

    const int array_size = 20;
    string Player1_Items[array_size], Player2_Items[array_size];
    Overall_Shop(Player1, Player2, P1_choice, P2_choice, Single_Multi, Player1_Items, Player2_Items, array_size, counter);

    string fightarray[9][160]={};
    makeFightScene(P1_choice,P2_choice,Player1_Items,Player2_Items,array_size,fightarray);

    Overall_Fighting(Player1_Items,Player2_Items,array_size,Player1,Player2,fightarray);

}

void StartMenu()                                            //Displays game name and tagline
{
    cout << "\t\t\t\t\t\t\t\t\t----------------\n\t\t\t\t\t\t\t\t\tLEAGUE SIMULATOR\n\t\t\t\t\t\t\t\t\t----------------" << endl;
    cout << "\t\t\t\t\t\t\t\t   Battle it out in the Arena!" << endl;
}

void SingleP_MultiP(bool& Single_Multi)                     //Determines if game will be single or multi player and stores decision in a variable
{
    cout << "\nWill you be playing with another player? Yes(Y)  No(N)" << endl;
    char yes_no;
    cin >> yes_no;

    if (yes_no == 'Y')
    {
        Single_Multi = true;
    }
    else
    {
        Single_Multi = false;
    }
}

void NamePlayers(string& P1,string& P2, bool Multiplayer)   //Names Players
{
    system("cls");
    if (Multiplayer)
    {
        cout << "Player 1 please enter your name: ";
        cin >> P1;
        cout << "Player 2 please enter your name: ";
        cin >> P2;
    }
}

void Display_Characters()                                  //Displays different charachter choices
{
    cout <<                                 "\t\t\t\t" << "___/^\\___"<< endl;
    cout << " _______ " << '\t' << " _______ " << '\t' << "|_______|" << '\t' << "/\\/\\_/\\/\\" << endl;
    cout << "| ^ _ ^ |" << '\t' << "| O . O |" << '\t' << "| U _ O |" << '\t' << "| 0 - 0 |" << endl;
    cout << "|_______|" << '\t' << "|_______|" << '\t' << "|_______|" << '\t' << "|_______|" << endl;
    cout << "    |    " << '\t' << " |  -  | " << '\t' << "    |    " << '\t' << " | \\_/ | " << endl;
    cout << "----|----" << '\t' << "-|  -  |-" << '\t' << "(|--|----" << '\t' << "=|  |  |=" << endl;
    cout << "    |    " << '\t' << " |__-__| " << '\t' << "   _|_   " << '\t' << " |__|__|" << endl;
    cout << "   / \\  " << '\t' << "  |   |  " << '\t' << "   | |   " << '\t' << " _|| ||_ " << endl;
    cout << "  /   \\ " << '\t' << "(=|   |=)" << '\t' << "  /   \\ " << '\t' << "(__| |__)" << endl;
    cout << endl;
}

void Customized_Choice(string P, int& Choice)               //Allows players to choose a charachter
{
    system("cls");
    cout << P << ", please choose your character\n\n1.\t\t2.\t\t3.\t\t4.\n";
    Display_Characters();
    cin >> Choice;
}

void Choose_Characters(int& counter, string Player, int& Choice, bool Multiplayer)
{
    if(counter == 1)
    {
        Customized_Choice(Player, Choice);
        counter = counter + 1;
        return;
    }
    else
    {
       if(Multiplayer)
       {
           Customized_Choice(Player, Choice);
           counter = 1;
       }
    }
}

void Table1()
{
    cout << "\t\t" << " _______ " << "\t\t" << "| No. |         SHOP         | Gold |" << "\t" << "|                 STATS                 | Exp |\n";
    cout << "\t\t" << "| ^ _ ^ |" << "\t\t" << "|-----|----------------------|------|" << "\t" << "|---------------------------------------|-----|\n";
    cout << "\t\t" << "|_______|" << "\t\t" << "|  1  |  EXP Cookie          |  150 |" << "\t" << "|            Restores 30 Exp            |  0  |\n";
    cout << "\t\t" << "    |    " << "\t\t" << "|  2  |  Healing Jamishiri   |  200 |" << "\t" << "|            Restores 20 HP             |  0  |\n";
    cout << "\t\t" << "----|----" << "\t\t" << "|  3  |  TH Sword            |  600 |" << "\t" << "| 30 dmg(15% chance to crit for 60 dmg) | 45  |\n";
    cout << "\t\t" << "    |    " << "\t\t" << "|  4  |  Dagger              |  250 |" << "\t" << "|                20 dmg                 | 25  |\n";
    cout << "\t\t" << "   / \\  " << "\t\t" << "|  5  |  Gun(China maal)     |  500 |" << "\t" << "| 20 dmg(5%  chance to crit for 70 dmg) | 40  |\n";
    cout << "\t\t" << "  /   \\ " << "\t\t" << "|  6  |  Shield              |  100 |" << "\t" << "|            +10 Max Health             |  0  |\n";
}

void Table2()
{
    cout << "\t\t" << " _______ " << "\t\t" << "| No. |         SHOP         | Gold |" << "\t" << "|                 STATS                 | Exp |\n";
    cout << "\t\t" << "| O . O |" << "\t\t" << "|-----|----------------------|------|" << "\t" << "|---------------------------------------|-----|\n";
    cout << "\t\t" << "|_______|" << "\t\t" << "|  1  |  EXP Cookie          |  150 |" << "\t" << "|            Restores 30 Exp            |  0  |\n";
    cout << "\t\t" << " |  -  | " << "\t\t" << "|  2  |  Healing Jamishiri   |  200 |" << "\t" << "|            Restores 20 HP             |  0  |\n";
    cout << "\t\t" << "-|  -  |-" << "\t\t" << "|  3  |  TH Sword            |  600 |" << "\t" << "| 30 dmg(15% chance to crit for 60 dmg) | 45  |\n";
    cout << "\t\t" << " |__-__| " << "\t\t" << "|  4  |  Dagger              |  250 |" << "\t" << "|                20 dmg                 | 25  |\n";
    cout << "\t\t" << "  |   |  " << "\t\t" << "|  5  |  Gun(China maal)     |  500 |" << "\t" << "| 20 dmg(5%  chance to crit for 70 dmg) | 40  |\n";
    cout << "\t\t" << "(=|   |=)" << "\t\t" << "|  6  |  Shield              |  100 |" << "\t" << "|            +10 Max Health             |  0  |\n";
}

void Table3()
{
    cout << "\t\t" << "___/^\\___"<<endl;
    cout << "\t\t" << "|_______|" << "\t\t" << "| No. |         SHOP         | Gold |" << "\t" << "|                 STATS                 | Exp |\n";
    cout << "\t\t" << "| U _ O |" << "\t\t" << "|-----|----------------------|------|" << "\t" << "|---------------------------------------|-----|\n";
    cout << "\t\t" << "|_______|" << "\t\t" << "|  1  |  EXP Cookie          |  150 |" << "\t" << "|            Restores 30 Exp            |  0  |\n";
    cout << "\t\t" << "    |    " << "\t\t" << "|  2  |  Healing Jamishiri   |  200 |" << "\t" << "|            Restores 20 HP             |  0  |\n";
    cout << "\t\t" << "(|--|----" << "\t\t" << "|  3  |  TH Sword            |  600 |" << "\t" << "| 30 dmg(15% chance to crit for 60 dmg) | 45  |\n";
    cout << "\t\t" << "   _|_   " << "\t\t" << "|  4  |  Dagger              |  250 |" << "\t" << "|                20 dmg                 | 25  |\n";
    cout << "\t\t" << "   | |   " << "\t\t" << "|  5  |  Gun(China maal)     |  500 |" << "\t" << "| 20 dmg(5%  chance to crit for 70 dmg) | 40  |\n";
    cout << "\t\t" << "  /   \\ " << "\t\t" << "|  6  |  Shield              |  100 |" << "\t" << "|            +10 Max Health             |  0  |\n";
}

void Table4()
{
    cout << "\t\t" << "/\\/\\_/\\/\\" << "\t\t" << "| No. |         SHOP         | Gold |" << "\t" << "|                 STATS                 | Exp |\n";
    cout << "\t\t" << "| 0 - 0 |"     << "\t\t" << "|-----|----------------------|------|" << "\t" << "|---------------------------------------|-----|\n";
    cout << "\t\t" << "|_______|"     << "\t\t" << "|  1  |  EXP Cookie          |  150 |" << "\t" << "|            Restores 30 Exp            |  0  |\n";
    cout << "\t\t" << " | \\_/ | "    << "\t\t" << "|  2  |  Healing Jamishiri   |  200 |" << "\t" << "|            Restores 20 HP             |  0  |\n";
    cout << "\t\t" << "=|  |  |="     << "\t\t" << "|  3  |  TH Sword            |  600 |" << "\t" << "| 30 dmg(15% chance to crit for 60 dmg) | 45  |\n";
    cout << "\t\t" << " |__|__|"      << "\t\t" << "|  4  |  Dagger              |  250 |" << "\t" << "|                20 dmg                 | 25  |\n";
    cout << "\t\t" << " _|| ||_ "     << "\t\t" << "|  5  |  Gun(China maal)     |  500 |" << "\t" << "| 20 dmg(5%  chance to crit for 70 dmg) | 40  |\n";
    cout << "\t\t" << "(__| |__)"     << "\t\t" << "|  6  |  Shield              |  100 |" << "\t" << "|            +10 Max Health             |  0  |\n";
}

void Table_Display(int choice)
{
    switch(choice)
    {
    case 1:
        Table1();
        break;
    case 2:
        Table2();
        break;
    case 3:
        Table3();
        break;
    case 4:
        Table4();
        break;
    }
}

void Shop(string Player, int choice)
{
   cout << Player << ", get ready for battle! Choose your items wisely\n\n";
   Table_Display(choice);
   cout << "\n\n";
}

void Item_Buyer(string Player_Items[], int array_size, string Player, int P_choice)
{
    string Shop_Items[6][2] = {
        {"EXP Cookie","150"       },
        {"Healing Jamishiri","200"},
        {"TH Sword","600"         },
        {"Dagger","250"           },
        {"Gun","500"              },
        {"Shield","100"           },
        };

    for(int i = 0; i < array_size; i++)
    {
        Player_Items[i] = "";
    }

    int gold = 1000;
    cout<<"You have " << gold << " gold." << endl;

    char yes_no;
    int min_gold = stoi(Shop_Items[5][1]);
    int counter = 0;

    while(gold >= min_gold)
    {
        if(counter == 0)
        {
            cout << "\nDo you wish to buy an item? Yes(Y) No(N)\n";
            cin >> yes_no;
        }
        else
        {
            cout << gold << " gold left.\n";
            cout << "\nDo you wish to buy another item? Yes(Y) No(N)\n";
            cin >> yes_no;
        }

        if(yes_no == 'N' || yes_no == 'n')
            break;

        cout << "Please enter the item no.\n";
        int choice;
        cin >> choice;

        if(gold >= stoi(Shop_Items[choice - 1][1]))
        {
            bool bought = false;
            for(int i = 0; i < array_size; i++)
            {
                if(counter == 0)
                {
                    break;
                }
                if(Shop_Items[choice - 1][0] == Player_Items[i])
                {
                    bought = true;
                }
            }
            if((!(choice < 3)) && bought == true)
            {
                cout << Shop_Items[choice - 1][0] << " can only be bought once.\nPlease try again.\n\n";
                system("pause");
                system("cls");
                Shop(Player, P_choice);
                continue;
            }
            Player_Items[counter] = Shop_Items[choice - 1][0];
            cout << Player_Items[counter] << " bought.\n\n";
            gold = gold -(stoi(Shop_Items[choice - 1][1]));
            counter = counter+1;
        }
        else
        {
            cout << "Insufficient gold. Please try again.\n\n";
        }
        system("pause");
        system("cls");
        Shop(Player, P_choice);
    }

    if(gold < min_gold)
        cout << "\nYou have " << gold << " gold left and cannot buy any more items.\n\n";
    else
    {
        system("pause");
        system("cls");
        Shop(Player, P_choice);
        cout << "\nYou have " << gold << " gold left and decided not to buy any more items.\n\n";
    }
}

void Output_Items(string Player, string Player_Items[], int array_size)
{
    cout << Player << ", your backpack includes:\n";

    string Items_copy[array_size];

    for(int i = 0; i < array_size; i++)
    {
        Items_copy[i] = Player_Items[i];
    }

    for(int i = 0; i < array_size; i++)
    {
        if(Items_copy[i] == "")
        {
            continue;
        }

        int counter=1;

        for(int j = i + 1; j < array_size; j++)
        {
            if(Items_copy[i] == Items_copy[j])
            {
                counter = counter+1;
                Items_copy[j] = "";
            }
        }

        if(i==0)
        {
            cout << counter << "x " << Items_copy[i];
        }
        else
        {
            cout << ", " << counter << "x " << Items_copy[i];
        }
    }
    cout << "\n\nGood luck in battle warrior!\n";
}

void Overall_Shop(string P1, string P2, int P1_choice, int& P2_choice, bool Multiplayer, string P1_Items[], string P2_Items[], int array_size, int& counter)
{
    system("cls");
    Shop(P1, P1_choice);
    Item_Buyer(P1_Items, array_size, P1, P1_choice);
    Output_Items(P1, P1_Items, array_size);
    system("pause");

    if(Multiplayer)
    {
        system("cls");
        Choose_Characters(counter, P2, P2_choice, Multiplayer);
        system("cls");
        Shop(P2, P2_choice);
        Item_Buyer(P2_Items, array_size, P2, P2_choice);
        Output_Items(P2, P2_Items, array_size);
        system("pause");
    }

    system("cls");
}

void clearScreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void printPreSpaces(int counter)    //printing the left spaces and part of cloud
{
    for(int prespaces = 20 - counter; prespaces >= 1; prespaces--)
    {
        switch (counter)
        {
        case 1:
            if (prespaces == 19)
            {
                cout << "_";
            }
            else if (prespaces == 9)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
            break;
        case 2:
            if (prespaces == 16)
            {
                cout << "_";
            }
            else if (prespaces == 17)
            {
                cout << ")";
            }
            else
            {
                cout << " ";
            }
            break;
        case 3:
            if (prespaces <= 13 && prespaces >= 12)
            {
                cout << "_";
            }
            else if (prespaces == 14)
            {
                cout << ")";
            }
            else if (prespaces == 9)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
            break;
        case 4:
            if (prespaces <= 16 && prespaces >= 11)
            {
                cout << "_";
            }
            else if (prespaces == 10)
            {
                cout << ")";
            }
            else
            {
                cout << " ";
            }
            break;
        case 5:
            if (prespaces == 11)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
            break;
        case 7:
            if (prespaces == 4)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
            break;
        default:
            cout << " ";
            break;
        }
    }
}

void printMidSpaces(int counter)    //printing the spaces between the mountains
{
    if (counter == 5)
    {
        cout << "\\/\\/\\/\\/";
    }
    else
    {
        for(int midspaces = 0; midspaces < 2 * (counter - 1); midspaces++)
        {
            cout << " ";
        }
    }
}

void printPostSpaces(int counter)   //printing the right spaces and part of cloud
{
    for(int postspaces = 20 - counter; postspaces >= 1; postspaces--)
    {
        switch (counter)
        {
        case 1:
            if (postspaces == 15)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
            break;
        case 2:
            if (postspaces == 2)
            {
                cout << "_";
            }
            else if (postspaces == 1)
            {
                cout << "(";
            }
            else if (postspaces == 7)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
            break;
        case 3:
            if (postspaces <= 5 && postspaces >= 4)
            {
                cout << "_";
            }
            else if (postspaces == 3)
            {
                cout << "(";
            }
            else if (postspaces == 11)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
            break;
        case 4:
            if (postspaces <= 5 && postspaces >= 1)
            {
                cout << "_";
            }
            else if (postspaces == 6)
            {
                cout << "(";
            }
            else
            {
                cout << " ";
            }
            break;
        case 6:
            if (postspaces == 5 || postspaces == 11)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
            break;
        default:
            cout << " ";
            break;
        }
    }
}

void makeMountain(int counter)      //making one complete mountain
{
    printPreSpaces(counter);
    cout << "/";
    printMidSpaces(counter);
    cout << "\\";
    printPostSpaces(counter);
}

void backgroundPrint()              //repeating for 4 mountains and road
{
    for(int counter = 1; counter <= 20; counter++)
    {
        for (int counter2 = 1; counter2 <= 4; counter2++)
        {
            makeMountain(counter);
        }
        cout << endl;
    }
}

void printRoad()
{
    for(int counter = 1; counter <= 160; counter++)
    {
        cout << "_";
    }
    cout << endl;
}

void printArray(string fightarray[9][160])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 160; col++)
        {
            cout << fightarray[row][col];
        }
        cout << endl;
    }
}

void initializeArray(string fightarray[9][160], int player1, int player2)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 160; col++)
        {
            fightarray[row][col] = " ";
        }
    }
    switch (player1)
    {
    case 1:
        //Making character 1:
        fightarray[1][3] = "_";
        fightarray[1][4] = "_";
        fightarray[1][5] = "_";
        fightarray[2][2] = "|";
        fightarray[2][3] = "^";
        fightarray[2][4] = "_";
        fightarray[2][5] = "^";
        fightarray[2][6] = "|";
        fightarray[3][2] = "|";
        fightarray[3][3] = "_";
        fightarray[3][4] = "_";
        fightarray[3][5] = "_";
        fightarray[3][6] = "|";
        fightarray[4][4] = "|";
        fightarray[5][1] = "-";
        fightarray[5][2] = "-";
        fightarray[5][3] = "-";
        fightarray[5][4] = "|";
        fightarray[5][5] = "-";
        fightarray[5][6] = "-";
        fightarray[5][7] = "-";
        fightarray[6][4] = "|";
        fightarray[7][3] = "/";
        fightarray[7][5] = "\\";
        fightarray[8][2] = "/";
        fightarray[8][6] = "\\";
        break;
    case 2:
        //Making character 2:
        fightarray[1][3] = "_";
        fightarray[1][4] = "_";
        fightarray[1][5] = "_";
        fightarray[2][2] = "|";
        fightarray[2][3] = "O";
        fightarray[2][4] = ".";
        fightarray[2][5] = "O";
        fightarray[2][6] = "|";
        fightarray[3][2] = "|";
        fightarray[3][3] = "_";
        fightarray[3][4] = "_";
        fightarray[3][5] = "_";
        fightarray[3][6] = "|";
        fightarray[4][3] = "|";
        fightarray[4][4] = "-";
        fightarray[4][5] = "|";
        fightarray[5][1] = "-";
        fightarray[5][2] = "-";
        fightarray[5][3] = "|";
        fightarray[5][4] = "-";
        fightarray[5][5] = "|";
        fightarray[5][6] = "-";
        fightarray[5][7] = "-";
        fightarray[6][3] = "|";
        fightarray[6][4] = "_";
        fightarray[6][5] = "|";
        fightarray[7][3] = "|";
        fightarray[7][5] = "|";
        fightarray[8][1] = "(";
        fightarray[8][2] = "=";
        fightarray[8][3] = "|";
        fightarray[8][4] = "|";
        fightarray[8][5] = "=";
        fightarray[8][6] = ")";
        break;
    case 3:
        //making character 3:
        fightarray[0][2] = "_";
        fightarray[0][3] = "/";
        fightarray[0][4] = "^";
        fightarray[0][5] = "\\";
        fightarray[0][6] = "_";
        fightarray[1][2] = "|";
        fightarray[1][3] = "_";
        fightarray[1][4] = "_";
        fightarray[1][5] = "_";
        fightarray[1][6] = "|";
        fightarray[2][2] = "|";
        fightarray[2][3] = "U";
        fightarray[2][4] = "_";
        fightarray[2][5] = "O";
        fightarray[2][6] = "|";
        fightarray[3][2] = "|";
        fightarray[3][3] = "_";
        fightarray[3][4] = "_";
        fightarray[3][5] = "_";
        fightarray[3][6] = "|";
        fightarray[4][4] = "|";
        fightarray[5][1] = "(";
        fightarray[5][2] = "-";
        fightarray[5][3] = "-";
        fightarray[5][4] = "|";
        fightarray[5][5] = "-";
        fightarray[5][6] = "-";
        fightarray[5][7] = "-";
        fightarray[6][3] = "_";
        fightarray[6][4] = "|";
        fightarray[6][5] = "_";
        fightarray[7][3] = "|";
        fightarray[7][5] = "|";
        fightarray[8][2] = "/";
        fightarray[8][6] = "\\";
        break;
    case 4:
        //making character 4:
        fightarray[1][2] = "/";
        fightarray[1][3] = "\\";
        fightarray[1][4] = "_";
        fightarray[1][5] = "/";
        fightarray[1][6] = "\\";
        fightarray[2][2] = "|";
        fightarray[2][3] = "0";
        fightarray[2][4] = "-";
        fightarray[2][5] = "0";
        fightarray[2][6] = "|";
        fightarray[3][2] = "|";
        fightarray[3][3] = "_";
        fightarray[3][4] = "_";
        fightarray[3][5] = "_";
        fightarray[3][6] = "|";
        fightarray[4][3] = "|";
        fightarray[4][4] = "V";
        fightarray[4][5] = "|";
        fightarray[5][1] = "=";
        fightarray[5][2] = "=";
        fightarray[5][3] = "|";
        fightarray[5][4] = "|";
        fightarray[5][5] = "|";
        fightarray[5][6] = "=";
        fightarray[5][7] = "=";
        fightarray[6][3] = "|";
        fightarray[6][4] = "_";
        fightarray[6][5] = "|";
        fightarray[7][2] = "_";
        fightarray[7][3] = "|";
        fightarray[7][5] = "|";
        fightarray[7][6] = "_";
        fightarray[8][1] = "(";
        fightarray[8][2] = "_";
        fightarray[8][3] = "|";
        fightarray[8][5] = "|";
        fightarray[8][6] = "_";
        fightarray[8][7] = ")";
        break;
    default:
        break;
    }

    switch (player2)
    {
    case 1:
        //Making character 1:
        fightarray[1][156] = "_";
        fightarray[1][155] = "_";
        fightarray[1][154] = "_";
        fightarray[2][157] = "|";
        fightarray[2][156] = "^";
        fightarray[2][155] = "_";
        fightarray[2][154] = "^";
        fightarray[2][153] = "|";
        fightarray[3][157] = "|";
        fightarray[3][156] = "_";
        fightarray[3][155] = "_";
        fightarray[3][154] = "_";
        fightarray[3][153] = "|";
        fightarray[4][155] = "|";
        fightarray[5][158] = "-";
        fightarray[5][157] = "-";
        fightarray[5][156] = "-";
        fightarray[5][155] = "|";
        fightarray[5][154] = "-";
        fightarray[5][153] = "-";
        fightarray[5][152] = "-";
        fightarray[6][155] = "|";
        fightarray[7][156] = "\\";
        fightarray[7][154] = "/";
        fightarray[8][157] = "\\";
        fightarray[8][153] = "/";
        break;
    case 2:
        //Making character 2:
        fightarray[1][156] = "_";
        fightarray[1][155] = "_";
        fightarray[1][154] = "_";
        fightarray[2][157] = "|";
        fightarray[2][156] = "O";
        fightarray[2][155] = ".";
        fightarray[2][154] = "O";
        fightarray[2][153] = "|";
        fightarray[3][157] = "|";
        fightarray[3][156] = "_";
        fightarray[3][155] = "_";
        fightarray[3][154] = "_";
        fightarray[3][153] = "|";
        fightarray[4][156] = "|";
        fightarray[4][155] = "-";
        fightarray[4][154] = "|";
        fightarray[5][158] = "-";
        fightarray[5][157] = "-";
        fightarray[5][156] = "|";
        fightarray[5][155] = "-";
        fightarray[5][154] = "|";
        fightarray[5][153] = "-";
        fightarray[5][152] = "-";
        fightarray[6][156] = "|";
        fightarray[6][155] = "_";
        fightarray[6][154] = "|";
        fightarray[7][156] = "|";
        fightarray[7][154] = "|";
        fightarray[8][158] = ")";
        fightarray[8][157] = "=";
        fightarray[8][156] = "|";
        fightarray[8][154] = "|";
        fightarray[8][153] = "=";
        fightarray[8][152] = "(";
        break;
    case 3:
        //making character 3:
        fightarray[0][157] = "_";
        fightarray[0][156] = "\\";
        fightarray[0][155] = "^";
        fightarray[0][154] = "/";
        fightarray[0][153] = "_";
        fightarray[1][157] = "|";
        fightarray[1][156] = "_";
        fightarray[1][155] = "_";
        fightarray[1][154] = "_";
        fightarray[1][153] = "|";
        fightarray[2][157] = "|";
        fightarray[2][156] = "O";
        fightarray[2][155] = "_";
        fightarray[2][154] = "U";
        fightarray[2][153] = "|";
        fightarray[3][157] = "|";
        fightarray[3][156] = "_";
        fightarray[3][155] = "_";
        fightarray[3][154] = "_";
        fightarray[3][153] = "|";
        fightarray[4][155] = "|";
        fightarray[5][158] = "-";
        fightarray[5][157] = "-";
        fightarray[5][156] = "-";
        fightarray[5][155] = "|";
        fightarray[5][154] = "-";
        fightarray[5][153] = "-";
        fightarray[5][152] = "(";
        fightarray[6][156] = "_";
        fightarray[6][155] = "|";
        fightarray[6][154] = "_";
        fightarray[7][156] = "|";
        fightarray[7][154] = "|";
        fightarray[8][157] = "\\";
        fightarray[8][153] = "/";
        break;
    case 4:
        //making character 4:
        fightarray[1][157] = "\\";
        fightarray[1][156] = "/";
        fightarray[1][155] = "_";
        fightarray[1][154] = "\\";
        fightarray[1][153] = "/";
        fightarray[2][157] = "|";
        fightarray[2][156] = "0";
        fightarray[2][155] = "-";
        fightarray[2][154] = "0";
        fightarray[2][153] = "|";
        fightarray[3][157] = "|";
        fightarray[3][156] = "_";
        fightarray[3][155] = "_";
        fightarray[3][154] = "_";
        fightarray[3][153] = "|";
        fightarray[4][156] = "|";
        fightarray[4][155] = "V";
        fightarray[4][154] = "|";
        fightarray[5][158] = "=";
        fightarray[5][157] = "=";
        fightarray[5][156] = "|";
        fightarray[5][155] = "|";
        fightarray[5][154] = "|";
        fightarray[5][153] = "=";
        fightarray[5][152] = "=";
        fightarray[6][156] = "|";
        fightarray[6][155] = "_";
        fightarray[6][154] = "|";
        fightarray[7][157] = "_";
        fightarray[7][156] = "|";
        fightarray[7][154] = "|";
        fightarray[7][153] = "_";
        fightarray[8][158] = ")";
        fightarray[8][157] = "_";
        fightarray[8][156] = "|";
        fightarray[8][154] = "|";
        fightarray[8][153] = "_";
        fightarray[8][152] = "(";
        break;
    default:
        break;
    }
}

void moveArray(string fightarray[9][160])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 79; col > 0; col--)
        {
            fightarray[row][col] = fightarray[row][col - 1];
        }
    }
    for (int row = 0; row < 9; row++)
    {
        for (int col = 81; col < 159; col++)
        {
            fightarray[row][col] = fightarray[row][col + 1];
        }
    }
}

void healthBar(bool shield1, bool shield2,int counter,int P1_hp,int P2_hp)
{
    if(counter==1)
    {
        cout << "Health";
        for (int i = 1; i <= 148; i++)
        {
            cout << " ";
        }
        cout << "Health" << endl;
        //making the dashes
        cout << " ";
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        if(shield1)
        {
            for (int i = 1; i <= 120; i++)
            {
                cout << " ";
            }
        }
        else
        {
            for (int i = 1; i <= 118; i++)
            {
                cout << " ";
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        cout << " " << endl;
        //making the bars
        if(shield1)
        {
            cout << "[";
            for (int i = 1; i <= 22; i++)
            {
                cout << "|";
            }
            cout << "]";
        }
        else
        {
            cout << "[";
            for (int i = 1; i <= 20; i++)
            {
                cout << "|";
            }
            cout << "]";
        }
        for (int i = 1; i <= 116; i++)
        {
            cout << " ";
        }

        if(shield2)
        {
            cout << "[";
            for (int i = 1; i <= 22; i++)
            {
                cout << "|";
            }
            cout << "]" << endl;
        }
        else
        {
            cout << "[";
            for (int i = 1; i <= 20; i++)
            {
                cout << "|";
            }
            cout << "]" << endl;
        }
        //making the dashes
        cout << " ";
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        if(shield1)
        {
            for (int i = 1; i <= 120; i++)
            {
                cout << " ";
            }
        }
        else
        {
            for (int i = 1; i <= 118; i++)
            {
                cout << " ";
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else //counter==2
    {
        cout << "Health";
        for (int i = 1; i <= 148; i++)
        {
            cout << " ";
        }
        cout << "Health" << endl;
        //making the dashes
        cout << " ";
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        for (int i = 1; i <=118; i++)
        {
            cout << " ";
        }
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        cout << " " << endl;
        //making the bars
        cout << "[";
        for (int i = 1; i <=(P1_hp/5); i++)
        {
            cout << "|";
        }
        for (int i = 1; i<=(20-(P1_hp/5)); i++)
        {
            cout << " ";
        }
        cout << "]";
        for (int i = 1; i <= 116; i++)
        {
            cout << " ";
        }
        cout << "[";
        for (int i = 1; i <= (P2_hp/5); i++)
        {
            cout << "|";
        }
        for (int i= 1; i<=(20-(P2_hp/5)); i++)
        {
            cout << " ";
        }
        cout << "]" << endl;
        //making the dashes
        cout << " ";
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        for (int i = 1; i <= 118; i++)
        {
            cout << " ";
        }
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
}

void xpBar(bool shield1,bool shield2,int counter,int P1_exp,int P2_exp)
{
    if(counter==1)
    {
        cout << "XP";
        for (int i = 1; i <= 156; i++)
        {
            cout << " ";
        }
        cout << "XP" << endl;
        //making the dashes
        cout << " ";
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        if(shield1)
        {
            for (int i = 1; i <= 120; i++)
            {
                cout << " ";
            }
        }
        else
        {
            for (int i = 1; i <= 118; i++)
            {
                cout << " ";
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        cout << " " << endl;
        //making the bars
        cout << "[";
        for (int i = 1; i <= 20; i++)
        {
            cout << "|";
        }
        cout << "]";
        if(shield1)
        {
            for (int i = 1; i <= 118; i++)
            {
                cout << " ";
            }
        }
        else
        {
            for (int i = 1; i <= 116; i++)
            {
                cout << " ";
            }
        }
        cout << "[";
        for (int i = 1; i <= 20; i++)
        {
            cout << "|";
        }
        cout << "]" << endl;
        //making the dashes
        cout << " ";
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        if(shield1)
        {
            for (int i = 1; i <= 120; i++)
            {
            cout << " ";
            }
        }
        else
        {
            for (int i = 1; i <= 118; i++)
            {
                cout << " ";
            }
        }
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
    else //if counter==2
    {
        cout << "XP";
        for (int i = 1; i <= 156; i++)
        {
            cout << " ";
        }
        cout << "XP" << endl;
        //making the dashes
        cout << " ";
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        for (int i = 1; i <= 118; i++)
        {
            cout << " ";
        }
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        cout << " " << endl;
        //making the bars
        cout << "[";
        for (int i = 1; i <= (P1_exp/5); i++)
        {
            cout << "|";
        }
        for (int i = 1; i <= (20-(P1_exp/5)); i++)
        {
            cout << " ";
        }
        cout << "]";
        for (int i = 1; i <= 116; i++)
        {
            cout << " ";
        }
        cout << "[";
        for (int i = 1; i <= (P2_exp/5); i++)
        {
            cout << "|";
        }
        for (int i = 1; i <= (20-(P2_exp/5)); i++)
        {
            cout << " ";
        }
        cout << "]" << endl;
        //making the dashes
        cout << " ";
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        for (int i = 1; i <= 118; i++)
        {
            cout << " ";
        }
        for (int i = 1; i <= 20; i++)
        {
            cout << "-";
        }
        cout << " ";
    }
}

void makeFightScene(int P1_choice,int P2_choice,string P1_Items[],string P2_Items[],int array_size,string fightarray[][160])
{

    initializeArray(fightarray, P1_choice, P2_choice);
    backgroundPrint();
    printRoad();
    printArray(fightarray);
    printRoad();
    for (int counter = 1; counter < 72; counter++)
    {
        clearScreen();
        moveArray(fightarray);
        backgroundPrint();
        printRoad();
        printArray(fightarray);
        printRoad();
    }


    bool shield1,shield2;
    shield1=false;
    shield2=false;
    for (int i=0;i<array_size;i++)
    {
        if(P1_Items[i]=="Shield")
            shield1=true;
        if(P2_Items[i]=="Shield")
            shield2=true;
    }

    healthBar(shield1,shield2,1,0,0);
    cout << endl;
    xpBar(shield1,shield2,1,0,0);
}
void outputFight()
{
    system("cls");
    for (int counter = 1; counter <= 20; counter++)
    {
        cout << endl;
    }
    for (int counter = 1; counter <= 76; counter++)
    {
        cout << " ";
    }
    cout << "FIGHT!!!";
}
void outputPlayer(string player_name, string items[], int no_of_items,int counter1)
{
    system("cls");

    if (counter1==1)
    {
        cout << player_name << " goes first.\n" << endl;
    }
    else
    {
        cout << player_name << "'s turn to fight.\n" << endl;
    }

    cout<<"You have...\n\n";

    for (int counter = 0; counter < no_of_items; counter++)
    {
        if (items[counter] != "")
        {
            cout << counter+1 << ". " << items[counter] << "\t";
        }
    }
}

void ItemFight(string P1_items[],string P2_items[],int array_size,string player1,string player2,string fightarray[][160])
{
    struct Player
    {
        string P_Items[20];
        int health;
        int exp;
        bool alive;
    };

    Player P1;
    Player P2;

    P1.P_Items[20];
    P1.health=100;
    P1.exp=100;
    P1.alive=true;

    P2.P_Items[20];
    P2.health=100;
    P2.exp=100;
    P2.alive=true;

    for(int i=0;i<20;i++)
    {
        P1.P_Items[i]=P1_items[i];
        P2.P_Items[i]=P2_items[i];
    }

    for(int i=0;i<20;i++)
    {
        if(P1.P_Items[i]=="Shield")
            P1.health=110;
        if(P2.P_Items[i]=="Shield")
            P2.health=110;
    }

    Alternate_Turns(player1,player2,P1.P_Items,P2.P_Items,array_size,P1.health,P1.exp,P2.health,P2.exp,P1.alive,P2.alive,fightarray);

    system("pause");
    system("cls");
    new_background(fightarray,P1.health,P2.health,P1.exp,P2.exp);
    system("cls");
    cout<<"Aftermath.....\n\n";

    if(P1.alive && (!(P2.alive)))
        cout<<player1<<" was victorious! "<<player2<<" died in battle.\n";
    else if(P2.alive && (!(P1.alive)))
        cout<<player2<<" was victorious! "<<player1<<" died in battle.\n";
    else if(P1.health>P2.health)
         cout<<player1<<" was victorious! They held their ground till the end!\n";
    else if(P2.health>P1.health)
         cout<<player2<<" was victorious! They held their ground till the end!\n";
    else
        cout<<"The duel ended in a tie.\n";
}

void One_Turn(string Items[],int array_size,bool& breaker,int& MainP_hp,int& MainP_exp,int& OtherP_hp,int& OtherP_exp,bool& alive,string MainP,string OtherP,string fightarray[][160])
{
    if (!(Turn_Possible(MainP_hp,MainP_exp,alive,array_size,Items)))
    {
        breaker=true;
        return;
    }

    string item_used;
    Take_Item_Input(Items,MainP_exp,item_used);

    int exp_restored=30;
    int health_restored=20;
    int thSword_dmg;
    int dagger_dmg=20;
    int gun_dmg;

    Change_Exp_Health(item_used,MainP_hp,MainP_exp,OtherP_hp,OtherP_exp,exp_restored,health_restored,thSword_dmg,dagger_dmg,gun_dmg);
    Item_animation(MainP,item_used,thSword_dmg,dagger_dmg,gun_dmg);

    cout<<endl;
    system("pause");
}

bool Turn_Possible(int Health,int exp,bool& alive,int array_size,string Items[])
{
    if(Health<=0)
    {
        alive=false;
        return false;
    }

    bool potions=false;
    for(int i=0;i<array_size;i++)
    {
        if((Items[i]=="EXP Cookie") || (Items[i]=="Healing Jamishiri"))
            potions=true;
    }

    if(exp<25 && (!potions))
    {
        return false;
    }
    else if(exp<40 && (!potions))
    {
        return false;
    }
    else if (exp<45 && (!potions))
    {
        return false;
    }

    return true;
}

void Take_Item_Input(string items[],int exp,string& item_used)
{
    int choice;
    cout<<"\nChoose an item: ";
    cin>>choice;

    bool valid=false;
    Usable(items,choice,valid,exp);

    if(valid==true)
    {
        item_used=items[choice-1];
    }
    else
    {
        while(valid==false)
        {
            cout<<"\nChoose an item: ";
            cin>>choice;
            Usable(items,choice,valid,exp);
        }
        item_used=items[choice-1];
    }

    if((item_used=="EXP Cookie") || (item_used=="Healing Jamishiri"))
    {
        items[choice-1]="";
    }
}

void Usable(string Items[],int choice,bool& valid,int exp)
{
    if(Items[choice-1]=="")
    {
        cout<<"\nThere is no item in that slot\nPlease try again\n\n";
        return;
    }

    if(Items[choice-1]=="Shield")
    {
        cout<<"You cannot use a shield to attack silly\nPlease try again\n\n";
        return;
    }

    int exp_i;
    if(Items[choice-1]=="TH Sword")
        exp_i=45;
    else if(Items[choice-1]=="Dagger")
        exp_i=25;
    else if(Items[choice-1]=="Gun")
        exp_i=40;
    else
        exp_i=0;

    if(exp<exp_i)
    {
        cout<<"\nInsufficient EXP.\nPlease try again.\n\n";
        return;
    }

    valid=true;
}

void Change_Exp_Health(string item_used,int& MainP_hp,int& MainP_exp,int& OtherP_hp,int& OtherP_exp,int exp_restored,int health_restored,int& thSword_dmg,int dagger_dmg,int& gun_dmg)
{
    srand(time(0));
    int x;
    x=rand()%100 + 1;

    if(x<=15)
        {thSword_dmg=60;}
    else
        {thSword_dmg=30;}

    if(x<=5)
        {gun_dmg=70;}
    else
        {gun_dmg=20;}

    if(item_used=="EXP Cookie")
    {
        if(MainP_exp<=(100-exp_restored))
            MainP_exp=MainP_exp+exp_restored;
        else
            MainP_exp=100;
    }

    if(item_used=="Healing Jamishiri")
    {
        if(MainP_hp<=(100-health_restored))
            MainP_hp=MainP_hp+health_restored;
        else if(MainP_hp>100)
            MainP_hp=MainP_hp;
        else
            MainP_hp=100;
    }

    if(item_used=="TH Sword")
    {
        OtherP_hp=OtherP_hp-thSword_dmg;
        MainP_exp=MainP_exp-45;
    }

    if(item_used=="Dagger")
    {
        OtherP_hp=OtherP_hp-dagger_dmg;
        MainP_exp=MainP_exp-25;
    }

    if(item_used=="Gun")
    {
        OtherP_hp=OtherP_hp-gun_dmg;
        MainP_exp=MainP_exp-40;
    }
}

void draw_XPCookie()
{
    cout << "\t\t\t\t\t\t\t\t\t\t" << " _____________ " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "{   .   . .  .}" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "{ .  ..   . . }" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "{   . EXP  .  }" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "{ . .Cookie  .}" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "{ .  . .  . . }" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "{  .  .  . .  }" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "{_____________}" << endl;
}

void draw_HealingJamishiri()
{
    cout << "\t\t\t\t\t\t\t\t\t\t" << "    _    " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   | |   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "---------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "|       |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "|       |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "|   H   |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "|   J   |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "|       |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "|       |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "---------" << endl;
}

void draw_THSword()
{
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   /^\\   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   |T|   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   |H|   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   | |   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   |S|   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   |W|   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   |O|   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   |R|   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   |D|   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   | |   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   | |   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "---------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   | |   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "   | |   " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "  -----  " << endl;
}

void draw_Dagger()
{
    cout << "\t\t\t\t\t\t\t\t\t\t" << "  /^\\  " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "  | |  " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "  | |  " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "  | |  " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "-------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "  | |  " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "  ---  " << endl;
}
void draw_Gun()
{
    cout << "\t\t\t\t\t\t\t\t\t\t" << " ___________ " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "|   -G$N-   |" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << "\\   ________|" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << " |  |-)       " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t" << " |__|          " << endl;
}

void Item_animation(string Player,string item_used,int thSword_dmg,int dagger_dmg,int gun_dmg)
{
    system("cls");

    cout<<Player<<" used "<<item_used<<" ";

    if(item_used=="EXP Cookie")
        {cout<<"to increase their EXP.\n";
        draw_XPCookie();}
    else if(item_used=="Healing Jamishiri")
        {cout<<"to increase their HP.\n";
        draw_HealingJamishiri();}
    else if(item_used=="TH Sword")
        {cout<<"for "<<thSword_dmg<<" damage.\n";
        draw_THSword();}
    else if(item_used=="Dagger")
        {cout<<"for "<<dagger_dmg<<" damage.\n";
        draw_Dagger();}
    else if(item_used=="Gun")
        {cout<<"for "<<gun_dmg<<" damage.\n";
        draw_Gun();}

}

void new_background(string fightarray[][160],int P1_hp,int P2_hp,int P1_exp,int P2_exp)
{
    system("cls");

    backgroundPrint();
    printRoad();
    printArray(fightarray);
    printRoad();
    healthBar(false,false,2,P1_hp,P2_hp);
    cout << endl;
    xpBar(false,false,2,P1_exp,P2_exp);
    cout<<endl;
    system("pause");
}

void Alternate_Turns(string P1,string P2,string P1_Items[],string P2_Items[],int array_size,int& P1_hp,int& P1_exp,int& P2_hp,int& P2_exp,bool& P1_alive,bool& P2_alive,string fightarray[][160])
{
    bool breaker=false;
    bool P1_can,P2_can;
    P1_can=true;
    P2_can=true;

    while((P1_can) || (P2_can))
    {
        if(P1_can)
        {
            One_Turn(P1_Items,array_size,breaker,P1_hp,P1_exp,P2_hp,P2_exp,P1_alive,P1,P2,fightarray);
            new_background(fightarray,P1_hp,P2_hp,P1_exp,P2_exp);
            if(breaker==true)
            {
                system("cls");
                cout<<"You can't do anything else.\n\n";
                P1_can=false;
                breaker=false;
                system("pause");
            }
        }

        if(P2_can)
        {
            outputPlayer(P2,P2_Items,array_size,2);
            cout<<"\n\n\n";
            system("pause");

            One_Turn(P2_Items,array_size,breaker,P2_hp,P2_exp,P1_hp,P1_exp,P2_alive,P2,P1,fightarray);
                new_background(fightarray,P1_hp,P2_hp,P1_exp,P2_exp);
            if(breaker==true)
            {
                system("cls");
                cout<<"You can't do anything else.\n\n";
                P2_can=false;
                breaker=false;
                system("pause");
            }
        }

        if(P1_can==false)
            continue;

        outputPlayer(P1,P1_Items,array_size,2);
        cout<<"\n\n\n";
        system("pause");
    }

    system("cls");
    for (int counter=1;counter<=20;counter++)
    {
        cout<<endl;
    }
    for (int counter=1;counter <=76;counter++)
    {
        cout<<" ";
    }
    cout << "Fight Ended\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Overall_Fighting(string P1_items[],string P2_items[],int array_size,string player1,string player2,string fightarray[][160])
{
    cout<<endl;
    system("pause");
    outputFight();
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    system("pause");
    outputPlayer(player1,P1_items,array_size,1);
    cout<<"\n\n";
    system("pause");
    ItemFight(P1_items,P2_items,array_size,player1,player2,fightarray);
}

