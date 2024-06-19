#pragma once
#include <ctime>
#include "MyString.h"

enum class TaskStatus {
	ON_HOLD,
	IN_PROCESS,
	DONE,
	OVERDUE,
};

namespace TaskHelperFunctions {
	time_t convertDateString(const MyString& date_str);
}

class Task {
private:
	uint32_t id; // to be handled by TaskManager (unique id = created tasks count)
	TaskStatus status;
	time_t due_date;
	MyString name;
	MyString description;

	const char* getStatusString() const;

public:
	Task(uint32_t id, const MyString& name, const MyString& due_date_str, const MyString& description);

	uint32_t getID() const;
	TaskStatus getStatus() const;
	time_t getDueDate() const;
	const MyString& getName() const;
	const MyString& getDescription() const;

	void updateName(const MyString& new_name);
	void updateDescription(const MyString& new_description);

	void start();
	void finish();

	void print() const;
};
