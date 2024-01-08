exceute: main.o
	g++ main.o -o binary
main.o: 
	g++ -c linked_list.cpp -I./ -o main.o
clean:
	rm *.0 binary