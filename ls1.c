//
// Created by lee on 2021/5/15.
//

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void do_ls(char []);
void dostat(char *);
void show_file_info(char *, struct stat *);
void mode_to_letters(int, char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

void main(int argc, char **argv){
    //char *argv[]中argv为字符型指针数组的首地址，是个常量，不能argv++（同理char a[]也不能a++），而**argv中argv是个变量，可以argv++，但是实际使用时两者都可以argv++，这是因为*argv[]是main函数的参数，数组作为函数参数时会自动退化为指针，因此main函数参数中的char *argv[]退化为char **argv（当char a[]和char *a[]用作函数参数时也会分别自动退化成char *a和char **a）。
    if (argc == 1)
        do_ls(".");
    else
        while( --argc ) {
            printf("%s : \n", *++argv);
            do_ls(*argv);
        }
}

void do_ls(char dirname[]){
    DIR *dir_ptr;
    struct dirent *direntp;

    if((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls1:cannot open %s\n", dirname);
    else{
        while((direntp = readdir( dir_ptr )) != NULL)
            dostat(direntp -> d_name);
        closedir(dir_ptr);
    }
}

void dostat(char *filename){
    struct stat info;
    if(stat(filename, &info) == -1)
        perror(filename);
    else
        show_file_info(filename, &info);
}

void show_file_info(char *filename, struct stat *info_p){
    char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
    void mode_to_letters();
    char modestr[11];

    mode_to_letters( info_p -> st_mode, modestr);

    printf("%s", modestr);
    printf("%4d", (int)info_p -> st_nlink);
    printf("%-8s", uid_to_name(info_p -> st_uid));
    printf("%-8s", gid_to_name(info_p -> st_gid));
    printf("%8ld", (long)info_p -> st_size);
    printf("%.12s", 4 + ctime(&info_p -> st_mtime));
    printf("%s\n", filename);
}
void mode_to_letters(int mode, char str[]){
    strcpy(str, "---------");

    if(S_ISDIR(mode))str[0] = 'd';
    if(S_ISCHR(mode))str[0] = 'c';
    if(S_ISBLK(mode))str[0] = 'b';
    if(mode & S_IRUSR)str[1] = 'r';
    if(mode & S_IWUSR)str[2] = 'w';
    if(mode & S_IXUSR)str[3] = 'x';
    if(mode & S_IRGRP)str[4] = 'r';
    if(mode & S_IWGRP)str[5] = 'w';
    if(mode & S_IXGRP)str[6] = 'x';
    if(mode & S_IROTH)str[7] = 'r';
    if(mode & S_IWOTH)str[8] = 'w';
    if(mode & S_IXOTH)str[9] = 'x';
}
#include <pwd.h>

char *uid_to_name(uid_t uid){
    struct passwd *getpwuid(), *pw_ptr;
    static char numstr[10];

    if((pw_ptr = getpwuid(uid)) == NULL){
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    else
        return pw_ptr -> pw_name;
}

#include <grp.h>

char *gid_to_name( gid_t gid){
    struct group *getgrgid(), *grp_ptr;
    static char numstr[10];

    if((grp_ptr = getgrgid(gid)) == NULL){
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else
        return grp_ptr -> gr_name;
}

