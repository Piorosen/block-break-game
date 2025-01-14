#include <spdlog/spdlog.h>
#include "ballview.h"
#include "buttonview.h"

grc::ballview::ballview(grc::point center, int radius, grc::color ballColor) 
	: view(grc::rect(center.x - radius,
					 center.y - radius,
					 center.x + radius,
					 center.y + radius), ballColor)
{
	this->radius = radius;
	this->initCenter = center;
	physical = std::make_shared<phy::object>();
	physical->collisionevent = [](std::weak_ptr<phy::object> self, std::weak_ptr<phy::object> other, phy::collisioninfo info, long long tick) {
		auto obj = self.lock();
		auto oobj = other.lock();
		
		double r = 0;
		grc::rect rc;
		grc::rect rc2;
		oobj->getType(r, rc2);
		obj->getType(r, rc);

		auto t = obj->getTransform();
		// gravity ������
		auto veloff = obj->velocity * (tick / 1000.0);

		obj->setTransform(phy::vector2d{ t.x - veloff.x, t.y - veloff.y });
		for (auto pos : info.other) {
			if (pos == phy::collisionPos::top && obj->velocity.y > 0) {
				/*double downSpeed = obj->gravity * obj->mesh * (tick / 1000.0);
				obj->velocity.y += downSpeed;*/
				obj->velocity.y *= -1;
			}
			else if (pos == phy::collisionPos::left && obj->velocity.x > 0) {
				obj->velocity.x *= -1;
			}
			else if (pos == phy::collisionPos::right && obj->velocity.x < 0) {
				obj->velocity.x *= -1;
			}
			else if (pos == phy::collisionPos::bottom && obj->velocity.y < 0) {
				obj->velocity.y *= -1;
			}

			switch (pos) {
			case phy::collisionPos::none:
				spdlog::info("collision Pos : [NONE]");
				break;
			case phy::collisionPos::left:
				spdlog::info("collision Pos : [left]");
				break;
			case phy::collisionPos::top:
				spdlog::info("collision Pos : [top]");
				break;
			case phy::collisionPos::right:
				spdlog::info("collision Pos : [right]");
				break;
			case phy::collisionPos::bottom:
				spdlog::info("collision Pos : [bottom]");
				break;
			}
		}
		obj->velocity = obj->velocity * 0.9;
	};
	physical->setTransform(phy::vector2d{
		(double)center.x,
		(double)center.y
		});
	physical->transformchanged = [this](phy::vector2d location) {
		auto radius = this->getRadius();
		auto speed = this->getPhysical()->velocity.magnitude();
		if (this->getPhysical()->getHidden()) {
			return;
		}

		if (speed < 100 || speed > 5000) {
			if (ballDeadEvent) {
				ballDeadEvent(this);
			}
		}
		else {
			this->frame = grc::rect(location.x - radius, location.y - radius,
									location.x + radius, location.y + radius);
		}
	};
	physical->setType(radius);
	physical->gravity = -200;
	physical->mesh = 10;
	physical->setHidden(true);
}

std::shared_ptr<phy::object> grc::ballview::getPhysical() const
{
	return physical;
}

void grc::ballview::reset()
{
	physical->setHidden(true);
	auto center = this->initCenter;

	this->frame = grc::rect(center.x - radius,
		center.y - radius,
		center.x + radius,
		center.y + radius);

	physical->velocity = phy::vector2d {
		0,0
	};
	physical->setTransform(phy::vector2d{
		(double)center.x,
		(double)center.y
		});

}

void grc::ballview::shot(grc::point click)
{
	spdlog::info("SHOT!");
	phy::vector2d pos{
		(double)click.x,
		(double)click.y
	};

	auto power = (pos - physical->getTransform()).normalization() * 2000;
	physical->velocity.x = power.x;
	physical->velocity.y = power.y;
	physical->setHidden(false);
}

void grc::ballview::shotable(bool able)
{
	this->shotalbe = able;
}

bool grc::ballview::render(long long tick)
{
	if (!getHidden()) {
		view::drawCircle(frame.center(), frame.size.width / 2.0, grc::color(0x000000ff));
		view::drawCircle(frame.center(), frame.size.width / 2.0 - 2, background);
		for (auto& v : controls)
		{
			v->render(tick);
		}
		return true;
	}
	else {
		return false;
	}
}

grc::mouseclick grc::ballview::click(int state, int x, int y)
{
	auto p = view::click(state, x, y);
	if (this->shotalbe) {
		auto pp = (grc::buttonstate)state;
		if (pp == grc::buttonstate::mouseUp) {
			auto pos = grc::point{ x, y };
			if (this->clickRange.exists(pos)) {
				shot(pos);
				this->shotalbe = false;
			}
		}
	}

	return p;
}

int grc::ballview::mouse(int x, int y)
{
	return view::mouse(x, y);
}
