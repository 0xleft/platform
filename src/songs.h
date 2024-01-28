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
    const char* notes = "";

    public:
        Song() {
            this->name = "NONE";
            this->length = 0;
            this->speed = 1;
            this->notes = "";
        }

        Song(const char* name, int length, int speed, const char* notes) {
            this->name = name;
            this->length = length;
            this->speed = speed;
            this->notes = notes;
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

        const char* getNotes() {
            return this->notes;
        }
};

class SongManager {
    private:
        Song songs[3] = {
            Song("SONG 1", 0, 0, "1"),
            Song("SONG 2", 0, 0, "2"),
            Song("SONG 3", 0, 0, "3")
        };

        int songCount = 3;
        Song selectedSong;
        int selectedSongIndex = 0;

    public:
        SongManager() {
            this->selectedSong = this->songs[0];
        }

        void drawSong(uint16_t x, uint16_t y, int index) {
            EADK::Display::drawString(x, y, 2, getSong(index).getName(), Black, index == this->selectedSongIndex ? LightBlue : White, 1, 2, false);
        }

        // draw selected the one before and the one after
        void drawSongList() {
            this->drawSong(20, EADK::Screen::Height / 2 - 20, this->selectedSongIndex - 1);
            this->drawSong(20, EADK::Screen::Height / 2 + 0, this->selectedSongIndex);
            this->drawSong(20, EADK::Screen::Height / 2 + 20, this->selectedSongIndex + 1);
        }

        int getSongCount() { return this->songCount; }
        Song getSelectedSong() { return this->selectedSong; }
        int getSelectedSongIndex() { return this->selectedSongIndex; }

        void setSelectedSong(int index) {
            if (index < 0) {
                index = this->songCount - 1;
            } else if (index >= this->songCount) {
                index = 0;
            }
            this->selectedSongIndex = index;
            this->selectedSong = this->songs[index];
        }
        Song getSong(int index) {
            if (index < 0) {
                index = this->songCount - 1;
            } else if (index >= this->songCount) {
                index = 0;
            }
            return this->songs[index];
        }
};

} // namespace songs
} // namespace platform

#endif