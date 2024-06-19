#include "User.h"

User::User(const MyString& username, const MyString& password) : username(username), password(password) {}

const MyString& User::getUsername() const {
	return username;
}

const MyString& User::getPassword() const {
	return password;
}

void User::addTask(Task& task) {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if ((task.getName() == tasks[i]->getName()) && (difftime(task.getDueDate(), tasks[i]->getDueDate()) == 0)) {
			throw std::runtime_error("A task with that name and due date already exists.");
		}
	}

	tasks.pushBack(&task);
}

void User::updateTaskName(uint32_t id, const MyString& new_name) {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getID() == id) {
			tasks[i]->updateName(new_name);
			return;
		}
	}

	throw std::runtime_error("No task with that ID found.");
}

void User::updateTaskDescription(uint32_t id, const MyString& new_description) {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getID() == id) {
			tasks[i]->updateDescription(new_description);
			return;
		}
	}

	throw std::runtime_error("No task with that ID found.");
}

void User::startTask(uint32_t id) {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getID() == id) {
			tasks[i]->start();
			return;
		}
	}

	throw std::runtime_error("No task with that ID found.");
}

void User::finishTask(uint32_t id) {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getID() == id) {
			tasks[i]->finish();
			return;
		}
	}

	throw std::runtime_error("No task with that ID found.");
}

void User::deleteTask(uint32_t id) {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getID() == id) {
			tasks.popAt(i);
			return;
		}
	}

	throw std::runtime_error("No task with that ID found.");
}

const Task& User::getTask(const MyString& name) const {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getName() == name) {
			return *tasks[i];
		}
	}

	throw std::runtime_error("No task with that ID found.");
}

const Task& User::getTask(uint32_t id) const {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getID() == id) {
			return *tasks[i];
		}
	}

	throw std::runtime_error("No task with that ID found.");
}

void User::listTasks(const MyString& final_date_str) const {
	time_t final_date = TaskHelperFunctions::convertDateString(final_date_str);

	size_t tasks_count = tasks.getSize();
	bool exists_task = false;

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getDueDate() < final_date) {
			exists_task = true;

			tasks[i]->print();
			std::cout << "-----------------" << std::endl;
		}
	}

	if (!exists_task) {
		std::cout << "There are no tasks before that date.";
	}
}

void User::listTasks() const {
	size_t tasks_count = tasks.getSize();

	if (tasks_count == 0) {
		std::cout << "There are no tasks.";
	}

	for (size_t i = 0; i < tasks_count; i++) {
		tasks[i]->print();
		std::cout << "-----------------" << std::endl;
	}
}

void User::listCompletedTasks() const {
	size_t tasks_count = tasks.getSize();
	bool exists_task = false;

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getStatus() == TaskStatus::DONE) {
			exists_task = true;

			tasks[i]->print();
			std::cout << "-----------------" << std::endl;
		}
	}

	if (!exists_task) {
		std::cout << "There are no completed tasks.";
	}
}
