#include <cstdlib>          // Used for system()
#include <iostream>         // Used for cout
#include <string>
#include <unordered_map>    // Used for Maps
#include <variant>



class CommandLineFlags {
public:
    // Constructor
    CommandLineFlags() {
        flags["verbose"] = false;
        flags["help"] = false;
        flags["version"] = false;
        flags["output"] = "";   // Placeholder for output file path

        shortFlags['v'] = "verbose";
        shortFlags['h'] = "help";
        shortFlags['V'] = "version";
        shortFlags['o'] = "output"; // Short flag for output
    }

    // Method to parse command line arguments
    void parseArguments(int argc, char* argv[]) {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];

            // Check for long flags
            if (arg.substr(0, 2) == "--") {
                std::string longFlag = arg.substr(2);
                if (flags.find(longFlag) != flags.end()) {
                    if (longFlag == "output" && (i + 1 < argc)) {
                        flags[longFlag] = argv[++i];    // Set next argument as value
                    } else {
                        flags[longFlag] = true;
                    }
                }
            }

            // Check for short flags
            else if (arg.substr(0, 1) == "-") {
                std::string flagSeq = arg.substr(1);
                for (char shortFlag : flagSeq) {
                    if (shortFlags.find(shortFlag) != shortFlags.end()) {
                        if (shortFlag == 'o' && (i + 1 < argc)) {
                            flags[shortFlags[shortFlag]] = argv[++i];   // Set next argument as value
                        } else {
                            flags[shortFlags[shortFlag]] = true;
                        }
                    }
                }
                
            }
        }
    }

    // Accessor methods to check flags
    bool isVerbose() const {
        return std::get<bool>(flags.at("verbose"));
    }

    bool isHelp() const {
        return std::get<bool>(flags.at("help"));
    }

    bool isVersion() const {
        return std::get<bool>(flags.at("version"));
    }

    std::string getOutputPath() const {
        return std::get<std::string>(flags.at("output"));
    }

private:
    std::unordered_map<std::string, std::variant<bool, std::string>> flags; // Stores flags
    std::unordered_map<char, std::string> shortFlags;                       // Maps short flags to long flags
};







class ArgParser {
public:
    // Remove once a name is picked and them replace all instances of it.
    ArgParser(char* programName) {
        this->programName = programName;
    }

    void addShortFlag(const std::string& flag, const std::string& description) {
        shortFlags[flag] = description;
    }

    void addLongFlag(const std::string& flag, const std::string& description) {
        longFlags[flag] = description;
    }

    void parse(int argc, char* argv[]) {

    }

    void showHelp() const {
        std::cout << "This program opens Google Snake in your default browser.\n\n";
        std::cout << "Usage: " << this->programName << " [arguments]\n";

        for (const auto& [flag, description] : this->shortFlags) {
            std::cout << "\t" << flag << ": " << description << "\n";
        }

        for (const auto& [flag, description] : this->longFlags) {
            std::cout << "\t" << flag << ": " << description << "\n";
        }
    }

private:
    std::string programName;

    std::unordered_map<std::string, std::string> shortFlags;
    std::unordered_map<std::string, std::string> longFlags;
};


/*
    Working on Stuff for now. Learn more about commenting and documentation.
*/



int main(int argc, char* argv[]) {

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == "help" || argv[i] == "--help") {
            std::cout << "This program opens Google Snake in your default browser.\n\nUsage: " << std::endl;
        } else if (argv[i] == "-m" || argv[i] == "--map") {
            std::string map = argv[i+1];
        }
    }

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