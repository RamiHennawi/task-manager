#pragma once
#include "MyString.h"
#include "Task.h"
#include "Vector.hpp"

class User {
private:
	MyString username;
	MyString password;
	Vector<Task*> tasks;

public:
	User(const MyString& username, const MyString& password);

	const MyString& getUsername() const;
	const MyString& getPassword() const;

	void addTask(Task& task);

	void updateTaskName(uint32_t id, const MyString& new_name);
	void updateTaskDescription(uint32_t id, const MyString& new_description);

	void startTask(uint32_t id);
	void finishTask(uint32_t id);
	void deleteTask(uint32_t id);

	const Task& getTask(const MyString& name) const;
	const Task& getTask(uint32_t id) const;

	void listTasks(const MyString& final_date_str) const;
	void listTasks() const;
	void listCompletedTasks() const;
};
