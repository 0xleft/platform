#ifndef EADKPP_EXTENDED_H
#define EADKPP_EXTENDED_H

#include <math.h>
#include <eadk.h>
#include <eadkpp.h>
#include <vector>

// for drawing more complex shapes like circles and triangles

namespace EADK
{

namespace Utils {

// return the value between a and b at t
static inline float lerp(float a, float b, float t) {
    return a + (b - a) * t;
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

} // namespace Display
} // namespace EADK

#endif // EADKPP_EXTENDED_H