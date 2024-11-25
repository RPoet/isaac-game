#ifndef RP_TIMER_H
#define RP_TIMER_H
#include <chrono>
//#if _DEBUG
//#if _M_X64
//#pragma comment(lib,"lib/timer/timer_chrono_d_x64.lib")
//#else
//#pragma comment(lib,"lib/timer/timer_chrono_d_x86.lib")
//#endif
//#elif _M_X64
//#pragma comment(lib,"lib/timer/timer_chrono_r_x64.lib")
//#else
//#pragma comment(lib,"lib/timer/timer_chrono_r_x86.lib")
//#endif

namespace RP {
	class RpTimer
	{
		static std::chrono::time_point<std::chrono::system_clock>	current_time;
		static std::chrono::time_point<std::chrono::system_clock>	previous_time;
		static std::chrono::duration<double>						delta_time;

		static double												play_time;
		static double												elapsed_time;
		static float												tick;
		static void													setTick(float);
	public:
		static void													init();
		static void													update();
		static double												getDeltaTime();
		static double												getPlayTime();
		static void													resetDeltaTime();

		static float												getTick();
	}; 
}
#endif // !TIMER_H

