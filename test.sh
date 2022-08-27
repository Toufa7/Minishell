#!/bin/bash

ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls
sleep 0.5
env | grep "_="
sleep 0.5
env | grep "SHLVL"
sleep 0.5
echo oui | cat -e
sleep 0.5
echo oui | echo non | echo something | grep oui
sleep 0.5
echo oui | echo non | echo something | grep non
sleep 0.5
echo oui | echo non | echo something | grep something
sleep 0.5
cd .. | echo "something"
sleep 0.5
cd .. | echo "something"
sleep 0.5
cd / | echo "something"
sleep 0.5
cd .. | pwd											
sleep 0.5
ifconfig | grep ":"
sleep 0.5
ifconfig | grep nothing								
sleep 0.5
whoami | grep $USER									
sleep 0.5
whoami | grep $USER > tmp/file						
sleep 0.5
whoami | cat -e | cat -e > tmp/file					
sleep 0.5
cat Makefile | grep "FLAGS"							
sleep 0.5
cat Makefile | cat -e | cat -e						
sleep 0.5
cat Makefile | grep "FLAGS" | grep "FLAGS" | cat -e	
sleep 0.5
export TEST=123 | cat -e | cat -e					
sleep 0.5
unset TEST | cat -e									
sleep 0.5
echo test | cat -e | cat -e | cat -e				
whereis ls | cat -e | cat -e > test					
sleep 0.5
echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e
sleep 0.5
ls -la | grep "."									
sleep 0.5
whereis grep > tmp/file
sleep 0.5								
whereis grep > tmp/file								
sleep 0.5
ls -la > tmp/file									
sleep 0.5