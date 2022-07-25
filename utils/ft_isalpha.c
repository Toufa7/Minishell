
int	ft_isalpha(int c)
{
	if (c < 65 || c > 122 || (c >= 91 && c <= 96))
		return (0);
	return (1);
}
