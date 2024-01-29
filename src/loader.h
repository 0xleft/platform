#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include <string.h>
#include <iostream>

namespace platform {
namespace loader {

std::vector<const char*> split(const char* txt, char ch) {
    std::vector<const char*> strs;
    // strtok with buffer
    char* buf = new char[strlen(txt) + 1];
    strcpy(buf, txt);

    char* pch = strtok(buf, &ch);
    while (pch != NULL) {
        strs.push_back(pch);
        pch = strtok(NULL, &ch);
    }

    delete[] buf;
    return strs;
}

// "toPressTime;row,toPressTime;row,toPressTime;row,..."
static inline std::vector<Button*> load(const char* notes) {
    std::vector<Button*> buttons;

    std::vector<const char*> notesSplit = split(notes, ',');
    for (const char* note : notesSplit) {
        std::vector<const char*> noteSplit = split(note, ';');
        // int toPressTime = atoi(noteSplit[0]);
        // int row = atoi(noteSplit[1]);
        if (noteSplit.size() != 2) {
            std::cout << "Invalid note: " << note << std::endl;
            continue;
        }
        // buttons.push_back(new Button(toPressTime, row));
    }

    return buttons;
};

} // namespace loader
} // namespace platform

#endif