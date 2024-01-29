#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <game.h>

namespace platform {
namespace loader {

class Loader {
    public:
        // notes format: toPressTime;Row,toPressTime;Row,
        // row is 1,2,3,4
        static std::vector<Button*> load(const char* string) {
            std::vector<Button*> buttons;
            std::string str = string;
            std::string delimiter = ",";
            size_t pos = 0;
            std::string token;
            while ((pos = str.find(delimiter)) != std::string::npos) {
                token = str.substr(0, pos);
                size_t pos2 = token.find(";");
                std::string time = token.substr(0, pos2);
                std::string row = token.substr(pos2 + 1, token.length());
                buttons.push_back(new Button(std::stoi(time), std::stoi(row)));
                str.erase(0, pos + delimiter.length());
            }
            return buttons;
        }
};

} // namespace loader
} // namespace platform

#endif