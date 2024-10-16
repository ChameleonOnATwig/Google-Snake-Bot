#include <cstdlib>  // Used for system()
#include <iostream> // Use for cout

int main() {
    // URL for Google Snake game
    std::string url = "https://snake.googlemaps.com/";

    std::cout << "Opening Google Snake in your web browser..." << std::endl;

    // Open the URL in the default web browser
    #ifdef _WIN32
        std::system(("start " + url).c_str());
    #elif __APPLE__
        std::system(("open " + url).c_str());
    #else
        std::system(("xdg-open " + url).c_str());
    #endif

    std::cout << "Successfully opened Google Snake in your web browser..." << std::endl;

    return 0;
}