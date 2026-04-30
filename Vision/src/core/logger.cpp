#include <iostream>
#include <string>
#include "vision/logger.h"
#include <thread>

#ifdef _WIN32
#include <windows.h>
#endif


#define C_Reset     "\033[0m"
#define C_Red       "\033[31m"
#define C_Green     "\033[32m"
#define C_Yellow    "\033[33m"
#define C_Blue      "\033[34m"
#define C_Cyan      "\033[36m"

Logger::Logger()
{
	logToConsole = true;
	logToFile = true;
	file.open(logFilePath, std::ios::out | std::ios::app);
	if (!file.is_open()) {
		std::cerr << C_Red << "Cannot open LogFile LOGER ERROR" << C_Reset << std::endl;
		logStatus = false;
	}
	else
	{
		logStatus = true;
		initialization();
	}
	status(logStatus);
}
Logger::Logger(bool logToFile, bool logToConsole)
{
	this->logToFile = logToFile;
	this->logToConsole = logToConsole;
	file.open(logFilePath, std::ios::out | std::ios::app);
	if (!file.is_open()) {
		std::cerr << C_Red << "Cannot open LogFile LOGER ERROR" << C_Reset << std::endl;
		logStatus = false;
	}
	else
	{
		logStatus = true;
		initialization();
	}
	status(logStatus);
}
void Logger::status(bool tf)
{
	if (tf)
		std::cout << "Logger is started" << std::endl;
	else
		std::cout << "Logger is dropdown" << std::endl;
}
Logger::~Logger()
{
	if (file.is_open()) {
		file.close();
	}
}
void Logger::info(const std::string& message)
{
	std::lock_guard<std::mutex> lock(logMutex);

	std::string plain = "[INFO]: " + message;

	if (logToConsole) {
		std::cout << C_Cyan << "[INFO]: " << C_Reset << message << std::endl;
	}

	if (logToFile && file.is_open()) {
		file << plain << std::endl;
	}

	if (logToWindow) {
		writeToWindow(plain);
	}
}
void Logger::warning(const std::string& message) {

	std::lock_guard<std::mutex> lock(logMutex);

	std::string plain = "[WARNING]: " + message;

	if (logToConsole) {
		std::cout << C_Yellow << "[WARNING]: " << C_Reset << message << std::endl;
	}

	if (logToFile && file.is_open()) {
		file << plain << std::endl;
	}

	if (logToWindow) {
		writeToWindow(plain);
	}
}
void Logger::error(const std::string& message) {
	std::lock_guard<std::mutex> lock(logMutex);

	std::string plain = "[ERROR]: " + message;

	if (logToConsole) {
		std::cout << C_Red << "[ERROR]: " << C_Reset << message << std::endl;
	}

	if (logToFile && file.is_open()) {
		file << plain << std::endl;
	}

	if (logToWindow) {
		writeToWindow(plain);
	}
}
void Logger::setLogToFile(bool enable) {
	logToFile = enable;
}
void Logger::setLogToConsole(bool enable) {
	logToConsole = enable;
}
void Logger::setLogToWindow(bool enable)
{
	logToWindow = enable;
}
void Logger::logFile(const std::string& message) {
	if (logToFile && file.is_open()) {
		file << message << std::endl;
	}
}
void Logger::initialization() {

	logToConsole = true;
	logToFile = false;

}

void Logger::startLogWindow()
{
#ifdef _WIN32
	if (pipeReady.load()) {
		return;
	}

	hPipe = CreateNamedPipe(
		TEXT("\\\\.\\pipe\\VisionPipe"),
		PIPE_ACCESS_OUTBOUND,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		1,
		4096,
		4096,
		0,
		NULL
	);

	if (hPipe == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to create log pipe\n";
		return;
	}

	system("start cmd /k \"title Vision Log Window && type \\\\.\\pipe\\VisionPipe\"");

	pipeThread = std::thread([this]() {
		BOOL connected = ConnectNamedPipe(hPipe, NULL);

		if (connected || GetLastError() == ERROR_PIPE_CONNECTED) {
			pipeReady.store(true);
			writeToWindow("[LOG WINDOW CONNECTED]\n");
		}
		});

	logToWindow = true;
#endif
}
void Logger::stopLogWindow()
{
	#ifdef _WIN32
	logToWindow = false;
	pipeReady.store(false);
	if (hPipe != INVALID_HANDLE_VALUE) {
		CloseHandle(hPipe);
		hPipe = INVALID_HANDLE_VALUE;
	}
	if (pipeThread.joinable()) {
		pipeThread.join();
	}
#endif
}
void Logger::writeToWindow(const std::string& message)
{
#ifdef _WIN32
	if (!logToWindow || !pipeReady.load() || hPipe == INVALID_HANDLE_VALUE) {
		return;
	}

	DWORD bytesWritten = 0;
	std::string msg = message + "\n";

	WriteFile(
		hPipe,
		msg.c_str(),
		static_cast<DWORD>(msg.size()),
		&bytesWritten,
		NULL
	);
#endif
}