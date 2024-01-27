# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    count_words.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 21:02:23 by iassambe          #+#    #+#              #
#    Updated: 2024/01/26 14:50:05 by iassambe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Gimme file"
	exit 1
fi

fd="$1"
prev=""

if [ ! -f "$fd" ]; then
	echo "Gimme NORMAL file"
	exit 2
fi

while IFS= read -r line; do
	current=$(echo "$line" | wc -w)
	if [ "$current" != "$prev" ] && [ -n "$prev" ]; then
		echo "Lines diff lol"
		exit 228
	fi
	echo "$line" | wc -w
	prev="$current"
done < "$fd"

lines=$(cat $fd | wc -l)

echo "\nlines in file - $lines"