#!/bin/bash

shopt -s xpg_echo
touch passed_packets.txt #prepare the output file
packets_all=$(cat /dev/stdin)

#"clean" the input: delete empty lines/comments/extra commas and whie spaces
while read -r packet 
do
	packet=$(echo "${packet}" | sed 's/ //g' | awk -F# '{print $1'})
	packet=$(echo "${packet}" | sed -E 's/,+/,/g')
	if [[ "${packet::1}" == ',' ]]; then
		packet=$(echo "$packet" | sed 's/,//')
	fi 
	if [[ "$packet" != "" ]]; then #empty lines
		echo "$packets_all" > packets_so_far.txt
		IFS=',' read -r -a rules <<< "$packet"
		for rule in "${rules[@]}"
		do
			#save packets that satisfy current rule in temp file
			./firewall.exe "$rule" <packets_so_far.txt > temp.txt
			cat temp.txt>packets_so_far.txt
		done
		cat packets_so_far.txt >> passed_packets.txt
	fi
done<$1
#sort and delete repeating packets
cat passed_packets.txt | sort -u | sed 's/ //g'
rm packets_so_far.txt temp.txt