#include "Calendar.h"

Calendar::Calendar()
{
}
Calendar::Calendar(int _day, float _time) {
	day = _day;
	time = _time;
	notified = isAfterNotifyTime();
}


Calendar::~Calendar()
{
}

Calendar Calendar::init()
{
	return Calendar(0, START_TIME);
}

Calendar Calendar::load(BinaryReader reader)
{

	int day = reader.readInt();
	float time = reader.readFloat();
	return Calendar(day, time);

}

void Calendar::update(float delta, Window *w)
{
	// 如果当前处于启动游戏或关闭游戏界面 则不用更新
	//if (GameManager.getGameState() == GameState.SPLASH_SCREEN) {
	//	return;
	//}
	// notified是false 并且 当前时间在NotifyTime之后
	if (!notified && isAfterNotifyTime()) {
		notifyWelcomeMessage();
	}
	checkPauseTime(w);
	checkTimeChange(delta, w);
	updateTime(delta);
	// 下面几行用于日历显示测试
	//std::cout << "time:" << formatTimeDays(time + day) << " time=" << time << std::endl;
	//std::cout << "day=" << day <<" time="<< time << std::endl;
	//std::cout  << "years:" << getYear() << " days:" << day << " hours:"<< getTimeHours() << " minutes" << getTimeMinutes() << std::endl;
}

void Calendar::updateTime(float delta)
{
	delta = pauseTime ? 0 : delta;
	time += delta / DAY_LENGTH_SECONDS;
	if (time >= 1) {
		day++;
		time -= 1;
	}
}

void Calendar::checkPauseTime(Window *w)
{
	if (w->isKeyPressed(80)) {	//P
		pauseTime = !pauseTime;
	}
}

void Calendar::checkTimeChange(float delta, Window *w)
{
	if (w->isKeyPressed(90)) {	//Z
		time += delta / CHEAT_DAY_SECONDS;
	}
	else if (w->isKeyPressed(88)) {	//X 暂时用不到回退功能
		time -= delta / CHEAT_DAY_SECONDS;
		if (time <= 0) {
			time += 1;
			day--;
			if (day < 0)
				day = 0;
		}
	}
}

void Calendar::notifyWelcomeMessage()
{
	return;
}

float Calendar::getRawTime()
{
	return time;
}

bool Calendar::isNightTime()
{
	return time > 0.9f || time < 0.25f;
}

bool Calendar::isAfterNotifyTime() {
	return day > 0 || time >= NOTIFY_TIME;
}

int Calendar::getTimeHours()
{
	return (int)(time * HOURS_IN_DAY);
}

int Calendar::getTimeMinutes()
{
	return (int)((time * HOURS_IN_DAY - (int)(time * HOURS_IN_DAY)) * 60);
}

int Calendar::getTimeMinutesNearest(int interval)
{
	int minutes = getTimeMinutes();
	return (minutes / interval) * interval;
}

int Calendar::getYear()
{
	return (day / (DAYS_PER_QUARTER * QUARTERS)) + 1;
}

int Calendar::getQuarter()
{
	return (day / DAYS_PER_QUARTER) % QUARTERS + 1;
}

int Calendar::getDay()
{
	return (day % DAYS_PER_QUARTER) + 1;
}

void Calendar::save(BinaryWriter writer)
{
	writer.writeInt(day);
	writer.writeFloat(time);
}

std::string Calendar::formatTimeHours(float timeInHours)
{
	return formatTimeDays(timeInHours / HOURS_IN_DAY);
}

std::string Calendar::formatTimeDays(float timeInDays)
{
	int daysPerYear = DAYS_PER_QUARTER * QUARTERS;
	float years = timeInDays / daysPerYear;
	if (years > 1) {
		int yearInt = ((int)years);
		std::string text = std::to_string(yearInt) + " 年";
		if (years < 10) {
			int days = (int)((years - yearInt) * daysPerYear);
			if (days != 0) {
				text += ", " + std::to_string(days);
				text += " 天";
			}
		}
		return text;
	}
	else if (timeInDays > 1) {
		int daysInt = ((int)timeInDays);
		std::string text = std::to_string(daysInt) + " 天";
		if (timeInDays < 10) {
			int hours = (int)((timeInDays - daysInt) * HOURS_IN_DAY);
			if (hours != 0) {
				text += ", " + std::to_string(hours);
				text += " 时";
			}
		}
		return text;
	}
	else {
		float hours = timeInDays * HOURS_IN_DAY;
		std::string text = std::to_string((int)hours) + " 时";
		return text;
	}
}


