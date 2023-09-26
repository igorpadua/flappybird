#include "flappy.hpp"

int main(int argc, char** argv)
{
    std::srand(std::time(0));

    auto flappy = std::make_unique<Flappy>();
    flappy->run();

    return 0;
}
