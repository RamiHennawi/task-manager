#pragma once
#include "Task.h"
#include "User.h"

class CollaborationTask : public Task {
private:
	User* assignee = nullptr;

public:
	CollaborationTask() = default;
	CollaborationTask(uint32_t id, const MyString& name, const MyString& due_date_str, const MyString& description, User& assignee);

	const User& getAssignee() const;
	User& getAssignee();

	void print() const override;
	
	// handle saving and reading from binary file
	void saveToFile(std::ofstream& out) const override;
	void readFromFile(std::ifstream& in) override;
};

