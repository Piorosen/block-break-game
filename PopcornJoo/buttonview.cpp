#include <spdlog/spdlog.h>
#include "buttonview.h"

grc::buttonview::buttonview(grc::rect f, int defaultImage, int downImage, int hoverImage) : view(f, defaultImage)
{
}

bool grc::buttonview::render(long long tick)
{
	
	return false;
}

grc::mouseclick grc::buttonview::click(int state, int x, int y)
{
	spdlog::info("buttonview - click : [{}, {}, {}]", state, x, y);
	mouseclick value =  view::click(state, x, y);
	if (value == mouseclick::ownLevel) {
		mouseEvent.Invoke(this, (buttonstate)state);
	}
	return value;
}

int grc::buttonview::keyboard(unsigned char key, int x, int y)
{
	return view::keyboard(key, x, y);
}

int grc::buttonview::mouse(int x, int y)
{
	int value = view::mouse(x, y);
	if (this->frame.exists(grc::point{ x, y })) {
		if (this->state == grc::buttonstate::mouseLeave) {
			spdlog::info("hover");
			mouseEvent.Invoke(this, grc::buttonstate::mouseHover);
			this->state = grc::buttonstate::mouseHover;
		}
	}
	else {
		if (this->state == grc::buttonstate::mouseHover) {
			spdlog::info("leave");
			mouseEvent.Invoke(this, grc::buttonstate::mouseLeave);
			this->state = grc::buttonstate::mouseLeave;
		}
	}
	return value;
}
