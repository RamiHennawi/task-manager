#pragma once
#include <fstream>
#include "MyString.h"
#include "Task.h"
#include "Dashboard.h"
#include "Vector.hpp"

class User {
private:
	MyString username;
	MyString password;
	Vector<Task*> tasks;
	Dashboard dashboard;

public:
	User() = default;
	User(const MyString& username, const MyString& password);

	const MyString& getUsername() const;
	const MyString& getPassword() const;

	const Task& getTask(const MyString& name) const;
	const Task& getTask(uint32_t id) const;

	void updateTaskName(uint32_t id, const MyString& new_name);
	void updateTaskDescription(uint32_t id, const MyString& new_description);

	void addTask(Task& task);

	void startTask(uint32_t id);
	void finishTask(uint32_t id);
	void deleteTask(uint32_t id);

	void listTasks(const MyString& final_date_str) const;
	void listTasks() const;
	void listCompletedTasks() const;

	// handle dashboard through user
	void removeTaskFromDashboard(uint32_t id);
	void addTaskToDashboard(uint32_t id);
	void listDashboard() const;

	void syncTasks(); // go through tasks and look at their due dates

	// handle saving and reading from binary file
	void saveToFile(std::ofstream& out) const;
	void readFromFile(std::ifstream& in);
};
