FLAGS=-Wall -Wextra
SRC=main.c

ifeq ($(OS), Windows_NT)
    OUTPUT=passgen.exe
    RM=del /F /Q
else
    OUTPUT=passgen
    RM=rm -rf
endif

all: $(OUTPUT)

$(OUTPUT):
	gcc $(FLAGS) $(SRC) -o $(OUTPUT)

clean:
	$(RM) $(OUTPUT)
