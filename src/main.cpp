#include "cheats.h"
#include "display.h"
#include "eadkpp.h"
#include "window_manager.h"

#define EADK_APP_NAME "Platform"
#define EADK_API_LEVEL 0

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = EADK_APP_NAME;
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = EADK_API_LEVEL;

int main(int argc, char * argv[]) {
	EADK::Display::clear(White);

	platform::windows::WindowManager windowManager;
	windowManager.runWindow<platform::windows::WindowType::WELCOME>();

	return 0;
}