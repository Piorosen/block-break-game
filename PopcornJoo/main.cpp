#include "application.h"
#include "mainScene.hpp"



int main(int argc, char** argv) {
	grc::application::shared->initialize(grc::size{ 500, 500 }, "������ �����");
	grc::application::shared->setScene(mainScene());

	grc::application::shared->run();
}