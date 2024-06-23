#include "Collaboration.h"

Collaboration::Collaboration(uint32_t id, const MyString& name, const MyString& creator) : id(id), name(name), creator(creator) {}

void Collaboration::addUser(User& new_user) {
	size_t usersCount = users.getSize();

	for (size_t i = 0; i < usersCount; i++) {
		if (users[i] == &new_user) {
			throw std::runtime_error("User already in collaboration.");
		}
	}

	users.pushBack(&new_user);
}

void Collaboration::addTask(Task& task) {
	if (includesTask(task.getID())) {
		throw std::runtime_error("Task already in collaboration.");
	}

	tasks.pushBack(&task);
}

void Collaboration::listTasks() const {
	size_t tasks_count = tasks.getSize();

	if (tasks_count == 0) {
		throw std::runtime_error("Collaborations is empty.");
	}

	std::cout << "Tasks for " << name << ": " << std::endl;

	for (size_t i = 0; i < tasks_count; i++) {
		tasks[i]->print();

		if (i != (tasks_count - 1)) {
			std::cout << "-----------------" << std::endl;
		}
	}

	std::cout << std::endl;
}

const MyString& Collaboration::getName() const {
	return name;
}

const MyString& Collaboration::getCreator() const {
	return creator;
}

size_t Collaboration::getTasksCount() const {
	return tasks.getSize();
}

uint32_t Collaboration::getTaskIDAtIndex(size_t index) {
	return tasks[index]->getID();
}

void Collaboration::removeTask(uint32_t id) {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getID() == id) {
			tasks.popAt(i);
			return;
		}
	}

	throw std::runtime_error("No task with that ID found.");
}

bool Collaboration::includesUser(const MyString& username) const {
	size_t users_count = users.getSize();

	if (creator == username) {
		return true;
	}

	for (size_t i = 0; i < users_count; i++) {
		if (users[i]->getUsername().c_str() == username) {
			return true;
		}
	}

	return false;
}

bool Collaboration::includesUser(const User& user) const {
	size_t users_count = users.getSize();

	for (size_t i = 0; i < users_count; i++) {
		if (users[i] == &user) {
			return true;
		}
	}

	return false;
}

bool Collaboration::includesTask(uint32_t id) const {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i]->getID() == id) {
			return true;
		}
	}

	return false;
}

void Collaboration::saveToFile(std::ofstream& out) const {
	out.write(reinterpret_cast<const char*>(&id), sizeof(id));

	name.saveToFile(out);
	creator.saveToFile(out);

	size_t users_count = users.getSize();
	out.write(reinterpret_cast<const char*>(&users_count), sizeof(users_count));

	for (size_t i = 0; i < users_count; i++) {
		MyString user_name = users[i]->getUsername();
		user_name.saveToFile(out);
	}

	size_t tasks_count = tasks.getSize();
	out.write(reinterpret_cast<const char*>(&tasks_count), sizeof(tasks_count));

	for (size_t i = 0; i < tasks_count; i++) {
		uint32_t task_id = tasks[i]->getID();
		out.write(reinterpret_cast<const char*>(&task_id), sizeof(task_id));
	}
}

void Collaboration::readFromFile(std::ifstream& in) {
	in.read(reinterpret_cast<char*>(&id), sizeof(id));

	name.readFromFile(in);
	creator.readFromFile(in);
}
