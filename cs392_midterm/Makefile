
.PHONY: task1 task2 task3

task1:
	echo "Compiling task 1"
	gcc -O0 -g -o task1 task1.c
	./task1 hello world ^@\(\)\(\) H@@H """"""DDD CS392

task2:
	echo "Compiling task 2"
	gcc -O0 -g -o task2 task2.c
	./task2

task3:
	echo "Compiling task 3"
	gcc -O0 -g -o task3 task3.c
	cp cs392_task3.txt cs392_task3_tmp.txt
	./task3
	echo "\n Original File ======================= "
	cat cs392_task3.txt
	echo "\n Correct result ======================="
	cat cs392_task3_res.txt
	echo "\n Your result ========================"
	cat cs392_task3_tmp.txt
	echo "\n"
	if cmp -s "cs392_task3_tmp.txt" "cs392_task3_res.txt"; then echo " Result: Passed"; else echo "Result : Failed"; fi	
	rm cs392_task3_tmp.txt	
