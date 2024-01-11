# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    count_words.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 21:02:23 by iassambe          #+#    #+#              #
#    Updated: 2023/11/30 17:16:41 by iassambe         ###   ########.fr        #
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
	exit 1
fi

while IFS= read -r line; do
	current=$(echo "$line" | wc -w)
	if [ "$current" != "$prev" ] && [ -n "$prev" ]; then
		echo "Lines diff lol"
		exit 1
	fi
	echo "$line" | wc -w
	prev="$current"
done < "$fd"

lines=$(cat $fd | wc -l)

echo "\nlines in file - $lines"