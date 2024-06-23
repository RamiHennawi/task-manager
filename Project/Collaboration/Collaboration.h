#pragma once
#include <iostream>
#include "MyString.h"
#include "User.h"
#include "Vector.hpp"
#include "Pair.hpp"

class Collaboration {
private:
	uint32_t id = 0; // to be handled by TaskManager (unique id = created collabs count)
	MyString name;
	MyString creator;
	Vector<User*> users;
	Vector<Task*> tasks;

public:
	Collaboration() = default;
	Collaboration(uint32_t id, const MyString& name, const MyString& creator);

	void addUser(User& new_user);

	void addTask(Task& task);
	void listTasks() const;

	const MyString& getName() const;
	const MyString& getCreator() const;

	size_t getTasksCount() const;
	uint32_t getTaskIDAtIndex(size_t index);

	void removeTask(uint32_t id);

	bool includesUser(const MyString& username) const;
	bool includesUser(const User& user) const;
	bool includesTask(uint32_t id) const;

	// handle saving and reading from binary file
	void saveToFile(std::ofstream& out) const;
	void readFromFile(std::ifstream& in);
};
