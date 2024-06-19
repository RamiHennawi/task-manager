#include "Collaboration.h"

Collaboration::Collaboration(uint32_t id, const MyString& name, const MyString& creator) : id(id), name(name), creator(creator) {}

void Collaboration::addUser(User& new_user) {
	size_t usersCount = users.getSize();

	for (size_t i = 0; i < usersCount; i++) {
		if (users[i] == &new_user) {
			throw std::runtime_error("User already in collaboration");
		}
	}

	users.pushBack(&new_user);
}

void Collaboration::assignTask(Task& task, User& user) {
	if (includesUser(user)) {
		tasks.pushBack(Pair<Task*, User*>(&task, &user));
	}
	else {
		throw std::runtime_error("User is not in the collaboration.");
	}
}

void Collaboration::listTasks() const {
	size_t tasksCount = tasks.getSize();

	if (tasksCount == 0) {
		std::cout << "There are no tasks.";
	}

	for (size_t i = 0; i < tasksCount; i++) {
		tasks[i].getFirst()->print();
		std::cout << "Assignee: " << tasks[i].getSecond()->getUsername() << std::endl;
		std::cout << "-----------------" << std::endl;
	}
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

const Task& Collaboration::getTaskAtIndex(size_t index) const {
	return *(tasks[index].getFirst());
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