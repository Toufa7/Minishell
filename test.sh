#!/bin/bash


cd 								
cd .. 							
cd . 							
cd /Users 						
cd // 							
cd '//' 						
cd ////// 						
cd ./././ 						
cd / 							
cd '/etc' 						
cd '/var' 						
cd "$PWD/prompt"				
cd "doesntexist"				
cd "doesntexist" 2>/dev/null	
cd ../../..						
cd ..							
cd ..							
cd ?							
cd +							
cd _							
cd bark bark					
cd '/'							
cd $PWD/file_tests				
cd $OLDPWD/builtins				

ECHO:

echo																
echo echo															
eCho																
eChO																
eCHO																
echo $																
echo $ $															
ECHO																
echo rhobebou														
echo stop barking													
echo "bonjour"														
echo bonjour														
echo 'bonjour'														
echo -n bonjour														
echo -nn bonjour													
echo -n -n -n bonjour												
echo "-n" bonjour													
echo -n"-n" bonjour													
echo "-nnnn" bonjour												
echo "-nnnn" -n bonjour												
echo "-n -n -n"-n bonjour											
echo "-n '-n'" bonjour												
echo $USER															
echo "$USER"														
echo "'$USER'"														
echo " '$USER' "													
echo text"$USER"													
echo text"'$USER'" ' $USER '										
echo "text"   "$USER"    "$USER"									
echo '              $USER          '								
echo               text "$USER"            "$USER"text				
echo ''''''''''$USER''''''''''										
echo """"""""$USER""""""""											
echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''	
echo $USER '' $USER $USER '' $USER '' $USER -n $USER				
echo ' \' ' \'													
echo '\" ' " \"\""												
echo \\\" \\\" \\\" \\\"\\\"\\\" \\\'\\\'\\\'					
echo "$USER""$USER""$USER"											
echo text"$USER"test												
echo '$USER' "$USER" "text \' text"									
echo '$USER'														
echo $USER " "														
echo "$USER""Users/$USER/file""'$USER'"'$USER'						
echo "$USER$USER$USER"												
echo '$USER'"$USER"'$USER'											
echo '"$USER"''$USER'"""$USER"										
echo " $USER  "'$PWD'												
echo " $USER  \$ "'$PWD'											
echo $USER=4														
echo $USER=thallard 												
echo $USER															
echo $?																
echo $PWD/file														
echo "$PWD/file"													
echo "text" "text$USER" ... "$USER"									
echo $PWD															

env | grep "_="														
export | grep "SHLVL"												
export | grep "OLDPWD"												
export | grep "PWD"													
export $?															
export TEST															
export TEST=														
export TEST=123														
export ___TEST=123													
export --TEST=123													
export ""=""														
export ''=''														
export "="="="														
export '='='='														
export TE\\\ST=100													
export TE-ST=100													
export -TEST=100													
export TEST-=100													
export _TEST=100													
export TEST															
export ==========													
export 1TEST=														
export TEST															
export ""=""														
export TES=T=""														
export TE+S=T=""													
export TES\\\\T=123
export TES.T=123
export TES\\\$T=123
export TES\\\\T
export TES.T=123
export TES+T=123
export TES=T=123
export TES}T=123
export TES{T=123
export TES-T=123
export -TEST=123
export _TEST=123
export TES_T=123
export TEST_=123
export TE*ST=123
export TES#T=123
export TES@T=123
export TES!T=123
export TES$?T=123
export =============123
export +++++++=123
export ________=123
export export
export echo
export pwd
export cd
export export
export unset
export sudo
export TES^T=123
export TES!T=123
export TES\~T=123
export TEST+=100


env | grep "_="																
env | grep "SHLVL"															
echo oui | cat -e															
echo oui | echo non | echo something | grep oui								
echo oui | echo non | echo something | grep non								
echo oui | echo non | echo something | grep something						
cd .. | echo "something"													
cd .. | echo "something"													
cd / | echo "something"														
cd .. | pwd																	
ifconfig | grep ":"															
ifconfig | grep nothing														
whoami | grep $USER															
whoami | grep $USER > tmp/file												
whoami | cat -e | cat -e > tmp/file											
cat Makefile | grep "FLAGS"													
cat Makefile | cat -e | cat -e												
cat Makefile | grep "FLAGS" | grep "FLAGS" | cat -e							
export TEST=123 | cat -e | cat -e											
unset TEST | cat -e															
echo test | cat -e | cat -e | cat -e										
whereis ls | cat -e | cat -e > test											
echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e
ls -la | grep "."															
whereis grep > tmp/file														
whereis grep > tmp/file														
ls -la > tmp/file															
ls -la > tmp/file															


unset
export TEST=100
unset doesntexist
unset PWD
unset PWD
unset OLDPWD
unset PATH
unset PATH
unset PATH
unset TES\\\\T
unset TES;T
unset TES.T
unset TES+T
unset TES=T
unset TES}T
unset TES{T
unset TES-T
unset -TEST
unset _TEST
unset TES_T
unset TEST_
unset TE*ST
unset TES#T
unset TES@T
unset TES!T
unset TES$?T
unset ============
unset +++++++
unset ________
unset export
unset echo
unset pwd
unset cd
unset unset
unset sudo
unset TES^T
unset TES!T
unset TES\~T
8:20
<in cmd "str1 str2 str3" | cmd2 -arg | cmd3 >out >out2
cmd "str1 str2 str3" >out | cmd2 -arg | cmd3 >out2 >out3
cmd "str1 str2 str3" >out | cmd2 -arg str | cmd3 str >out2 >out3
cmd <in -arg | cmd2 "str |" >out>>out2
cmd1 <in1 -arg1 > out1 | cmd2 <in2 -arg2 > out2


echo $PWD
echo $PWD|cat -e
echo $PWD hallo | cat -e
echo '$PWD hallo | cat -e'
echo "$PWD hallo | cat -e"


export TEST=1 test=2 sup=																
export TEST=1 test=2 sup= | env															


wc < Makefile -l | cat -e > outfile | echo hello | rev > outfile2						

< test.txt < Makefile<README.md wc -l|cat -e | rev										

< Makefile cat > out | < README.md cat -e 												
< README.md cat -e | <Makefile cat														

< in1 cat -e | < in2 cat																
< in1 cat -e > out1 | < in2 cat															

env | rev | head -5 | cat -e | rev														
< in1 <in2 <in3 < Makefile rev | head -5 | cat -e | rev > out > out2 > out3 >> out4		

echo ok"hello"ok1"mfg" == echo ok'hello'ok1'mfg'
-- okhellook1mfg

echo okhellook1"mfg" == echo okhellook1'mfg'
-- okhellook1mfg

echo "o""k       "hellook1 == echo 'o''k       'hellook1
-- ok       hellook1

echo '"***hello***"'
"***hello***"

echo "'***hello***'"
"***hello***'

echo ok"'hello'"ok1"hello1"ok2

echo "text"   "$USER"    "$USER"
echo """"""""$USER""""""""
echo "-n -n -n"-n bonjour
echo "'$USER'"
< in1 < in2																				
< in1 cat < in2																			
< Makefile > outfile																	
> out																					


echo "$PWD         "a
/Users/wollio/Desktop/projects/4/minishell         a

echo "         $PWD"
         /Users/wollio/Desktop/projects/4/minishell