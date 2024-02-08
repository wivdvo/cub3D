
int need_check(char c)
{
	const int need_check = {0, N S E W}
	if(c jedan od need )
		return 1; 
	return 0; 
}

right_check(dot[row][column], mapa)
{
	int wall;
	IF(DOT is INVALID)
		return 0;
	if dot == need_check)
	{
		IF(STRLEN(MAP[row]) - 1 <= dot[column])
			return 0;
		mapa[columnt] + 1;
		wall = 0;
		while(wall == 0 && mapa[row][column] != '\0')
		{
			if(mapa[row][column] == ' ')
				return (0);
			if(mapa[row][column] == 1)
				wall = 1;
			column ++;
		}
		return(wall)
	}
	return 1;
}


left_check(dot_row, column, mapa)
{
	int wall;
	IF(DOT is INVALID)
		return 0;
	IF(dot == need_check)
	{
		if(column == 0)
			return 0;
		mapa_column - 1; 
		wall = 0;
		while(wall == 0 && mapa_colum != -1)
		{
			if(mapa[row][column] == ' ', '\n , '\0)
				return (0);
			if(mapa[row][column] == 1)
				wall = 1;
			map_column--;
		}
		return(wall);
	}
}

down_check(karakter, last_row, mapa, row, column)
{
	wall = 0;
	if(karakter is invalid )
		retunr 0;
	if(dot == Need check)
	{
		if(row == index_last_row)
			retunr0; 
		while(i < last_row && wall == 0;)
		{
			if(strlen(mapa[row + i]) -1 <= columnt )
				return 0;
			if(mapa[row + i][column] == ' ')
				retunr (0);
			if(mapa[row][column] == 1)
				wall = 1;
			i++;
		}
		return(wall);
	}
	return 1; 
}

up_check(karakter, mapa, row, column)
{
	int wall; 
	if(karakter is invalid )
		retunr 0; 
	if(karater == need check)
	{
		if(row == 0)
			return 0;
		while(row >= 1 && wall == 0;)
		{
			if(strlen(mapa[row -1] -1 <= column ))
				return 0; 
			if(mapa[row][column] == ' ')
				return(0);
			if(mapa[row][column] == 1)
				wall = 1;
			row--;
		}
		return(wall);
	}
	return 1;
}



closed_map()
{
	prebroji redove_mape; 
	za svaki red 
	za svaki stupac
	 Provjera[red][stupac]
	 		right_check();
			left_check();
			up_check();
			down_check();

}