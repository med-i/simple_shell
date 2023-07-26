#!/bin/bash

# Usage : ./check.sh | less -r
# copy this file inside your project folder and run ./checker.sh | less -r

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
function run_check()
{
    echo "--> [" $1 "] <--"
    chars1=$(wc -m < 1a2b3c4d5e6f7g8h9i)
    chars2=$(wc -m < 1a2b3c4d5e6f7g8h9b)
    if diff 1a2b3c4d5e6f7g8h9i 1a2b3c4d5e6f7g8h9b >/dev/null; then
        echo -e "\e[32mSuccess\e[0m"
    else
        echo -e "\e[31mFailed\e[0m"
        echo -e "\e[0m[Got]\e[31m"
        cat 1a2b3c4d5e6f7g8h9i
        echo -e "\e[0m[" $chars1 "Chars]\e[31m"
        echo -e "\e[0m[Expected]\e[31m"
        cat 1a2b3c4d5e6f7g8h9b
        echo -e "\e[0m[" $chars2 "Chars]\e[0m"
    fi
    rm 1a2b3c4d5e6f7g8h9i 1a2b3c4d5e6f7g8h9b;
    echo "************************************"
}
######### case 1
command1=$(echo "exit 98" | ./hsh 2>&1)
command2=$(echo "exit 98" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""exit" with 98"

######### case 2
command1=$(echo "exit -12" | ./hsh 2>&1)
command2=$(echo "exit -12" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""exit" with negative"

######### case 3
command1=$(echo "exit 980" | ./hsh 2>&1)
command2=$(echo "exit 980" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""exit" with 980"

######### case 4
command1=$(echo "exit abc" | ./hsh 2>&1)
command2=$(echo "exit abc" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""exit" with string"

######### case 5
command1=$(echo "ls ; exit 98" | ./hsh 2>&1)
command2=$(echo "ls ; exit 98" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check "comman separator ";" 2 cmd"

######### case 6
command1=$(echo "ls -la ; ls ; ls" | ./hsh 2>&1)
command2=$(echo "ls -la ; ls ; ls" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check "command separator ";" 3 cmd"

######### case 7
command1=$(echo "ls -la;ls" | ./hsh 2>&1)
command2=$(echo "ls -la;ls" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check "command separator ";" no space"

######### case 8
command1=$(echo "ls -la ; ls /homzz3" | ./hsh 2>&1)
command2=$(echo "ls -la ; ls /homzz3" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check "command separator ";" success ; fail"

######### case 8
command1=$(echo "ls && ls /home" | ./hsh 2>&1)
command2=$(echo "ls && ls /home" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check "single "&&""

######### case 9
command1=$(echo "ls && ls /home && echo hi" | ./hsh 2>&1)
command2=$(echo "ls && ls /home && echo hi" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check "two "&&" "

######### case 10
command1=$(echo "ls && ls /home && echo hi && /bin/ls" | ./hsh 2>&1)
command2=$(echo "ls && ls /home && echo hi && /bin/ls" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check "three "&&" "

######### case 11
command1=$(echo "ls;" | ./hsh 2>&1)
command2=$(echo "ls;" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check " "ls;" "

######### case 12
command1=$(echo "ls ;" | ./hsh 2>&1)
command2=$(echo "ls ;" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""ls ;" "

######### case 13
command1=$(echo "/bin/ls zzee ; /bin/ls" | ./hsh 2>&1)
command2=$(echo "/bin/ls zzee ; /bin/ls" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""cmd" fail ; cmd"

######### case 14
command1=$(echo "echo $$" | ./hsh 2>&1)
command2=$(echo "echo $$" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""echo" dollarx2"

######### case 15
command1=$(echo "echo $helloMe" | ./hsh 2>&1)
command2=$(echo "echo $helloMe" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""echo" invalid variable"

######### case 16
command1=$(echo "echo $PATH" | ./hsh 2>&1)
command2=$(echo "echo $PATH" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""echo"  dollar path"

######### case 17
command1=$(echo "ls /homzz
echo $?" | ./hsh 2>&1)
command2=$(echo "ls /homzz
echo $?" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""echo" status fail"


######### case 18
command1=$(echo "echo comment #dont print this line" | ./hsh 2>&1)
command2=$(echo "echo comment #dont print this line" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check "command and "comment" "

######### case 19
command1=$(echo "#comment dont print me" | ./hsh 2>&1)
command2=$(echo "#comment dont print me" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""comment" only"

######### case 20
command1=$(echo "echo print#this line" | ./hsh 2>&1)
command2=$(echo "echo print#this line" | sh 2>&1)
echo "$command1" > 1a2b3c4d5e6f7g8h9i
echo "$command2" > 1a2b3c4d5e6f7g8h9b
run_check ""comment" sign in echo"

#>>>> betty testing  <<<<<<

#remove the hashs below to enable betty testing

#echo "-->" Check documentation
#betty-doc *.c *.h
#echo "-->" Check style
#betty-style *.c *.h
