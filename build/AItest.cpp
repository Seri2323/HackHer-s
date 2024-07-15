#include "../src/dataCard/dataCard.h"
#include <iostream>

int main() {
    std::string saveFolder = "../Assets/Textures/clothes/";
    std::string prompt = "Generate an image and description for a trendy jacket";

    DataCard dataCard(saveFolder);
    std::vector<std::string> result = dataCard.generateDataCard(prompt);

    if (!result.empty()) 
    {
        std::cout << "Gen-Z Bio: " << result[0] << std::endl;
        std::cout << "Name: " << result[1] << std::endl;
        std::cout << "Description: " << result[2] << std::endl;
    } else {
        std::cerr << "Failed to generate data card" << std::endl;
    }

    return 0;
}
