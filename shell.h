#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define BUFF_FLUSH -1
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024

#define USEget_line 0
#define USE_STRTOK 0

#define history_file	".simple_shell_history"
#define history_max	4096

#define CON_LOWER	1
#define CON_UNSIGNED	2

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

extern char **envir;

/**
 * struct list_string - displays all struct
 * @number: number
 * @strn: string
 * @next: next node
 */
typedef struct list_string
{
	int number;
	char *strn;
	struct list_string *next;
} list_string;

/**
 * struct commandinfo - contains mockup-arguements to pass
 * @commandname: string from getline  arguements
 * @commandargs:an array
 * @commandpath: string path
 * @numargs: the  count
 * @linecount: the count
 * @errorcode: the error code
 * @linecount_error: if on count
 * @fname: the program filename
 * @env: local copy of environ
 * @envir: custom modified copy of environ
 * @history: the history node
 * @alias: the alias node
 * @envir_changed: on if environ
 * @status: the return status
 * @commandbuffer: address of pointer
 * @commandtype: CMD_type
 * @readfd: the fd
 * @historycount: the history line
 */
typedef struct commandinfo
{
	char *commandname;
	char **commandargs;
	char *commandpath;
	int numargs;
	unsigned int linecount;
	int errorcode;
	int linecount_error;
	char *fname;
	list_string *env;
	list_string *history;
	list_string *alias;
	char **envir;
	int envir_changed;
	int status;
	char **commandbuffer;
	int commandtype;
	int readfd;
	int historycount;
} inform_t;


/**
 * struct build - has built-in strings
 * @type: build command flag
 * @func:  pointer
 */
typedef struct build
{
	char *type;
	int (*func)(inform_t *);
} build_table;


int deli(char, char *);
int inte(inform_t *);
int toi(char *);
int alphabet(int);


int shs(inform_t *, char **);
int fd_build(inform_t *);
void fd_command(inform_t *);
void fk_command(inform_t *);


int id_command(inform_t *, char *);
char *d_char(char *, int, int);
char *fd_path(inform_t *, char *, char *);


int phash(char **);


int len_str(char *);
int str_cmp(char *, char *);
char *sts_wt(const char *, const char *);
char *str_cat(char *, char *);


char *string_copy(char *, char *);
char *string_dup(const char *);
void print_s(char *);
int print_ch(char);


void print_str(char *);
int print_char(char);
int print_fd(char c, int fd);
int print_sfd(char *str, int fd);


char *memory_set(char *, char, unsigned int);
void *real(void *, unsigned int, unsigned int);
void free_f(char **);

int free_b(void **);

char *string_cat(char *, char *, int);
char *string_cpy(char *, char *, int);
char *string_chr(char *, char);

char **str_tow2(char *, char);
char **str_tow(char *, char *);
void free_mem(char **shr);

int dis_als(inform_t *);
int dis_hist(inform_t *);


int customcd(inform_t *);
int customexit(inform_t *);
int customhelp(inform_t *);



char *con_num(long int, int, int);
void rmv_comments(char *);
void prt_err(inform_t *, char *);
int err_at(char *);
int prt_d(int, int);


int pop_env(inform_t *);
char *disp_env(inform_t *, const char *);
int set_env(inform_t *);
int get_env(inform_t *);
int rmv_env(inform_t *);


int get_line(inform_t *, char **, size_t *);
ssize_t get_inp(inform_t *);
void inthand(int);


void del_info(inform_t *);
void release_info(inform_t *, int);
void put_info(inform_t *, char **);


int set_info(inform_t *, char *, char *);
char **get_envir(inform_t *);
int rmv_info(inform_t *, char *);


int read_hist(inform_t *info);
char *get_hist(inform_t *info);
int order_hist(inform_t *info);
int build_hist(inform_t *info, char *buf, int linecount);
int write_hist(inform_t *info);


ssize_t get_id_node(list_string *, list_string *);
size_t length_list(const list_string *);
list_string *node_start(list_string *, char *, char);
char **list_stringo_str(list_string *);
size_t disp_list(const list_string *);


list_string *node_add(list_string **, const char *, int);
list_string *nodeend_add(list_string **, const char *, int);
size_t disp_list_str(const list_string *);
void avail_list(list_string **);
int rmv_node(list_string **, unsigned int);


int var_rep(inform_t *);
int is_chn(inform_t *, char *, size_t *);
void ck_chn(inform_t *, char *, size_t *, size_t, size_t);
int str_rep(char **, char *);
int als_rep(inform_t *);

char **envirr;

#endif

