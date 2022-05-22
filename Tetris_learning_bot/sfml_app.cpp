#include <SFML/Graphics.hpp>
#include "UserGame.h"
#include "AIGame.h"

int main()
{
    srand(unsigned int(time(NULL)));
    AssetManager manager;
    // UserGame* u = new UserGame();
    // u->Start();
    AIGame* AIG = new AIGame();
    AIG->Start();

    return 0;
}