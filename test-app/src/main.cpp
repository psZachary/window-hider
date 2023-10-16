#include <iostream>

#include "../wh/wh.h"

int main()
{
    wh::WH_RESULT res = wh::hide_window("Untitled - Notepad");

    if (res == wh::success) {
        std::cout << "Window hidden" << std::endl;
    }
    else if (res == wh::already_hidden)
    {
		std::cout << "Window already hidden" << std::endl;
	}
    else {
        std::cout << "Window failed to hide: " << res << std::endl;
    }
    
    std::cin.get();

    return 0;
}
