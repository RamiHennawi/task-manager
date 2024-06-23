#include "CollaborationTask.h"
#pragma warning(disable : 4996)

CollaborationTask::CollaborationTask(uint32_t id, const MyString& name, const MyString& due_date_str, const MyString& description, const MyString& assignee)
	: Task(id, name, due_date_str, description), assignee(assignee) {}

const MyString& CollaborationTask::getAssignee() const {
	return assignee;
}

void CollaborationTask::print() const {
	std::cout << "Task ID: " << id << std::endl;
	std::cout << "Task name: " << name << std::endl;
	std::cout << "Task description: " << description << std::endl;
	std::cout << "Due date: " << ctime(&due_date);
	std::cout << "Status: " << getStatusString() << std::endl;
	std::cout << "Assignee: " << assignee << std::endl;
}

Task* CollaborationTask::clone() const {
	return new CollaborationTask(*this);
}

void CollaborationTask::saveToFile(std::ofstream& out) const {
	short type = 1;
	out.write(reinterpret_cast<const char*>(&type), sizeof(type));

	out.write(reinterpret_cast<const char*>(&id), sizeof(id));
	out.write(reinterpret_cast<const char*>(&status), sizeof(status));
	out.write(reinterpret_cast<const char*>(&due_date), sizeof(due_date));

	name.saveToFile(out);
	description.saveToFile(out);
	assignee.saveToFile(out);
}

void CollaborationTask::readFromFile(std::ifstream& in) {
	in.read(reinterpret_cast<char*>(&id), sizeof(id));
	in.read(reinterpret_cast<char*>(&status), sizeof(status));
	in.read(reinterpret_cast<char*>(&due_date), sizeof(due_date));

	name.readFromFile(in);
	description.readFromFile(in);
	assignee.readFromFile(in);
}
