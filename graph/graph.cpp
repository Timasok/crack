#include "graph_module.h"

using namespace sf;

// int main()
// {}

int picturePerfect()
{
    Music loading_music;
    loading_music.openFromFile("fraer.wav");

    loading_music.play();

    RenderWindow window(VideoMode(540, 480), "BOAB");

    return 0;
}
