#pragma once
#include <fstream>
#include "Vector.hpp"
#include "Task.h"

class Dashboard {
private:
	Vector<Task*> tasks;

	bool containsTask(Task& task) const;

public:
	Dashboard() = default;

	void addTask(Task& task);
	void removeTask(Task& task);

	void listTasks() const;

	void saveToFile(std::ofstream& out) const; // reading is handled by TaskManager
};
