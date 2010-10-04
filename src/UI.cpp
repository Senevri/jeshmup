#include "UI.h"
#include "Point2d.h"
#include "Logging.h"
#include "DrawEngine.h"

#include <SDL.h>

#include <GL/gl.h>

UI* UI::m_instance = 0;

UI::UI()
{

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
    engine.renderText("jeshmup ver:nnnn", Point2d(5,5));
}

