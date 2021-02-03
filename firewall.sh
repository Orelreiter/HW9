#!/bin/bash
while read packet
do
	echo "$packet" >> packetlist.txt
done

cat "$1" > listofrules.txt

rule_1st=1

# Clearing spaces and comments even though it should ignore blackened lines.

while read line 
do
	line=`echo "$line" |sed 's/[[:space:]]//g' | sed 's/#.*//g'`
	if [[ "$line" == "" ]]; then
		continue
	fi
	
# This splits the first rule to subrules by passing over each subrule.  
	readarray -d , -t subrule <<< "$line"
# Going over each substring and checking whether it counts as a rule,
# it also checks the packets.
	for (( counter=0; counter < ${#subrule[*]}; counter++ ))
	do
		if [[ "${subrule[counter]}" =~ "dst-port" || "${subrule[counter]}" =~ "src-port" 
			|| "${subrule[counter]}" =~ "dst-ip" || "${subrule[counter]}" =~ "src-ip" ]];
			then
				if (( rule_1st == 1 )); then 
					./firewall.exe "${subrule[counter]}"< packetlist.txt > rules_of_packets.txt
					rule_1st=0
				else
					./firewall.exe "${subrule[counter]}" < rules_of_packets.txt > tmp.txt
					cat tmp.txt > rules_of_packets.txt
				fi
			fi
		if (( counter==${#subrule[*]}-1 )); then
				cat rules_of_packets.txt >> rules_of_packets_combine.txt 
		fi
	done
done < listofrules.txt

# Each packet that will be hold one of the rules created it will be added 
# to the output

sort rules_of_packets_combine.txt |uniq |sed 's/[[:space:]]//g'
rm rules_of_packets.txt
rm tmp.txt
rm listofrules.txt
rm packetlist.txt
rm rules_of_packets_combine.txt
