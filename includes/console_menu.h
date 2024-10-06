#ifndef _console_menu
#define _console_menu

#include<string>
#include<map>

using namespace std;

class ConsoleMenu {
        private:
        map<string, string>menuOptionMap; // store all the options to display.
        int longestStringName;
        int longestStringDescriptor;
        string askSentence;
        string welcomeSentence;
        void printChar(int amount, char charPar);
    public:
        ConsoleMenu();
        void AddMenuOptions(string name, string descriptor);
        void RemoveMenuOption(string name);
        void DisplayMenu();
        void SetAskSentence(string sentence); // ask after the menu prints for you to input something
        void SetWelcomeSentence(string sentence);
        void DisplayWelcomeMessage();
};

#endif // !_console_menu
