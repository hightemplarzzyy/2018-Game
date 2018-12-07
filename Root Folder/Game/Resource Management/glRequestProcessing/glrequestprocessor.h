#pragma once

#include <chrono>
#include "glrequestqueue.h"
#include "glrequest.h"

class GlRequestProcessor
{
private:
	static float MAX_TIME_MILLIS;
	static GlRequestQueue requestQueue;

public:
	//向队列添加任务
	static void sendRequest(GlRequest request){ requestQueue.addRequest(request); }

	//执行队列中的任务，最多执行8毫秒
	static void dealWithTopRequests()
	{
		float remainingTime = MAX_TIME_MILLIS * 1000000;
		auto time_now = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
		auto start = time_now.time_since_epoch().count();
		while (requestQueue.hasRequests())
		{
			requestQueue.acceptNextRequest().executeGlRequest();
			auto time_now = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
			auto end = time_now.time_since_epoch().count();
			long timeTaken = end - start;
			remainingTime -= timeTaken;
			start = end;
			if (remainingTime < 0)
				break;
		}
	}

	//将队列中的任务执行完
	static void completeAllRequests()
	{
		while (requestQueue.hasRequests())
			requestQueue.acceptNextRequest().executeGlRequest();
	}
};