#pragma once
#include "../../Resource Management/languages/gametext.h"
#include "../../Resource Management/utils/binaryreader.h"
#include "../../Resource Management/utils/binarywriter.h"
#include "../../Render Engine/basics/window.h"
#include <iostream>



class Calendar
{
public:
	Calendar();
	Calendar(int _day, float _time);
	~Calendar();

	/* 日历初始化 */
	Calendar init();

	/* 读档-读取day和time */
	Calendar load(BinaryReader reader);

	/* 更新状态 */
	void update(float delta, Window *w);

	/* 更新时间:每当有时间偏移的时候，且不再暂停期间，更新时间 */
	void updateTime(float delta);

	/* P暂停时间 */
	void checkPauseTime(Window *w);

	/* Z加速时间 X回退时间 */
	void checkTimeChange(float delta, Window *w);

	/* 欢迎信息 */
	void notifyWelcomeMessage();


	/* 时间范围[0,1),接近0代表一天开始，接近1代表一天的结束 */
	float getRawTime();

	/* 是否处在夜晚时间 */
	bool isNightTime();

	/* 判断当前时间是否在NotifyTime之后 */
	bool isAfterNotifyTime();

	/* 获得当前小时数 */
	int getTimeHours();

	/* 获得当前分钟数 */
	int getTimeMinutes();

	/* 获得当前分钟数的近似值，比如以每5min的间隔显示 */
	int getTimeMinutesNearest(int interval);

	/* 获得当前年数 */
	int getYear();

	/* 获得当前季度 */
	int getQuarter();

	/* 获得当前天数 */
	int getDay();

	/* 存档-存储day和time */
	void save(BinaryWriter writer);

	std::string formatTimeHours(float timeInHours);
	/* 返回自定义字符串格式日历 */
	std::string formatTimeDays(float timeInDays);


private:
	// 683;Welcome Message Title;Welcome;
	std::string TITLE = GameText::getText(683);
	// 684;Welcome Message;Welcome to Equilinox! Click the flashing task tab and follow the first task to get started.;
	std::string MESSAGE = GameText::getText(684);
	/* 892-897;年\天\时 */
	std::string YEAR = GameText::getText(892);
	std::string YEARS = GameText::getText(893);
	std::string DAY = GameText::getText(894);
	std::string DAYS = GameText::getText(895);
	std::string HR = GameText::getText(896);
	std::string HRS = GameText::getText(897);

	float NOTIFY_TIME = 7.03 / 24;	// ？

	float DAY_LENGTH_SECONDS = 720;	// 每天=720s
	float CHEAT_DAY_SECONDS = 10;	// CHEAT模式下：每天=10s
	float START_TIME = 7 / 24;		// 开始时间
	float HOURS_IN_DAY = 24;		// 每天=24h
	float HOUR_LENGTH = DAY_LENGTH_SECONDS / HOURS_IN_DAY;	// 每小时=30s

	int QUARTERS = 1;				// 每年=1季度
	int DAYS_PER_QUARTER = 10;		// 1季度=10天

	int day;				// 天数
	float time;				// 当天的某一具体时刻
	bool notified;			// 是否修改时间
	bool pauseTime = false;	// 是否暂停时间


};

