#ifndef _SHELL_H_
#define _SHELL_H_

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
/*#include <fcnt1.h>*/
#include <fcntl.h>


#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CON_LOWERCASE 1
#define CON_UNSIGNED 2

#define USEget_line 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **envir;
/**
 * struct list_string - singly linked list
 * @number: number
 * @string: string
 * @next: next node
 */
typedef struct list_string
{	int number;
	char *string;
	struct list_string *next;
} list_string;

/**
 * struct commandinfo - pseudo arguments
 * @commandname: containis arguments
 * @commandargs: string from commandname
 * @commandpath: string for command
 * @numargs: argument count
 * @line_count: error count
 * @errorcode: error code
 * @linecount_flag: count line of input
 * @fname: filename
 * @env: copy of environment
 * @history: history
 * @alias: alias
 * @envir: modified copy of environment
 * @env_changed: changed environment
 * @status: return status
 * @commandtype: cmd type
 * @commandbuffer: cmd buffer
 * @readfd: read line input
 * @historycount: history line
 */

typedef struct commandinfo
{
	char *commandname;
	char **commandargs;
	char *commandpath;
	int numargs;
	unsigned int line_count;
	int errorcode;
	int linecount_flag;
	char *fnanme;
	list_string *env;
	list_string *history;
	list_string *alias;
	char **envir;
	int env_changed;
	int status;
	char **commandbuffer;
	int commandtype;
	int readfd;
	int historycount;
} inform_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \ 0, 0, 0}

/**
 * struct build - string build
 * @type: command
 * @func: function
 */

typedef struct build
{
	char *type;
	int (*func)(inform_t *);
} build_table;

/* hoop */
int hash(inform_t *, char **);
int fd_build(inform_t *);
void fd_command(inform_t *);
void fk_command(inform_t *);

int id_command(inform_t *, char *);
char *d_char(char *, int, int);
char *fd_path(inform_t *,char *, char *);

int phash(char **);

void print_str(char *);
int print_char(char);
int print_fd(char ch, int fd);
int print_sfd(char *str, int sfd);

int len_str(char *);
int str_cmp(char *, char *);
char *sts_wt(const char *, const char *);
char *str_cat(char *, char *);

char *string_copy(char *, char *);
char *string_dup(const char *);
void print_s(char *);
int print_ch(char);

char *string_cpy(char *, char *, int);
char *string_cat(char *, char *, int);
char *string_chr(char *, char);

char **strt_ow(char *, char *);
char **str_ow2(char *, char);

char *memory_set(char *, char, unsigned int);
void free_f(char **);
void *real(void *, unsigned int, unsigned int);

int free_b(void **);

int inte(inform_t *);
int deli(char, char *);
int alphabet(int);
int at(char *);

int err_at(char *);
void prt_err(inform_t *, char *);
int prt_d(int, int);
char *con_num(long int, int, int);
void rmv_comments(char *);

int customexit(inform_t *);
int customcd(inform_t *);
int customhelp(inform_t *);

int dis_hist(inform_t *);
int dis_alias(inform_t *);

ssize_t get_inp(inform_t *);
int get_line(inform_t *, char **, size_t *);
void inthand(int);

void del_info(inform_t *);
void put_info(inform_t *, char **);
void release_info(inform_t *, int);

char *disp_env(inform_t *);
int get_env(inform_t *);
int rmv_env(inform_t *);
int pop_env(inform_t *);

char **get_envir(inform_t *);
int rmv_info(inform_t *, char *);
int set_info(inform_t *, char *, char *);

char *get_hist(inform_t *info);
int write_hist(inform_t *info);
int read_hist(inform_t *info);
int build_hist(inform_t *info, char *buf, int linecount);
int order_hist(inform_t *info);

list_string *node_add(list_string **, const char *, int);
list_string *nodeend_add(list_string **, const char *, int);
size_t disp_list(const list_string *);
list_string *node_start(list_string *, char *, char);
ssize_t get_id_node(list_string *, list_string *);

int is_chn(inform_t *, char *, size_t *);
void chk_chn(inform_t *, char *, size_t *, size_t, size_t);
int als_rep(inform_t *);
int var_rep(inform_t *);
int str_rep(char **, char *);

#endif
