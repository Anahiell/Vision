#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <mutex>
#include <Windows.h>

class Logger {
private:
	bool logToFile;
	bool logToConsole;
	bool logStatus;
	bool logToWindow = false;

	std::string logFilePath = "logVision.txt";
	std::ofstream file;
public:

	Logger();
	Logger(bool logToFile, bool logToConsole);
	void status(bool logStatus);
	void info(const std::string& message);
	void warning(const std::string& message);
	void error(const std::string& message);

	void setLogToFile(bool enable);
	void setLogToConsole(bool enable);
	void setLogToWindow(bool enable);

	void startLogWindow();
	void stopLogWindow();

	std::mutex logMutex;

	void logFile(const std::string& message);
	void initialization();
	~Logger();
#ifdef _WIN32
	HANDLE hPipe = INVALID_HANDLE_VALUE;
	std::thread pipeThread;
	std::atomic<bool> pipeReady{ false };
#endif
	void writeToWindow(const std::string& message);

};