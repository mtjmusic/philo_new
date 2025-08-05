<div align="center">
<img width="500" alt="Image  5, 2025, 08_31_02 PM" src="https://github.com/user-attachments/assets/58ebb479-9a90-4dd2-9c7b-8fa4e6011fac" />
</div>


# Philosophers Project

This project implements the classic "Dining Philosophers" problem in C, focusing on multi-threading and process synchronization. It simulates a group of philosophers seated at a round table, sharing forks to eat spaghetti while alternating between eating, thinking, and sleeping. The challenge is to manage shared resources (forks) to prevent starvation, deadlocks, and data races.

## Overview

### Objective
Ensure philosophers can eat, think, and sleep without starving or encountering synchronization issues.

### Structure
- **Mandatory Part**: Represents each philosopher as a thread, using mutexes to control fork access.
- **Bonus Part**: Represents each philosopher as a process, using semaphores to manage fork availability (not included in this description).

### Constraints
- Global variables are prohibited.
- Program accepts arguments: `number_of_philosophers`, `time_to_die`, `time_to_eat`, `time_to_sleep`, and optionally `number_of_times_each_philosopher_must_eat`.
- Logs state changes (e.g., eating, sleeping, thinking, dying) with timestamps in milliseconds.
- Ensures no data races and proper memory management.

## Features

### Mandatory Program (`philo`)
- Each philosopher is a thread, with mutexes protecting fork access to avoid conflicts.

### Simulation Rules
- Philosophers require two forks to eat.
- The simulation halts if a philosopher dies (fails to eat within `time_to_die`) or if all philosophers eat the specified number of times (if provided).
- State change logs are displayed without overlap, and death notifications must appear within 10ms of the event.

## Technical Details

- **Language**: C
- **Allowed Functions**:
  - Mandatory: `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`.
- **Makefile**: Includes rules for `NAME`, `all`, `clean`, `fclean`, `re`, and a `bonus` rule for the bonus part.
- **Directory Structure**:
  - Mandatory: `philo/`

## Learning Outcomes

- Practical experience with multi-threading and process management.
- Application of mutexes for resource synchronization.
- Handling concurrency challenges in a simulated environment.
