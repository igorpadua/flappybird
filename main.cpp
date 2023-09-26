#include "flappy.hpp"

int main(int argc, char** argv)
{
    auto flappy = std::make_unique<Flappy>();
    flappy->run();

    return 0;
}
