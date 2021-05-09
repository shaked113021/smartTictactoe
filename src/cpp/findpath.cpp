#include "../include/findpath.h"
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>

void errorHandling(ssize_t buffWritten) {
  if (buffWritten == -1) {
    std::string message { "Error at findpath.c/findpath()/readlink(char *path, char *buf, size_t bufsiz): " };
    switch (errno) {
      case EACCES: {
        std::cerr << message << "Search permission is denied for a component of the path prefix" <<std::endl;
        break;
      }
      case EFAULT: {
        std::cerr << message << "buf extends outside the process's allocated address space" <<std::endl;
        break;
      }
      case EINVAL: {
        std::cerr << message << "bufsiz is not positive or The named file is not a symbolic link" <<std::endl;
        break;
      }
      case EIO: {
        std::cerr << message << "An I/O error occurred while reading from the file system" <<std::endl;
        break;
      }
      case ELOOP: {
        std::cerr << message << "Too many symbolic links were encountered in translating the pathname" <<std::endl;
        break;
      }
      case ENAMETOOLONG: {
        std::cerr << message << "A pathname, or a component of a pathname, was too long" <<std::endl;
        break;
      }
      case ENOENT: {
        std::cerr << message << "The named file does not exist" <<std::endl;
        break;
      }
      case ENOMEM: {
        std::cerr << message << "Insufficient kernel memory was available" <<std::endl;
        break;
      }
      case ENOTDIR: {
        std::cerr << message << "A component of the path prefix is not a directory" <<std::endl;
        break;
      }
      default: {
        std::cerr << message << "Unknown Error" <<std::endl;
        break;
      }
    }
    exit(EXIT_FAILURE);
  }
}

char* exclude_exec(char* path) {
  int slashIndex = 0;
  for (int i = 0; path[i] != '\0'; ++i) {
    if (path[i] == '/') slashIndex = i;
  }
  char* excluded = new char[slashIndex + 1];

  for (int i = 0; i < slashIndex; ++i) {
    excluded[i] = path[i];
  }

  excluded[slashIndex] = '\0';
  return excluded;
}

std::string FindPath() {
  const size_t buffSize = 100;
  char* buffer = new char[buffSize];
  ssize_t buffWritten = readlink("/proc/self/exe", buffer, buffSize);
  errorHandling(buffWritten);
  char* buffreduced = new char[buffWritten + 1];
    
  strcpy(buffreduced, buffer);
  delete buffer;
    
  char* path = exclude_exec(buffreduced);
  delete buffreduced;
  std::string strpath { path };
  delete path;

  return strpath;
}