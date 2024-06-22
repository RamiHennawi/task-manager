#include "CollaborationTask.h"
#pragma warning(disable : 4996)

CollaborationTask::CollaborationTask(uint32_t id, const MyString& name, const MyString& due_date_str, const MyString& description, User& assignee)
	: Task(id, name, due_date_str, description), assignee(&assignee) {}

const User& CollaborationTask::getAssignee() const {
	return *assignee;
}

void CollaborationTask::print() const {
	std::cout << "Task ID: " << id << std::endl;
	std::cout << "Task name: " << name << std::endl;
	std::cout << "Task description: " << description << std::endl;
	std::cout << "Due date: " << ctime(&due_date);
	std::cout << "Status: " << getStatusString() << std::endl;
	std::cout << "Assignee: " << getAssignee().getUsername() << std::endl;
}

void CollaborationTask::saveTask(std::ofstream& out) const {
	out.write(reinterpret_cast<const char*>(&id), sizeof(id));
	out.write(reinterpret_cast<const char*>(&status), sizeof(status));
	out.write(reinterpret_cast<const char*>(&due_date), sizeof(due_date));

	name.saveToFile(out);
	description.saveToFile(out);
	assignee->saveToFile(out);
}

void CollaborationTask::readTask(std::ifstream& in) {
	in.read(reinterpret_cast<char*>(&id), sizeof(id));
	in.read(reinterpret_cast<char*>(&status), sizeof(status));
	in.read(reinterpret_cast<char*>(&due_date), sizeof(due_date));

	name.readFromFile(in);
	description.readFromFile(in);
	assignee->readFromFile(in);
}
