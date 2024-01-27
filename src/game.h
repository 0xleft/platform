#ifndef GAME_H
#define GAME_H

#include <eadkpp_extended.h>
#include <vector>
#include <palette.h>

namespace platform
{
    enum class Row {
        FIRST,
        SECOND,
        THIRD,
        FOURTH,
    };

    enum class DrawType {
        CLEAR,
        DRAW,
    };

    class Button {
    private:
        int toPressTime; // time at which the button should be pressed
        Row row;
        bool clicked = false;

        template<DrawType dt, Row row>
        void drawRow(int relativeTime, int speed) {
            float t = (float)relativeTime / EADK::Screen::Height;
            if (dt == DrawType::CLEAR) {
                t = (float)(relativeTime - speed) / EADK::Screen::Height;
                relativeTime -= speed;
            }

            float lerpedX = 0;
            float lerpedWidth = EADK::Utils::lerp(10, 50, t);
            float lerpedHeight = EADK::Utils::lerp(8, 15, t);

            switch (row) {
                case Row::FIRST:
                    lerpedX = EADK::Utils::lerp(EADK::Screen::Width / 2 - 35, EADK::Screen::Width / 2 - 175, t);
                    break;
                case Row::SECOND:
                    lerpedX = EADK::Utils::lerp(EADK::Screen::Width / 2 - 15, EADK::Screen::Width / 2 - 75, t);
                    break;
                case Row::THIRD:
                    lerpedX = EADK::Utils::lerp(EADK::Screen::Width / 2 + (15 - lerpedWidth), EADK::Screen::Width / 2 + (75 - lerpedWidth), t);
                    break;
                case Row::FOURTH:
                    lerpedX = EADK::Utils::lerp(EADK::Screen::Width / 2 + (35 - lerpedWidth), EADK::Screen::Width / 2 + (175 - lerpedWidth), t);
                    break;
            }

            EADK::Display::drawRect(lerpedX, relativeTime, lerpedWidth, lerpedHeight, dt == DrawType::CLEAR ? White : isClicked() ? Green : Black); // amazing
        }
    public:
        Button(int toPressTime, Row row) {
            this->toPressTime = toPressTime;
            this->row = row;
        }

        int getToPressTime() {
            return toPressTime;
        }

        Row getRow() {
            return row;
        }

        void click() {
            clicked = true;
        }

        bool isClicked() {
            return clicked;
        }

        void draw(int time, int speed) {
            // domain of x: [0, EADK::Screen::Height]
            int relativeTime = time - toPressTime;
            if (relativeTime > EADK::Screen::Height || relativeTime < 0) {
                return;
            }

            switch (row) {
                case Row::FIRST:
                    drawRow<DrawType::CLEAR, Row::FIRST>(relativeTime, speed);
                    drawRow<DrawType::DRAW, Row::FIRST>(relativeTime, speed);
                    break;
                case Row::SECOND:
                    drawRow<DrawType::CLEAR, Row::SECOND>(relativeTime, speed);
                    drawRow<DrawType::DRAW, Row::SECOND>(relativeTime, speed);
                    break;
                case Row::THIRD:
                    drawRow<DrawType::CLEAR, Row::THIRD>(relativeTime, speed);
                    drawRow<DrawType::DRAW, Row::THIRD>(relativeTime, speed);
                    break;
                case Row::FOURTH:
                    drawRow<DrawType::CLEAR, Row::FOURTH>(relativeTime, speed);
                    drawRow<DrawType::DRAW, Row::FOURTH>(relativeTime, speed);
                    break;
            }
        }
    };

    static inline void drawLines() {
        // middle screen - 20 px
        EADK::Display::drawLine(EADK::Screen::Width / 2 + 20, 0, EADK::Screen::Width / 2 + 100, EADK::Screen::Height, Black);
        EADK::Display::drawLine(EADK::Screen::Width / 2 + 40, 0, EADK::Screen::Width / 2 + 200, EADK::Screen::Height, Black);
        EADK::Display::drawLine(EADK::Screen::Width / 2 - 100, EADK::Screen::Height, EADK::Screen::Width / 2 - 20, 0, Black);
        EADK::Display::drawLine(EADK::Screen::Width / 2 - 200, EADK::Screen::Height, EADK::Screen::Width / 2 - 40, 0, Black);
        EADK::Display::drawLine(EADK::Screen::Width / 2, 0, EADK::Screen::Width / 2, EADK::Screen::Height, Black);
    }

    class Game {
    private:
        std::vector<Button> buttons;
        int maxTime = 0;
        int time = 0;
        int speed = 1;
        int points = 0;
        int streak = 0;
    public:
        Game(int speed, int maxTime) {
            this->speed = speed;
            this->maxTime = maxTime;
        }

        void pressButton(Row row) {
            for (Button button : buttons) {
                if (button.getRow() == row && (button.getToPressTime() - time < 10 && button.getToPressTime() - time > -10)) {
                    button.click();
                    streak++;
                    points += 100; // debatable
                }
            }
        }

        void addButton(Button button) {
            buttons.push_back(button);
        }
        void setSpeed(int speed) {
            this->speed = speed;
        }
        bool isOver() {
            return time > maxTime;
        }
        int getTime() {
            return time;
        }

        void step() {
            time += speed;
            for (Button button : buttons) {
                button.draw(time, speed);
            }

            // check for passed buttons
            // for (Button button : buttons) {
            //     if (button.getToPressTime() - time < -10 && !button.isClicked()) {
            //         streak = 0;
            //     }
            // }
// 
            // // remove passed buttons
            // for (int i = 0; i < buttons.size(); i++) {
            //     if (buttons[i].getToPressTime() - time < -10 || buttons[i].getToPressTime() - time > 10) {
            //         buttons.erase(buttons.begin() + i);
            //         i--;
            //     }
            // }
        }

        void play() {
            while (!isOver()) {
                step();
                EADK::Keyboard::State kbd = EADK::Keyboard::scan();
                if (kbd.keyDown(EADK::Keyboard::Key::Seven)) {
                    pressButton(platform::Row::FIRST);
                }
                if (kbd.keyDown(EADK::Keyboard::Key::Eight)) {
                    pressButton(platform::Row::SECOND);
                }
                if (kbd.keyDown(EADK::Keyboard::Key::Nine)) {
                    pressButton(platform::Row::THIRD);
                }
                if (kbd.keyDown(EADK::Keyboard::Key::LeftParenthesis)) {
                    pressButton(platform::Row::FOURTH);
                }
                if (kbd.keyDown(EADK::Keyboard::Key::EXE)) {
                    return;
                }

                EADK::Timing::msleep(10);
	        }
        }
    };

} // namespace platform

#endif // GAME_H