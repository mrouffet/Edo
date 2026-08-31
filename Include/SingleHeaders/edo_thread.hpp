// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_SH_THREAD_GUARD
#define EDO_SH_THREAD_GUARD

#include <cstdint>

#include <mutex>
#include <atomic>
#include <thread>

namespace edo::thread
{
// ##############################################################
// #						Pool								#
// ##############################################################

	template <uint8_t threadNum>
	class ThreadPool
	{
		std::thread mThreads[threadNum];
	};

// ##############################################################
}

#endif // EDO_SH_THREAD_GUARD
