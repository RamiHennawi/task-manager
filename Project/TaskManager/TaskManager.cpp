#include "TaskManager.h"
#include <fstream>

Task& TaskManager::getTask(uint32_t id) {
	size_t tasks_count = tasks.getSize();

	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i].getID() == id) {
			return tasks[i];
		}
	}

	throw std::runtime_error("No task with that ID found.");
}

User& TaskManager::getUser(const MyString& username) {
	size_t users_count = users.getSize();

	for (size_t i = 0; i < users_count; i++) {
		if (users[i].getUsername() == username) {
			return users[i];
		}
	}

	throw std::runtime_error("No user with that username found.");
}

void TaskManager::saveТasks() const {
	std::ofstream out(FILE_DB_TASKS, std::ios::binary | std::ios::out);

	if (!out.is_open()) {
		throw std::runtime_error("Unable to open tasks DB.");
	}
	
	size_t tasks_count = tasks.getSize();
	out.write(reinterpret_cast<const char*>(&tasks_count), sizeof(tasks_count));

	// save the number of created tasks, so we can use it on next load as id
	out.write(reinterpret_cast<const char*>(&created_tasks), sizeof(created_tasks));

	for (size_t i = 0; i < tasks_count; i++) {
		tasks[i].saveToFile(out);
	}

	out.close();
}

void TaskManager::loadTasks() {
	std::ifstream in(FILE_DB_TASKS, std::ios::binary | std::ios::in);

	if (!in.is_open()) {
		throw std::runtime_error("Unable to open tasks DB.");
	}

	size_t tasks_count;
	in.read(reinterpret_cast<char*>(&tasks_count), sizeof(tasks_count));

	uint32_t current_id;
	in.read(reinterpret_cast<char*>(&current_id), sizeof(current_id));
	created_tasks = current_id;

	for (size_t i = 0; i < tasks_count; i++) {
		Task* task = new Task();;
		task->readFromFile(in);

		tasks.pushBack(*task); // add the task to the vector
	}

	in.close();
}

void TaskManager::saveUsers() const {
	std::ofstream out(FILE_DB_USERS, std::ios::binary | std::ios::out);

	if (!out.is_open()) {
		throw std::runtime_error("Unable to open users DB.");
	}

	size_t users_count = users.getSize();
	out.write(reinterpret_cast<const char*>(&users_count), sizeof(users_count));

	for (size_t i = 0; i < users_count; i++) {
		users[i].saveToFile(out);
	}

	out.close();
}

void TaskManager::loadUsers() {
	std::ifstream in(FILE_DB_USERS, std::ios::binary);

	if (!in.is_open()) {
		throw std::runtime_error("Unable to open users DB.");
	}

	size_t users_count;
	in.read(reinterpret_cast<char*>(&users_count), sizeof(users_count));

	for (size_t i = 0; i < users_count; i++) {
		User* loaded_user = new User();
		loaded_user->readFromFile(in);

		// load user's tasks
		size_t user_tasks_count;
		in.read(reinterpret_cast<char*>(&user_tasks_count), sizeof(user_tasks_count));

		for (size_t j = 0; j < user_tasks_count; j++) {
			uint32_t loaded_id;
			in.read(reinterpret_cast<char*>(&loaded_id), sizeof(loaded_id));

			try {
				loaded_user->addTask(getTask(loaded_id));
			}
			catch (std::exception& exc) {
				std::cout << "Error occurred when loading task with ID " << loaded_id << "." << std::endl;
			}
		}

		// load users's dashboard tasks
		size_t user_dashboard_tasks_count;
		in.read(reinterpret_cast<char*>(&user_dashboard_tasks_count), sizeof(user_dashboard_tasks_count));

		for (size_t j = 0; j < user_dashboard_tasks_count; j++) {
			uint32_t loaded_id;
			in.read(reinterpret_cast<char*>(&loaded_id), sizeof(loaded_id));

			try {
				loaded_user->addTaskToDashboard(loaded_id);
			}
			catch (...) {
				std::cout << "Error occurred when adding to dashboard task with ID " << loaded_id << "." << std::endl;
			}
		}

		loaded_user->syncTasks(); // sync the tasks with the current time
		users.pushBack(*loaded_user); // add the user to the vector
	}

	in.close();
}

void TaskManager::saveCollaborations() const {
	std::ofstream out(FILE_DB_COLLABORATIONS, std::ios::binary | std::ios::out);

	if (!out.is_open()) {
		throw std::runtime_error("Unable to open collaborations DB.");
	}

	size_t collabs_count = collaborations.getSize();
	out.write(reinterpret_cast<const char*>(&collabs_count), sizeof(collabs_count));

	// save the number of created collabs, so we can use it on next load as id
	out.write(reinterpret_cast<const char*>(&created_collabs), sizeof(created_collabs));

	for (size_t i = 0; i < collabs_count; i++) {
		collaborations[i].saveToFile(out);
	}

	out.close();
}

void TaskManager::loadCollaborations() {
	std::ifstream in(FILE_DB_COLLABORATIONS, std::ios::binary | std::ios::in);

	if (!in.is_open()) {
		throw std::runtime_error("Unable to open collaborations DB.");
	}

	size_t collabs_count;
	in.read(reinterpret_cast<char*>(&collabs_count), sizeof(collabs_count));

	uint32_t current_id;
	in.read(reinterpret_cast<char*>(&current_id), sizeof(current_id));
	created_collabs = current_id;

	for (size_t i = 0; i < collabs_count; i++) {
		Collaboration* collab = new Collaboration();
		collab->readFromFile(in);

		// load users in collaboration
		size_t collab_users_count;
		in.read(reinterpret_cast<char*>(&collab_users_count), sizeof(collab_users_count));

		for (size_t j = 0; j < collab_users_count; j++) {
			MyString user_name;
			user_name.readFromFile(in);

			try {
				collab->addUser(getUser(user_name));
			}
			catch (std::exception& exc) {
				std::cout << exc.what() << std::endl;
			}
		}

		// load tasks in collaboration
		size_t collab_tasks_count;
		in.read(reinterpret_cast<char*>(&collab_tasks_count), sizeof(collab_tasks_count));

		for (size_t j = 0; j < collab_tasks_count; j++) {
			uint32_t loaded_id;
			in.read(reinterpret_cast<char*>(&loaded_id), sizeof(loaded_id));

			try {
				collab->addTask(getTask(loaded_id));
			}
			catch (std::exception& exc) {
				std::cout << exc.what() << std::endl;
			}
		}

		collaborations.pushBack(*collab); // add the collaboration to the vector
	}

	in.close();
}

TaskManager::TaskManager() {
	// load all resources when starting (creating task-manager)
	try {
		loadTasks();
	} 
	catch (const std::exception& exc) {
		std::cout << "Error with loading tasks: " << exc.what() << std::endl;
	}

	try {
		loadUsers();
	}
	catch (const std::exception& exc) {
		std::cout << "Error with loading users: " << exc.what() << std::endl;
	}

	try {
		loadCollaborations();
	}
	catch (const std::exception& exc) {
		std::cout << "Error with loading collaborations: " << exc.what() << std::endl;
	}
}

TaskManager::~TaskManager() {
	// save all resources when exiting (deleting task-manager)
	try {
		saveТasks();
	}
	catch (const std::exception& exc) {
		std::cout << "Error with saving tasks: " << exc.what() << std::endl;
	}

	try {
		saveUsers();
	}
	catch (const std::exception& exc) {
		std::cout << "Error with saving users: " << exc.what() << std::endl;
	}

	try {
		saveCollaborations();
	}
	catch (const std::exception& exc) {
		std::cout << "Error with saving collaborations: " << exc.what() << std::endl;
	}
}

void TaskManager::registerUser(const MyString& username, const MyString& password) {
	size_t usersCount = users.getSize();

	for (size_t i = 0; i < usersCount; i++) {
		if (users[i].getUsername() == username) {
			throw std::runtime_error("User already registered!");
		}
	}

	User* new_user = new User(username, password);
	users.pushBack(*new_user);
}

void TaskManager::loginUser(const MyString& username, const MyString& password) {
	size_t usersCount = users.getSize();

	for (size_t i = 0; i < usersCount; i++) {
		if (users[i].getUsername() == username && users[i].getPassword() == password) {
			logged_in_user = &users[i];
			return;
		}
	}

	throw std::runtime_error("Invalid username or password.");
}

void TaskManager::logoutUser() {
	if (logged_in_user) {
		logged_in_user = nullptr;
		return; 
	}
	
	throw std::runtime_error("No user is currently logged in.");
}

void TaskManager::addTask(const MyString& name, const MyString& due_date_str, const MyString& description) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	Task* new_task = new Task(created_tasks++, name, due_date_str, description);
	tasks.pushBack(*new_task);
	logged_in_user->addTask(*new_task);
}

void TaskManager::updateTaskName(uint32_t id, const MyString& new_name) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->updateTaskName(id, new_name);
}

void TaskManager::updateTaskDescription(uint32_t id, const MyString& new_description) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->updateTaskDescription(id, new_description);
}

void TaskManager::startTask(uint32_t id) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->startTask(id);
}

void TaskManager::finishTask(uint32_t id) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->finishTask(id);
}

void TaskManager::deleteTask(uint32_t id) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	// delete from the user list + dashboard
	logged_in_user->deleteTask(id);

	// delete from tasks vector
	size_t tasks_count = tasks.getSize();
	for (size_t i = 0; i < tasks_count; i++) {
		if (tasks[i].getID() == id) {
			tasks.popAt(i);
		}
	}

	// delete from collaborations
	size_t collabs_count = collaborations.getSize();
	for (size_t i = 0; i < collabs_count; i++) {
		try {
			collaborations[i].removeTask(id);
		} catch (...) {}
	}
}

const Task& TaskManager::getUserTask(uint32_t id) const {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->getTask(id);
}

const Task& TaskManager::getUserTask(const MyString& name) const {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->getTask(name);
}

void TaskManager::listTasks() const {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->listTasks();
}

void TaskManager::listTasks(const MyString& final_date_str) const {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->listTasks(final_date_str);
}

void TaskManager::listCompletedTasks() const {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->listCompletedTasks();
}

void TaskManager::removeTaskFromDashboard(uint32_t id) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->removeTaskFromDashboard(id);
}

void TaskManager::addTaskToDashboard(uint32_t id) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->addTaskToDashboard(id);
}

void TaskManager::listDashboard() const {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	logged_in_user->listDashboard();
}

void TaskManager::addCollaboration(const MyString& name) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	Collaboration* new_collaboration = new Collaboration(created_collabs++, name, logged_in_user->getUsername());
	collaborations.pushBack(*new_collaboration);
}

void TaskManager::deleteCollaboration(const MyString& name) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	size_t collaborations_count = collaborations.getSize();
	for (size_t i = 0; i < collaborations_count; i++) {
		// find the collaboration by name
		if (collaborations[i].getName() == name) {
			size_t tasks_count = collaborations[i].getTasksCount();

			// get the id of the task and then remove it (we pop it at the end from the vector in colaborations 
			// => we always work with the task at index 0
			for (size_t j = 0; j < tasks_count; j++) {
				deleteTask(collaborations[i].getTaskIDAtIndex(0));
			}

			collaborations.popAt(i);
			return;
		}
	}

	throw std::runtime_error("No collaboration with that name found.");
}

void TaskManager::listCollaborations() const {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	size_t collaborations_count = collaborations.getSize();

	if (collaborations_count == 0) {
		throw std::runtime_error("User is not part of any collaborations.");
	}

	for (size_t i = 0; i < collaborations_count; i++) {
		if (collaborations[i].includesUser(logged_in_user->getUsername())) {
			std::cout << collaborations[i].getName();

			if (i != (collaborations_count - 1)) {
				std::cout << "; ";
			}
		}
	}

	std::cout << std::endl;
}

void TaskManager::listTasksInCollaboration(const MyString& name) const {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	size_t collaborations_count = collaborations.getSize();

	for (size_t i = 0; i < collaborations_count; i++) {
		if (collaborations[i].getName() == name) {
			collaborations[i].listTasks();
			return;
		}
	}

	throw std::runtime_error("No collaboration with that name found.");
}

void TaskManager::addCollaborator(const MyString& collaboration_name, const MyString& user_name) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	size_t collaborations_count = collaborations.getSize();

	for (size_t i = 0; i < collaborations_count; i++) {
		if (collaborations[i].getName() == collaboration_name) {
			collaborations[i].addUser(getUser(user_name));
			return;
		}
	}

	throw std::runtime_error("No collaboration with that name found.");
}

void TaskManager::assignTaskInCollaboration(const MyString& collaboration_name, const MyString& assignee_name, const MyString& task_name, const MyString& task_final_date_str, const MyString& task_description) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	CollaborationTask* new_task = new CollaborationTask(created_tasks++, task_name, task_final_date_str, task_description, getUser(assignee_name));

	size_t collaborations_count = collaborations.getSize();
	for (size_t i = 0; i < collaborations_count; i++) {
		// find collaboration
		if (collaborations[i].getName() == collaboration_name) {
			// check if assignee is in the collaboration
			if (!collaborations[i].includesUser(assignee_name)) {
				throw std::runtime_error("Assignee is not a part of the collaboration.");
			}

			tasks.pushBack(*new_task);
			collaborations[i].addTask(*new_task);
			getUser(assignee_name).addTask(*new_task);
			return;
		}
	}

	throw std::runtime_error("No collaboration with that name found.");
}
