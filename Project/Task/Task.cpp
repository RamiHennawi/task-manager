#include "Task.h"
#include <sstream>
#include <iomanip>

namespace TaskHelperFunctions {
	time_t convertDateString(const MyString& date_str) {
		struct tm tm_struct;

		std::istringstream ss(date_str);
		ss >> std::get_time(&tm_struct, "%Y-%m-&d");

		if (ss.fail()) {
			throw std::invalid_argument("Invalid date format (must be yyyy-mm-dd).");
		}
		
		return mktime(&tm_struct);
	}
}

const char* Task::getStatusString() const {
	switch(status) {
		case TaskStatus::ON_HOLD: return "ON HOLD";
		case TaskStatus::IN_PROCESS: return "IN PROCESS";
		case TaskStatus::DONE: return "DONE";
		case TaskStatus::OVERDUE: return "OVERDUE";
	}

	return "";
}

Task::Task(uint32_t id, const MyString& name, const MyString& due_date_str, const MyString& description) : id(id), status(TaskStatus::ON_HOLD), 
	due_date(TaskHelperFunctions::convertDateString(due_date_str)), name(name), description(description) {}

uint32_t Task::getID() const {
	return id;
}

TaskStatus Task::getStatus() const {
	return status;
}

time_t Task::getDueDate() const {
	return due_date;
}

const MyString& Task::getName() const {
	return name;
}

const MyString& Task::getDescription() const {
	return description;
}

void Task::updateName(const MyString& new_name) {
	name = new_name;
}

void Task::updateDescription(const MyString& new_description) {
	description = new_description;
}

void Task::start() {
	status = TaskStatus::IN_PROCESS;
}

void Task::finish() {
	status = TaskStatus::DONE;
}

void Task::print() const {
	std::cout << "Task ID: " << id << std::endl;
	std::cout << "Task name: " << name << std::endl;
	std::cout << "Task description: " << description << std::endl;
	std::cout << "Due date: " << ctime(&due_date) << std::endl;
	std::cout << "Status: " << getStatusString() << std::endl;
}
