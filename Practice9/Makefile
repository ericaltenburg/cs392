.PHONY: task1 

task1:
	echo "Compiling task "
	gcc -O0 -g -o get_google_webpage get_google_webpage.c
	./get_google_webpage www.google.com /tmp/google.page
	if cat /tmp/google.page | grep -q 'www.google.com'; then echo " Result: Passed"; else echo "Result : Failed"; fi
