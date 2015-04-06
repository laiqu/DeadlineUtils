# DeadlineUtils


# 2D visualization
Rysuje siatkę 2D! 
* Można strzałkami ją przesuwać, z shiftem szybciej przesuwać, z dwoma shiftami jeszcze szybciej przesuwać!
* Plusem zoomować, minusem zoomować w drugą stronę, a 0 wrócić do początku.
* Obsługuje callbacki na mouse release, mouse hover, oraz callback dla wszystkich widocznych pól.
Kompilacja prawdopodobnie cos w stylu (jakby co to g++ o dziwo tez dziala):
clang++ -std=c++11 Globals.cpp GridWorld.cpp 2d.cpp -o 2d  -lsfml-graphics -lsfml-window -lsfml-system                                       

# Conn
* get_connection - zwraca pointer do polaczenia (tcp::iostream) z danym hostem/portem
* login          - zakladajac taka komunikacje jak zawsze, loguje do servera
* precommand     - zakladajac taka komunikacje jak zawsze, sprawdza czy jest ERROR czy OK w polaczeniu
* starts_with    - w sumie nigdzie nie uzywam, ale sprawdza czy dany string ma prefixa.

Dorzucilem jeszcze cos co byle jak laczy vis z laczeniem sie zeby byl jakis start.
Ergo kompilacja 2dtemplejta wyglada jakos tak:
clang++ -std=c++11 2dtemplate.cpp 2dvis/Globals.cpp 2dvis/GridWorld.cpp -lsfml-graphics -lsfml-window -lsfml-system -lboost_system -lpthread

Wymaga SFML'a 2.2 (jest na AURze)
