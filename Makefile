all: myshell stringa

myshell: myshell.c
	gcc myshell.c -o myshell

stringa: stringa.c
	gcc stringa.c -o stringa

clean:
	rm -f ./myshell
	rm -f ./stringa
