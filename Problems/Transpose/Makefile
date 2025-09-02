# run with 'make -i'
# Note: the large spaces are tabs, this is important
# Run GCOV, requires that we build the code
# All of these runs of ./prog are a test case
# We want to cover 100% of prog through these tests
run-tests-coverage: build
	./prog test_normal.txt out_test_normal.txt
	./prog
	./prog nonexistent_file.txt output.txt
	./prog test_invalid_dimensions.txt output.txt
	./prog test_insufficient_values.txt output.txt
	./prog test_huge_memory.txt output.txt
	./prog test_matrix_alloc_failure.txt output.txt
	./prog test_row_alloc_failure.txt output.txt
	./prog test_output_file_failure.txt /nonexistent/directory/output.txt
	gcov prog.c

# Run Valgrind to find memory leaks, requires that we build the code
# All of these runs of valgrind ./prog are a test case, mirroring coverage tests
run-tests-leak: build
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog test_normal.txt out_test_normal.txt
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog nonexistent_file.txt output.txt
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog test_invalid_dimensions.txt output.txt
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog test_insufficient_values.txt output.txt
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog test_huge_memory.txt output.txt
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog test_matrix_alloc_failure.txt output.txt
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog test_row_alloc_failure.txt output.txt
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog test_output_file_failure.txt /nonexistent/directory/output.txt

# Compile the code, requires that we clean up some files first.
# Add –lm if your code needs the math library.
build: clean
	gcc -fprofile-arcs -ftest-coverage -g prog.c -o prog
clean:
	rm -f *~
	rm -f prog
	rm -f *.gcda *.gcno *.gcov
