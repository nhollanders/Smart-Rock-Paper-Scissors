#include <iostream>
#include <string>
#include <map>

#include "includes/console_menu.h"
#include "includes/rpc.h"

using namespace std;

map<string,int> optionMap = {{"rock", 1},{"paper", 2},{"scissors", 3}};

void mainGame(ConsoleMenu inPlayMenu, RPC gameBot)
{
    bool gameIsRunning = true;

    cout << string(100, '\n'); // clears the screen

    while ( gameIsRunning == true )
    {
        inPlayMenu.DisplayMenu();
        bool innerGameLoopRunning = true;
        string InputData;

        while (innerGameLoopRunning = true)
        {
            cout << "Make a move: ";
            std::getline(cin, InputData);

            if ( optionMap[InputData] )
            {
                int choice = optionMap[InputData];

                gameBot.takeInput(choice); // places the input into memory
                gameBot.makeNextMove(); // makes the next move for the bot, this must happen to generate a response.
                gameBot.DisplayOutput(); // displays the output

                int winState = gameBot.getWinState();

                if ( winState == 1 )
                {
                    innerGameLoopRunning = false;
                    break;
                }
                else if ( winState == 2 )
                {
                    innerGameLoopRunning = false;
                    break;
                }
                else if ( winState == 3 )
                {
                    continue;
                }
            }
            else
            {
                cout << "Please input a valid response..." << endl;
                continue;
            }
        }

        cout << "Play again? (y/n): ";
        std::getline(cin, InputData);
        char opt = InputData[0];
        if ( opt == 'y')
        {
            continue;
        }
        else
        {   
            gameIsRunning = false;
            break;
        }
    }
}

int main() 
{
    bool isRunning = true;

    string currentInput;
    string lastInput;

    ConsoleMenu CM_Main = ConsoleMenu();
    CM_Main.AddMenuOptions("Quit", "Quits the program");
    CM_Main.AddMenuOptions("Play", "Starts a round");
    CM_Main.AddMenuOptions("Dif", "Modifys Difficulty");
    CM_Main.SetWelcomeSentence("Welcome to Rock Paper Scissors!");
    CM_Main.SetAskSentence("Input a command: ");

    CM_Main.DisplayWelcomeMessage();

    ConsoleMenu DifficultyMenu = ConsoleMenu();
    DifficultyMenu.AddMenuOptions("1", "Random responses");
    DifficultyMenu.AddMenuOptions("2", "10 move memory");
    DifficultyMenu.AddMenuOptions("3", "Always wins");
    DifficultyMenu.SetAskSentence("Please Input a number from 1 to 3: ");

    ConsoleMenu GameMenu = ConsoleMenu();
    GameMenu.AddMenuOptions("Rock", "W: Scissors, L: Paper");
    GameMenu.AddMenuOptions("Paper", "W: Rock, L: Scissors");
    GameMenu.AddMenuOptions("Scissors", "W: Paper, L:Rock");

    RPC gameBot = RPC(); // the bot we use for this session

    while (isRunning)
    {   
        CM_Main.DisplayMenu();
        
        std::getline(cin, currentInput);

        for (int i = 0; i < currentInput.length(); i++) // converts all input to lowercase so it dosent break anything.
        {
            currentInput[i] = tolower(currentInput[i]);
        }
        
        if ( currentInput == "quit" ) // if you type quit
        {
            isRunning = false;
            break;
        }
        else if ( currentInput == "dif" ) // if you type dif for the difficulty
        {
            bool choosing = true;

            DifficultyMenu.DisplayMenu();

            string inputOption;
            int cleanOption;
            std::getline(cin, inputOption);

            if ( inputOption == "quit" )
            {
                isRunning = false;
                break; 
            }

            try
            {
                cleanOption = stoi(inputOption);
            }
            catch(...)
            {
                cout << "Invalid input!" << endl;
                continue;
            }

            if ( cleanOption > 0 && cleanOption < 4 )
            {
                gameBot.setDifficulty(cleanOption);
            }
            else
            {
                cout << "Invalid input!" << endl;
                continue;
            }
        }
        else if ( currentInput == "play" ) // if you type play it goes to the main game function
        {
            mainGame(GameMenu, gameBot);
        }
        else
        {
            cout << "Invalid Option" << endl;
        }
    }

    return 0;
}