run: build
	./p2

build: compile ArrayList.o BinaryTree.o CityIndex.o Controller.o CostIndex.o FileReader.o Indexor.o IntArray.o LinkedList.o TimeIndex.o main.o restaurant.o
	gcc -g -o p2 ArrayList.o BinaryTree.o CityIndex.o Controller.o CostIndex.o FileReader.o Indexor.o IntArray.o LinkedList.o TimeIndex.o main.o restaurant.o

compile: ArrayList.c BinaryTree.c CityIndex.c Controller.c CostIndex.c FileReader.c Indexor.c IntArray.c LinkedList.c TimeIndex.c main.c restaurant.c
	gcc -c ArrayList.c 
	gcc -c BinaryTree.c 
	gcc -c CityIndex.c 
	gcc -c Controller.c 
	gcc -c CostIndex.c 
	gcc -c FileReader.c 
	gcc -c Indexor.c 
	gcc -c IntArray.c 
	gcc -c LinkedList.c 
	gcc -c TimeIndex.c 
	gcc -c main.c 
	gcc -c restaurant.c
	
	