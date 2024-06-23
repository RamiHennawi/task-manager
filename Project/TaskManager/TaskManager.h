#pragma once
#include "User.h"
#include "Task.h"
#include "TasksContainer.h"
#include "CollaborationTask.h"
#include "Collaboration.h"
#include "Vector.hpp"

// NOTE: each file has a "default/empty" state when there is no data (it contains '0' or '1 0' depending on the file
// that is so, to indicate that there that the starting id is 1 and there are 0 objects of the type
constexpr const char* FILE_DB_USERS = "users.dat";
constexpr const char* FILE_DB_TASKS = "tasks.dat";
constexpr const char* FILE_DB_COLLABORATIONS = "collaborations.dat";

// TaskManager stores all users, tasks, collabs and manages all commands!
class TaskManager {
private:
	Vector<User> users;
	TasksContainer tasks;
	Vector<Collaboration> collaborations;
	User* logged_in_user = nullptr;

	uint32_t created_tasks = 1; // to manage unique task id
	uint32_t created_collabs = 1; // to manage unique collab id

	Task& getTask(uint32_t id);
	User& getUser(const MyString& username);

	void saveТasks() const;
	void loadTasks();

	void saveUsers() const;
	void loadUsers();

	void saveCollaborations() const;
	void loadCollaborations();

public:
	TaskManager();
	~TaskManager();

	// handle user profiles
	void registerUser(const MyString& username, const MyString& password);
	void loginUser(const MyString& username, const MyString& password);
	void logoutUser();

	// handle user (personal) tasks
	void addTask(const MyString& name, const MyString& due_date_str, const MyString& description);
	void updateTaskName(uint32_t id, const MyString& new_name);
	void updateTaskDescription(uint32_t id, const MyString& new_description);

	void startTask(uint32_t id);
	void finishTask(uint32_t id);
	void deleteTask(uint32_t id);

	const Task& getUserTask(uint32_t id) const;
	const Task& getUserTask(const MyString& name) const;

	void listTasks() const;
	void listTasks(const MyString& final_date_str) const;
	void listCompletedTasks() const;

	// handle user dashboard
	void removeTaskFromDashboard(uint32_t id);
	void addTaskToDashboard(uint32_t id);
	void listDashboard() const;

	// handle collaborations
	void addCollaboration(const MyString& name);
	void deleteCollaboration(const MyString& name);

	void listCollaborations() const;
	void listTasksInCollaboration(const MyString& name) const;

	void addCollaborator(const MyString& collaboration_name, const MyString& user_name);
	void assignTaskInCollaboration(const MyString& collaboration_name, const MyString& assignee_name, const MyString& task_name, const MyString& task_final_date_str, const MyString& task_description);
};
