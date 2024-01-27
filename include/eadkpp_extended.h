#ifndef EADKPP_EXTENDED_H
#define EADKPP_EXTENDED_H

#include <math.h>
#include <eadk.h>
#include <eadkpp.h>
#include <vector>

// for drawing more complex shapes like circles and triangles

namespace EADK
{
namespace Display
{

static void drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color)
{
    eadk_rect_t rect = {x, y, width, height};
    eadk_display_push_rect_uniform(rect, color);
};

static void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color)
{
    uint16_t dx = x2 - x1;
    uint16_t dy = y2 - y1;
    uint16_t steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x1;
    float y = y1;

    for (uint16_t i = 0; i <= steps; i++)
    {
        drawRect(x, y, 1, 1, color);
        x += xInc;
        y += yInc;
    }
};

static void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color, uint16_t width) {
    // but with width
    for (uint16_t i = 0; i < width; i++) {
        drawLine(x1, y1 + i, x2, y2 + i, color);
    }
};

static void drawCircle(uint16_t x, uint16_t y, uint16_t radius, Color color, bool fill = false) {
    uint16_t x0 = 0;
    uint16_t y0 = radius;
    uint16_t d = 3 - 2 * radius;
    if (fill) {
        while (y0 >= x0) // only formulate 1/8 of circle
        {
            drawLine(x - x0, y - y0, x + x0, y - y0, color);
            drawLine(x - y0, y - x0, x + y0, y - x0, color);
            drawLine(x - x0, y + y0, x + x0, y + y0, color);
            drawLine(x - y0, y + x0, x + y0, y + x0, color);
            if (d < 0) {
                d += 4 * x0++ + 6;
            } else {
                d += 4 * (x0++ - y0--) + 10;
            }
        }
    } else {
        while (y0 >= x0) // only formulate 1/8 of circle
        {
            drawRect(x + x0, y + y0, 1, 1, color);
            drawRect(x + y0, y + x0, 1, 1, color);
            drawRect(x + y0, y - x0, 1, 1, color);
            drawRect(x + x0, y - y0, 1, 1, color);
            drawRect(x - x0, y - y0, 1, 1, color);
            drawRect(x - y0, y - x0, 1, 1, color);
            drawRect(x - y0, y + x0, 1, 1, color);
            drawRect(x - x0, y + y0, 1, 1, color);
            if (d < 0) {
                d += 4 * x0++ + 6;
            } else {
                d += 4 * (x0++ - y0--) + 10;
            }
        }
    }
};

static void drawCircle(uint16_t x, uint16_t y, uint16_t radius, Color color, uint16_t width) {
    // but with width
    for (uint16_t i = 0; i < width; i++) {
        drawCircle(x, y, radius + i, color);
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

static void drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color, bool fill)
{
    if (fill) {
        for (uint16_t i = 0; i < height; i++) {
            drawLine(x, y + i, x + width, y + i, color);
        }
    } else {
        drawRect(x, y, width, height, color);
    }
};

static void clear(Color color)
{
    drawRect(0, 0, Screen::Width, Screen::Height, color);
};

} // namespace Display
} // namespace EADK

#endif // EADKPP_EXTENDED_H