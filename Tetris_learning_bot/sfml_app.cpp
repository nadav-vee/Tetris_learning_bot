#include <SFML/Graphics.hpp>
#include "UserGame.h"

int main()
{
    srand(time(NULL));
    UserGame* u = new UserGame();
    u->Start();

    return 0;
}