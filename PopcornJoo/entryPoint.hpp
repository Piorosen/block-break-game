#pragma once

#include "mainScene.hpp"
#include "ingame.hpp"

std::shared_ptr<grc::scene> entryPoint() {
	return getMainScene([](grc::colorbuttonview* view, grc::buttonstate state) {
		spdlog::info("Start �̺�Ʈ �߻�");
		// Start �̺�Ʈ
	}, [](grc::colorbuttonview* view, grc::buttonstate state) {
		// End �̺�Ʈ
		spdlog::info("End �̺�Ʈ �߻�");
	});

}