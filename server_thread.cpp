#include "server_thread.h"

Thread::Thread() {}

Thread::~Thread() {}

void Thread::empezar() {
    thread = std::thread(&Thread::operator(), this);
}

void Thread::unir() {
    thread.join();
}