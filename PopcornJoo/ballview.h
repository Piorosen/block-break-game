#pragma once
#include <vector>
#include <functional>

#include "view.h"
#include "object.h"

namespace grc
{
    class ballview : public view
    {
    private:
        std::shared_ptr<phy::object> physical;
        int radius;

    public:
        // ��ü�� ������ �� �ð� ���� �ð�.
        ballview(grc::point center, int radius, grc::color ballColor = grc::color(0xff00ff00));

        std::shared_ptr<phy::object> getPhysical() const;

        std::function<void(ballview*)> mouseEvent;

        virtual bool render(long long tick) override;
        virtual mouseclick click(int state, int x, int y) override;
        virtual int mouse(int x, int y) override;

    protected:
    };
}