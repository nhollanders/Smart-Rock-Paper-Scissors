#include "console_menu.h"
#include <iostream>
#include <string>
#include <algorithm>

ConsoleMenu::ConsoleMenu() // constructor
{
    longestStringName = 4; // 4 because its the length of opts
    longestStringDescriptor = 11; // 11 because its the length of descriptors
    askSentence = "";
    welcomeSentence = "";
}

void ConsoleMenu::printChar(int amount, char charpar)
{
    for (int i = 0; i < amount; i++)
    {
        cout << charpar;
    }
}

void ConsoleMenu::SetAskSentence(string sentence) { askSentence = sentence; }
void ConsoleMenu::SetWelcomeSentence(string sentence) { welcomeSentence = sentence; }

void ConsoleMenu::DisplayWelcomeMessage() { cout << welcomeSentence << endl; }

void ConsoleMenu::AddMenuOptions(string name, string descriptor)
{
    // finding shortest name
    if ( longestStringName < name.length() )
    {
        longestStringName = name.length();
    }

    // finding shortest descriptor
    if ( longestStringDescriptor < descriptor.length() )
    {
        longestStringDescriptor = descriptor.length();
    }

    menuOptionMap[name] = descriptor;
}

void ConsoleMenu::RemoveMenuOption(string name)
{
    menuOptionMap.erase(name);
}

void ConsoleMenu::DisplayMenu()
{
    // first line
    int diameter = 2 + longestStringName + 3 + longestStringDescriptor + 2; // space taken horitontally by all the text.
    printChar(diameter, '_');
    cout << endl;

    // helper box on the second line goes here
    cout << '|' << ' ' << "Opts";
    printChar(max(0, longestStringName - 4), ' ');
    cout << ' ' << '|' << ' ' << "Descriptors";
    printChar(max(0, longestStringDescriptor - 11), ' ');
    cout << ' ' << '|' << endl << '|';
    printChar(longestStringName + 2, '_');
    cout << '|';
    printChar(longestStringDescriptor + 2, '_');
    cout << '|' << endl;


    // start looping for each entry in the dictionary
    for (auto const& [name, descriptor] : menuOptionMap)
    {
        cout << '|' << ' ' << name;
        printChar( (longestStringName - name.length()), ' '); // adds the spaces after the name so it dosent cause the middle line to be uneven.
        cout << ' ' << '|' << ' ' << descriptor;
        printChar( (longestStringDescriptor - descriptor.length()), ' ');
        cout << ' ' << '|' << endl;
    }

    // finish up with the bottom line
    cout << '|';
    printChar(longestStringName + 2, '_');
    cout << '|';
    printChar(longestStringDescriptor + 2, '_');
    cout << '|' << endl;

    if ( askSentence.length() > 0 )
    {
        cout << askSentence;
    }
    else // if we arent asking for anything then we can skip that and just end the line.
    {
        cout << endl;
    }
}