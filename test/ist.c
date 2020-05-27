main()
{
	initialize env_list;
	start msh_main
}

msh_main()
{
	initialize reading struct
	read->handle loop (read_input && parse_input)
}

parse_input()
{
	turn the raw input into tokens
	turn the tokens into commands
}

read_input()
{
	get the raw input, display the line using termcaps etc..
}


//make a command, set it's iostream to default (-1)
//loop over all the arguments, update iostream accordingly
//if a pipe is encountered, create one with pipe(), if iostream is default, set the output to pipe[WRITE]
//at the start of a command, check (???) to see if a pipe is created to be set as iostream[READ]
run_commands()
{
	loop over all commands
	{
		set the redirections
		execute command
	}
	cleanup
}

//the commandtype could be dependant BUILTIN, ABSOLUTE, RELATIVE
//and handled by a dispatcher.
execute()
{
	check if command is: builtin, abs path, relative path
	run it
	{
		fork()
		close other fds
		execve
		close io fds
	}
}
