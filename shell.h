#ifndef SHELL_HEADER
#define SHELL_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* define macros and assign spec values */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define FREE_BUFF -1
#define GETLINE_MAC 0
#define HISTORY_BUF	".gates_of_shell"
#define HISTORY_MAX_SIZE	4096
#define CLI_NORMAL	0
#define CLI_OR		1
#define CLI_AND		2
#define CLI_ARGS	3
#define CONV_LC	1
#define CONV_INT_UNS	2

extern char **environ;


/**
 * struct strilist - singly linked list
 * @num: integer variable field
 * @st: string
 * @next: pointer to next node
 */
typedef struct strilist
{
	int num;
	char *st;
	struct strilist *next;
} sll_table;

/**
 *struct func_params - uniform prototype for function pointer struct
 *
 *@arg: raw input command
 *@argv: array of strings gotten from argument
 *@path: a string path for the current command
 *@argc: argument count
 *@lnc_var: error count var
 *@err_num: error code for exit()s
 *@lnc_fvar: count this line of input
 *@fname: program's filename descriptor
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: hist node
 *@alias: the alias node
 *@env_state: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@rdfldesc: file descriptor line input is read from
 *@hist_ln_count: the history  ufline number count
 */
typedef struct func_params
{
	char *arg;
	char **agv;
	char *path;
	int agc;
	unsigned int lnc_var;
	int err_num;
	int lnc_fvar;
	char *fname;
	sll_table *env;
	sll_table *history;
	sll_table *alias;
	char **environ;
	int env_state;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int rdfldesc;
	int hist_ln_count;
} inf_table;

/**
 *struct tblbuilt_in - contains a builtin string and associated function
 *@type: command flag for builtins
 *@func: the function
 */
typedef struct tblbuilt_in
{
	char *type;
	int (*func)(inf_table *);
} table_builtin;

#define INFO_INITIALIZE \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* Declared Program Functions */
int _strcmp(char *, char *);
char *to_comp(const char *, const char *);
int _strlen(char *);
char *_strconcat(char *, char *);
int prompt_loop(inf_table *, char **);
void find_cmd(inf_table *);
void fork_cmd(inf_table *);
int find_builtin(inf_table *);
char *cpystr(char *, char *);
char *duplstr(const char *);
void strprint(char *);
int charprint(char);
int is_seq(inf_table *, char *, size_t *);
void verify_seq(inf_table *, char *, size_t *, size_t, size_t);
int manip_alias(inf_table *);
int vard_rep(inf_table *);
int rep_str(char **, char *);
int interactive_ses(inf_table *);
int strdelim_checker(char, char *);
int is_alpha_check(int);
int ascii_std(char *);
void input_printff(char *);
int stderrprint(char);
int filedesc_print(char c, int fd);
int output_fd(char *str, int fd);
int func_exit(inf_table *);
int cd_func(inf_table *);
int help_func(inf_table *);
int func_history(inf_table *);
int func_alias(inf_table *);
int rev_ascii_std(char *);
void err_printfunc(inf_table *, char *);
int dec_print(int, int);
char *num_conv(long int, int, int);
void coms_rem(char *);
int is_cmd(inf_table *, char *);
char *dup_chars(char *, int, int);
char *func_find_path(inf_table *, char *, char *);
char *strcpi(char *, char *, int);
char *strcocate(char *, char *, int);
char *strchkr(char *, char);
char **word_tok(char *, char *);
char *memfill(char *, char, unsigned int);
void free_strs(char **);
void *mem_realloc(void *, unsigned int, unsigned int);
void struct_init_(inf_table *);
void struct_init_md(inf_table *, char **);
void free_inf_table(inf_table *, int);
int mem_free(void **);
char *get_envalue(inf_table *, const char *);
int print_curr_env(inf_table *);
int make_env(inf_table *);
char *get_history_func_files(inf_table *info);
int mk_history_func(inf_table *info);
int get_history_func(inf_table *info);
int build_history_list(inf_table *info, char *buf, int linecount);
int renumber_history(inf_table *info);
int rem_made_env(inf_table *);
int add_to_envlist(inf_table *);
ssize_t inputcmd_chain(inf_table *);
int nline_input(inf_table *, char **, size_t *);
void sigintHandler(int);
size_t list_len(const sll_table *);
char **sll_tableo_strings(sll_table *);
size_t print_list(const sll_table *);
sll_table *node_starts_with(sll_table *, char *, char);
ssize_t get_node_index(sll_table *, sll_table *);
char **getenv_info(inf_table *);
int rem_env_var(inf_table *, char *);
int set_new_env(inf_table *, char *, char *);
sll_table *create_node(sll_table **, const char *, int);
sll_table *create_node_end(sll_table **, const char *, int);
size_t print_list_str(const sll_table *);
int delete_node_speci_index(sll_table **, unsigned int);
void free_nds_list(sll_table **);

#endif
