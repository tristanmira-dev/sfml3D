#ifndef GAME_STATE_MGR
#define GAME_STATE_MGR

#include <vector>

namespace Main {

	using FnPtr = void(*)();
	
	struct FnPtrMethods {
		FnPtr load;
		FnPtr init;
		FnPtr update;
		FnPtr draw;
		FnPtr free;
		FnPtr unload;

		inline FnPtrMethods(FnPtr load = nullptr, FnPtr init = nullptr, FnPtr update = nullptr, FnPtr draw = nullptr, FnPtr free = nullptr) 
			: load{ nullptr }, init{ nullptr }, update{ nullptr }, draw{ nullptr }, free{ nullptr }, unload{ nullptr } {
		
		};
	};
}
	
namespace Main {

	class Game_S_Mgr {

		public:

			Game_S_Mgr(int current, int next, int previous);
			Game_S_Mgr(int startingState);
			void run();
			void updateMethods();
			void registerMethod(FnPtrMethods methods);
			void registerState(int state);

		private:

			int previous;
			int next;
			int current;
			std::vector<FnPtr> registeredMethods;
			std::vector<int> registeredStates;
		
	};
}


#endif