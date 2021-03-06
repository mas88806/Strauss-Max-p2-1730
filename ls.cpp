#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <list>

using std::cout;
using std::endl;
using std::list;

bool direnticmp(struct dirent * a, struct dirent * b){
  return strcasecmp(a->d_name, b->d_name) < 0;
}

int main(const int argc, const char * argv[]){

  if (argc > 2)
    {
      cout << "Usage: " << argv[0]
	   << " [FILE] " << endl;
      return EXIT_FAILURE;
    }

   if (argc == 2){
    const char * filename = argv[1];
    struct stat buf;
    stat(filename, &buf);
    struct passwd *pw = getpwuid(buf.st_uid);
    struct group *gr = getgrgid(buf.st_gid);

    cout << "-" 
	 << (((buf.st_mode & S_IRUSR) != 0) ? "r" : "-")
	 << (((buf.st_mode & S_IWUSR) != 0) ? "w" : "-")
	 << (((buf.st_mode & S_IXUSR) != 0) ? "x" : "-")
         << (((buf.st_mode & S_IRGRP) != 0) ? "r" : "-")
	 << (((buf.st_mode & S_IWGRP) != 0) ? "w" : "-")
	 << (((buf.st_mode & S_IXGRP) != 0) ? "x" : "-")
         << (((buf.st_mode & S_IROTH) != 0) ? "r" : "-")
	 << (((buf.st_mode & S_IWOTH) != 0) ? "w" : "-")
	 << (((buf.st_mode & S_IXOTH) != 0) ? "x" : "-")
	 << ". " << buf.st_nlink << " " << pw->pw_name
	 << " " << gr->gr_name << " " << buf.st_size
	 << " " << ctime(&buf.st_mtim.tv_sec) << " "
	 << filename << endl;
     }
      else {
	list<struct dirent *> entries;
	struct dirent * entry = nullptr;
	DIR * pwd = opendir(".");

	if (pwd == nullptr) {
	  perror("ls");
	} else {
	  while ((entry = readdir(pwd)) != nullptr){
	    entries.push_back(entry);
	  }
	  entries.sort(direnticmp);
	    for (auto dir : entries){
	      const char * filename = dir->d_name;
    struct stat buf;
    stat(filename, &buf);
    struct passwd *pw = getpwuid(buf.st_uid);
    struct group *gr = getgrgid(buf.st_gid);

    cout << "-" 
	 << (((buf.st_mode & S_IRUSR) != 0) ? "r" : "-")
	 << (((buf.st_mode & S_IWUSR) != 0) ? "w" : "-")
	 << (((buf.st_mode & S_IXUSR) != 0) ? "x" : "-")
         << (((buf.st_mode & S_IRGRP) != 0) ? "r" : "-")
	 << (((buf.st_mode & S_IWGRP) != 0) ? "w" : "-")
	 << (((buf.st_mode & S_IXGRP) != 0) ? "x" : "-")
         << (((buf.st_mode & S_IROTH) != 0) ? "r" : "-")
	 << (((buf.st_mode & S_IWOTH) != 0) ? "w" : "-")
	 << (((buf.st_mode & S_IXOTH) != 0) ? "x" : "-")
	 << ". " << buf.st_nlink << " " << pw->pw_name
	 << " " << gr->gr_name << " " << buf.st_size
	 << " " << ctime(&buf.st_mtim.tv_sec) << " "
	 << filename << endl;
	    }
	  closedir(pwd);
     }
	return EXIT_SUCCESS;
      }
}//main
