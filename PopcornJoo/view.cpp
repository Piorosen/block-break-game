#define GL_SILENCE_DEPRECATION

#include "view.h"
#include "application.h"

#if defined(_WIN32)
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <spdlog/spdlog.h>

// 0 : Ŭ�� X
// 1 : root Ŭ�� O
// 2 : ���� ���� Ŭ�� O
grc::mouseclick grc::view::click(int state, int x, int y)
{
    if (getHidden())
    {
        return mouseclick::none;
    }

    mouseclick wrapCheck = mouseclick::none;
    for (auto& p : this->controls)
    {
        wrapCheck = p->click(state, x, y);
        if ((int)wrapCheck > 0)
        {
            return mouseclick::parentLevel;
        }
    }

    if (this->frame.location.x < x && x < this->frame.location.x + this->frame.size.width &&
        this->frame.location.y < y && y < this->frame.location.y + this->frame.size.height)
    {
        return mouseclick::ownLevel;
    }
    else
    {
        return mouseclick::none;
    }
}

// 0 : ���� X
// 1 : ���� O
int grc::view::keyboard(unsigned char key, int x, int y)
{
    if (getHidden())
    {
        return 0;
    }
    int wrapCheck = 0;
    for (auto& p : this->controls)
    {
        wrapCheck = p->keyboard(key, x, y);
        if (wrapCheck > 0)
        {
            return 1;
        }
    }
}


void grc::view::setHidden(bool value)
{
    isHidden = value;
    glutPostRedisplay();
}

bool grc::view::getHidden() const
{
    return this->isHidden;
}

bool grc::view::render(long long tick)
{
    if (!getHidden())
    {
        if (backgroundImage.has_value())
        {
            /*grc::rect r;
            r.location = { frame.location.x + borderSize, frame.location.y + borderSize };
            r.size = { frame.size.width - borderSize * 2, frame.size.height - borderSize * 2 };
            this->drawRect(this->frame, this->borderColor);
            this->drawRect(r, this->background);
            */
            drawImage(this->frame, backgroundImage.value());
        }
        else
        {
            drawRect(this->frame, this->background);
        }
        for (auto& v : controls)
        {
            v->render(tick);
        }
        return true;
    }
    else
    {
        return false;
    }
}

int grc::view::mouse(int x, int y)
{
    if (getHidden())
    {
        return 0;
    }
    int wrapCheck = 0;
    for (auto& p : this->controls)
    {
        wrapCheck = p->mouse(x, y);
        if (wrapCheck > 0)
        {
            return 1;
        }
    }
}



void grc::view::drawRect(grc::rect size, grc::color color) const
{
    glColor4f(color.red / 255.0, color.green / 255.0, color.blue / 255.0, color.alpha / 255.0);
    glBegin(GL_QUADS); //4���� �ϳ��� �簢���� �����Ѵ�. �ݽð� �������� 4���� vertex�� ��������� �Ѵ�.
    grc::point lup = { size.location.x, size.location.y + size.size.height };
    grc::point rup = { size.location.x + size.size.width, size.location.y + size.size.height };
    grc::point lbp = { size.location.x, size.location.y };
    grc::point rbp = { size.location.x + size.size.width, size.location.y };

    const auto& displaySize = grc::application::shared->getSize();
    float displayX = displaySize.width / 2,
        displayY = -displaySize.height / 2;

    glVertex2f(lbp.x / displayX - 1, lbp.y / displayY + 1); // x, y
    glVertex2f(rbp.x / displayX - 1, rbp.y / displayY + 1);
    glVertex2f(rup.x / displayX - 1, rup.y / displayY + 1);
    glVertex2f(lup.x / displayX - 1, lup.y / displayY + 1);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); //��� ����
}

void grc::view::drawCircle(grc::point pt, float radius, grc::color color) const
{
    const int lineAmount = (int)radius; //# of triangles used to draw circle

    double twicePi = 2.0f * MATH_PI;
    const auto& displaySize = grc::application::shared->getSize();
    float displayX = displaySize.width / 2,
        displayY = -displaySize.height / 2;

    float ptX = pt.x / displayX - 1, ptY = pt.y / displayY + 1;
    float szX = (radius * 2) / displaySize.width, szY = (radius * 2) / displaySize.height;

    glColor4f(color.red / 255.0, color.green / 255.0, color.blue / 255.0, color.alpha / 255.0);
    glBegin(GL_POLYGON);

    for (int i = 0; i <= lineAmount; i++)
    {
        auto xx = ptX + (szX * cos(i * twicePi / lineAmount));
        auto yy = ptY + (szY * sin(i * twicePi / lineAmount));
        glVertex2f(xx, yy);
    }
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); //��� ����
}

void grc::view::drawLine(grc::point x, grc::point y, float thin, grc::color color) const
{
    const auto& displaySize = grc::application::shared->getSize();
    float displayX = displaySize.width / 2,
        displayY = -displaySize.height / 2;

    glLineWidth(thin);
    glColor4f(color.red / 255.0, color.green / 255.0, color.blue / 255.0, color.alpha / 255.0);
    glBegin(GL_LINES);
    glVertex2f(x.x / displayX - 1, x.y / displayY + 1);
    glVertex2f(y.x / displayX - 1, y.y / displayY + 1);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); //��� ����
}

void grc::view::drawImage(grc::rect size, unsigned int imageId) const
{
    grc::point lup = { size.location.x, size.location.y + size.size.height };
    grc::point rup = { size.location.x + size.size.width, size.location.y + size.size.height };
    grc::point lbp = { size.location.x, size.location.y };
    grc::point rbp = { size.location.x + size.size.width, size.location.y };

    const auto& displaySize = grc::application::shared->getSize();
    float displayX = displaySize.width / 2,
        displayY = -displaySize.height / 2;

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, imageId);
    glBegin(GL_QUADS);

    glTexCoord2f(1.0, 1.0);
    glVertex2f(rup.x / displayX - 1, rup.y / displayY + 1);

    glTexCoord2f(0.0, 1.0);
    glVertex2f(lup.x / displayX - 1, lup.y / displayY + 1);

    glTexCoord2f(0.0, 0.0);
    glVertex2f(lbp.x / displayX - 1, lbp.y / displayY + 1); // x, y

    glTexCoord2f(1.0, 0.0);
    glVertex2f(rbp.x / displayX - 1, rbp.y / displayY + 1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void grc::view::drawBitmapText(std::string text, grc::point pos) const
{
    // grc::point lup = {this->frame.location.x, this->frame.location.y + this->frame.size.height};
    // grc::point rup = {this->frame.location.x + this->frame.size.width, this->frame.location.y + this->frame.size.height};
    // grc::point lbp = {this->frame.location.x, this->frame.location.y};
    // grc::point rbp = {this->frame.location.x + this->frame.size.width, this->frame.location.y};

    int fontSize = 3;
    const auto& displaySize = grc::application::shared->getSize();
    float displayX = displaySize.width / 2,
        displayY = -displaySize.height / 2;

    glColor3f(1, 0, 0);
    glRasterPos2f((pos.x - (fontSize * text.size() * 2)) / displayX - 1, (pos.y + (7.5)) / displayY + 1);
    glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, fontSize);
    for (auto& t : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, t);
    }
    glColor3f(1, 1, 1);
}