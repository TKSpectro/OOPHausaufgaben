Aufbau einer Datei zum einlesen:
ACHTUNG: Zuerst ALLE Junctions und dann alle Roads

Für Junctions:
"Junction";x;y;Name;
Für Roads:
"Road";Junction1Name;Junction2Name;Name;x;y;...;...;
Road;Leipziger Platz;Hanseplatz;Umweg;300;250;100;120;
Für Vehicle(noch nicht implementiert):
"Vehicle";RoadName;Speed;

Bsp.:

Junction;100;120;Hanseplatz;
Junction;300;250;Leipziger Platz;
Road;Hanseplatz;Leipziger Platz;Leipziger Straße;100;120;200;400;300;250;
Road;Leipziger Platz;Hanseplatz;Umweg;300;250;100;120;