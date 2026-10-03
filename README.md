# philosophers - 42 School Project

Implementation of the dining philosophers problem using threads and mutexes in C.

## Overview

This project solves the classic dining philosophers problem, demonstrating understanding of concurrent programming, thread synchronization, and deadlock prevention. Philosophers alternate between eating, sleeping, and thinking, sharing forks with their neighbors.

## Rules

- Philosophers sit at a circular table with a fork between each pair
- Each philosopher needs both forks (left and right) to eat
- After eating, they sleep, then think, then repeat
- A philosopher dies if they don't eat within the specified time
- The simulation stops when a philosopher dies or all have eaten the required number of meals

## Features

### Simulation
- Configurable number of philosophers (1-200)
- Configurable time-to-die, time-to-eat, and time-to-sleep
- Optional number of meals each philosopher must eat
- Real-time status output with timestamps

### Thread Safety
- Mutex protection for forks (prevents race conditions)
- Print lock for synchronized output
- End lock for clean simulation termination
- Deadlock prevention via ordered mutex acquisition

### Monitoring
- Death watcher thread monitors all philosophers
- Victory watcher thread checks meal completion
- Clean shutdown on simulation end

## Project Structure

```
philosophers/
├── src/
│   ├── main.c              # Entry point and thread management
│   ├── start.c             # Simulation initialization and argument parsing
│   ├── routine.c           # Philosopher behavior (eat, sleep, think)
│   ├── watchers.c          # Death and victory monitoring threads
│   ├── utils.c             # Utility functions (ft_atoi, get_time, ft_calloc)
│   └── philo_utils.c       # Simulation utilities (free, print)
├── inc/
│   └── philosophers.h      # Header with structures and declarations
├── Makefile                # Build configuration
└── .gitignore
```

## Compilation

### Basic compilation
```bash
make
```
Compiles the philosopher program.

### Clean build
```bash
make re
```
Removes all compiled files and recompiles everything.

### Cleaning
```bash
make clean    # Removes obj/ directory
make fclean   # Removes obj/ and philo binary
```

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

### Arguments
- `number_of_philosophers`: Number of philosophers (1-200)
- `time_to_die`: Time in milliseconds before a philosopher dies without eating
- `time_to_eat`: Time in milliseconds it takes to eat
- `time_to_sleep`: Time in milliseconds it takes to sleep
- `number_of_meals` (optional): Number of meals each philosopher must eat

### Examples

```bash
# 4 philosophers, 310ms to die, 200ms to eat, 100ms to sleep
./philo 4 310 200 100

# 5 philosophers with mandatory 5 meals each
./philo 5 800 200 200 5

# 1 philosopher (special case - will die alone)
./philo 1 800 200 200
```

### Output Format

```
timestamp_ms philosopher_id action
```

Actions:
- `has taken a fork` - Philosopher picked up a fork
- `is eating` - Philosopher is eating
- `is sleeping` - Philosopher is sleeping
- `is thinking` - Philosopher is thinking
- `died` - Philosopher died (simulation ends)
- `Philosophers have eaten.` - All philosophers completed required meals

## Error Handling

The program validates all inputs:

- **Wrong argument count**: "Error" and exit
- **Invalid numbers**: Rejects non-numeric, negative, or zero values
- **Too many philosophers**: Rejects > 200 philosophers
- **Times too small**: Rejects eat/sleep times < 60ms (prevents busy waiting)
- **Memory allocation**: Handles malloc failures gracefully

## Implementation Details

### Deadlock Prevention
Philosophers acquire forks in address order (lower address first) to prevent circular wait conditions.

### Thread Synchronization
- `print_lock`: Ensures only one philosopher prints at a time
- `end_lock`: Protects `end_simulation` flag
- `eating`: Protects `last_meal` and `meals_eaten` updates
- Fork mutexes: Prevent two philosophers from using the same fork

### Special Cases
- **1 philosopher**: Takes one fork and waits (will die - no second fork available)
- **Even number of philosophers**: Optimal fork sharing
- **Odd number of philosophers**: May require more coordination

## Code Quality

- Complies with 42 school's norminette standards
- No memory leaks (valgrind verified)
- Thread-safe operations with proper mutex usage
- Clean separation of concerns
- Proper error handling and resource cleanup

## Requirements

- GCC compiler
- Make
- pthread library (POSIX threads)
- Unix-like environment (Linux, macOS, or WSL)

## Author

- **Mario Pico** (@Davter17)

## License

This project is part of the 42 school curriculum and follows its academic guidelines.
