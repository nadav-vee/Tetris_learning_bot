#include <SFML/Graphics.hpp>
#include "UserGame.h"
#include "AIGame.h"

int main()
{
    srand(time(NULL));
    UserGame* u = new UserGame();
    u->Start();

    return 0;
}