.PHONY: task3

task1:
	@echo "Compiling task 3"
	@gcc -O0 -g -o server server.c
	@gcc -O0 -g -o client client.c
	@./server &
	@./client
	@sleep 1
	@if ps -h | grep -v "grep" | grep -q "./server"; then pkill server; ipcrm -M 0xffffffff; fi
