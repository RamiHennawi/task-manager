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

	void saveToFile(std::ofstream& out) const;
	void readFromFile(std::ifstream& in);

	void addTask(Task& task);
	void removeTask(Task& task);

	void listTasks() const;
};
