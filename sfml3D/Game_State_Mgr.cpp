#include "Game_State_Mgr.h"
#include <vector>

namespace Main {

	#define QUIT registeredStates[registeredStates.size()-1]
    #define RESTART registeredStates[registeredStates.size()-2]

	Game_S_Mgr::Game_S_Mgr(int current, int next, int previous) : current{ current }, next{ next }, previous{ previous }, registeredMethods{}, registeredStates{} {
		/*EMPTY BY DESIGN*/
	}
	Game_S_Mgr::Game_S_Mgr(int startingState) : current{ startingState }, next{ startingState }, previous{ startingState }, registeredMethods{}, registeredStates{} {
		/*EMPTY BY DESIGN*/
	}
	void Game_S_Mgr::registerMethod(FnPtrMethods methods) {

	}
	void Game_S_Mgr::updateMethods() {
		
	}
	void Game_S_Mgr::registerState(int state) {
		registeredStates.push_back(state);
	}

	void Game_S_Mgr::run() {

		while (current != QUIT) {

			if (next != RESTART) {
				updateMethods();

			}
			
			while (current == next) { // CHECK FOR A CHANGE IN STATE
				//current = QUIT;
			}

			if (next == RESTART) { //CHECK IF NEXT STATE IS RESTART, NO NEED TO UNLOAD IF SO.
				//methods.free();
				previous = current;
				current = next;
			} else {
				//methods.unload();
			}
		}


	}
	
}