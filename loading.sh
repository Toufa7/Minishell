function ProgressBar {
    let _progress=(${1}*100/${2}*100)/100
    let _done=(${_progress}*4)/10
    let _left=40-$_done
    _fill=$(printf "%${_done}s")
    _empty=$(printf "%${_left}s")

printf "\rMinishell Loading: [${_fill// /#}${_empty// /-}] ${_progress}%%"

}
_start=1

_end=10

for number in $(seq ${_start} ${_end})
do
    sleep 0.1
    ProgressBar ${number} ${_end}
done
printf '\n          Minishell Created Successfully\n'