CSTUFF = -Wall -pedantic -std=c99
all: 
	gcc secretSanta.c $(CSTUFF) -o santa
	mkdir Results

run:
	./santa Roommates Alliyya Cindy Vivian Anh 

alternate:
	gcc nonCommand.c $(CSTUFF) -o santa

ORun:
	./santa
	espeak "Merry Christmas"

clean:
	rm -r Results
	rm santa