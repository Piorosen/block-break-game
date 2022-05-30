#pragma once

#include "mainScene.hpp"
#include "ingameScene.hpp"
#include "helpScene.hpp"

std::shared_ptr<grc::scene> help;
std::shared_ptr<grc::scene> ingame;
std::shared_ptr<grc::scene> mainView;

std::shared_ptr<grc::scene> entryPoint() {
	ingame = getIngameScene();

	help = getHelpScene([]() {
		grc::application::shared->setScene(mainView);
		});

	mainView = getMainScene([](grc::colorbuttonview* view, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			spdlog::info("Start �̺�Ʈ �߻�");
			grc::application::shared->setScene(ingame);
		}
		// Start �̺�Ʈ
		}, [](grc::colorbuttonview* view, grc::buttonstate state) {
			// End �̺�Ʈ
			if (state == grc::buttonstate::mouseUp) {
				grc::application::shared->setScene(help);
				spdlog::info("End �̺�Ʈ �߻�");
			}
		});

	return mainView;
}