#include <stdio.h>
#include <unistd.h>

void    echo(char *str)
{
	(void) str;
}



/*

echo $$ =  Display PID of shell

echo $? = The shell obtained status of grep (shell built-in)

which 'command' == get command's path

echo lol$USER jsdhidcg$TEMP
echo lol$USER jsdhidcg$PWD
echo lol$USER jsdhidcg'$PWD'
echo lol$USER jsdhidcg"$PWD"
echo lol$USERjsdhidcg$PWD
echo $USER
echo lol$USERjsdhidcg$PWDfu
echo $lol$USERjsdhidcg$PWDfu
echo "$lol$USERjsdhidcg$PWDuy"
echo $lol"$USER"jsdhidcg$PWDuy
echo lol"$USER"jsdhidcg$PWDuy
echo lol"$USER"jsdhidcg"$PWD"uy
echo lol"$USER"jsdhidcg'$PWD'uy
echo lol"$USER"jsdhidcg$PWDuy

*/
