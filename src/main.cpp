#include <cheats.h>
#include "display.h"
#include "eadkpp.h"
#include "palette.h"
#include "game.h"

#define EADK_APP_NAME "Platform"
#define EADK_API_LEVEL 0

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = EADK_APP_NAME;
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = EADK_API_LEVEL;

int main(int argc, char * argv[]) {
	EADK::Display::clear(White);

	platform::drawLines();

	platform::Game game = platform::Game(3, 1000);
	for (int i = 0; i < 4; i++) {
		platform::Button* button = new platform::Button(300 + i * 100, platform::Row::FIRST);
		game.addButton(button);
	}

	for (int i = 0; i < 4; i++) {
		platform::Button* button = new platform::Button(300 + i * 100, platform::Row::SECOND);
		game.addButton(button);
	}

	for (int i = 0; i < 4; i++) {
		platform::Button* button = new platform::Button(300 + i * 100, platform::Row::THIRD);
		game.addButton(button);
	}

	for (int i = 0; i < 4; i++) {
		platform::Button* button = new platform::Button(300 + i * 100, platform::Row::FOURTH);
		game.addButton(button);
	}

	game.play();
}