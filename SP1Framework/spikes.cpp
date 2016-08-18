#include <sstream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "game.h"

void spikes_on() {
	int secondcounter = 0;

	for (int secondcounter = 0; secondcounter >= 0; secondcounter++){
		if (secondcounter % 2 == 0){
			ostringstream ss;
			ss << fixed;
			ss << "\r" << "a" << flush;

			/* if (playerPositionX == spikeX && playerPositionY == spikeY){
				}
			*/

			this_thread::sleep_for(chrono::seconds(10));
		}

		else {
			ostringstream ss;
			ss << fixed;
			ss << "\r" << "b" << std::flush;
			this_thread::sleep_for(chrono::seconds(10));
		}
	}
}