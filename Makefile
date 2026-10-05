clean:
	rm t9search

main: t9search.c
	gcc -std=c23 -Wall -Wextra -Werror -pedantic t9search.c -o t9search

run: t9search.c seznam.txt
	gcc -std=c23 -Wall -Wextra -Werror -pedantic t9search.c -o t9search
	./t9search < seznam.txt