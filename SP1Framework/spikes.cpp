#include <sstream>
#include <stdio.h>
#include <chrono>
#include <thread>

void spikes_on() {
	int secondcounter = 0;

	for (int secondcounter = 0; secondcounter >= 0; secondcounter++){
		if (secondcounter % 2 == 0){
			std::ostringstream ss;
			ss << std::fixed;
			ss << "\r" << "a" << std::flush;

			/* if (playerPositionX == spikeX && playerPositionY == spikeY){
				}
			*/

			std::this_thread::sleep_for(std::chrono::seconds(10));
		}

		else {
			std::ostringstream ss;
			ss << std::fixed;
			ss << "\r" << "b" << std::flush;
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}
	}
}