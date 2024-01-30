#ifndef SONGS_H
#define SONGS_H

#include <string>
#include <eadk.h>
#include <eadkpp.h>
#include <eadkpp_extended.h>
#include "palette.h"

namespace platform {
namespace songs {
    
class Song {
    const char* name;
    int length = 0;
    int speed = 1;
    int start = 0;
    std::vector<Button*> notes = {};

    public:
        Song() {
            this->name = "NONE";
            this->length = 0;
            this->speed = 1;
            this->notes = {};
        }

        Song(const char* name, int start, int length, int speed, std::vector<Button*> notes) {
            this->name = name;
            this->length = length;
            this->speed = speed;
            this->notes = notes;
            this->start = start;
        }

        int getStart() {
            return this->start;
        }

        const char* getName() {
            return this->name;
        }

        int getLength() {
            return this->length;
        }

        int getSpeed() {
            return this->speed;
        }

        std::vector<Button*> getNotes() {
            return this->notes;
        }
};

class SongManager {
    private:
        std::vector<Song*> songs = {
            new Song("HIGH HOPES", 0, 0, 0, {}),
            new Song("NONE", 0, 0, 0, {}),
            new Song("NONE", 0, 0, 0, {}),
        };

        int songCount = 3;
        int selectedSongIndex = 0;

    public:
        void drawSong(uint16_t x, uint16_t y, int index) {
            EADK::Display::drawString(x, y, 2, getSong(index)->getName(), Black, index == this->selectedSongIndex ? LightBlue : White, 1, 2, false);
        }

        // draw selected the one before and the one after
        void drawSongList() {
            this->drawSong(20, EADK::Screen::Height / 2 - 40, this->selectedSongIndex - 2);
            this->drawSong(20, EADK::Screen::Height / 2 - 20, this->selectedSongIndex - 1);
            this->drawSong(20, EADK::Screen::Height / 2 + 0, this->selectedSongIndex);
            this->drawSong(20, EADK::Screen::Height / 2 + 20, this->selectedSongIndex + 1);
            this->drawSong(20, EADK::Screen::Height / 2 + 40, this->selectedSongIndex + 2);
        }

        int getSongCount() { return this->songCount; }
        Song* getSelectedSong() { return getSong(this->selectedSongIndex); }
        int getSelectedSongIndex() { return this->selectedSongIndex; }

        void setSelectedSong(int index) {
            if (index < 0) {
                index = this->songCount - 1;
            } else if (index >= this->songCount) {
                index = 0;
            }
            this->selectedSongIndex = index;
        }
        Song* getSong(int index) {
            if (index < 0) {
                index = this->songCount - 1;
            } else if (index >= this->songCount) {
                index = 0;
            }
            return this->songs[index];
        }

        ~SongManager() {
            for (Song* song : this->songs) {
                delete song;
            }
        }
};

} // namespace songs
} // namespace platform

#endif