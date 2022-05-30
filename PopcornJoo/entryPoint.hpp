#pragma once

#include "mainScene.hpp"
#include "ingame.hpp"

std::shared_ptr<grc::scene> entryPoint() {
	return getMainScene([](grc::colorbuttonview* view, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			spdlog::info("Start �̺�Ʈ �߻�");
		}
		// Start �̺�Ʈ
	}, [](grc::colorbuttonview* view, grc::buttonstate state) {
		// End �̺�Ʈ
		if (state == grc::buttonstate::mouseUp) {
			spdlog::info("End �̺�Ʈ �߻�");
		}
	});

}