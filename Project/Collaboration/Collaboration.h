#pragma once
#include <iostream>
#include "MyString.h"
#include "CollaborationTask.h"
#include "User.h"
#include "Vector.hpp"
#include "Pair.hpp"

class Collaboration {
private:
	uint32_t id; // to be handled by TaskManager (unique id = created collabs count)
	MyString name;
	MyString creator;
	Vector<User*> users;
	Vector<CollaborationTask*> tasks;

public:
	Collaboration() = default;
	Collaboration(uint32_t id, const MyString& name, const MyString& creator);

	void addUser(User& new_user);

	void assignTask(CollaborationTask& task);
	void listTasks() const;

	const MyString& getName() const;
	const MyString& getCreator() const;

	size_t getTasksCount() const;
	const CollaborationTask& getTaskAtIndex(size_t index) const;

	void removeTask(uint32_t id);

	bool includesUser(const MyString& username) const;
	bool includesUser(const User& user) const;
};
