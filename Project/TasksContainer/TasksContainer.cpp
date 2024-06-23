#include "TasksContainer.h"
#include "CollaborationTask.h"

namespace {
    const int DEFAULT_CAPACITY = 8;
}

void TasksContainer::resize() {
    Task** newCollection = new Task * [capacity *= 2];
    for (size_t i = 0; i < count; i++) {
        newCollection[i] = tasks[i];
    }

    delete[] tasks;
    tasks = newCollection;
}

TasksContainer::TasksContainer() : count(0), capacity(DEFAULT_CAPACITY) {
    tasks = new Task * [capacity];
}

TasksContainer::TasksContainer(const TasksContainer& other) {
    copyFrom(other);
}

TasksContainer::TasksContainer(TasksContainer&& other) noexcept {
    moveFrom(std::move(other));
}

TasksContainer& TasksContainer::operator=(const TasksContainer& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

TasksContainer& TasksContainer::operator=(TasksContainer&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

TasksContainer::~TasksContainer() {
    free();
}

void TasksContainer::addTask(Task* new_task) {
    if (count == capacity) {
        resize();
    }

    tasks[count++] = new_task;
}

void TasksContainer::removeTask(uint32_t id) {
    size_t index = count;
    for (size_t i = 0; i < count; i++) {
        if (tasks[i]->getID() == id) {
            index = i;
            break;
        }
    }

    if (index == count) {
        throw std::runtime_error("No task with that ID found.");
    }

    delete tasks[index];

    // shift remaining tasks
    for (size_t i = index; i < count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    tasks[count - 1] = nullptr; // clear the last element
    count--;
}

Task& TasksContainer::getTask(uint32_t id) {
    for (size_t i = 0; i < count; i++) {
        if (tasks[i]->getID() == id) {
            return *tasks[i];
        }
    }

    throw std::runtime_error("No task with that ID found.");
}

const Task& TasksContainer::getTask(uint32_t id) const {
    for (size_t i = 0; i < count; i++) {
        if (tasks[i]->getID() == id) {
            return *tasks[i];
        }
    }

    throw std::runtime_error("No task with that ID found.");
}

void TasksContainer::saveToFile(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (size_t i = 0; i < count; i++) {
        tasks[i]->saveToFile(out);
    }
}

void TasksContainer::readFromFile(std::ifstream& in) {
    size_t tasks_count;
    in.read(reinterpret_cast<char*>(&tasks_count), sizeof(tasks_count));

    for (size_t i = 0; i < tasks_count; i++) {
        Task* task;

        short type;
        in.read(reinterpret_cast<char*>(&type), sizeof(type));

        if (type == 0) {
            task = new Task();
        }
        else {
            task = new CollaborationTask();
        }

        task->readFromFile(in);

        addTask(task); // add the task to the vector
    }
}

void TasksContainer::free() {
    for (size_t i = 0; i < count; i++) {
        delete tasks[i];
    }
    delete[] tasks;
}

void TasksContainer::copyFrom(const TasksContainer& other) {
    count = other.count;
    capacity = other.capacity;
    tasks = new Task * [capacity];

    for (size_t i = 0; i < count; i++) {
        tasks[i] = other.tasks[i]->clone();
    }
}

void TasksContainer::moveFrom(TasksContainer&& other) {
    tasks = other.tasks;
    capacity = other.capacity;
    count = other.count;

    other.tasks = nullptr;
    other.count = other.capacity = 0;
}
