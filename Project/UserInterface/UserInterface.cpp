#include "UserInterface.h"
#include <sstream>

void UserInterface::registerUser(std::stringstream& ss) {
	char username[ARGUMENT_SIZE], password[ARGUMENT_SIZE];
	ss >> username >> password;

	// validate input
	if (!strlen(username) || !strlen(password)) {
		std::cout << "Invalid input. Format is 'register <username> <password>'.\n";
		return;
	}

	try {
		task_manager.registerUser(username, password);
		std::cout << "User successfully registered!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::loginUser(std::stringstream& ss) {
	char username[ARGUMENT_SIZE], password[ARGUMENT_SIZE];
	ss >> username >> password;

	// validate input
	if (!strlen(username) || !strlen(password)) {
		std::cout << "Invalid input. Format is 'login <username> <password>'.\n";
		return;
	}

	try {
		task_manager.loginUser(username, password);
		std::cout << "Welcome back, " << username << "!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::logout() {
	try {
		task_manager.logoutUser();
		std::cout << "Logged out successfully!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::addTask(std::stringstream& ss) {
	char name[ARGUMENT_SIZE], date[ARGUMENT_SIZE], desc[ARGUMENT_SIZE];
	ss >> name >> date;
	ss.ignore(); // ignore additional ' '
	ss.getline(desc, ARGUMENT_SIZE); // it could have ' '

	// validate input
	if (!strlen(name) || !strlen(date) || !strlen(desc)) {
		std::cout << "Invalid input. Format is 'add-task <name> <due_date> <description>'.\n";
		return;
	}

	try {
		task_manager.addTask(name, date, desc);
		std::cout << "Task added succesfully!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (const std::exception& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::getTask(std::stringstream& ss) {
	char name[ARGUMENT_SIZE];
	ss >> name;

	try {
		task_manager.getUserTask(name).print();
	}
	catch (std::runtime_error& exc) {
		// check if it was get-task <id>
		std::stringstream numberString(name);

		uint32_t id;
		numberString >> id;

		try {
			task_manager.getUserTask(id).print();
		}
		catch (const std::runtime_error& exc) {
			std::cout << exc.what() << std::endl;
		}
	}
}

void UserInterface::updateTaskName(std::stringstream& ss) {
	uint32_t id;
	char name[ARGUMENT_SIZE];
	ss >> id >> name;

	// validate input
	if (!id || !strlen(name)) {
		std::cout << "Invalid input. Format is 'update-task-name <id> <name>'.\n";
		return;
	}

	try {
		task_manager.updateTaskName(id, name);
		std::cout << "Task name updated succesfully!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::updateTaskDescription(std::stringstream& ss) {
	uint32_t id;
	char desc[ARGUMENT_SIZE];
	ss >> id >> desc;

	// validate input
	if (!id || !strlen(desc)) {
		std::cout << "Invalid input. Format is 'update-task-description <id> <description>'.\n";
		return;
	}

	try {
		task_manager.updateTaskDescription(id, desc);
		std::cout << "Task description updated succesfully!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::startTask(std::stringstream& ss) {
	uint32_t id;
	ss >> id;

	// validate input
	if (!id) {
		std::cout << "Invalid input. Format is 'start-task <id>'.\n";
		return;
	}

	try {
		task_manager.startTask(id);
		std::cout << "Task started succesfully!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::finishTask(std::stringstream& ss) {
	uint32_t id;
	ss >> id;

	// validate input
	if (!id) {
		std::cout << "Invalid input. Format is 'finish-task <id>'.\n";
		return;
	}

	try {
		task_manager.finishTask(id);
		std::cout << "Task finished succesfully! Congrats on completing it!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::deleteTask(std::stringstream& ss) {
	uint32_t id;
	ss >> id;

	// validate input
	if (!id) {
		std::cout << "Invalid input. Format is 'delete-task <id>'.\n";
		return;
	}

	try {
		task_manager.deleteTask(id);
		std::cout << "Task deleted succesfully!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::listTasks(std::stringstream& ss) const {
	char input[ARGUMENT_SIZE];
	ss >> input;

	if (!strlen(input)) {
		try {
			task_manager.listTasks();
		}
		catch (const std::runtime_error& exc) {
			std::cout << exc.what() << std::endl;
		}
	}
	else {
		// check if it was get-task <collab-name>
		try {
			task_manager.listTasksInCollaboration(input);
		}
		catch (const std::runtime_error& e) {
			// check if it was get-task <date>
			try {
				task_manager.listTasks(input);
			}
			catch (const std::runtime_error& exc) {
				std::cout << exc.what() << std::endl;
			}
			catch (...) {
				std::cout << "No collaboration with that name found or incorrect data format (must be yyyy-mm-dd)." << std::endl;
			}

		}
	}
}

void UserInterface::listCompletedTasks() const {
	try {
		task_manager.listCompletedTasks();
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::removeTaskFromDashboard(std::stringstream& ss) {
	uint32_t id;
	ss >> id;

	// validate input
	if (!id) {
		std::cout << "Invalid input. Format is 'remove-task-from-dashboard <id>'.\n";
		return;
	}

	try {
		task_manager.removeTaskFromDashboard(id);
		std::cout << "Task removed successfully!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::addTaskToDashboard(std::stringstream& ss) {
	uint32_t id;
	ss >> id;

	// validate input
	if (!id) {
		std::cout << "Invalid input. Format is 'add-task-to-dashboard <id>'.\n";
		return;
	}

	try {
		task_manager.addTaskToDashboard(id);
		std::cout << "Task added successfully!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (const std::logic_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::listDashboard() const {
	try {
		task_manager.listDashboard();
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::addCollaboration(std::stringstream& ss) {
	char name[ARGUMENT_SIZE];
	ss >> name;

	// validate input
	if (!strlen(name)) {
		std::cout << "Invalid input. Format is 'add-collaboration <name>'.\n";
		return;
	}

	try {
		task_manager.addCollaboration(name);
		std::cout << "Collaboration added succesfully!\n";
	}
	catch(const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::deleteCollaboration(std::stringstream& ss) {
	char name[ARGUMENT_SIZE];
	ss >> name;

	// validate input
	if (!strlen(name)) {
		std::cout << "Invalid input. Format is 'delete-collaboration <name>'.\n";
		return;
	}

	try {
		task_manager.deleteCollaboration(name);
		std::cout << "Collaboration deleted succesfully!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::listCollaborations() const {
	try {
		task_manager.listCollaborations();
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::addUserToCollaboration(std::stringstream& ss) {
	char collab_name[ARGUMENT_SIZE], user_name[ARGUMENT_SIZE];
	ss >> collab_name >> user_name;

	// validate input
	if (!strlen(collab_name) || !strlen(user_name)) {
		std::cout << "Invalid input. Format is 'add-user <collaboration name> <username>'.\n";
		return;
	}

	try {
		task_manager.addCollaborator(collab_name, user_name);
		std::cout << "User added succesfully to " << collab_name << "!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::assignTaskInCollaboration(std::stringstream& ss) {
	char collab_name[ARGUMENT_SIZE], user_name[ARGUMENT_SIZE], task_name[ARGUMENT_SIZE], task_date[ARGUMENT_SIZE], task_desc[ARGUMENT_SIZE];
	ss >> collab_name >> user_name >> task_name >> task_date;
	ss.ignore(); // ignore additional ' '
	ss.getline(task_desc, ARGUMENT_SIZE); // it could have ' '

	// validate input
	if (!strlen(collab_name) || !strlen(user_name) || !strlen(task_name) || !strlen(task_date) || !strlen(task_desc)) {
		std::cout << "Invalid input. Format is 'assign-task <collaboration name> <username> <task name> <task due_date> <task description>'.\n";
		return;
	}

	try {
		task_manager.assignTaskInCollaboration(collab_name, user_name, task_name, task_date, task_desc);
		std::cout << "Task assigned succesfully to " << user_name << "!\n";
	}
	catch (const std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::start() {
	std::cout << "TASK MANAGER\n\n";
	std::cout << "> ";

	while (true) {
		char buffer[BUFFER_SIZE];
		std::cin.getline(buffer, BUFFER_SIZE, '\n');

		std::stringstream ss(buffer);

		char command[COMMAND_SIZE];
		ss.getline(command, COMMAND_SIZE, ' ');

		if (strcmp(command, COMMANDS::EXIT) == 0) {
			break;
		}
		else if (strcmp(command, COMMANDS::REGISTER) == 0) {
			registerUser(ss);
		}
		else if (strcmp(command, COMMANDS::LOGIN) == 0) {
			loginUser(ss);
		}
		else if (strcmp(command, COMMANDS::LOGOUT) == 0) {
			logout();
		}
		else if (strcmp(command, COMMANDS::ADD_TASK) == 0) {
			addTask(ss);
		}
		else if (strcmp(command, COMMANDS::GET_TASK) == 0) {
			getTask(ss);
		}
		else if (strcmp(command, COMMANDS::UPDATE_TASK_NAME) == 0) {
			updateTaskName(ss);
		}
		else if (strcmp(command, COMMANDS::UPDATE_TASK_DESC) == 0) {
			updateTaskDescription(ss);
		}
		else if (strcmp(command, COMMANDS::START_TASK) == 0) {
			startTask(ss);
		}
		else if (strcmp(command, COMMANDS::FINISH_TASK) == 0) {
			finishTask(ss);
		}
		else if (strcmp(command, COMMANDS::DELETE_TASK) == 0) {
			deleteTask(ss);
		}
		else if (strcmp(command, COMMANDS::LIST_TASKS) == 0) {
			listTasks(ss);
		}
		else if (strcmp(command, COMMANDS::LIST_COMPLETED_TASKS) == 0) {
			listCompletedTasks();
		}
		else if (strcmp(command, COMMANDS::REMOVE_TASK_FROM_DASHBOARD) == 0) {
			removeTaskFromDashboard(ss);
		}
		else if (strcmp(command, COMMANDS::ADD_TASK_TO_DASHBOARD) == 0) {
			addTaskToDashboard(ss);
		}
		else if (strcmp(command, COMMANDS::LIST_DASHBOARD) == 0) {
			listDashboard();
		}
		else if (strcmp(command, COMMANDS::ADD_COLLABORATION) == 0) {
			addCollaboration(ss);
		}
		else if (strcmp(command, COMMANDS::DELETE_COLLABORATION) == 0) {
			deleteCollaboration(ss);
		}
		else if (strcmp(command, COMMANDS::LIST_COLLABORATIONS) == 0) {
			listCollaborations();
		}
		else if (strcmp(command, COMMANDS::ADD_USER_TO_COLLABORATION) == 0) {
			addUserToCollaboration(ss);
		}
		else if (strcmp(command, COMMANDS::ASSIGN_TASK_IN_COLLABORATION) == 0) {
			assignTaskInCollaboration(ss);
		}
		else {
			std::cout << "Invalid command!\n";
		}

		ss.clear();
		std::cout << "> ";
	}

	std::cout << "Exited successfully!\n";
	return;
}
