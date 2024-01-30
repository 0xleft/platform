#ifndef Level_H
#define Level_H

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

enum class ClickType {
    RIGHT,
    WRONG,
    NONE,
};

class Button {
private:
    int toPressTime; // time at which the button should be pressed
    Row row;
    ClickType clicked = ClickType::NONE;

    template<DrawType dt, Row row>
    void drawRow(int relativeTime, int speed) {
        float t = (float)relativeTime / EADK::Screen::Height;
        if (dt == DrawType::CLEAR) {
            t = (float)(relativeTime - speed) / EADK::Screen::Height;
            relativeTime -= speed;
        }

        float lerpedX = 0;
        float lerpedWidth = EADK::Utils::lerp(10, 20, t);
        float lerpedHeight = EADK::Utils::lerp(8, 10, t);

        switch (row) {
            case Row::FIRST:
                lerpedX = EADK::Utils::lerp(EADK::Screen::Width / 2 - 35, EADK::Screen::Width / 2 - 120, t);
                break;
            case Row::SECOND:
                lerpedX = EADK::Utils::lerp(EADK::Screen::Width / 2 - 15, EADK::Screen::Width / 2 - 45, t);
                break;
            case Row::THIRD:
                lerpedX = EADK::Utils::lerp(EADK::Screen::Width / 2 + (15 - lerpedWidth), EADK::Screen::Width / 2 + (45 - lerpedWidth), t);
                break;
            case Row::FOURTH:
                lerpedX = EADK::Utils::lerp(EADK::Screen::Width / 2 + (35 - lerpedWidth), EADK::Screen::Width / 2 + (120 - lerpedWidth), t);
                break;
        }

        EADK::Display::drawRect(lerpedX, relativeTime, lerpedWidth, lerpedHeight, dt == DrawType::CLEAR ? White : (getClickColor(this->clicked))); // amazing
    }

    static EADK::Color getClickColor(ClickType clickType) {
        switch (clickType) {
            case ClickType::RIGHT:
                return Green;
            case ClickType::WRONG:
                return Red;
            case ClickType::NONE:
                return Black;
        }
    };
public:
    Button(int toPressTime, Row row) {
        this->toPressTime = toPressTime;
        this->row = row;
    }

    Button(int toPressTime, int row) {
        this->toPressTime = toPressTime;
        switch (row) {
            case 1:
                this->row = Row::FIRST;
                break;
            case 2:
                this->row = Row::SECOND;
                break;
            case 3:
                this->row = Row::THIRD;
                break;
            case 4:
                this->row = Row::FOURTH;
                break;
        }
    }

    int getToPressTime() {
        return toPressTime;
    }

    Row getRow() {
        return row;
    }

    void click(ClickType clickType) {
        clicked = clickType;
    }

    ClickType getClickedType() {
        return clicked;
    }

    void clear(int time, int speed) {
        int relativeTime = time - toPressTime;
        if (relativeTime > EADK::Screen::Height || relativeTime < 0) {
            return;
        }

        switch (row) {
            case Row::FIRST:
                drawRow<DrawType::CLEAR, Row::FIRST>(relativeTime, speed);
                break;
            case Row::SECOND:
                drawRow<DrawType::CLEAR, Row::SECOND>(relativeTime, speed);
                break;
            case Row::THIRD:
                drawRow<DrawType::CLEAR, Row::THIRD>(relativeTime, speed);
                break;
            case Row::FOURTH:
                drawRow<DrawType::CLEAR, Row::FOURTH>(relativeTime, speed);
                break;
        }
    }

    void draw(int time, int speed) {
        // domain of x: [0, EADK::Screen::Height]
        int relativeTime = time - toPressTime;
        if (relativeTime > EADK::Screen::Height || relativeTime < 0) {
            return;
        }

        switch (row) {
            case Row::FIRST:
                drawRow<DrawType::DRAW, Row::FIRST>(relativeTime, speed);
                break;
            case Row::SECOND:
                drawRow<DrawType::DRAW, Row::SECOND>(relativeTime, speed);
                break;
            case Row::THIRD:
                drawRow<DrawType::DRAW, Row::THIRD>(relativeTime, speed);
                break;
            case Row::FOURTH:
                drawRow<DrawType::DRAW, Row::FOURTH>(relativeTime, speed);
                break;
        }
    }
};

static inline void drawLines() {
    // middle screen - 20 px
    EADK::Display::drawLine(EADK::Screen::Width / 2 + 20, 0, EADK::Screen::Width / 2 + 90, EADK::Screen::Height, Black);
    EADK::Display::drawLine(EADK::Screen::Width / 2 + 40, 0, EADK::Screen::Width / 2 + 150, EADK::Screen::Height, Black);
    EADK::Display::drawLine(EADK::Screen::Width / 2 - 90, EADK::Screen::Height, EADK::Screen::Width / 2 - 20, 0, Black);
    EADK::Display::drawLine(EADK::Screen::Width / 2 - 150, EADK::Screen::Height, EADK::Screen::Width / 2 - 40, 0, Black);
    EADK::Display::drawLine(EADK::Screen::Width / 2, 0, EADK::Screen::Width / 2, EADK::Screen::Height, Black);

    // horizontal
    EADK::Display::drawLine(0, EADK::Screen::Height - 30, EADK::Screen::Width, EADK::Screen::Height - 30, Black);
}

class Level {
private:
    std::vector<Button*> firstRowButtons;
    std::vector<Button*> secondRowButtons;
    std::vector<Button*> thirdRowButtons;
    std::vector<Button*> fourthRowButtons;
    int maxTime = 0;
    int time = 0;
    int speed = 1;
    int points = 0;
    int streak = 0;
    Button* firstRowLastButton = nullptr;
    Button* secondRowLastButton = nullptr;
    Button* thirdRowLastButton = nullptr;
    Button* fourthRowLastButton = nullptr;
public:
    Level(int speed, int maxTime) {
        this->speed = speed;
        this->maxTime = maxTime;
    }

    template<Row row>
    void pressButton() {
        Button* button = nullptr;
        switch (row) {
            case Row::FIRST:
                button = firstRowLastButton;
                break;
            case Row::SECOND:
                button = secondRowLastButton;
                break;
            case Row::THIRD:
                button = thirdRowLastButton;
                break;
            case Row::FOURTH:
                button = fourthRowLastButton;
                break;
        }

        if (button == nullptr) {
            return;
        }

        int relativeTime = time - button->getToPressTime();
        if (button->getClickedType() == ClickType::NONE) {
            if (relativeTime > EADK::Screen::Height || relativeTime < 0) {
                return;
            }

            if (relativeTime > EADK::Screen::Height || relativeTime < EADK::Screen::Height - speed * 10 - 40) {
                button->click(ClickType::WRONG);
                streak = 0;
                drawScore();
                return;
            }

            button->click(ClickType::RIGHT);
            streak++;
            points += 100; // debatable
            drawScore();
        }
    }

    int getPoints() {
        return points;
    }

    void drawScore() {
        char* points_s = EADK::Utils::numberToString(this->points);
        char* points = EADK::Utils::concatChars("SCORE ", points_s);
        EADK::Display::drawString(10, 10, 3, points, Black, White, 1, 2, false);
        delete points_s;
        delete points;
    }

    void addButton(Button* button) {
        switch (button->getRow()) {
            case Row::FIRST:
                firstRowButtons.push_back(button);
                break;
            case Row::SECOND:
                secondRowButtons.push_back(button);
                break;
            case Row::THIRD:
                thirdRowButtons.push_back(button);
                break;
            case Row::FOURTH:
                fourthRowButtons.push_back(button);
                break;
        }
    }
    void setSpeed(int speed) {
        this->speed = speed;
    }
    bool isOver() {
        return time >= maxTime;
    }
    int getTime() {
        return time;
    }

    void setTime(int time) {
        this->time = time;
    }

    void step() {
        time += speed;
        int firstRowTimeLatest = 999999999;
        int secondRowTimeLatest = 999999999;
        int thirdRowTimeLatest = 999999999;
        int fourthRowTimeLatest = 999999999;

        for (Button* button : firstRowButtons) {
            button->clear(time, speed);
        }
        for (Button* button : secondRowButtons) {
            button->clear(time, speed);
        }
        for (Button* button : thirdRowButtons) {
            button->clear(time, speed);
        }
        for (Button* button : fourthRowButtons) {
            button->clear(time, speed);
        }

        for (Button* button : firstRowButtons) {
            button->draw(time, speed);
            if (button->getToPressTime() < firstRowTimeLatest) {
                firstRowTimeLatest = button->getToPressTime();
                firstRowLastButton = button;
            }
        }
        for (Button* button : secondRowButtons) {
            button->draw(time, speed);
            if (button->getToPressTime() < secondRowTimeLatest) {
                secondRowTimeLatest = button->getToPressTime();
                secondRowLastButton = button;
            }
        }
        for (Button* button : thirdRowButtons) {
            button->draw(time, speed);
            if (button->getToPressTime() < thirdRowTimeLatest) {
                thirdRowTimeLatest = button->getToPressTime();
                thirdRowLastButton = button;
            }
        }
        for (Button* button : fourthRowButtons) {
            button->draw(time, speed);
            if (button->getToPressTime() < fourthRowTimeLatest) {
                fourthRowTimeLatest = button->getToPressTime();
                fourthRowLastButton = button;
            }
        }

        // remove buttons that are out of screen and delete them
        for (int i = 0; i < firstRowButtons.size(); i++) {
            if (time - firstRowButtons[i]->getToPressTime() > EADK::Screen::Height) {
                delete firstRowButtons[i];
                firstRowButtons.erase(firstRowButtons.begin() + i);
                i--;
            }
        }

        for (int i = 0; i < secondRowButtons.size(); i++) {
            if (time - secondRowButtons[i]->getToPressTime() > EADK::Screen::Height) {
                delete secondRowButtons[i];
                secondRowButtons.erase(secondRowButtons.begin() + i);
                i--;
            }
        }

        for (int i = 0; i < thirdRowButtons.size(); i++) {
            if (time - thirdRowButtons[i]->getToPressTime() > EADK::Screen::Height) {
                delete thirdRowButtons[i];
                thirdRowButtons.erase(thirdRowButtons.begin() + i);
                i--;
            }
        }

        for (int i = 0; i < fourthRowButtons.size(); i++) {
            if (time - fourthRowButtons[i]->getToPressTime() > EADK::Screen::Height) {
                delete fourthRowButtons[i];
                fourthRowButtons.erase(fourthRowButtons.begin() + i);
                i--;
            }
        }
    }

    void play() {
        platform::drawLines();
        while (!isOver()) {
            step();
            EADK::Keyboard::State kbd = EADK::Keyboard::scan();
            if (kbd.keyDown(EADK::Keyboard::Key::Seven)) {
                pressButton<platform::Row::FIRST>();
            }
            if (kbd.keyDown(EADK::Keyboard::Key::Eight)) {
                pressButton<platform::Row::SECOND>();
            }
            if (kbd.keyDown(EADK::Keyboard::Key::Nine)) {
                pressButton<platform::Row::THIRD>();
            }
            if (kbd.keyDown(EADK::Keyboard::Key::LeftParenthesis)) {
                pressButton<platform::Row::FOURTH>();
            }
            if (kbd.keyDown(EADK::Keyboard::Key::EXE)) {
                break;
            }

            EADK::Timing::msleep(10);
        }
    }

    ~Level() {
        for (Button* button : firstRowButtons) {
            delete button;
        }
        for (Button* button : secondRowButtons) {
            delete button;
        }
        for (Button* button : thirdRowButtons) {
            delete button;
        }
        for (Button* button : fourthRowButtons) {
            delete button;
        }
    }
};
} // namespace platform

#endif // Level_H