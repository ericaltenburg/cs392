# **
# Author:		Eric Altenburg
# Date: 		5 September 2019
# Description:	Adding from 1 to 10,000,000
# **

def main():
	counter = 0

	for i in range(10000000+1):
		counter = counter + i

	print(counter)

# Calling main method
if __name__ == "__main__":
	main()



# C program:

# # include <stdio.h>
# unsigned long sum;
# .
# .
# .

# print("The final value is %lu ", sum);