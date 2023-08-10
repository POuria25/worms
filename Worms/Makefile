LOGFILE=$(LOGPATH) `date +'DATE: %d/%m/%y - TIME: %H:%M:%S'`
CPP_FILES = main.cpp worms.cpp timer.cpp gameobject.cpp obstacles.cpp weapon.cpp powerbar.cpp projectile.cpp shapes.cpp bazooka.cpp utils.cpp shotgun.cpp view.cpp game.cpp
AUTHOR = 'Pouria Inc'
MESSAGE = 
CFLAGS += -I/usr/include/SDL 
CFLAGS += -I/usr/include/SDL2
all:
	g++ -std=c++17 -Wall -Wextra -o main $(CPP_FILES) -lSDL2 -lm -lSDL2_ttf
	#./main

send:
	git add .
	git commit -m "Sent -> $(LOGFILE) by $(AUTHOR) : $(MESSAGE)"
	git push

receive:
	git pull

clean:
	rm -f main

valgrind:
	g++ -g -std=c++17 -Wall -Wextra -o main $(CPP_FILES) -lSDL2 -lm -lSDL2_ttf
	valgrind --leak-check=full ./main

gdb:
	g++ -g -std=c++17 -Wall -Wextra -o main $(CPP_FILES) -lSDL2 -lm -lSDL2_ttf
	gdb ./main

memory_sanitizer:
	clang++ -fsanitize=memory -fno-omit-frame-pointer -g -std=c++17 -I/usr/include/SDL2 -o main $(CPP_FILES) -lSDL2 -lm -lSDL2_ttf

tar:
	tar -czvf 03.tar.gz *cpp *hpp Makefile assets report.pdf

.PHONY: all send receive clean tar

# when git for the first time: 
# git init
# git add .
# git commit -m "first commit"
# (git branch -M <new-branch name>) (optional)
# git remote add origin <url> (i.e. git@github.com:Pouria/Worms.git)
# git push -u origin <new-branch-name> (or by default master or main )

# then runnning : 
# make send AUTHOR="Pouria" MESSAGE="update"
# will produce a nice push with an automatic push to the git repo
