#pragma once
#include <fstream>
#include "Vector.hpp"
#include "Task.h"

class Dashboard {
private:
	Vector<Task*> tasks;

public:
	Dashboard() = default;

	void saveToFile(std::ofstream& out) const;
	void readFromFile(std::ifstream& in);

	void addTask(Task& task);
	void removeTask(uint32_t id);

	void listTasks() const;
};
