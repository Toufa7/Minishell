#!/bin/sh


# $@ ==> $@ is nearly the same as $*, both meaning "all command line arguments". 

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"
SEPARATOR="----------------------------------------"
ECHO="
███████╗ ██████╗██╗  ██╗ ██████╗ 
██╔════╝██╔════╝██║  ██║██╔═══██╗
█████╗  ██║     ███████║██║   ██║
██╔══╝  ██║     ██╔══██║██║   ██║
███████╗╚██████╗██║  ██║╚██████╔╝
╚══════╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝ 
"


function test()
{
	MINISHELL=$(echo $@ | ./minishell 2>&-)
	MINISHELL_EXIT_STATUS=$?
	BASH=$(echo $* | bash 2>&-)
	BASH_EXIT_STATUS=$?
	if [ "$MINISHELL" == "$BASH" ] && [ "$MINISHELL_EXIT_STATUS" == "$BASH_EXIT_STATUS" ];
    then
		printf " $GREEN%s$RESET" "Valid ✅ "
	else
		printf " $RED%s\n$RESET" "              Wrong ❌"
	fi
	printf "$CYAN \"$*\" $RESET"
	if [ "$MINISHELL" != "$BASH" ];
    then
    {
		echo
		printf $RED"Minishell output  => $MINISHELL\n $SEPARATOR $RESET"
		echo
		printf $GREEN"Bash output       => $BASH\n $SEPARATOR $RESET\n"
        sleep 2
    }
	fi
	if [ "$MINISHELL_EXIT_STATUS" != "$BASH_EXIT_STATUS" ]; then
		echo
		echo
		printf $RED"Minishell exit status   => $RED$MINISHELL_EXIT_STATUS$RESET\n"
		printf $GREEN"Bash exit status        => $GREEN$BASH_EXIT_STATUS$RESET\n"
	fi
	echo
	sleep 0.1
}


printf "%s$ECHO\n"
                                 


test echo "$"
test eChO ""$""																
test echo '$'
test echo ''$''
test echo "$_" #Last Command actually not required
test echo $"test"$
test echo "$0"
test echo $1337
test echo																
test echo echo															
test echo ""																
test eCHO ''																
test echo $																
test echo $ $															
test echo																
test echo wow														
test echo Hello World													
test echo "Salam Alikoum"														
test echo Salam Alikoum														
test echo 'Salam Alikoum'														
test echo -n Salam Alikoum														
test echo -nn Salam Alikoum													
test echo -n -n -n Salam Alikoum												
test echo "-n" Salam Alikoum													
test echo -n"-n" Salam Alikoum													
test echo "-nnnn" Salam Alikoum												
test echo "-nnnn" -n Salam Alikoum												
test echo "-n -n -n"-n Salam Alikoum											
test echo "-n '-n'" Salam Alikoum												
test echo $USER															
test echo "$USER"														
test echo "'$USER'"														
test echo " '$USER' "													
test echo text"$USER"													
test echo text"'$USER'" ' $USER '										
test echo "text"   "$USER"    "$USER"									
test echo '              $USER          '								
test echo               text "$USER"            "$USER"text				
test echo ''''''''''$USER''''''''''										
test echo """"""""$USER""""""""											
test echo $USER'$USER'Once a gunner always a gunner $USER COYG      $USER ''	
test echo $USER '' $USER $USER '' $USER '' $USER -n $USER				
test echo ' \' ' \'														
test echo '\" ' " \"\""													
test echo \\\" \\\" \\\" \\\"\\\"\\\" \\\'\\\'\\\'						
test echo "$USER""$USER""$USER"											
test echo text"$USER"test												
test echo '$USER' "$USER" "text \' text"									
test echo '$USER'														
test echo $USER " "														
test echo "$USER""Users/$USER/file""'$USER'"'$USER'						
test echo "$USER$USER$USER"												
test echo '$USER'"$USER"'$USER'											
test echo '"$USER"''$USER'"""$USER"										
test echo " $USER  "'$PWD'												
test echo " $USER  \$ "'$PWD'											
test echo $USER=4														
test echo $USER=POMS 												
test echo $USER															
test echo $?																
test echo $PWD/file														
test echo "$PWD/file"													
test echo "text" "text$USER" ... "$USER"									
test echo $PWD															