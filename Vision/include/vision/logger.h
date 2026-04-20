#pragma once


class Logger {
public:
	static void info(const std::string& message);
	static void warning(const std::string& message);
	static void error(const std::string& message);
};