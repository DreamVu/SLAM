# ifndef DATA_LOCK_HPP
# define DATA_LOCK_HPP

# include <iostream>


struct DataLock
{
    static const int READ = 0;
    static const int WRITE = 1;  

    int pipe_fd[2];
    
    std::string name;
    
    int write_calls;
    int read_calls; 
    
    DataLock();
    
    bool Write(void* ptr, int size);
    
    bool Read(void* ptr, int size);

    bool Notify();
    
    bool Wait(); 

    void Destroy();

    void Create();
    
};

# endif //DATA_LOCK_HPP
