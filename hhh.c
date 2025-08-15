if (oldpwd && *oldpwd)
	{
		old_line = ft_strjoin("OLDPWD=", oldpwd);
		if (!old_line)
			return (1);
		add_or_update_env(env, old_line);
		free(old_line);
	}
