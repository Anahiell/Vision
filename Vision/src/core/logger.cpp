#include <iostream>
#include <string>
#include "vision/logger.h"

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
	file.open(logFilePath,std::ios::out | std::ios::app);
	if (!file.is_open()) {
		std::cerr << C_Red << "Cannot open LogFile LOGER ERROR" << C_Reset << std::endl;
		logStatus = false;
	}
	else
	{
		logStatus = true;
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
	}
	status(logStatus);
}
void Logger::status(bool tf)
{
	if(tf)
	std::cout << "Logger is started"<<std::endl;
	else
		std::cout << "Logger is dropdown" << std::endl;
}
Logger::~Logger()
{
	if (file.is_open()) {
		file.close();
	}
}
void Logger::info(const std::string& message) {
	std::cout << C_Cyan << "[INFO]: "<< C_Reset << message << std::endl;
}
void Logger::warning(const std::string& message) {
	
	std::cout << C_Yellow <<"[WARNING]"<< C_Reset << message << std::endl;
}
void Logger::error(const std::string& message) {
	std::cout << C_Red <<"[ERROR]"<< C_Reset << message << std::endl;
}