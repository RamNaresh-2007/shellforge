if (i < command_count - 1)
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }


            /*
             * Convert Shellforge argv
             * into execvp argument format.
             */

            char *args[MAX_ARGS + 1];

            for (int j = 0;
                 j < cmd->argc;
                 j++)
            {
                args[j] = cmd->argv[j];
            }

            args[cmd->argc] = NULL;


            /*
             * Built-ins inside a pipe.
             *
             * Note:
             * cd inside a pipeline will only
             * affect this child process.
             */

            if (is_builtin(cmd))
            {
                int result =
                    execute_builtin(cmd);

                _exit(result == 0 ? 0 : 1);
            }


            /*
             * Execute external command.
             */

            execvp(args[0], args);


            perror(args[0]);

            _exit(127);
        }


        /* ================================================
           PARENT PROCESS
           ================================================ */


        /*
         * Parent no longer needs
         * the previous pipe read end.
         */

        if (previous_read != -1)
        {
            close(previous_read);
        }


        /*
         * Parent keeps the read end of the
         * current pipe for the next command.
         */

        if (i < command_count - 1)
        {
            close(pipefd[1]);

            previous_read = pipefd[0];
        }
        else
        {
            previous_read = -1;
        }
    }


    /*
     * Wait for every child process.
     */

    int final_status = 0;

    for (int i = 0; i < command_count; i++)
    {
        int status;

        if (waitpid(pids[i],
                    &status,
                    0) < 0)
        {
            perror("waitpid");
            continue;
        }


        /*
         * Save status of the last command.
         */

        if (i == command_count - 1)
        {
            if (WIFEXITED(status))
            {
                final_status =
                    WEXITSTATUS(status);
            }
        }
    }


    return final_status;
}
