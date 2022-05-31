#pragma once
#include <vector>

#include "view.h"
#include "rect.h"

namespace grc
{
    class spriteview : public view
    {
    private:
        int timer = 0;
        bool playTimer = false;

    public:
        // ��ü�� ������ �� �ð� ���� �ð�.
        int durationMS = 1000;
        std::vector<int> images;

        spriteview(grc::rect f, std::vector<int> image);

        void play();
        void stop();
        void reset();

        virtual bool render(long long tick) override;
    };
}