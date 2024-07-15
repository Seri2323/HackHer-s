#pragma once
#include "../defines.h"
#include <string>
#include <vector>
#include <pybind11/embed.h>

class DataCard
{
public:
    DataCard(const std::string& saveFolder);
    std::vector<std::string> generateDataCard();

private:
    std::string saveFolder;
    void initializePython();
    void initializeAI();

    static bool pythonInitialized;
    static pybind11::scoped_interpreter guard;
    pybind11::object aiInstance;

    unsigned int generatedCardCount = 0;
    unsigned int humanMadeCardCount = 0;
    
    std::vector<std::vector<std::string>> humanMadeCards = {
        {"Party Bibes - Femme Fatale", "Red Cocktail Dress", "RedDress.png"},
        {"Relaxed - Street Wear", "Blue Top", "Blue tshirt.png"},
        {"Casual yet Chic", "Denim Dress", "Stuti_Puti_2.png"},
        {"French Chic", "Cotton Dress", "Stuti_Puti_3.png"},
        {"Old Money Vibes", "White Shirt", "White_Shirt.png"},
        {"BadAss Vibes", "Blue Vest", "Untitled2.png"}
    };
};
