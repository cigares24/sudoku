all:
	gcc *.c -o sudoku

clean:
	rm -rf sudoku

re: clean all
