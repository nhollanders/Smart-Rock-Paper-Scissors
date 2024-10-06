#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "rpc.h"

RPC::RPC() // constructor
{
    difficulty = 1;
    memory.resize(10);

    // chances from memory (used for difficulty 2)
    playerChanceOfRock = 0.0;
    playerChanceOfPaper = 0.0;
    playerChanceOfScissors = 0.0;
}

void RPC::setDifficulty(int level) { difficulty = level; }
int RPC::getDifficulty() { return difficulty; }
void RPC::clearMemory() { memory.clear(); }

void RPC::takeInput(int moveTaken)
{   
    if ( memory.size() >= 9 ) // if its reaches 10 elements which is the memory maximum.
    {
        memory.erase(memory.begin());
    }
    memory.push_back(moveTaken);
}

void RPC::makeNextMove()
{
    srand(time(0));
    
    switch (difficulty)
    {
    case 1: // random
        nextMove = ( rand() % 3  + 1 ); // always random from 1 to 3
        break;
    case 2: // uses memory
    {
        int rockCount = 0;
        int paperCount = 0;
        int scissorsCount = 0;

        for (int i = 0; i < memory.size(); i++) // scan memory looking for data
        {
            if ( memory[i] == 1 )
            {
                rockCount++;
            }
            else if ( memory[i] == 2 )
            {
                paperCount++;
            }
            else if ( memory[i] == 3 )
            {
                scissorsCount++;
            }
        }

        playerChanceOfRock = (rockCount / memory.size()) * 100; // calculate the percentage of each move
        playerChanceOfPaper = (paperCount / memory.size()) * 100;
        playerChanceOfScissors = (scissorsCount / memory.size()) * 100;

        if ( playerChanceOfRock > playerChanceOfPaper && playerChanceOfRock > playerChanceOfScissors ) //determine whats most common and make play based on that info.
        {
            nextMove = 2; // bot paper
        }
        else if ( playerChanceOfPaper > playerChanceOfRock && playerChanceOfPaper > playerChanceOfScissors )
        {
            nextMove = 3; // bot scissors
        }
        else if ( playerChanceOfScissors > playerChanceOfRock && playerChanceOfScissors > playerChanceOfPaper )
        {
            nextMove = 1; // bot rock
        }
        else
        {
            nextMove = ( rand() % 3  + 1 ); // always random from 1 to 3
        }

        break;
    }
    case 3: // auto wins
        int playerOption = memory.back(); // returns the last move thats been made.

        if ( playerOption == 1 )
        {
            nextMove = 2; // bot paper
        }
        else if ( playerOption == 2 )
        {
            nextMove = 3; // bot scissors
        }
        else if ( playerOption == 3 )
        {
            nextMove = 1; // bot rock
        }

        break;
    };
}

int RPC::getWinState()
{
    int playerOption = memory.back(); // returns the last move thats been made.

    if ( playerOption == nextMove)
    {
        return 3;
    }
    
    switch (playerOption)
    {
    case 1: // rock
        switch (nextMove)
        {
        case 2:
            return 2; // bot paper
        case 3:
            return 1; // bot scissors
        }
    case 2: // paper
        switch (nextMove)
        {
        case 1:
            return 1; // bot rock
        case 3:
            return 2; // bot scissors
        }
    case 3: // scissors
        switch (nextMove)
        {
        case 1:
            return 2; // bot rock
        case 2:
            return 1; // bot paper
        }
    }
    return 3; // incase something goes wrong it will fully default to a tie.
}

void RPC::DisplayOutput()
{
    int winState = getWinState();

    cout << "Bot chose: ";
    switch (nextMove)
    {
    case 1:
        cout << "Rock";
        break;
    case 2:
        cout << "Paper";
        break;
    case 3:
        cout << "Scissors";
        break;
    }
    cout << endl;

    switch (winState)
    {
    case 1:
        cout << "Well done! you win." << endl;
        break;
    case 2:
        cout << "Better luck next time, you lose." << endl;
        break;
    case 3:
        cout << "Its a tie try again." << endl;
        break;
    };
    cout << endl;
}