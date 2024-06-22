#pragma once
#include "User.h"
#include "Task.h"
#include "Collaboration.h"
#include "Vector.hpp"

constexpr const char* FILE_DB_USERS = "users.dat";
constexpr const char* FILE_DB_TASKS = "tasks.dat";
constexpr const char* FILE_DB_COLLABORATIONS = "collaborations.dat";

class TaskManager {
private:
	Vector<User> users;
	Vector<Task> tasks;
	Vector<Collaboration> collaborations;
	User* logged_in_user = nullptr;

	uint32_t created_tasks = 0;
	uint32_t created_collabs = 0;

	Task& getTask(uint32_t id);

	void saveТasks() const;
	void loadTasks();

	void saveUsers() const;
	void loadUsers();

	void saveCollaborations() const;
	void loadCollaborations();

public:
	TaskManager();
	~TaskManager();

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

	const Task& getUserTask(uint32_t id) const; // moje bi da e fr print?
	const Task& getUserTask(const MyString& name) const;

	void listTasks() const;
	void listTasks(const MyString& final_date_str) const;
	void listCompletedTasks() const;

	void addCollaboration(const MyString& name);
	void deleteCollaboration(const MyString& name);

	void listCollaborations() const;
	void listTasksInCollaboration(const MyString& name) const;

	void addCollaborator(const MyString& collaboration_name, const MyString& user_name);
	void assignTaskInCollaboration(const MyString& collaboration_name, const MyString& asignee_name, const MyString& task_name, const MyString& task_final_date_str, const MyString& task_description);
};
