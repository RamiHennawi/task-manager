#pragma once
#include "Vector.hpp"
#include "Task.h"

class Dashboard {
private:
	Vector<Task*> tasks;

public:
	Dashboard() = default;

	void addTask(Task& task);
	void removeTask(uint32_t id);

	void listTasks() const;
};
