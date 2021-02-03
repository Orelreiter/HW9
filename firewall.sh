#!/bin/bash
while read packet
do
	echo "$packet" >> packetlist.txt
done

cat "$1" > rulelist.txt

# Clearing spaces and comments even though it should ignore blackened lines.

while read line 
do
	line=`echo "$line" |sed 's/[[:space:]]//g' | sed 's/#.*//g'`
	if [[ "$line" == "" ]]; then
		continue
	fi
# This splits the first rule to subrules by passing over each subrule.  
# Going over each substring and checking whether it counts as a rule,
# it also checks the packets.  
	readarray -d , -t subrule <<< "$line"
	first_rule=1
	for (( counter=0; counter < ${#subrule[*]}; counter++ ))
	do
		if [[ "${subrule[counter]}" =~ "src-ip" || "${subrule[counter]}" =~ "dst-ip" 
			|| "${subrule[counter]}" =~ "src-port" ||
			 "${subrule[counter]}" =~ "dst-port" ]] ;then

			if (( first_rule == 1 )); then 
				./firewall.exe "${subrule[counter]}"< packetlist.txt > rules_packet.txt
				first_rule=0
			else
				./firewall.exe "${subrule[counter]}" < rules_packet.txt > tmp.txt
				cat tmp.txt > rules_packet.txt
			fi
		fi
		if (( counter==${#subrule[*]}-1 )); then
				cat rules_packet.txt >> packet_and_rule.txt 
		fi
	done
done < rulelist.txt

# Each packet that will be hold one of the rules created it will be added 
# to the output

rm rules_packet.txt
rm tmp.txt
sort packet_and_rule.txt |uniq |sed 's/[[:space:]]//g'
rm rulelist.txt
rm packetlist.txt
rm packet_and_rule.txt
