#pragma once
#include "TaskManager.h"

constexpr size_t BUFFER_SIZE = 1024;
constexpr size_t COMMAND_SIZE = 50;
constexpr size_t ARGUMENT_SIZE = 100;

namespace COMMANDS {
	constexpr const char* EXIT = "exit";

	constexpr const char* REGISTER = "register";
	constexpr const char* LOGIN = "login";
	constexpr const char* LOGOUT = "logout";

	constexpr const char* ADD_TASK = "add-task";
	constexpr const char* GET_TASK = "get-task";

	constexpr const char* UPDATE_TASK_NAME = "update-task-name";
	constexpr const char* UPDATE_TASK_DESC = "update-task-description";

	constexpr const char* START_TASK = "start-task";
	constexpr const char* FINISH_TASK = "finish-task";
	constexpr const char* DELETE_TASK = "delete-task";

	constexpr const char* LIST_TASKS = "list-tasks";
	constexpr const char* LIST_COMPLETED_TASKS = "list-completed-tasks";

	constexpr const char* REMOVE_TASK_FROM_DASHBOARD = "remove-task-from-dashboard";
	constexpr const char* ADD_TASK_TO_DASHBOARD = "add-task-to-dashboard";
	constexpr const char* LIST_DASHBOARD = "list-dashboard";

	constexpr const char* ADD_COLLABORATION = "add-collaboration";
	constexpr const char* DELETE_COLLABORATION = "delete-collaboration";
	constexpr const char* LIST_COLLABORATIONS = "list-collaborations";
	constexpr const char* ADD_USER_TO_COLLABORATION = "add-user";
	constexpr const char* ASSIGN_TASK_IN_COLLABORATION = "assign-task";
}

class UserInterface {
private:
	TaskManager task_manager;

	void registerUser(std::stringstream& ss);
	void loginUser(std::stringstream& ss);
	void logout();

	void addTask(std::stringstream& ss);
	void getTask(std::stringstream& ss);

	void updateTaskName(std::stringstream& ss);
	void updateTaskDescription(std::stringstream& ss);

	void startTask(std::stringstream& ss);
	void finishTask(std::stringstream& ss);
	void deleteTask(std::stringstream& ss);

	void listTasks(std::stringstream& ss) const;
	void listCompletedTasks() const;

	void removeTaskFromDashboard(std::stringstream& ss);
	void addTaskToDashboard(std::stringstream& ss);
	void listDashboard() const;

	void addCollaboration(std::stringstream& ss);
	void deleteCollaboration(std::stringstream& ss);
	void listCollaborations() const;
	void addUserToCollaboration(std::stringstream& ss);
	void assignTaskInCollaboration(std::stringstream& ss);

public:
	void start();
};

