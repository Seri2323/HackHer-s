#include "dataCard.h"
#include <iostream>
#include <pybind11/embed.h> // everything needed for embedding
#include <pybind11/pybind11.h>
#include <filesystem>

namespace py = pybind11;

py::scoped_interpreter DataCard::guard{};

DataCard::DataCard(const std::string& saveFolder) : saveFolder(saveFolder) 
{
    initializeAI();
    humanMadeCardCount=humanMadeCards.size();
}


void DataCard::initializeAI() 
{
    py::module aiModule = py::module::import("AI");
    py::object aiClass = aiModule.attr("AI");
    aiInstance = aiClass(saveFolder);
    std::cout << "AI initialized" << std::endl;
}

std::vector<std::string> DataCard::generateDataCard() 
{
    ++generatedCardCount;
    if (generatedCardCount <= humanMadeCardCount) 
    {
        return humanMadeCards[generatedCardCount - 1];
    }
    try 
    {
     
        py::object result = aiInstance.attr("runAll")(PROMPT, generatedCardCount);
        return result.cast<std::vector<std::string>>();
    } 
    catch (const py::error_already_set& e) 
    {
        std::cerr << e.what() << std::endl;
        return humanMadeCards[generatedCardCount - 1 % humanMadeCardCount];
    }
}
