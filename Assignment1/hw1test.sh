#!/bin/bash
PROGNAME=$1
TESTSPASSED=0
TESTSRUN=0

# Use this function when programs read fron stdin
# Pass the program input as the first argument, and the expected output as the second
run_test_read_stdin() {
	(( TESTSRUN++ ))
	input=$1
	expected=$2
	output=$( echo "$input" | ./cs392_ass1 )

	if [ "$output" == "$expected" ]; then
		(( TESTSPASSED++ ))
		echo "Test $TESTSRUN passed"
	else
		echo "Test $TESTSRUN failed. Expected '$expected', but recieved '$output'"
	fi
}

echo 'Runnings tests...'

# Add more tests here
run_test_read_stdin '' ''
run_test_read_stdin '|/\/correct>:(!' 'correct'
run_test_read_stdin '123' '123'
run_test_read_stdin '0b1' '0b1'
run_test_read_stdin '0723' '0723'
run_test_read_stdin '0xdab' '0xdab'

echo "$TESTSPASSED/$TESTSRUN tests passed"
