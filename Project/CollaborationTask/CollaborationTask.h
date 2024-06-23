#pragma once
#include "Task.h"
#include "User.h"

class CollaborationTask : public Task {
private:
	MyString assignee;

public:
	CollaborationTask() = default;
	CollaborationTask(uint32_t id, const MyString& name, const MyString& due_date_str, const MyString& description, const MyString& assignee);

	const MyString& getAssignee() const;

	void print() const override;

	Task* clone() const override;
	
	// handle saving and reading from binary file
	void saveToFile(std::ofstream& out) const override;
	void readFromFile(std::ifstream& in) override;
};

