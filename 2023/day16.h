char data1[][10] =
{
    ".|...\\....",
    "|.-.\\.....",
    ".....|-...",
    "........|.",
    "..........",
    ".........\\",
    "..../.\\\\..",
    ".-.-/..|..",
    ".|....-|.\\",
    "..//.|...."
};

char data[][110] =
{
    "\\.......-..|.....-.........\\.|.\\................................................-......................\\.../..",
    "...........|......\\...\\...-..-......................--.....|...........\\....|./..........-../-......|....-.../",
    "...|\\...............................././............./......|....\\/................/......../...........|...\\.",
    "........-............-......................|..|......................................|......................\\",
    "........../..................\\............|......./............................-./....\\.......................",
    ".....-....-..\\..|..|.-...\\...\\.........................../......-..--.......|..\\......\\...|.........|..../....",
    ".........\\.....|.....................................|.......|..........-.....................................",
    ".......|..........|................................................-............-......../......|........./...",
    "\\.....-|............./........-.....\\.....-......-....\\...........-.........\\..|............./................",
    ".../......\\...-...........-.......|...-......\\-.........../......../..\\..............-.............|..........",
    "....|........................./..|.|......./....../.......-.......................\\./.........................",
    ".........\\.......|/.........-...................\\.......|..\\...............|..../....-.....-..../.............",
    "/..-........\\..........................\\-....|...\\......\\.............|../..-.....|...................../../..",
    "............/|.......................|.............\\...\\.......\\........../...........-./...................\\.",
    ".........../.-....\\.\\.....................\\./............\\...............................-.................\\..",
    "......\\\\.......-........-.|..........................-............-...........................................",
    "............-....-.....|....\\........|.............................../.........-|...|\\..-...............|.....",
    "............/...-....|....|......-..\\..\\.-............-./\\.-.........|....//...............-.........-|.......",
    "..............-............................-..................\\\\...\\..\\-..\\................./.............\\.\\.",
    ".../......|......../..../......../..\\./..............|..../................/.........|...............././.....",
    ".............\\.|...|....-...-.........|.......\\.....\\.........\\..-.......-...............\\...\\..\\|..../.......",
    ".......-..........\\../..........................\\......\\../......\\...-....|..../...|./..\\............-.-......",
    ".................\\....-...................../.........-.......................-..............|................",
    "..-\\.............-..............-../.-../...../.......|..................|.......-................|.......\\...",
    ".......\\|.-....\\.../..................\\......\\....../..|-.........-.........|....\\..................\\........|",
    ".....././...........\\.-........-..-...\\..........-\\.............|.....|..-.........|...............|..........",
    "..............-..|........./..\\..|............-..........|......................./....................\\-.\\....",
    "...................-..............................................-....-....|..............-.........|././.../",
    "...\\...........................|..\\...................../..........-......./......./...............|..........",
    ".......................-......../...-....../....../.....././.|.......\\|......\\..........-.../..-......./......",
    "...\\..............\\../..|..-\\........................../-....\\........................../........./...|.|...-.",
    "..........\\...../...|.|.......\\........./................\\.......-.-.....|........|/..............\\...........",
    "..................\\....\\....|......\\.......//.............../.|.\\................../..........|..-............",
    ".......\\.\\............./...............-....................../........................\\./...................-",
    ".........../....\\...........|\\./|...|................./...-........\\.\\.....\\.....|......|....\\...../..........",
    "...........\\.....|......|...........|............/............................................\\/........../|..",
    "..../......\\\\.................../.|.......|...--..\\.-../\\/.................|..................................",
    "....................\\....\\..|................................\\.........-...........-................|.........",
    ".........................|...-......-.................\\...............|\\......./...--\\........................",
    "..../....|..|......\\..\\....................../|.....................\\|............................-...|.......",
    "\\......./...../..............\\......|...|.\\....../.....|...................|...........\\.......\\.............\\",
    "...............|./..-..-|....\\....-.................-................-.........../..\\..-......................",
    "..-.............................\\.\\-.................\\...........-........|.......-..............-....../.....",
    "........\\.-.................../\\..............-.|.................................\\.|.........-..............|",
    "...................................|..\\.........|...-................./.......-.....-/.\\..........\\...\\|......",
    "./........-.......|......|../...-.\\...........\\.........|-............................-..-...\\.....//......|..",
    "..................-........\\.../............................................./.....|......./....\\........|....",
    "..-|..........-......................|.\\...............................\\/........../.....|...............|....",
    "...\\......\\.\\.....|.........|...../.|../.............................|.....\\./....../............./..\\........",
    ".......\\..-.\\...-//................-...........................-........\\..../..................-.............",
    "..../.................\\..|..........\\\\.....-......................|-.................\\.........|..............",
    "..\\.\\...-..../........|..................................\\...|-.././......\\.\\......./|......./-....-......-\\..",
    "-......................................-.......................\\............\\...............|.\\.........\\.....",
    "../.-....../......................\\..........................-..\\......\\.......|...\\.-.....................|..",
    "..-..-..\\...............\\-...............................\\...............-........./......-.\\............-....",
    ".............--....\\...-../........./-.......................\\............................-...................",
    "....-..............-\\../-...........-......|\\...............................|.........--........./......\\../..",
    "....-.\\/.../.-.........|........./........-................\\..............\\.../........|............|.....--..",
    "........\\-...\\...........|...\\.......-\\.....|-...........................................-|............\\......",
    "............./.-..........\\....................\\......\\............\\.../../.-...-.......-.....................",
    ".......|\\..........-....................|.|.../.-.|.\\...\\/....../...|..-./....................................",
    "./.....\\.-.../...\\.......|.........../....................-.....................\\|..\\..|........|...\\.........",
    ".................|..........--..../..|............|..|.......-.....|.......-................\\.................",
    ".-.-.....|..|/..............................-...............-\\....|..................\\.|.....\\.\\...........|..",
    "......................-\\|-..\\...|.............\\................................../...\\........\\|..............",
    "..........--\\..\\...........-...|........-......................\\./..|.........................................",
    "...........|.|.....|.....................|........./....-.......-.......|................\\....................",
    "....-..............\\.....\\....-........................\\............--.............-.-...............//.......",
    "\\.......\\..........|.\\................................\\......|.........-..|...................../.............",
    "................\\...\\.....|...........-..|................\\...........|.........|............|............../.",
    ".................................-/........../....../..............|................../.../...\\..../..........",
    ".....\\..\\........|......|...................|............\\..\\................./....../............|.........|.",
    "............................................|.........|...................|..\\........-...........\\...-/......",
    ".......//-..........\\........|......//................\\..........-........|......\\.......-.......\\....-.......",
    "-........\\.......\\.....--.........................-.............|..../.........../............/.......-..\\.../",
    ".....\\|..../..-.\\..-....|.-......|...................../..\\...|/............/../.......\\..............|..-.../",
    "........-...........-.........|.....-.............................../.........-................../.\\..-....\\..",
    "..................|......................|.\\......\\../....................../.-............././...........\\...",
    ".|....\\.....\\..........\\.................\\....\\....................\\....................\\/......|............\\",
    "/...\\..\\......-...-...........................-.......\\|....\\............/..............................|.....",
    "............|..\\...../..-..|.........|..-..............-.....-\\.........\\.......-...................\\...../..-",
    "....../................./.........../..............-....|.......................\\........................./...",
    "....\\..-......./............................................/.............|......./..-..\\\\........../..../....",
    ".............................................|................./.......................|......|.............-.",
    "........|......-................\\.................|.|.-............/.......|...............|...........\\......",
    "............................................................|.../..............................\\........|.....",
    "....../....\\.|.|\\/|..............-....|......../.-....................-......|.-.......................\\......",
    "./......../....................../.../..............\\..................\\....\\...-/............\\...............",
    "...-..../...\\.|.....|.......|...........\\......||..|.................................-.....................|..",
    "/..-/........|.......................|..../-./................|................/.......|...-../...............",
    "....../-..................|..|....-..|.......................|-......-..\\...././..../-\\....|......|..|........",
    "...........-................\\..........-..........................................-...........................",
    "..|.................................|........................\\...................|......\\\\....................",
    "..../....../...-........//............-..................-..........................-...\\................\\....",
    "......|...................|...../.............................-.................--.../...............|...|...\\",
    "....../...........\\..|....-.|..|.............../-.................-.............|.....-..........\\/......|....",
    "......|.........../....\\............./.........\\......\\...-.\\.......|...-.....|./.....-........./.............",
    "..\\.|......../........-....|.-...................//|.........-...............|................................",
    "...................................\\............/..............-................/-......-........\\.........-..",
    ".-...-..|....|................|...|.........|.....//...../............\\...............-.|.....................",
    "../...............................\\..............-..........-.................................................",
    "...-..\\....-...|/.............-......|/...-..|..-.........|...\\..|../...|.....|.........................|...-.",
    "....../.......\\.......--.............../....\\......................\\...\\..........................-...........",
    "..-......-.......|....\\|.../...-..-....|......\\.|..............................-...............|...|..........",
    "......-....../............-./.-.............\\.-\\/............../................................./............",
    "..........--/..../..|...\\.....\\.....|.\\...\\.....................................\\|......./............-|..-..\\",
    "..|......................../\\........./.................\\............-......-............/..........|....|.|..",
    ".-|.....................-..-..\\...............-...................|....../...........................\\........",
    ".................-.......\\\\.../........-.............\\.......-......|\\..........|....-..............\\...../...",
    "|.......|...\\..................\\../................|..\\.................../..\\......-..\\.-................/..."
};