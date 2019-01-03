#pragma once

#include "glrequest.h"
#include <queue>

class GlRequestQueue
{
private:
	std::queue<GlRequest> requestQueue;

public:
	void addRequest(GlRequest request){ requestQueue.push(request); }

	GlRequest acceptNextRequest()
	{ 
		GlRequest req = requestQueue.front();
		requestQueue.pop(); 
		return req;
	}

	bool hasRequests() { return !requestQueue.empty(); }
};