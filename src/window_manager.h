#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include <eadk.h>
#include <eadkpp.h>
#include <eadkpp_extended.h>
#include <palette.h>
#include "level.h"
#include "songs.h"

namespace platform {
namespace windows {

enum class WindowType {
    SONG,
    WELCOME,
    SELECT_SONG,
    SONG_END,
};

class WindowManager {
    private:
        songs::SongManager* songManager = new songs::SongManager();

        void runWelcomeWindow() {
            EADK::Display::clear(White);
            EADK::Display::drawString(EADK::Screen::Width / 2, EADK::Screen::Height / 2, 3, "WELCOME", Black, White);
            EADK::Display::drawString(EADK::Screen::Width / 2, EADK::Screen::Height / 2 + 20, 2, "PRESS EXE TO CONTINUE", Black, White);

            while (true) {
                EADK::Keyboard::State kbd = EADK::Keyboard::scan();
                if (kbd.keyDown(EADK::Keyboard::Key::EXE)) {
                    EADK::Display::clear(White);
                    EADK::Display::drawString(EADK::Screen::Width / 2, EADK::Screen::Height / 2, 3, "LOADING", Black, White);
                    EADK::Timing::msleep(300);
                    break;
                }
                if (kbd.keyDown(EADK::Keyboard::Key::Back)) {
                    return;
                }
                EADK::Timing::msleep(10);
            }

            runWindow<WindowType::SELECT_SONG>();
        }

        void runSelectSongWindow() {
            EADK::Display::clear(White);
            songManager->drawSongList();

            while (true) {
                EADK::Keyboard::State kbd = EADK::Keyboard::scan();
                if (kbd.keyDown(EADK::Keyboard::Key::Up)) {
                    EADK::Display::clear(White);
                    songManager->setSelectedSong(songManager->getSelectedSongIndex() - 1);
                    songManager->drawSongList();
                }
                if (kbd.keyDown(EADK::Keyboard::Key::Down)) {
                    EADK::Display::clear(White);
                    songManager->setSelectedSong(songManager->getSelectedSongIndex() + 1);
                    songManager->drawSongList();
                }
                if (kbd.keyDown(EADK::Keyboard::Key::EXE)) {
                    EADK::Display::clear(White);
                    EADK::Display::drawString(EADK::Screen::Width / 2, EADK::Screen::Height / 2, 3, "LOADING...", Black, White);
                    EADK::Timing::msleep(1000);
                    break;
                }
                if (kbd.keyDown(EADK::Keyboard::Key::Back)) {
                    return;
                }
                EADK::Timing::msleep(100);
            }

            runWindow<WindowType::SONG>();
        }

        void runSongWindow() {
            EADK::Display::clear(White);
            
            platform::Level level = platform::Level(songManager->getSelectedSong()->getSpeed(), songManager->getSelectedSong()->getLength());
            for (Button* button : songManager->getSelectedSong()->getNotes()) {
                level.addButton(button);
            }
            level.setTime(songManager->getSelectedSong()->getStart());
            level.play();

            runLevelEndWindow(level);
        }

        void runLevelEndWindow(platform::Level& level) {
            EADK::Display::clear(White);
            EADK::Display::drawString(EADK::Screen::Width / 2, EADK::Screen::Height / 2, 3, "LEVEL END", Black, White);
            // score
            char* score = EADK::Utils::numberToString(level.getPoints());
            char* full = EADK::Utils::concatChars("POINTS: ", score);
            EADK::Display::drawString(EADK::Screen::Width / 2, EADK::Screen::Height / 2 + 20, 2, full, Black, White);
            delete[] score;
            delete[] full;

            EADK::Timing::msleep(500);

            while (true) {
                EADK::Keyboard::State kbd = EADK::Keyboard::scan();
                if (kbd.keyDown(EADK::Keyboard::Key::Back)) {
                    EADK::Display::clear(White);
                    EADK::Display::drawString(EADK::Screen::Width / 2, EADK::Screen::Height / 2, 3, "LOADING...", Black, White);
                    EADK::Timing::msleep(1000);
                    break;
                }
                EADK::Timing::msleep(10);
            }

            runWindow<WindowType::SELECT_SONG>();
        }

    public:
        WindowManager() {};

        template<WindowType type>
        void runWindow() {
            switch (type) {
                case WindowType::SONG:
                    runSongWindow();
                    break;
                case WindowType::WELCOME:
                    runWelcomeWindow();
                    break;
                case WindowType::SELECT_SONG:
                    runSelectSongWindow();
                    break;
            }
        }

        ~WindowManager() {
            delete songManager;
        }
};

}
}

#endif