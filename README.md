## Minishell 
A team project, was made by two students of school 21.
## How to use it
- Using make will create the minishell executable.
- Simply run it with :  
./minishell
## Available options

Minishell runs executables from an absolute, relative or environment PATH (/bin/ls or ls), including arguments or options. ' and " work the same as bash, except for multiline commands.
You can separate commands with ";", as well as use redirections > >> < and pipes |.

Environment variables are handled, like $HOME, including the return code $?.
You can use Ctrl-C to interrupt and Ctrl-\ to quit a program, as well as Ctrl-D to throw an EOF, same as in bash.

According to the task some functions were to be recoded manually (echo, pwd, cd, env, export, unset and exit). 

Finally, our minishell can keep its history like the bash does.
