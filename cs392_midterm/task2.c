#include<stdio.h>
#include<string.h>

int cs392_substr_count(char * str, char * substr){

	/* Please write down your code here
	 *
	 * No API is allowed to use here 
	 * No additional array or dynamic memory is allowed to use here
	 * Please write down your pledge of honor system as comment 
	 *
	 * */
	int count = 0; // Holds the total amount of occurrences in the str

	// size_t sub_size = sizeof(substr) / sizeof(char);
	// size_t str_size = sizeof(str) / sizeof(char);

	//size_t doesn't work, wasted so much time on this :)))

	int subs = 0;
	while(substr[subs] != '\0')  {
		subs++;
	}
	int strs = 0;
	while(str[strs] != '\0') {
		strs++;
	}

	if (substr[0] == '\0') { // If the substring is empty
		return count;
	}

	for (int i = 0; i < strs; i++) { // Iterate through the arrray checking each one

		// Iterate thorugh the array until sub[0] is found, then from there you loop again until all of them are found, if all found then incremment 1, and keep track of how much
		// you go forward in loop, then increment i that amount. If it is not found, then break out of loop and then 
		// increment i that amount - 1 as it might start there. This has an absolute horrible time complexity but hey, if it works

		int j;
		for (j = 0; j < subs; j++) { // Iterate through the substring
			if (str[i+j] != substr[j]) { // If they are not equal, then you break
				break;
			}
		}

		if (j == subs) {
			count ++;
			j = 0;
		}
	}

	return count;
}


int main(int argc, char ** argv){

	int index; 
	int cnt;

	printf("CS_392 midterm task 2: \n");

	printf("	Test case 1 string \"%s\" and substring \"%s\"\n", "aaaa", "a");
	
	cnt = cs392_substr_count("aaaa", "a");

	printf("	Correct result 4 and your result %d\n", cnt);

	if(cnt == 4)
		printf("	=== Result: PASSED === \n\n");
	else
		printf("	=== Result: FAILED === \n\n");	


	printf("	Test case 2 string \"%s\" and substring \"%s\"\n", "aaaa", "");
	
	cnt = cs392_substr_count("aaaa", "");

	printf("	Correct result 0 and your result %d\n", cnt);

	if(cnt == 0)
		printf("	=== Result: PASSED === \n\n");
	else
		printf("	=== Result: FAILED === \n\n");	


	printf("	Test case 3 string \"%s\" and substring \"%s\"\n", "abc@def@ab@c@abc", "abc");
	
	cnt = cs392_substr_count("abc@def@ab@c@abc", "abc");

	printf("	Correct result 2 and your result %d\n", cnt);

	if(cnt == 2)
		printf("	=== Result: PASSED === \n\n");
	else
		printf("	=== Result: FAILED === \n\n");	

	return 0;
}


