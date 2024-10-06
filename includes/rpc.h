#ifndef _rpc
#define _rpc

#include <string>
#include <vector>

using namespace std;

class RPC {
    private:
        vector<int> memory;
        int difficulty;
        int nextMove;
        double playerChanceOfRock;
        double playerChanceOfPaper;
        double playerChanceOfScissors;
    public:
        RPC();
        void setDifficulty(int level);
        int getDifficulty();
        void clearMemory();
        void takeInput(int moveTaken);
        int getWinState();
        void DisplayOutput();
        void makeNextMove();
};

#endif // !_rpc