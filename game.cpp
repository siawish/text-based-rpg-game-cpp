#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

int Class_choice = 0;
int quest_choice = 0;
int Quest_counter = 0;
int random_counter = 0;
bool battle_outcome = 0;
//bool enemy_fled = false;
//int branch_counter = 0;

struct Player 
{
	string name;
	string Class;
	int health;
	int exp;
	string inventory[5];
	int level;
	string game_log;
	int Max_health = 100;
};

struct Quest
{
	string description;
	int Difficulty;
	int Experience_Reward;
	string Artifact;
	string boss_name;
};

void Create_character(Player &player);
bool check_name(const Player &player);
bool check_Class(int &Class_choice);
void display_Character_Info(Player& player);
void Main_menu();
void Handle_main_choice(Player& player);
bool check_main_choice(int& main_choice);
void Embark_on_quest(Player& player);
bool check_quest_choice(int& quest_choice);
void Battle(Player& player, Quest& quest);
bool check_attack_choice(int& attack_choice);
void Handle_Attack_Choice(int attack_choice, int& Player_Attack, Player& player);
void Perform_Enemy_Attack(int& Enemy_Attack, int& quest_difficulty, string& boss_name, int& enemy_health,bool& enemy_fled,int Max_enemy_health);
void random_events(Player& player, int& enemy_health, Quest& quest);
void Story_line(Player& player,const bool &enemy_fled);
void Level_Up(Player& player,Quest &quest);


int main()
{
 
	srand(time(0));

	Player Character;
	Create_character(Character);
    
	while (1)
	{
       		if(Quest_counter=0)
		{
			Story_line();
		}
		display_Character_Info(Character);
		Main_menu();
		Handle_main_choice(Character);
	}

	cout << "\n\n";
	system("pause");

	return 0;
}

void Create_character(Player& player)
{
    bool flag = 0;

    do {
        cout  << "\n\nEnter your Name: ";
        getline(cin, player.name);


        flag = check_name(player);


    } while (flag != 1);

    do
    {
        cout << "\n\nChoose Your Class: ";
        cout << "\n1.Saiyan\n2.Ninja\n3.Knight";
        cout << "\n\nEnter Your Choice: ";
        cin >> Class_choice;


    } while (!check_Class(Class_choice));


    switch (Class_choice)
    {

    case 1:
        player.Class = "Saiyan";
        break;
    case 2:
        player.Class = "Ninja";
        break;
    case 3:
        player.Class = "Knight";
        break;
    }



    player.exp = 0;
    player.health = player.Max_health;
    player.level = 1;
    player.game_log = "\n\n----------GAME LOG----------\n\n";

}

bool check_name(const Player& player)
{
    int character_counter = 0;

    for (int i = 0; i < player.name.length(); i++)
    {
        if (isalpha(player.name[i]))
        {
            character_counter++;
        }
    }

    if (character_counter >= 4)
    {
        return 1;
    }
    else
    {
        cout << "\n\nPlease Enter At lease 4 Characters in your name. You can add spaces and special characters too.";
        return 0;
    }

}

bool check_Class(int &Class_choice)
{
    if (cin.fail() || Class_choice < 1 || Class_choice > 3)
    {
        cin.clear();  // Clear error flag

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input

        cout << "\nInvalid input. Please enter a number between 1 and 3." << endl;

        return false;
    }

    return true;
}

void display_Character_Info(Player& player)
{
    cout << "\n\n-----Character Information-----";
    cout << "\n\nName: " << player.name;
    cout << "\nClass: " << player.Class;
    cout << "\nExperience: " << player.exp;
    cout << "\nHealth: " << player.health;
    cout << "\nLevel: " << player.level;

    cout << endl << endl;
    

    cout << "\n\n" << player.game_log;

    
    cout << "\n\n---------Inventory---------";
    for (int i = 0; i < 5; ++i)
    {
        cout << endl;
        cout << i + 1 << ". " << player.inventory[i];
    }
    cout << endl << endl;
    
}

void Main_menu()
{
    cout << "\n\n-----Main Menu-----\n\n";

    cout << "\n\n1.Embark on a Quest.";
    cout << "\n2.Leave the Game.";
    
   
}

void Handle_main_choice(Player& player)
{
    int main_choice;

    do
    {
        cout << "\n\nEnter Your Choice: ";
        cin >> main_choice;

    } while (!check_main_choice(main_choice));

    switch (main_choice)
    {
    case 1:
        Embark_on_quest(player);
        break;
    case 2:
        cout << "\n\nThank You For Playing Adventure Time.";
        exit(0);
        break;
    }

}

bool check_main_choice(int& main_choice)
{
    if (cin.fail() || main_choice < 1 || main_choice > 2)
    {
        cin.clear();  // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        cout << "\nInvalid input. Please enter a number between 1 and 2." << endl;
        return false;
    }

    return true;
}

void Embark_on_quest(Player& player)
{

    Quest quests_Saiyan[] = {
                       {"The Lost Brother ", 1 , 25 , "Dragon Ball (1)","Raditz"},

                       {"The Fallen Prince", 2 , 50 , "Dragon Ball (2)","Vegeta"},

                       {"Ginyu the Tyrant", 3 , 75 , "Dragon Ball (3)","Captain Ginyu"},

                       {"Pride and Shame", 4 , 100 ,"Dragon Ball (4)","Freeza"},

                       {"Shenron the Wise Dragon", 5 , 200 ,"Dragon Ball (5)","Shenron"}


    };
    Quest quests_Ninja[] = {
                      {"The Widow of the Blood Mist Village", 1 , 25 , "Blood Scroll","Mei Mei"},

                      {"Prince of the Hidden Sand Village", 2 , 50 , "Sand Scroll","Gaara"},

                      {"Killer-Bee the Rapper", 3 , 75 , "Lightning Scroll","Killer-Bee"},

                      {"Pain of the Akatsuki", 4 , 100 ,"Beast Scroll","Onoki"},

                      {"Itachi the Genjutsu Master", 5 , 200 ,"Sharingan Scroll","Itachi"}

    };
    Quest quests_Knight[] = {
                     {"Escorting a noble", 1 , 25 , "Goblin Bag","Goblin"},

                     {"Trial of Valor", 2 , 50 , "Electric boots","JIN"},

                     {"Rescue Mission", 3 , 75 , "Daimond Ring","Voldemort"},

                     {"Beast Hunt", 4 , 100 ,"Ghoul skin","Ghoul"},

                     {"Slay the dragon", 5 , 200 ,"Dragon Scale","Dragon"}

    };

    if (Class_choice == 1)
    {

        for (int i = 0; i < sizeof(quests_Saiyan) / sizeof(quests_Saiyan[i]); ++i)
        {
            cout << "\n" << i + 1 << ". " << quests_Saiyan[i].description << ", (Difficulty: " << quests_Saiyan[i].Difficulty << ")";
        }

    }

    else if (Class_choice == 2)
    {

        for (int i = 0; i < sizeof(quests_Ninja) / sizeof(quests_Ninja[i]); ++i)
        {
            cout << "\n" << i + 1 << ". " << quests_Ninja[i].description << ", (Difficulty: " << quests_Ninja[i].Difficulty << ")";
        }
    }

    else
    {
        for (int i = 0; i < sizeof(quests_Knight) / sizeof(quests_Knight[i]); ++i)
        {
            cout << "\n" << i + 1 << ". " << quests_Knight[i].description << ", (Difficulty: " << quests_Knight[i].Difficulty << ")";
        }
    }


    do {
        cout << "\n\nEnter your choice: ";
        cin >> quest_choice;

    } while (!check_quest_choice(quest_choice));

    Quest Selected_Quest;


    if (Class_choice == 1)
    {
        Selected_Quest = quests_Saiyan[quest_choice - 1];
    }
    else if (Class_choice == 2)
    {
        Selected_Quest = quests_Ninja[quest_choice - 1];
    }
    else if (Class_choice == 3)
    {
        Selected_Quest = quests_Knight[quest_choice - 1];
    }

    Battle(player, Selected_Quest);


}

bool check_quest_choice(int& quest_choice)
{

    if (cin.fail() || quest_choice < 1 || quest_choice > 5)
    {
        cin.clear();  // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        cout << "\nInvalid input. Please enter a number between 1 and 5." << endl;
        return false;
    }

    return true;
}

void Battle(Player& player, Quest& quest)
{
    battle_outcome = 0;

    int enemy_health = 100 * quest.Difficulty;

    int Max_enemy_health = enemy_health;

    int Player_Attack = 0;
    
    int Enemy_Attack = 0;

    int random_counter = 0;

    bool enemy_fled = false;

    cout << "\n\n-----Battle Begins-----";

    do
    {
        cout << "\n------------------------";
        cout << "\n\n" << player.name << " Health: " << player.health;
        cout << "\n" << quest.boss_name << "'s Health: " << enemy_health;
        cout << "\n------------------------";

        cout << endl << endl;
        

        cout << "\n\n-----" << player.name << "'s Turn-----";

        cout << "\n\n\n------Choose Your Attack----- ";
        cout << "\n\n1.Heavy Attack";
        cout << "\n2.Light Attack";
        cout << "\n3.Flee from the Battle";

        int attack_choice;

        do
        {
            cout << "\n\nEnter Your Choice: ";
            cin >> attack_choice;

        } while (!check_attack_choice(attack_choice));

        Handle_Attack_Choice(attack_choice, Player_Attack, player);

        if (attack_choice != 3)
        {
            enemy_health -= Player_Attack;

            cout << "\n\nYou Inflicted a Damage of " << Player_Attack << " on " << quest.boss_name;

            cout << "\n\n-----" << quest.boss_name << "'s Turn-----";

            

            Perform_Enemy_Attack(Enemy_Attack, quest.Difficulty, quest.boss_name, enemy_health, enemy_fled,Max_enemy_health);

            if (enemy_fled == true)
            {
                battle_outcome = true;
                break;
            }

            else
            {
                player.health -= Enemy_Attack;

                cout << "\n\nThe " << quest.boss_name << " Inflicted a Damage of " << Enemy_Attack << " on You.";

                if (player.health > (30 * player.Max_health) / (100) && enemy_health > (30 * Max_enemy_health) / (100))
                {

                    if (random_counter == 0)
                    {
                        random_events(player, enemy_health, quest);
                        random_counter++;
                    }

                }
            }

        }

    } while (player.health > 0 && enemy_health > 0);

    if (enemy_health <= 0 || enemy_fled == true)
    {
        cout << "\n\nYou Won the Battle!";
        player.exp += quest.Experience_Reward;

        if (player.exp >= 100)
        {
            Level_Up(player,quest);
        }

       
      
        random_counter = 0;
        player.health = player.Max_health;
        battle_outcome = true;
       
        player.inventory[quest_choice - 1] = quest.Artifact;
        cout << "\n\nItem Obtained: " << player.inventory[quest_choice - 1];
        player.game_log += "\n\nCompleted: " + quest.description;
       
        cout << endl;
        Story_line(player, enemy_fled);
        
    }

    else
    {
        cout << "\n\nYou Lost!!!";
        battle_outcome = true;
        player.exp -= 10 * quest.Difficulty;

        if (player.exp < 0)
        {
            player.exp = 0;
        }

        player.game_log+= "\nLOST: " + quest.description;
        random_counter = 0;
       
        player.health = player.Max_health;
    }
    
    
    Quest_counter++;

}

bool check_attack_choice(int& attack_choice)
{
    if (cin.fail() || attack_choice < 1 || attack_choice > 3)
    {
        cin.clear();  // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        cout << "\nInvalid input. Please enter a number between 1 and 3." << endl;
        return false;
    }

    return true;
}

void Handle_Attack_Choice(int attack_choice, int& Player_Attack, Player& player)
{
    
    switch (attack_choice)
    {
    case 1:
        Player_Attack = rand() % (player.level * 50) + 1;
        break;

    case 2:
        Player_Attack = rand() % (player.level * 30) + 1;
        break;

    case 3:

        if ( player.health < (50 * player.Max_health) /100 )            //Player Health less the 50%
        {
            cout << "\n\nYou tried to escape but the Beast Killed You.";
            cout << "\n\nGame Over!";
            exit(0);
        }
        else
        {
            cout << "\n\nYou successfully escaped from the Creature.";
            player.exp -= 50;
            cout << "\n\nYou Lost 50 Experience points.";
            player.health = player.Max_health;
            display_Character_Info(player);
            Main_menu();
            Handle_main_choice(player);
            break;
        }
        break;

    default:

        cout << "\nChoose a valid option";
    }
}

void Perform_Enemy_Attack(int& Enemy_Attack, int& quest_difficulty, string& boss_name, int& enemy_health,bool& enemy_fled,int Max_enemy_health)
{
    int enemy_attack_choice = rand() % 3 + 1;

    if (enemy_attack_choice == 1)
    {
        Enemy_Attack = rand() % (quest_difficulty * 30) + 1;
    }
    else if(enemy_attack_choice == 2)
    {
        Enemy_Attack = rand() % (quest_difficulty * 20) + 1;
    }

    else if(enemy_attack_choice == 3)
    {
        if (enemy_health <= (20 * Max_enemy_health) / (100))
        {
            cout << "\n\n" << boss_name << " fled from the battle ground.";
            enemy_fled = true;
            return;
        }
        
        
    }

}

void Level_Up(Player& player,Quest &quest)
{
    player.level++;
    player.exp = 0;
    player.Max_health += 100;
}

void random_events(Player& player, int& enemy_health, Quest& quest)
{
    bool random_number = (rand() % 2);


    if (random_number == 1)
    {
        random_counter++;

        string event;

        cout << "\n\nA Random Event has Occured.";

        int random = rand() % 4 + 1;

        if (random == 1)
        {

            int a, b, tries = 0, correct_counter = 0, wrong_counter = 0;

            enemy_health -= 50;

            event = "\n\nThe " + quest.boss_name + " sets up cunning traps in the surrounding area.\nThe " + quest.boss_name + " sacrificed his health points to setup this trap,\nguess the locations of the mines to avoid getting injured and further losing your Health Points.";

            cout << "\n\n" << event;

            cout << "\n\nYour Health: " << player.health;
            cout << "\n\n" << quest.boss_name << "'s Health: " << enemy_health;

            int maze_1[3][3] = {

                {1,0,1},
                {0,1,1},
                {1,1,0}
            };

            int maze_2[3][3] = {

                {0,1,0},
                {1,1,1},
                {1,0,1}
            };

            int maze_3[3][3] = {

                {1,1,0},
                {1,0,1},
                {0,1,1}
            };

            int mazes = rand() % 3 + 1;

            cout << "\n\n  --------MAZE--------\n\n";

            for (int i = 0; i < 3; i++)

            {
                cout << "\t";
                for (int j = 0; j < 3; j++)
                {
                    cout << "* ";
                }
                cout << endl;
            }

            if (mazes == 1)
            {

                cout << "\n\nYou have 3 tries.";

                for (int i = 0; i < 3; i++)
                {
                    cout << "\n\nEnter the location of Mine " << i + 1 << ": ";
                    cin >> a >> b;
                    if (maze_1[a - 1][b - 1] == 0)
                    {
                        cout << "\n\nYou have spotted the Mine " << i + 1 << ".";
                        correct_counter++;
                    }
                    else
                    {
                        cout << "\n\nYour guess was wrong:";
                        cout << "\n\nYour Health was reduced By 10.";
                        player.health -= 10;
                        cout << "\n\nYour Health: " << player.health;
                        wrong_counter++;
                    }
                }
            }

            else if (mazes == 2)
            {

                cout << "\n\nYou have 3 tries.";

                for (int i = 0; i < 3; i++)
                {
                    cout << "\n\nEnter the location of Mine " << i + 1 << ": ";
                    cin >> a >> b;
                    if (maze_2[a - 1][b - 1] == 0)
                    {
                        cout << "\n\nYou have spotted Mine " << i + 1 << ".";
                        correct_counter++;
                    }
                    else
                    {
                        cout << "\n\nYour guess was wrong:";
                        cout << "\n\nYour Health was reduced By 10.";
                        player.health -= 10;
                        cout << "\n\nYour Health: " << player.health;
                        wrong_counter++;
                    }
                }
            }

            else if (mazes == 3)
            {

                cout << "\n\nYou have 3 tries.";

                for (int i = 0; i < 3; i++)
                {
                    cout << "\n\nEnter the location of Mine " << i + 1 << ": ";
                    cin >> a >> b;
                    if (maze_3[a - 1][b - 1] == 0)
                    {
                        cout << "\n\nYou have spotted Mine " << i + 1 << ".";
                        correct_counter++;
                    }
                    else
                    {
                        cout << "\n\nYour guess was wrong:";
                        cout << "\n\nYour Health was reduced By 10.";
                        player.health -= 10;
                        cout << "\n\nYour Health: " << player.health;
                        wrong_counter++;
                    }
                }
            }


            player.game_log += "\nThe " + quest.boss_name + " sets up a Trap.";
            player.game_log += "\nYou correctly Guessed " + to_string(correct_counter) + " traps.";
            player.game_log += "\nHealth reduced " + to_string(wrong_counter * 10);

        }

        else if (random == 2)
        {
            random_counter++;
            bool your_guess = 0;
            event = quest.boss_name + " wants to Test your wisdom.He gives you a riddle to solve.";
            cout << "\n\n" << event;
            player.game_log+= "\n\n" + event;

            int riddles = rand() % 3 + 1;


            if (Class_choice == 1)
            {
                if (riddles == 1)
                {
                    string answer = "rage";
                    string user_answer = "";
                    cout << "\n\nRiddle: I am an unstoppable force, born from fury's embrace. What form do I take?";
                    cout << "\n\nGive it your best shot (Enter your answer in lower-case letters): ";
                    cin >> user_answer;

                    if (user_answer == answer)
                    {
                        cout << "\n\nYour Guess was Correct.";
                        player.exp += quest.Experience_Reward;
                        player.health += 20;
                        enemy_health -= 20;
                        your_guess = 1;
                    }
                    else
                    {
                        cout << "\n\nYour Guess was not Correct.";

                        player.health -= 20;
                        enemy_health += 15;
                    }

                }
                else if (riddles == 2)
                {
                    string answer = "warrior";
                    string user_answer = "";
                    cout << "\n\nRiddle:I rise with a golden aura, transcending limits with each battle's heat. Who am I?";
                    cout << "\n\nGive it your best shot (Enter your answer in lower-case letters without space): ";
                    cin >> user_answer;

                    if (user_answer == answer)
                    {
                        cout << "\n\nYour Guess was Correct.";
                        player.exp += quest.Experience_Reward;
                        player.health += 20;
                        enemy_health -= 20;
                        your_guess = 1;
                    }
                    else
                    {
                        cout << "\n\nYour Guess was not Correct.";

                        player.health -= 20;
                        enemy_health += 15;
                    }
                }
                else
                {
                    string answer = "superpower";
                    string user_answer = "";
                    cout << "\n\nRiddle:Born of stars, I wield the power to shake worlds. What am I?";
                    cout << "\n\nGive it your best shot (Enter your answer in lower-case letters): ";
                    cin >> user_answer;

                    if (user_answer == answer)
                    {
                        cout << "\n\nYour Guess was Correct.";
                        player.exp += quest.Experience_Reward;
                        player.health += 20;
                        enemy_health -= 20;
                        your_guess = 1;
                    }
                    else
                    {
                        cout << "\n\nYour Guess was not Correct.";

                        player.health -= 20;
                        enemy_health += 15;
                    }
                }
            }

            else if (Class_choice == 2)
            {
                if (riddles == 1)
                {
                    string answer = "stealth";
                    string user_answer = "";
                    cout << "\n\nRiddle:  I vanish in the shadows, a ghost in the night. What hides within?";
                    cout << "\n\nGive it your best shot (Enter your answer in lower-case letters): ";
                    cin >> user_answer;

                    if (user_answer == answer)
                    {
                        cout << "\n\nYour Guess was Correct.";
                        player.exp += quest.Experience_Reward;
                        player.health += 20;
                        enemy_health -= 20;
                        your_guess = 1;
                    }
                    else
                    {
                        cout << "\n\nYour Guess was not Correct.";

                        player.health -= 20;
                        enemy_health += 15;
                    }

                }
                else if (riddles == 2)
                {
                    string answer = "shadow";
                    string user_answer = "";
                    cout << "\n\nRiddle:I am the master of concealment, adept in the art of surprise. Who am I?";
                    cout << "\n\nGive it your best shot (Enter your answer in lower-case letters without space): ";
                    cin >> user_answer;

                    if (user_answer == answer)
                    {
                        cout << "\n\nYour Guess was Correct.";
                        player.exp += quest.Experience_Reward;
                        player.health += 20;
                        enemy_health -= 20;
                        your_guess = 1;
                    }
                    else
                    {
                        cout << "\n\nYour Guess was not Correct.";

                        player.health -= 20;
                        enemy_health += 15;
                    }
                }
                else
                {
                    string answer = "invisibility";
                    string user_answer = "";
                    cout << "\n\nRiddle: I move with silent footsteps, unseen yet omnipresent. What skill am I?";
                    cout << "\n\nGive it your best shot (Enter your answer in lower-case letters): ";
                    cin >> user_answer;

                    if (user_answer == answer)
                    {
                        cout << "\n\nYour Guess was Correct.";
                        player.exp += quest.Experience_Reward;
                        player.health += 20;
                        enemy_health -= 20;
                        your_guess = 1;
                    }
                    else
                    {
                        cout << "\n\nYour Guess was not Correct.";

                        player.health -= 20;
                        enemy_health += 15;
                    }
                }
            }


            else
            {
                if (riddles == 1)
                {
                    string answer = "defender";
                    string user_answer = "";
                    cout << "\n\nRiddle:Clad in steel, I am a guardian of realms. What's my calling?";
                    cout << "\n\nGive it your best shot (Enter your answer in lower-case letters): ";
                    cin >> user_answer;

                    if (user_answer == answer)
                    {
                        cout << "\n\nYour Guess was Correct.";
                        player.exp += quest.Experience_Reward;
                        player.health += 20;
                        enemy_health -= 20;
                        your_guess = 1;
                    }
                    else
                    {
                        cout << "\n\nYour Guess was not Correct.";

                        player.health -= 20;
                        enemy_health += 15;
                    }

                }
                else if (riddles == 2)
                {
                    string answer = "knight";
                    string user_answer = "";
                    cout << "\n\nRiddle:I am the wielder of chivalry's might, shining under the sun's gleam. What am I?";
                    cout << "\n\nGive it your best shot (Enter your answer in lower-case letters without space): ";
                    cin >> user_answer;

                    if (user_answer == answer)
                    {
                        cout << "\n\nYour Guess was Correct.";
                        player.exp += quest.Experience_Reward;
                        player.health += 20;
                        enemy_health -= 20;
                        your_guess = 1;
                    }
                    else
                    {
                        cout << "\n\nYour Guess was not Correct.";

                        player.health -= 20;
                        enemy_health += 15;
                    }
                }
                else
                {
                    string answer = "protector";
                    string user_answer = "";
                    cout << "\n\nRiddle: My heart beats with loyalty, my blade sings with honor. Who am I?";
                    cout << "\n\nGive it your best shot (Enter your answer in lower-case letters): ";
                    cin >> user_answer;

                    if (user_answer == answer)
                    {
                        cout << "\n\nYour Guess was Correct.";
                        player.exp += quest.Experience_Reward;
                        player.health += 20;
                        enemy_health -= 20;
                        your_guess = 1;
                    }
                    else
                    {
                        cout << "\n\nYour Guess was not Correct.";

                        player.health -= 20;
                        enemy_health += 15;
                    }
                }
            }

            event = quest.boss_name + " asked you a Riddle.";

            if (your_guess == 1)
            {
                player.game_log += "\n\nYour guess was Correct.";
            }
            else
            {
                player.game_log += "\n\nYour guess was not Correct.";
            }
        }

        else if (random == 3)
        {
            random_counter++;
            cout << "\n\nA Natural Disaster Occured reducing the health both " << player.name << " and " << quest.boss_name;
            player.health -= 20;
            enemy_health -= 20;

            cout << "\n" << player.name << "'s Health: " << player.health;
            cout << "\n" << quest.boss_name << "'s Health: " << enemy_health;

            event = "A Natural Disaster Occured reducing the health of both " + player.name + " and " + quest.boss_name;
            player.game_log += event + "\n" + player.name + " and " + quest.boss_name + " was reduced by 20.";
        }

        else
        {
            random_counter++;
            event = "In the midst of our heated clash, a sudden interruption shattered the tension as a third party,\n unforeseen and enigmatic, emerged into our battleground.";
            cout << "\n\n" << event;

            int third_party = rand() % 2 + 1;
            int damage = rand() % 30 + 1;

            if (third_party == 1)
            {
                enemy_health -= damage;
                cout << "\n\n" << player.name << "'s Ally came to his help,inflicting a damage of " << damage << " on " << quest.boss_name;
                player.game_log += "\n" + event + " and inflicted a damage of " + to_string(damage) + " on " + quest.boss_name;

            }
            else
            {
                player.health -= damage;
                cout << "\n\n" << quest.boss_name << "'s Ally came to his help,inflicting a damage of " << damage << " on " << player.name;
                player.game_log += "\n" + event + " and inflicted a damage of " + to_string(damage) + " on " + player.name;

            }



        }


    }


}

void Story_line(Player &player,const bool &enemy_fled)
{
    if (Quest_counter == 0)
    {
        if (player.Class == "Saiyan")
        {
            cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            cout << "\n\nThe Saiyan protagonist embarks on a quest to rediscover their lost heritage and unlock the dormant potential within their Saiyan bloodline.\nThe journey involves training under celestial masters to harness raw energy, \nseeking legendary artifacts scattered across the cosmos, \nand mastering the art of transformation.\nThe ultimate goal is to awaken the legendary Super Saiyan form, a transformation of immense power, to defend the universe from impending threats.";
            cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            cout << endl << endl;
            system("pause");
        }
        else if (player.Class == "Ninja")
        {
            cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            cout << "\n\nThe Ninja embarks on a perilous quest to uncover ancient scrolls scattered across hidden landscapes.\nThese scrolls contain secret techniques and ancestral knowledge crucial to preserving the ninja clan's legacy.\nThe journey involves mastering stealth, agility, and various ninja arts while confronting rogue factions seeking to exploit these ancient secrets.\nThe ultimate challenge lies in mastering the Forbidden Shadow Arts, unlocking their true potential, and restoring balance to the ninja world.";
            cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            cout << endl << endl;
            system("pause");
        }
        else if (player.Class == "Knight")
        {
            cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            cout << "\n\nThe Knight sets forth on a quest to uphold honor and restore the tarnished reputation of their order.\nTheir journey entails safeguarding sacred relics, seeking lost artifacts of legendary valor, and undergoing trials to prove their worthiness.\nThe quest involves defending the kingdom from dark forces, forming alliances with noble allies, and ultimately confronting a corrupted nemesis threatening the realm.\nThe final test is to reclaim the lost virtue of chivalry, embodying it in a decisive battle to restore peace and honor to the land.";
            cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            cout << endl << endl;
            system("pause");
        }
    }

    /*if (player.Class == "Saiyan")
    {
        if (quest_choice == 1)
        {
            if (enemy_fled == false)
            {
                if (branch_counter == 0)
                {
                    cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                    cout << "\n\nAfter a fierce and relentless battle with Raditz, " << player.name << " emerged victorious, battered but triumphant.\nThe skies cleared as the energy of the clash dissipated, leaving Raditz defeated on the battlefield.\nDespite the intense struggle, " << player.name << "'s determination and newfound strength prevailed, marking the beginning\nof their journey towards even greater challenges in the quest for the Dragon Balls.";
                    cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                    Quest Goku[] = { "Brother's Revenge", 1 , 25 , "A Dragon Ball","Goku" };
                    cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                    cout << "\n\nGoku's arrival startled everyone, his expression grave as he sensed the lingering energy of the battle with Raditz.\n'I felt the turmoil, ' he said, eyes narrowing in determination.\n'Let me assist in settling this score.'";
                    cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                    Battle(player, Goku[0]);
                    branch_counter++;
                }

                else
                {
                    cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                    cout << "\n\nGoku, determined to avenge Raditz's defeat, faced " << player.name << " with unwavering resolve.\nThe battle raged fiercely, each strike resonating with unparalleled power.\nDespite Goku's legendary strength, " <<player.name<<"'s determination and newfound prowess proved overwhelming.Goku gave a Dragon Ball as a reward to " << player.name << ".";
                    cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                }
                
            }

            else
            {
                if (branch_counter == 0)
                {
                    cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                    cout << "\n\nIn a surprising turn of events, Raditz, realizing the impending defeat, cunningly fled the battlefield, leaving behind the precious  Dragon Ball. \n" << player.name << ", though victorious, stood amidst the echoes of the battle, watching as Raditz vanished into the distance.With the Dragon Ball now abandoned,  \n" << player.name << " felt a mix of triumph and curiosity, wondering about Raditz's hasty departure and the potential repercussions of leaving such a powerful artifact unguarded.\nAs  " << player.name << " claimed the Dragon Ball, the quest took an unexpected twist, foreshadowing the challenges that awaited them in the unfolding journey.";
                    cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

                }
               
            }
           

        }
    }*/

    if (Class_choice == 1)
    {
        if (quest_choice == 1 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nAfter a fierce and relentless battle with Raditz, " << player.name << " emerged victorious, battered but triumphant.\nThe skies cleared as the energy of the clash dissipated, leaving Raditz defeated on the battlefield.\nDespite the intense struggle, " << player.name << "'s determination and newfound strength prevailed, marking the beginning\nof their journey towards even greater challenges in the quest for the Dragon Balls. " << player.name << " took the Dragon Ball that Raditz was Hiding.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a surprising turn of events, Raditz, realizing the impending defeat, cunningly fled the battlefield, leaving behind the precious  Dragon Ball. \n" << player.name << ", though victorious, stood amidst the echoes of the battle, watching as Raditz vanished into the distance.With the Dragon Ball now abandoned,  \n" << player.name << " felt a mix of triumph and curiosity, wondering about Raditz's hasty departure and the potential repercussions of leaving such a powerful artifact unguarded.\nAs  " << player.name << " claimed the Dragon Ball, the quest took an unexpected twist, foreshadowing the challenges that awaited them in the unfolding journey.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
        }
        else if (quest_choice == 2 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nWounded but resolute, " << player.name << "stood amidst the aftermath of the fierce battle with Vegeta, the fallen prince.\nThe air crackled with lingering energy as " << player.name << " claimed the coveted Dragon Ball,  a testament to his growing strength.\nThe defeated Vegeta, begrudgingly acknowledging the defeat, vanished into the shadows,\nleaving " << player.name << " to reflect on the challenges that lay ahead in their heroic journey.\nWith the Fallen Prince quest now conquered, a new chapter in the epic saga had begun, promising even greater trials and rewards.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nSensing the overwhelming power of " << player.name << " , hesitated for a moment before abruptly retreating.\nHis pride wounded, Vegeta vanished into the shadows, leaving behind a trail of echoing laughter and a promise of future confrontation.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
        else if (quest_choice == 3 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nAs the battle reached its climax, Ginyu, the leader of the Ginyu Force, fought valiantly against "<< player.name << ".\nDespite his cunning tactics and formidable power, Ginyu found himself outmatched by " << player.name << "'s unwavering determination and skill.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a surprising turn, sensing the overwhelming strength of " << player.name<< ", Ginyu, leader of the Ginyu Force, opted for a strategic retreat.\nDespite his pride taking a blow, Ginyu cunningly vanished from the battlefield, leaving behind a taunting echo of his laughter.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
        else if (quest_choice == 4 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nThe battlefield quaked as Freeza, the tyrant of the universe, faced off against player.name in a clash of unparalleled magnitude.\nDespite Freeza's immense power and ruthless tactics," << player.name << "'s unyielding determination and newfound strength turned the tide of battle.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nAs the battle raged on, Freeza, realizing the imminent threat posed by " << player.name << "'s growing strength, made a calculated decision to retreat. With a cunning maneuver, Freeza vanished into the cosmos, leaving behind a trail of echoing threats and a chilling promise of his return.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
        else if (quest_choice == 5 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nThe confrontation between " << player.name << " and Shenron, the eternal dragon, was a clash of cosmic forces.\nShenron, usually an invulnerable entity, faced an unexpected challenge in " << player.name << "'s determination and unique abilities.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nShenron, the all-powerful dragon, faced an unexpected challenge in " << player.name<< ", sensing an unusual strength within them.\nIn a surprising turn, Shenron, realizing the unforeseen threat, vanished into the Dragon Balls' mystical realm, leaving behind a lingering sense of mystique and uncertainty.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
    }

    else if (Class_choice == 2)
    {
        if (quest_choice == 1 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nThe battlefield trembled as " << player.name << " faced off against the formidable Mizukage, a master of water-style jutsu and renowned for their tactical prowess.\nDespite  Mei Mei's skill and cunning, " << player.name << " determination and strategic acumen turned the tide of the battle.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a surprising turn, sensing the rising strength and resolve of " << player.name << ", the Mizukage opted for a strategic retreat, vanishing into the mist without a trace.\nThe sudden departure left a sense of unease among onlookers, as the Mizukage was known for their stoic resolve and unwavering presence.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
        }
        else if (quest_choice == 2 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nGaara, the Kazekage, known for his mastery over sand-based jutsu and unwavering determination, faced off against " << player.name << " in a fierce battle.\nDespite his impressive skill, Gaara found himself overwhelmed by " << player.name << "'s unyielding resolve and adaptability.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a surprising turn, sensing the increasing power and determination of " << player.name << ", Gaara, the Kazekage, chose a strategic retreat, vanishing into the sands without leaving a trace.\nHis unexpected departure left a sense of curiosity and speculation among those witnessing the battle, as Gaara was known for his unwavering resolve.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
        else if (quest_choice == 3 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {
                
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nKiller Bee, the enigmatic rapper and Jinchuriki of the Eight-Tails, engaged in a fierce battle against " << player.name << ".\nDespite his incredible skill and the immense power of the Tailed Beast within him, Killer Bee found himself overwhelmed by " << player.name << " strategic prowess and adaptability.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a surprising turn, sensing the evolving strength and adaptability of " << player.name << ", Killer Bee, the Jinchuriki of the Eight-Tails, opted for a strategic retreat, vanishing swiftly from the battlefield.\nHis sudden departure left a sense of curiosity and wonder among those witnessing the clash, as Killer Bee was renowned for his unique fighting style and unwavering spirit.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
        else if (quest_choice == 4 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nPain, the enigmatic leader of the Akatsuki and possessor of the Rinnegan, faced " << player.name << " in a cataclysmic showdown.\nDespite his overwhelming power and mastery over multiple jutsu, Pain found himself taken aback by " << player.name << " resilience and tactical ingenuity.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a surprising turn, sensing an unexpected resolve and strength within " << player.name << ", Pain, the leader of the Akatsuki, chose a strategic retreat, vanishing from the battlefield without a trace.\nHis abrupt departure left a sense of intrigue and wonder among those witnessing the intense clash, as Pain was known for his unwavering determination and formidable abilities.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
        else if (quest_choice == 5 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIf Itachi, the prodigious Uchiha, faced defeat against " << player.name << ", it would have been an earth-shattering event in the shinobi world.\nDespite his exceptional skills in genjutsu and tactical brilliance, Itachi's defeat would signify the rise of an immensely powerful adversary.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIf Itachi, renowned for his strategic genius and unparalleled skills, opted for a strategic retreat in the face of a formidable opponent like " << player.name << ", it would create a sense of intrigue and speculation among those witnessing the confrontation.\nItachi's retreat would be unexpected, considering his reputation for facing challenges head-on.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
    }
    
    else if (Class_choice == 3)
    {
        if (quest_choice == 1 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a classic tale of valor and bravery, the courageous knight faced off against the cunning Goblin in a fierce battle.\nDespite the Goblin's traps and deceptive maneuvers, the " << player.name << " unwavering determination and skill prevailed.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a surprising turn, sensing the unyielding resolve and might of the knight, the cunning Goblin chose a strategic retreat, vanishing into the depths of the forest without leaving a trace.\nIts sudden disappearance left a sense of intrigue and caution among those witnessing the clash, as the Goblin was renowned for its deceitful tactics and elusive nature.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
        }
        
        else if (quest_choice == 2 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIt would be a significant turn of events if JIN, known for their exceptional abilities, faced defeat. JIN's remarkable skills and reputation would make their loss surprising and impactful.\nGasps would echo as onlookers witnessed this unexpected outcome, disbelief coloring the atmosphere.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIf JIN, renowned for their exceptional abilities, chose to strategically retreat from a confrontation, it would be an unexpected turn of events.\nJIN's departure would leave a sense of intrigue and speculation among witnesses, given their reputation for facing challenges head-on.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
        else if (quest_choice == 3 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a legendary clash of dark forces and unwavering valor, the courageous knight faced off against the malevolent Voldemort.\nDespite Voldemort's dark magic and cunning strategies, the knight's indomitable spirit and noble bravery prevailed.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nSensing the unyielding courage and might of the knight, the dark and menacing Voldemort chose a strategic retreat, vanishing into the shadows without leaving a trace.\nHis sudden disappearance left a sense of wonder and caution among those witnessing the confrontation, as Voldemort was renowned for his malevolence and determination.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
        else if (quest_choice == 4 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a clash of otherworldly creatures and unwavering valor, the knight faced off against the formidable ghoul.\nDespite the ghoul's eerie abilities and supernatural powers, the knight's bravery and strategic prowess prevailed.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nThe knight's display of courage had compelled the ghoul to reassess the situation, prompting a mix of curiosity and wariness among allies and onlookers.\nPeople whispered about the reasons behind the ghoul's retreat, some speculating about hidden motives or potential future encounters.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
        else if (quest_choice == 5 && battle_outcome == true)
        {
            if (enemy_fled == false)
            {

                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a breathtaking clash between the mighty dragon and the courageous knight, the knight emerged victorious.\nDespite the dragon's immense power and ferocity, the knight's bravery, strategic acumen, and unwavering determination prevailed.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";

            }
            else if (enemy_fled == true)
            {
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
                cout << "\n\nIn a surprising turn of events, sensing the resolute bravery and determination of the knight, the majestic dragon chose a strategic retreat, soaring into the skies and disappearing into the distant horizon.\nIts sudden departure left an aura of wonder and admiration among those witnessing the encounter, as dragons were known for their awe-inspiring presence and indomitable strength.";
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------";
            }
        }
    }

}
