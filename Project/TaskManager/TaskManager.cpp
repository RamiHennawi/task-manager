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
		tasks[i].saveTask(out);
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
		Task* task = new Task();
		task->readTask(in);

		tasks.pushBack(*task);
	}
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
			catch (...) {
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
				std::cout << "Error occurred when loading task with ID " << loaded_id << "." << std::endl;
			}
		}

		users.pushBack(*loaded_user);
	}

	in.close();
}

void TaskManager::saveCollaborations() const {
}

void TaskManager::loadCollaborations() {
}

TaskManager::TaskManager() {
	loadTasks();
	loadUsers();
	loadCollaborations();
	// try catch!
}

TaskManager::~TaskManager() {
	saveТasks();
	saveUsers();
	saveCollaborations();
	// try catch!
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
	}
	else {
		throw std::runtime_error("No user is currently logged in.");
	}
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

void TaskManager::addCollaboration(const MyString& name) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	Collaboration new_collaboration(created_collabs++, name, logged_in_user->getUsername());
	collaborations.pushBack(new_collaboration);
}

void TaskManager::deleteCollaboration(const MyString& name) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	size_t collaborations_count = collaborations.getSize();
	for (size_t i = 0; i < collaborations_count; i++) {
		if (collaborations[i].getName() == name) {
			size_t tasks_count = collaborations[i].getTasksCount();

			for (size_t j = 0; j < tasks_count; j++) {
				Task current_task = collaborations[i].getTaskAtIndex(j);
				size_t users_count = users.getSize();

				/*for (size_t k = 0; k < users_count; k++) {
					if (collaborations[i].includesUser(users[k].getUsername()) && users[k].hasTask(current_task.getName(), current_task.getDueDate())) {
						uint32_t task_id = users[k].getTask(current_task.getName()).getID();
						users[k].deleteTask(task_id);
					}
				}*/
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
			std::cout << collaborations[i].getName() << ", ";
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
	/*if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	size_t collaborations_count = collaborations.getSize();

	for (size_t i = 0; i < collaborations_count; i++) {
		if (collaborations[i].getName() == collaboration_name) {
			collaborations[i].addUser(getUser(user_name));
			return;
		}
	}

	throw std::runtime_error("No collaboration with that name found.");*/
}

void TaskManager::assignTaskInCollaboration(const MyString& collaboration_name, const MyString& asignee_name, const MyString& task_name, const MyString& task_final_date_str, const MyString& task_description) {
	if (!logged_in_user) {
		throw std::runtime_error("No user is currently logged in.");
	}

	Task new_task(created_tasks++, task_name, task_final_date_str, task_description);

	size_t collaborations_count = collaborations.getSize();

	for (size_t i = 0; i < collaborations_count; i++) {
		if (collaborations[i].getName() == collaboration_name) {
			/*collaborations[i].assignTask(new_task, getUser(asignee_name));*/
			// check if user exists?
			
			size_t users_count = users.getSize();
			for (size_t j = 0; j < users_count; j++) {
				if (users[i].getUsername() == asignee_name) {
					users[i].addTask(new_task);
					break;
				}
			}

			return;
		}
	}

	throw std::runtime_error("No collaboration with that name found.");
}
