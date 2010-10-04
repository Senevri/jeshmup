#ifndef UI_H
#define UI_H

class Point2d;
class SDL_Surface;

#include <string>
#include <SDL_ttf.h>

/**
  * UI class hopefully something useful.
  * Now provides 2D text drawing facilities.
  */
class UI
{
private:
    UI();
    ~UI();

public:
    static UI* instance();
    bool initialize();

    static void drawText(const std::string& text, const Point2d& position);

private:
    bool initializeTTF();

private:
    TTF_Font *m_uiFont;
};

#endif // UI_H
