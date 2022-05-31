#pragma once
#include <vector>
#include <functional>

#include "view.h"
#include "object.h"

namespace grc
{
    class wallview : public view
    {
    private:
        std::shared_ptr<phy::object> physical;
        int radius;

    public:
        // ��ü�� ������ �� �ð� ���� �ð�.
        wallview(grc::point center, int radius, grc::color ballColor = grc::color(0xff00ffff));

        std::shared_ptr<phy::object> getPhysical() const;

        std::function<void(wallview*)> mouseEvent;

        virtual bool render(long long tick) override;
        virtual mouseclick click(int state, int x, int y) override;
        virtual int mouse(int x, int y) override;

    protected:
    };
}