#include<stdio.h>
#include<string.h>

void cs392_strswap(char * src, char * dst){

	/* Please write down your code here
	 *
	 * You can assume both src and dst are big enough to hold the data of each other
	 * No API is allowed to use here 
	 * No additional array or dynamic memory is allowed to use here
	 * Please write down your pledge of honor system as comment 
	 *
	 * */

	// Make a for loop that will go char by char and then swap the two of them until there is nothing left in both of them
	// Need to find out how to go until the end, check if /0 is there

	size_t src_size = sizeof(src) / sizeof(char);
	size_t dst_size = sizeof(dst) / sizeof(char);
	size_t biggest = 0;
	int equal = 0;

	if (src_size > dst_size) { // Figures out which one is bigger
		biggest = src_size;
	} else if (dst_size > src_size) {
		biggest = dst_size;
	} else if (dst_size == src_size) {
		biggest = src_size;
		equal = 1; // They are equal now
	}


	if (equal == 1) { // They are of equal length
		for (size_t i = 0; i < biggest; i ++) {
			char temp = src[i];
			src[i] = dst[i];
			dst[i] = temp;
		}
	} else {
		for (size_t i = 0; i < biggest; i++) { // Go to the biggest,

			if (src[i] == '\0' || dst[i] == '\0') { // One of the strings reached the end

				if (src[i] == '\0') { // It was str

					while (dst[i] != '\0') { // Finish off the dst then break
						src[i] = dst[i];
						i ++;
					}
					break;
				} else if (dst[i] == '\0') { // it was dst

					while(src[i] != '\0') {
						dst[i] = src[i];
						i++;
					}
					break;
				}
			} else { // Neither has ended so continue on with swapping
				char temp1 = src[i];
				src[i] = dst[i];
				dst[i] = temp1;
			}

		}
	}

}


int main(int argc, char ** argv){

	int index; 
	char src[128];
	char dst[128];

	printf("CS_392 midterm task 1: \n");

	index = 1; 

	while(index <= 5){

		printf("	Test case %d:\n", index);

		memset(src, 0, 128);
		memset(dst, 0, 128);

		strcpy(src, argv[index]);
		strcpy(dst, argv[index+1]);

		cs392_strswap(src, dst);
		
		printf("	Original src: \"%s\"; Original dst: \"%s\"; Swapped src \"%s\"; Swapped dst \"%s\"\n", argv[index], argv[index+1], src, dst);	

		if(strcmp(src, argv[index+1]) == 0 && strcmp(dst, argv[index]) == 0)	
			printf("	=== Result: PASSED === \n\n");
		else
			printf("	=== Result: FAILED === \n\n");	

		index += 2;
	}

	return 0;
}


