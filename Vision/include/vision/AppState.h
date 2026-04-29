#pragma once

#include <atomic>

namespace vision {
	struct AppState {
		std::atomic<bool> running{ true };
		std::atomic<bool> loggerEnabled{ true };
		std::atomic<bool> cameraEnabled{ true };
		std::atomic<bool> gpuEnabled{ false };
	};
}