#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "graph_module.h"

using namespace sf;

int picturePerfect()
{
    Music loading_music;
    loading_music.openFromFile("fraer.wav");

    loading_music.play();

    RenderWindow window(VideoMode(540, 480), "BOAB");

    return 0;
}
