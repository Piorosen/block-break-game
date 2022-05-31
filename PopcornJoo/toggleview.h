#pragma once
#include <vector>
#include <functional>
#include "view.h"

#include "buttonview.h"

namespace grc
{
    class toggleview : public view
    {
    private:
        int onImage;
        int offImage;

        bool toggle = false;

    public:
        // ��ü�� ������ �� �ð� ���� �ð�.
        toggleview(grc::rect f, int on = -1, int off = -1);

        std::function<void(grc::toggleview*, bool)> toggleEvent;

        virtual bool render(long long tick) override;
        virtual mouseclick click(int state, int x, int y) override;

    protected:
    };


}