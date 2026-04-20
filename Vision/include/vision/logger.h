#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>

class Logger {
private:
	bool logToFile;
	bool logToConsole;
	bool logStatus;
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

	void logFile(const std::string& message);
	~Logger();
};