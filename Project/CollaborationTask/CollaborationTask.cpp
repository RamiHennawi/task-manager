#include "CollaborationTask.h"

CollaborationTask::CollaborationTask(uint32_t id, const MyString& name, const MyString& due_date_str, const MyString& description, User& assignee)
	: Task(id, name, due_date_str, description), assignee(&assignee) {}

const User& CollaborationTask::getAssignee() const {
	return *assignee;
}
