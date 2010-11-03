#include "UI.h"
#ifdef WIN32
#include <windows.h>
#endif

#include "Point2d.h"
#include "Logging.h"
#include "DrawEngine.h"

#include <SDL.h>

#include <GL/gl.h>

UI* UI::m_instance = 0;

UI::UI()
{
	this->m_srequest="";
}

UI::~UI()
{

}

UI* UI::instance()
{
    /// @todo Make thread safe
    if( !m_instance )
    {
        m_instance = new UI();
    }
    return m_instance;
}

void UI::update(DrawEngine& engine)
{
    engine.renderText("jeshmup ver:0.1.81", Point2d(5,5));
	engine.renderText(m_instance->m_srequest, Point2d(5, 560));
}

