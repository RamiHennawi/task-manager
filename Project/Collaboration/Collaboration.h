#pragma once
#include <iostream>
#include "MyString.h"
#include "Task.h"
#include "User.h"
#include "Vector.hpp"
#include "Pair.hpp"

class Collaboration {
private:
	uint32_t id; // to be handled by TaskManager (unique id = created collabs count)
	MyString name;
	MyString creator;
	Vector<User*> users;
	Vector<Pair<Task*, User*>> tasks;

public:
	Collaboration(uint32_t id, const MyString& name, const MyString& creator);

	void addUser(User& new_user);

	void assignTask(Task& task, User& user);
	void listTasks() const;

	const MyString& getName() const;
	const MyString& getCreator() const;

	size_t getTasksCount() const;
	const Task& getTaskAtIndex(size_t index) const;

	bool includesUser(const MyString& username) const;
	bool includesUser(const User& user) const;
};
