#include "defines.h"
#include "dash/dash.h"
#include "mainScreen/mainScreen.h"
#include "startWindow/justForgeStarter.h"
#include <filesystem>
#include <string>

int main()
{
    // delete AI generated cards that is from number 4 and above
    int i = 4;
    while (true)
    {
        std::string path = "Stuti_Putti_" + std::to_string(i) + ".png";
        path = CLOTH_DATA_TEXTURE_DIR + path;

        if (std::filesystem::exists(path))
        {
            std::filesystem::remove(path);
            ++i;
        }
        else
        {
            break;
        }
    }

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Santra", sf::Style::Close);

    StartScreen startScreen(&window);
    while (startScreen.run());
    printf("Start screen closed\n");

    Dash dash(&window);
    while (dash.run());
    printf("Dash closed\n");

    MainScreen mainScreen(&window);
    mainScreen.run();
    printf("Main screen closed\n");

    return 0;
}
