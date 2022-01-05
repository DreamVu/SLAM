# ifndef SEMAPHORE_H
# define SEMAPHORE_H

# include <string>
# include <iostream>
# include <stdlib.h>
# include <semaphore.h>


class Semaphore
{
    sem_t mutex; 

	bool entered;

    std::string name;
    
public:

    Semaphore();
    ~Semaphore();
    
    void EnterCriticalSection();
    
    void LeaveCriticalSection();

    void SetName(std::string prefix, int index);
    
    
};

# endif //SEMAPHORE_H
