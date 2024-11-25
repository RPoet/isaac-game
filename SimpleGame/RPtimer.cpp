
#include "stdafx.h"
#include <Windows.h>
#include "rptimer.h"

using nanosec		= std::chrono::time_point<std::chrono::system_clock>;
using sec			= std::chrono::duration<double>;
nanosec  RP::RpTimer::current_time;
nanosec  RP::RpTimer::previous_time;
sec		RP::RpTimer::delta_time;
double	RP::RpTimer::play_time		= 0;
double	RP::RpTimer::elapsed_time	= 0;
float	RP::RpTimer::tick			= 0;

void RP::RpTimer::init()
{
	DEVMODEA monitorSettings;
	EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &monitorSettings);
	RP::RpTimer::setTick(static_cast<double>(1.0L/ static_cast<double>(monitorSettings.dmDisplayFrequency)));
	RP::RpTimer::current_time = std::chrono::system_clock::now();
	RP::RpTimer::previous_time = std::chrono::system_clock::now();
	RP::RpTimer::play_time = 0;
	RP::RpTimer::elapsed_time = 0;
}

void RP::RpTimer::update()
{
	RP::RpTimer::current_time = std::chrono::system_clock::now();
	RP::RpTimer::delta_time = (RP::RpTimer::current_time - RP::RpTimer::previous_time);
	RP::RpTimer::previous_time = RP::RpTimer::current_time;
	RP::RpTimer::elapsed_time += RP::RpTimer::delta_time.count();
	RP::RpTimer::play_time += RP::RpTimer::delta_time.count();
}

double RP::RpTimer::getDeltaTime()
{
	return (RP::RpTimer::elapsed_time);
}

double RP::RpTimer::getPlayTime()
{
	return (RP::RpTimer::play_time);
}

void RP::RpTimer::resetDeltaTime()
{
	RP::RpTimer::elapsed_time = 0; // 확인 필요.
}

void RP::RpTimer::setTick(float tick)
{
	RP::RpTimer::tick = tick;
}

float RP::RpTimer::getTick()
{
	return RP::RpTimer::tick;
}




