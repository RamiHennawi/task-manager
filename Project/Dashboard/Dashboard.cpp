#include "Dashboard.h"

void Dashboard::saveToFile(std::ofstream& out) const {
	size_t tasks_count = tasks.getSize();
	out.write(reinterpret_cast<const char*>(&tasks_count), sizeof(tasks_count));

	for (size_t i = 0; i < tasks_count; i++) {
		uint32_t task_id = tasks[i]->getID();
		out.write(reinterpret_cast<const char*>(&task_id), sizeof(task_id));
	}
}

void Dashboard::readFromFile(std::ifstream& in) {
	
}

void Dashboard::addTask(Task& task) {
	if (task.getStatus() != TaskStatus::OVERDUE) {
		tasks.pushBack(&task);
	}
	else {
		throw std::logic_error("Cannot add an overdue task to the dashboard.");
	}
}

void Dashboard::removeTask(uint32_t id) {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getID() == id) {
			tasks.popAt(i);
			return;
		}
	}

	throw std::runtime_error("No task with that ID found.");
}

void Dashboard::listTasks() const {
	size_t tasks_count = tasks.getSize();

	if (tasks_count == 0) {
		std::cout << "There are no tasks.";
	}

	for (size_t i = 0; i < tasks_count; i++) {
		tasks[i]->print();
		std::cout << "-----------------" << std::endl;
	}
}
