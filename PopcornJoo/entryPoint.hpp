#pragma once

#include "mainScene.hpp"
#include "ingameScene.hpp"
#include "helpScene.hpp"

std::shared_ptr<grc::scene> entryPoint() {
	std::shared_ptr<grc::scene> help;
	std::shared_ptr<grc::scene> ingame;
	std::shared_ptr<grc::scene> main;


	help = getHelpScene([main]() {
		grc::application::shared->setScene(main);
		});

	main = getMainScene([help](grc::colorbuttonview* view, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			spdlog::info("Start �̺�Ʈ �߻�");
			grc::application::shared->setScene(help);
		}
		// Start �̺�Ʈ
		}, [](grc::colorbuttonview* view, grc::buttonstate state) {
			// End �̺�Ʈ
			if (state == grc::buttonstate::mouseUp) {
				spdlog::info("End �̺�Ʈ �߻�");
			}
		});

	return main;
}