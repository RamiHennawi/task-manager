#pragma once
#include <fstream>
#include <iostream>
#include "Task.h"

class TasksContainer {
private:
	Task** tasks = nullptr;
	size_t count = 0;
	size_t capacity = 8;

	void resize();

public:
	TasksContainer();
	TasksContainer(const TasksContainer& other);
	TasksContainer(TasksContainer&& other) noexcept;
	TasksContainer& operator=(const TasksContainer& other);
	TasksContainer& operator=(TasksContainer&& other) noexcept;
	~TasksContainer();

	void addTask(Task* new_task);
	void removeTask(uint32_t id);

	Task& getTask(uint32_t id);
	const Task& getTask(uint32_t id) const;

	// handle saving and reading from binary file
	void saveToFile(std::ofstream& out) const;
	void readFromFile(std::ifstream& in);

private:
	void free();
	void copyFrom(const TasksContainer& other);
	void moveFrom(TasksContainer&& other);
};
