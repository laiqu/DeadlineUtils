# DeadlineUtils


# 2D visualization
Rysuje siatkę 2D! 
* Można strzałkami ją przesuwać, z shiftem szybciej przesuwać, z dwoma shiftami jeszcze szybciej przesuwać!
* Plusem zoomować, minusem zoomować w drugą stronę, a 0 wrócić do początku.
* Obsługuje callbacki na mouse release, mouse hover, oraz callback dla wszystkich widocznych pól.
Kompilacja prawdopodobnie cos w stylu (jakby co to g++ o dziwo tez dziala):
clang++ -std=c++11 Globals.cpp GridWorld.cpp 2d.cpp -o 2d  -lsfml-graphics -lsfml-window -lsfml-system                                       

Wymaga SFML'a 2.2 (jest na AURze)
