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
	void requestWrite(const std::string &s){ m_srequest = s; }

    void update(DrawEngine& engine);

private:
	std::string m_srequest;	
    static UI* m_instance;
};

#endif // UI_H
