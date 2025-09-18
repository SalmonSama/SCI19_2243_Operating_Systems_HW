#ifndef OSLAB08_PETERSON_H
#define OSLAB08_PETERSON_H

#define TRUE 1
#define FALSE 0

// Structure to hold the shared variables for Peterson's algorithm
struct Memory {
    int turn;     // Indicates whose turn it is to enter the critical section
    int flag[2];  // flag[i] = TRUE means process i is ready to enter
};

/**
 * @brief Initializes the shared memory segment for Peterson's algorithm.
 */
void initializePeterson();

/**
 * @brief Detaches from and removes the shared memory segment.
 */
void removePeterson();

/**
 * @brief Implements the entry section of Peterson's algorithm for a process.
 * * @param i The process ID (0 or 1).
 */
void enterCriticalSection(int i);

/**
 * @brief Implements the exit section of Peterson's algorithm for a process.
 * * @param i The process ID (0 or 1).
 * @return int Returns 0 on success.
 */
int exitCriticalSection(int i);

#endif // OSLAB08_PETERSON_H