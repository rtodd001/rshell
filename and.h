#ifndef AND_H
#define AND_H

#include "connector.h"
#include <sys/wait.h>
#include <unistd.h>

class And: public Connector{
public:
  And(){
    char a[3] = "&&";
    setRep(a);
  };
  And(char* rep): Connector(rep){};
  And(char* rep, Base* left): Connector(rep, left){};
  bool run();
};

bool And::run(){
  if(this->getLeft() == nullptr || this->getRight() == nullptr){
    throw("Invalid Tree");
  }
  else{
    pid_t pid = fork();
    int child_status;
    if(pid == -1){
      perror("Fork Failed:");
      return false;
    }
    else if(pid == 0){
      this->getLeft()->run();
      exit(errno);
    }
    else{
      waitpid(pid, &child_status, 0);
      if(WEXITSTATUS(child_status) == 3){
        exit(3);
      }
      if(WEXITSTATUS(child_status) == 0){
          return this->getRight()->run();
      }
    }
  }
}

#endif