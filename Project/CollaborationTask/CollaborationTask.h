#pragma once
#include "Task.h"
#include "User.h"

class CollaborationTask : public Task {
private:
	User* assignee = nullptr;

public:
	CollaborationTask(uint32_t id, const MyString& name, const MyString& due_date_str, const MyString& description, User& assignee);

	const User& getAssignee() const;

	void print() const override;
	
	void saveTask(std::ofstream& out) const override;
	void readTask(std::ifstream& in) override;
};

