all: 
	g++ scanner.cpp -o output -w
	./output
clean:
	rm -rf *o output output.txt