#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <windows.h>

void spikes_on() {
	int secondcounter = 0;

	for (int secondcounter = 0; secondcounter >= 0; secondcounter++){
		if (secondcounter % 2 == 0){
			std::cout << "\r" << "a" << std::flush;
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}

		else {
			std::cout << "\r" << "b" << std::flush;
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}
	}
}