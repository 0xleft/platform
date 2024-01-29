#ifndef EADKPP_EXTENDED_H
#define EADKPP_EXTENDED_H

#include <math.h>
#include <eadk.h>
#include <eadkpp.h>
#include <vector>
// include sprintf
#include <stdio.h>
#include <string.h>

// for drawing more complex shapes like circles and triangles

namespace EADK
{

namespace Utils {

// return the value between a and b at t
static inline float lerp(float a, float b, float t) {
    return a + (b - a) * t;
};

// return the value between a and b at t
// remember to delete the buffer after using this
static inline const char* numberToString(int number) {
    int numDigits = number == 0 ? 1 : static_cast<int>(std::log10(std::abs(number))) + 1;
    static char* buffer = nullptr;
    delete[] buffer; // delete the old buffer
    buffer = new char[numDigits + 1]; // allocate a new buffer
    sprintf(buffer, "%d", number);
    return buffer;
};

// remember to delete the buffer after using this
static inline const char* concatChars(const char* a, const char* b) {
    static char* buffer = nullptr;
    delete[] buffer;
    buffer = new char[strlen(a) + strlen(b) + 1];
    strcpy(buffer, a);
    strcat(buffer, b);
    return buffer;
};

} // namespace Utils

namespace Display
{

static void drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color)
{
    if (x + width > Screen::Width || y + height > Screen::Height) return;
    eadk_rect_t rect = {x, y, width, height};
    eadk_display_push_rect_uniform(rect, color);
};

static void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color)
{
    int16_t dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int16_t dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int16_t err = dx + dy, e2;

    while(true)
    {
        drawRect(x1, y1, 1, 1, color);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}

static void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color, uint16_t width) {
    // but with width
    for (uint16_t i = 0; i < width; i++) {
        drawLine(x1, y1 + i, x2, y2 + i, color);
    }
};

static void drawCircle(uint16_t x, uint16_t y, uint16_t radius, Color color, bool fill = false) {
    // https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
    if (fill) {
        for (uint16_t i = 0; i < radius; i++) {
            drawCircle(x, y, radius - i, color);
        }
    } else {
        int16_t f = 1 - radius;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * radius;
        int16_t x1 = 0;
        int16_t y1 = radius;

        drawRect(x, y + radius, 1, 1, color);
        drawRect(x, y - radius, 1, 1, color);
        drawRect(x + radius, y, 1, 1, color);
        drawRect(x - radius, y, 1, 1, color);

        while(x1 < y1)
        {
            if(f >= 0)
            {
                y1--;
                ddF_y += 2;
                f += ddF_y;
            }
            x1++;
            ddF_x += 2;
            f += ddF_x;

            drawRect(x + x1, y + y1, 1, 1, color);
            drawRect(x - x1, y + y1, 1, 1, color);
            drawRect(x + x1, y - y1, 1, 1, color);
            drawRect(x - x1, y - y1, 1, 1, color);
            drawRect(x + y1, y + x1, 1, 1, color);
            drawRect(x - y1, y + x1, 1, 1, color);
            drawRect(x + y1, y - x1, 1, 1, color);
            drawRect(x - y1, y - x1, 1, 1, color);
        }
    }
};

static void drawTriangle(uint16_t x, uint16_t y, uint16_t angle, uint16_t size, Color color, bool fill = false) {
    // angle is in degrees
    // todo
    float angleRad = angle * 3.14 / 180.0;
    float x1 = x + size * cos(angleRad);
    float y1 = y + size * sin(angleRad);
    float x2 = x + size * cos(angleRad + 2 * 3.14 / 3);
    float y2 = y + size * sin(angleRad + 2 * 3.14 / 3);
    float x3 = x + size * cos(angleRad + 4 * 3.14 / 3);
    float y3 = y + size * sin(angleRad + 4 * 3.14 / 3);
    if (fill) {
        drawLine(x, y, x1, y1, color);
        drawLine(x, y, x2, y2, color);
        drawLine(x, y, x3, y3, color);
    } else {
        drawLine(x1, y1, x2, y2, color);
        drawLine(x2, y2, x3, y3, color);
        drawLine(x3, y3, x1, y1, color);
    }
};

static void drawTriangle(uint16_t x, uint16_t y, uint16_t angle, uint16_t size, Color color, uint16_t width) {
    // but with width
    for (uint16_t i = 0; i < width; i++) {
        drawTriangle(x, y, angle, size + i, color);
    }
};

static void clear(Color color)
{
    drawRect(0, 0, Screen::Width, Screen::Height, color);
};

static void drawLetter(uint16_t x, uint16_t y, char letter, Color color, uint16_t size = 1) {
    // most amazing switch ever
    switch (letter) {
        case '1':
            drawLine(x + 10, y, x + 10, y + 10, color, size);
            break;
        case '2':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 10, y, x + 10, y + 5, color, size);
            drawLine(x + 10, y + 5, x, y + 5, color, size);
            drawLine(x, y + 5, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            break;
        case '3':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 10, y, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x, y + 10, color, size);
            drawLine(x, y + 5, x + 10, y + 5, color, size);
            break;
        case '4':
            drawLine(x, y, x, y + 5, color, size);
            drawLine(x, y + 5, x + 10, y + 5, color, size);
            drawLine(x + 10, y, x + 10, y + 10, color, size);
            break;
        case '5':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 5, color, size);
            drawLine(x, y + 5, x + 10, y + 5, color, size);
            drawLine(x + 10, y + 5, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x, y + 10, color, size);
            break;
        case '6':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x + 10, y + 5, color, size);
            drawLine(x + 10, y + 5, x, y + 5, color, size);
            break;
        case '7':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 10, y, x + 10, y + 10, color, size);
            break;
        case '8':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x + 10, y, color, size);
            drawLine(x + 10, y, x, y, color, size);
            drawLine(x + 10, y + 10, x, y + 10, color, size);
            drawLine(x, y + 5, x + 10, y + 5, color, size);
            break;
        case '9':
            drawLine(x, y, x + 10, y, color, size);
            // drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x + 10, y, color, size);
            drawLine(x + 10, y, x, y, color, size);
            drawLine(x + 10, y + 5, x, y + 5, color, size);
            drawLine(x, y, x, y + 5, color, size);
            break;
        case '0':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x + 10, y, color, size);
            drawLine(x + 10, y, x, y, color, size);
            drawLine(x + 10, y + 10, x, y + 10, color, size);
            break;
        case 'A':
            drawLine(x, y, x + 5, y + 10, color, size);
            drawLine(x + 5, y + 10, x + 10, y, color, size);
            drawLine(x + 2, y + 5, x + 8, y + 5, color, size);
            break;
        case 'B':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 10, y, x + 10, y + 5, color, size);
            drawLine(x + 10, y + 5, x, y + 5, color, size);
            drawLine(x, y + 5, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            break;
        case 'C':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            break;
        case 'D':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 10, y, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x, y + 10, color, size);
            break;
        case 'E':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 5, x + 10, y + 5, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            break;
        case 'F':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 5, x + 10, y + 5, color, size);
            break;
        case 'G':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x + 10, y + 5, color, size);
            break;
        case 'H':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x + 10, y, x + 10, y + 10, color, size);
            drawLine(x, y + 5, x + 10, y + 5, color, size);
            break;
        case 'I':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 5, y, x + 5, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            break;
        case 'J':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 5, y, x + 5, y + 10, color, size);
            drawLine(x, y + 10, x + 5, y + 10, color, size);
            break;
        case 'K':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 5, x + 10, y, color, size);
            drawLine(x, y + 5, x + 10, y + 10, color, size);
            break;
        case 'L':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            break;
        case 'M':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x + 10, y, x + 10, y + 10, color, size);
            drawLine(x, y, x + 5, y + 5, color, size);
            drawLine(x + 10, y, x + 5, y + 5, color, size);
            break;
        case 'N':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x + 10, y, x + 10, y + 10, color, size);
            drawLine(x, y, x + 10, y + 10, color, size);
            break;
        case 'O':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x + 10, y, color, size);
            break;
        case 'P':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 10, y, x + 10, y + 5, color, size);
            drawLine(x + 10, y + 5, x, y + 5, color, size);
            break;
        case 'Q':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x + 10, y, color, size);
            drawLine(x + 5, y + 5, x + 10, y + 10, color, size);
            break;
        case 'R':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 10, y, x + 10, y + 5, color, size);
            drawLine(x + 10, y + 5, x, y + 5, color, size);
            drawLine(x, y + 5, x + 10, y + 10, color, size);
            break;
        case 'S':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x, y, x, y + 5, color, size);
            drawLine(x, y + 5, x + 10, y + 5, color, size);
            drawLine(x + 10, y + 5, x + 10, y + 10, color, size);
            drawLine(x + 10, y + 10, x, y + 10, color, size);
            break;
        case 'T':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 5, y, x + 5, y + 10, color, size);
            break;
        case 'U':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x + 10, y, x + 10, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            break;
        case 'V':
            drawLine(x, y, x + 5, y + 10, color, size);
            drawLine(x + 5, y + 10, x + 10, y, color, size);
            break;
        case 'W':
            drawLine(x, y, x, y + 10, color, size);
            drawLine(x + 10, y, x + 10, y + 10, color, size);
            drawLine(x, y + 10, x + 5, y + 5, color, size);
            drawLine(x + 10, y + 10, x + 5, y + 5, color, size);
            break;
        case 'X':
            drawLine(x, y, x + 10, y + 10, color, size);
            drawLine(x + 10, y, x, y + 10, color, size);
            break;
        case 'Y':
            drawLine(x, y, x + 5, y + 5, color, size);
            drawLine(x + 10, y, x + 5, y + 5, color, size);
            drawLine(x + 5, y + 5, x + 5, y + 10, color, size);
            break;
        case 'Z':
            drawLine(x, y, x + 10, y, color, size);
            drawLine(x + 10, y, x, y + 10, color, size);
            drawLine(x, y + 10, x + 10, y + 10, color, size);
            break;
        case ' ':
            break;
    }
};

static void adjustCoordsString(uint16_t x, uint16_t y, uint16_t spacing, const char* string, uint16_t* xOut, uint16_t* yOut) {
    uint16_t i = 0;
    while (string[i] != '\0') {
        i++;
    }
    *xOut = x - i * (10 + spacing) / 2;
    *yOut = y - 5;
};

static void drawString(uint16_t x, uint16_t y, uint16_t spacing, const char* string, Color color, uint16_t size = 1) {
    uint16_t i = 0;
    while (string[i] != '\0') {
        drawLetter(x + i * (10 + spacing), y, string[i], color, size);
        i++;
    }
};

static void drawString(uint16_t x, uint16_t y, uint16_t spacing, const char* string, Color color, Color backGroundColor, uint16_t size = 1, int padding = 2, bool adjustCoords = true) {
    // adjust coords
    uint16_t xOut = x;
    uint16_t yOut = y;
    if (adjustCoords) adjustCoordsString(x, y, spacing, string, &xOut, &yOut);

    uint16_t i = 0;
    while (string[i] != '\0') {
        i++;
    }
    drawRect(xOut - padding, yOut - padding, i * (10 + spacing) + padding * 2, 10 + padding * 2, backGroundColor);
    i = 0;
    while (string[i] != '\0') {
        drawLetter(xOut + i * (10 + spacing), yOut, string[i], color, size);
        i++;
    }
};

} // namespace Display
} // namespace EADK

#endif // EADKPP_EXTENDED_H