#ifndef UI_H
#define UI_H

#include <string>

class DrawEngine;

/**
  * UI class hopefully something useful.
  * Now provides 2D text drawing facilities.
  */
class UI
{
private:
    UI();
    UI(const UI&);
    ~UI();
    UI& operator=(const UI&);

public:
    static UI* instance();

    void update(DrawEngine& engine);

private:
    static UI* m_instance;
};

#endif // UI_H
