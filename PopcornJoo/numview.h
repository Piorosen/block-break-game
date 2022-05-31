#pragma once
#include <vector>
#include <functional>
#include "view.h"

#include "buttonview.h"
    
namespace grc
{
    class numview : public view
    {
    private:
        std::vector<int> numListImage;
        int num = 0;

    public:
        // ��ü�� ������ �� �ð� ���� �ð�.
        numview(grc::rect f, std::vector<int> numList, int defaultNum = 0);

        void setNum(int num) {
            this->num = num;
        }

        virtual bool render(long long tick) override;

    protected:
    };


}