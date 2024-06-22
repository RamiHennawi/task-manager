#include "UserInterface.h"
#include <sstream>

void UserInterface::registerUser(std::stringstream& ss) {
	char username[ARGUMENT_SIZE], password[ARGUMENT_SIZE];
	ss >> username >> password;

	try {
		task_manager.registerUser(username, password);
		std::cout << "User successfully registered!\n";
	}
	catch (std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::loginUser(std::stringstream& ss) {
	char username[ARGUMENT_SIZE], password[ARGUMENT_SIZE];
	ss >> username >> password;

	try {
		task_manager.loginUser(username, password);
		std::cout << "Welcome back, " << username << "!\n";
	}
	catch (std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::logout() {
	try {
		task_manager.logoutUser();
		std::cout << "Logged out successfully!\n";
	}
	catch (std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::addTask(std::stringstream& ss) {
	char name[ARGUMENT_SIZE], date[ARGUMENT_SIZE], desc[ARGUMENT_SIZE];
	ss >> name >> date;
	ss.ignore(); // ignore additional ' '
	ss.getline(desc, ARGUMENT_SIZE); // it could have ' '

	try {
		task_manager.addTask(name, date, desc);
		std::cout << "Task added succesfully!\n";
	}
	catch (std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (std::exception& exc) {
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
		// check if it was get-task id
		std::stringstream numberString(name);

		uint32_t id;
		numberString >> id;

		try {
			task_manager.getUserTask(id).print();
		}
		catch (std::runtime_error& exc) {
			std::cout << exc.what() << std::endl;
		}
	}
}

void UserInterface::updateTaskName(std::stringstream& ss) {
	uint32_t id;
	char name[ARGUMENT_SIZE];
	ss >> id >> name;

	try {
		task_manager.updateTaskName(id, name);
		std::cout << "Task name updated succesfully!\n";
	}
	catch (std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::updateTaskDescription(std::stringstream& ss) {
	uint32_t id;
	char desc[ARGUMENT_SIZE];
	ss >> id >> desc;

	try {
		task_manager.updateTaskDescription(id, desc);
		std::cout << "Task description updated succesfully!\n";
	}
	catch (std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::startTask(std::stringstream& ss) {
	uint32_t id;
	ss >> id;

	try {
		task_manager.startTask(id);
		std::cout << "Task started succesfully!\n";
	}
	catch (std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::finishTask(std::stringstream& ss) {
	uint32_t id;
	ss >> id;

	try {
		task_manager.finishTask(id);
		std::cout << "Task finished succesfully!\n";
	}
	catch (std::runtime_error& exc) {
		std::cout << exc.what() << std::endl;
	}
}

void UserInterface::deleteTask(std::stringstream& ss) {
	uint32_t id;
	ss >> id;

	try {
		task_manager.deleteTask(id);
		std::cout << "Task finished succesfully!\n";
	}
	catch (std::runtime_error& exc) {
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
		else {
			std::cout << "Invalid command!\n";
		}

		ss.clear();
		std::cout << "> ";
	}

	std::cout << "Exited successfully!\n";
	return;
}
