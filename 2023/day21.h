const char *data1[] =
{
    "...........",
    ".....###.#.",
    ".###.##..#.",
    "..#.#...#..",
    "....#.#....",
    ".##..S####.",
    ".##..#...#.",
    ".......##..",
    ".##.#.####.",
    ".##..##.##.",
    "..........."
};

const char* data[] =
{
    "...................................................................................................................................",
    ".............#......#.........#....#...#.##.........#.#.#...............#..#................#......#.....#.....###...........#.....",
    ".#............#.#....#......#..#....#..##.........#...#...#.......................#.......#..##.....#......#...........#........#..",
    ".#..##......#.#...##...............#..#....#.#........#...#.........................#.....#........#..#.......#...............#.#..",
    "....#....##......#.#..#.#...#............#.#............#................###...##........#.....#....#..#.#.........................",
    "...#.....#...#....#.#..#..#.#.....#...........#.........#.......#..................###..#.............#.........#......#.....#.....",
    "....#...##..........#.##...#.......#..#..#....#.##....#..........................#.#.#..........#....#.................#...........",
    "......#.....#...........#...#...#....#...........#............#.#.............#.........##.....#...#.##...#..#.................##..",
    ".......#..#...........#........#...#.#........................#..............#........##............#.......#.#...#...........#....",
    "........#.........#..........#.#.#.#.#.#.......##...............#....#.............................#......#..#.............##....#.",
    ".#.##.................#..........##....##.#.#......#..............................##.#......#.......#...........#.#..#....###.#..#.",
    ".#.#......#..........#........##...........#..#............##......#.............#..#...........#.............#..............#.....",
    "....#.............#....#......#....#...........#...............#.............................#.#........#......#.##..#..#.#...###..",
    "....#.............#.................#.............................................#.#....#.#.......#..##..#...........#..#.#.#..#..",
    "...................................#.#...#.#.................#..#..#.....#...........................#....#..#...#.............##..",
    "....##.#...........#.......#...............#..........#.............#.#.............#......##...#........#.........#.....##.##.....",
    "............#..#.......#..................................##......#....................#..##.........#..#.....#...#................",
    ".....###..#.##.#.......#.................................#.....##.........#............#......#......#........#..#.................",
    "..#.#....##.......#.........###......#...#............##..#...........#..##.................##.....#.........###...#.......#.#.....",
    ".................#.#.........##....#................#.............##.#.........................#...............................#...",
    "............................#.#........#............#............................#........#.#..............##.#.#.#.....#..........",
    "...#...#.....#..............#.#..................#.#......##..........#.........#....................##...#.#.....#..#..........#..",
    "..........#...#........#....#.##................##................#.####...#..#.##...........#............#.##......#.#..#..#...#..",
    ".#.....#........#.......#.......#..#...............#........#......#..#..#.###..............#.####....##........#....#.#.......#...",
    "..##....#....................#...............#...............#...................#.................#.#..#........#............#....",
    "...#..#....#........#...##..#.#..#.............................#.......#...#...#.....................#.##....##......#..#..#.....#.",
    ".....#....#..............##..#.............#..#...#........##..#...#...#.........................##.....#....#......#..#...........",
    ".##......#.#...................................#..........#.#.......#...#...##......#...........#..#.....#......#..#...............",
    ".......#..##.........#.............................#.#.............#...##..#.####........#.............#......#.......##.......#...",
    "...#.................#.##..##.#........................#.#..........##.....#......#....#.#.........#...............................",
    "..............#......#.................##..#.........#....###...#........#......#.....#......................##.....#..........#...",
    "......#.......##..#..#.......#..................#.......#..##........#....#..#...#.##...................#..........#......#........",
    "..#..#.#.#.....#...#.........#..............#..#....#......#......#.#.....#......#......#.....................#.#..................",
    "..................#.....................#.#.......#.#..........#.....#.........#....#.....#............##..#...#...#...........#...",
    ".#...#......#.#.#.....................#............#.......#....#.............#..#....#..##.#..........#.......#..#...#....#.......",
    ".#....#..#.#...........##............#.#....#.#..#......###.............#..#.....#..#.##.#..#......................#.........#.....",
    "...#...#.......#.#..#..#............#..#....#..#....#..#.......#.........#......#.#.###...........................#.......###......",
    "...#...........#.......##............#..#.....##..####.......#..........#....#...#.........................#....#..#...............",
    ".........#.......#....#..............#...........#.#................#....#.....##......#......#.............................#..#...",
    "..##....#.#.#....#.................#..#....#...#...#..........#...#...#...#....#.....#........................#......#.............",
    "..#....##.........#.#...........#..#.##.#..........................#......##.....#...#...#.....#..#.............##.................",
    "...#........#...##.#............#..#...#.#.#.#....#.#..#..............#.###.#.#..#......#..#.......#..........#....##.#.....##.....",
    "..#.#..#......#............#.##.....#.....#.....##.....##.......#........#.#......#.....#.#.......#..............#....#...#.#..#...",
    "..................#.........#..#.#.#.#..........#....#......#........#....................#.............#.....................#....",
    ".......................................#..#.....#..#....##............#...........#...#.............#..#......................#....",
    "..#.............#..........#..#........##..#.......................#..#......#...#.#.#......#..#...................#.....#.##......",
    "...#..#................#.#........#.#.................#..#.....#........##.....#...........##......#..#..#......................#..",
    "..###.....#..................#................#.#....................#..............#....#...........................#.#.##.....##.",
    ".........#...#...........#.#...#....#.........#..##.###..............#......#..#....#....###.#.........................#...........",
    "......#..##...........##......#..#..#.#................#..............#...#......#....#.....#...............#...............#...#..",
    ".#......##.........##.......###..#.##.#......#...#.............#..#....#..#.................##...................................#.",
    "...........................................##........#......#....................#.#...................##....#............##.....#.",
    "..#..##..#........#.......###...#.....#............#.#............#..##....#............##..........#.##.......###.................",
    "........#..................#...#.........#..........#.#.....#..............##......................................................",
    "...............#...#......##.................#.......#...#................#..#.............#.....#...........#...#.................",
    "....................#.......#.....#...#.#..#.......#........#......#...#.###........#....#....#.......#...#.#.....#.#..............",
    "...#..............#.#......#.#.#..#.#....#.....#..#........#...............#...##..........................#.......................",
    "...............#........#................#.#.....#....#..#......#......##....##....#.#........##.#.....#.........##.............#..",
    "...#.......#....#......#.....#.#....#...........#.#..........#....#.......#..#............#.#.....#.###............................",
    ".##........#..#...#..##.##..#.#.#.......#......#.#.........................#.....#...............#.................................",
    ".#..............#......#.#.##.#.....##..#..............#....#.#..................##..#....#..#.#...#..#..........#..#..#.........#.",
    "..........#..............#.............#....#...........##.#...#....#...#..#..#......#....#.#.#.....##..............##.............",
    ".............#...#...#............#.....##..#......#.#.#........#.......#................#...........#............#.......#........",
    "..............#...###.#.#.......##........#.#..##......#.#.#..#...........#..............#.......#....#.#.#........................",
    "..........##...###........#........#..#...............##..#....##......##........##...#.......#.....###....#...#..#.#...#..#.......",
    ".................................................................S.................................................................",
    "..............#...##...........................#.....#..#...#......#...................#............#...........##.................",
    "........#..###.........#...#........#..#...#...............#.........#..........#...#............#...#........##..##......#........",
    "............#.....###.....##.....#.#..#..#..#.....#............#.......#.#....#.....#.#...#......##.........#...#....#.#...........",
    "........#....#...##..##...........#.......#.....#........##.....#.......#......#.....................#.....#....#..#...............",
    "...........#..##.#...#...#......#.#.......#............#.......#....#........#....#........##.....#...#....#....#.....#............",
    "....................#........##........#..............#.##.#..##...#..#.....##.............#....#.........#.##..................#..",
    "........................#.........#..................#..#...................#.#.............#...........##..#...#.#...#.........#..",
    "...................##..#........#..............##....#...#.........................#....#....#.##...........##.#...................",
    ".##.................#...#.....#.#..#.#..#.#...#....#..............#..#..#...........##.....................##..#...#...............",
    "...............#.........#....#.###..........#......................##...##.......#..##.###..#.....#...............................",
    ".##..............#.....#.#.#............#......#...............#..#.#.........#.......#..#...#....#.#.........#..#.................",
    "......#.............#..........#................................#..........#...#......#.#...#.....#...........#............##......",
    "..#....#..........#...#.....##......#........#................#.........##............#......#........#..##....#...................",
    "..#...#...................................#..#...........#........#....##.....#....#....#.....###..#..#......#...........#.........",
    "...#.#...#..........##...........#.................##...#.........#......#.....#....#.....#......#..............................#..",
    ".#........#..............##.....#..#.....#...#...##.#........................................#.#....#.......................###....",
    "..#....#.............#.....................#.......#.......#.##.....#............#.....#.....#...#...............................#.",
    ".#...#.#...............#.#.........##.......#.###.....#...............#...#.....#......#..##.....#...#.#.#...............#..##..#..",
    "......##...#................#...........#.#......#.................#....#...#...#..............#.#.......#.........#...#.##........",
    "............#...#.......#.....##.#..#...#...................#.............#...........##.........#..#.....#............##.....#....",
    "....#..###.......#............##...##........#.#....#...................###............#.#...#..#..#.#..............#.........#....",
    "..........#......#........##............##....................#.#..#................#....##.#.#.#....##.#...........##....#........",
    "............##.#...#..............##......#......#.......#...........#.........#..........##.#.................#............#...#..",
    "...#.......#.......................#.......#...#...........................##..#..............#....##..........................#.#.",
    ".#..#.#....#.#....#..............#.........#..........#.......#.#..............#....#.#..##.#....#.....................#..#.#......",
    "..#....#.........#..............#...#...#..#.#..#..##....##..#.........#....................#.......#........##......#...#..#...#..",
    "..##.........#..#.##....................##.#.#......#..#.#........#...........#...#.....#..####....................#...#...........",
    "...#...............#..##...............#......#...##.........#.........#........##.............##..........#.#..#.........#........",
    "....#............................#.#......#....#.#...#......#.......#.........#...........##..................#.#..................",
    "...................#...................................#.....#.....#.#....#...........#.....##...............#...............#.#.#.",
    "..#..#.......#.##.#..#...#................#..#.......#....#..#.......#...#........#...#....#.#..........#......#......###..#.......",
    ".......#.................#..........#.......#..........................#..##...#.##..#..##.#..........#....#.......................",
    ".......#........#.........#...........#.....#..#..............#.......#.#..##......#........#.............##................###....",
    ".#.....#.#....##.....#................#..............#...............#..##..##.#.......#.#.#...........#......#......#..#.#........",
    ".....#..#...............#..#.#..............#..#........................#.....#.#....###...........#......##......#..#.............",
    ".....##..........#.#.#...................#..........#........##.......#....#......#....##.........#.#....#............#..#.........",
    "........#.#........#.#..#.#...#.........................##.#.........#.............##...#.............#..#...##..#..#..............",
    "....#...................#.....#.#.#.......##........#.#.#..#.........#....##......................#...#.#..#......#.........##.....",
    ".....#.....#...........#.....#............................#..#........#............#.................#................##..#.#......",
    ".###..#.......##..#.............#.....................#......##......#..............#..................#..#.........#........#.....",
    "..#.#...#............#........................#............##..#...##....##....#..#......................#..#..........#.#.........",
    "......#.........#..#......................................#.#.#.#.#..#......................#.##...#....#..#.#.....................",
    "....#..........................................#.....##.........................#.................##...........#....##......#...##.",
    "....................#.......#.#....##...#........#.....#...##......#.....#......................#..#.....#.#..#...#...#............",
    "..#................#......#.#...#.......#....................##.#.......#.#...#...............##.#.....#......#.#..###....#..#.#...",
    "........................#........#....#.#.#.......#.#...................#.##....#............#.......#...#....#..#....##....#..#...",
    "..............#...#.#...####.......................#....##.....#...#...#.#.#...#..............#....#.#....#..................##....",
    ".....#.....#..............#...#......#....#.............##................#..................................#..........#..........",
    "......##.........#.......#...#....#...##....#..............#.#.#...........##................#..................#...#...#..........",
    ".#..#.....#.......#.#..#...#......#.....#............................#.....................#..#..#..#....#.......#.........#.#...#.",
    "......#.#..#.#.#..............#....#....#..#..............#............##................#......#......##.#..#....#................",
    "...........#...................##.#..##.#.##...#.........#.##..#.........#............#.#.#.#...#.#.#..#..##.#......##.........##..",
    "........##.......#.#..#........#..##.#..#.#.....#.........#.##.#..................#.##................###..##.....#.....#..........",
    ".....................#...#........#.##.........#...........##..##.#.............#.............#....#.....##....#.#.....#.##........",
    "...#...##...............#.##...........#.#.................#....#...#.#............#.#....##......#.........#..#....#.#.#.......#..",
    "..#..#.#...........#..##....#...#...##..###..#...#................#............................#.........#.......#...#...#.#.#..##.",
    "............#..........#.#.#...##...............#...#.............................###....###..........###......#.......#....#.#....",
    "..#.#.##.........##....#.#...............#...#..#...................#........#.#.........#.#...#......#....#.#....##.....#....#....",
    "...#.#.......#...#...#....#.....#...#..#.....#....#............#...#.......##.#................#...#......#....#.........##........",
    ".................#.#.###........#..#...##............##...........#.............................#.#.#.......#.........#...#....##..",
    "....#..........#.......##.......#..#.....#..#.......................................#..........#..............#.........#.##....#..",
    "......#......#..##..#..##....#........#.#....##........#.#..................#.#.....#.............###.#...#...#........#.....#.....",
    "......#.........##....#...................#...#..#..#..................#............#.....#..#.......#....#......#..#........#.....",
    "..#.............#....#......#...###.......#..#....................................#.........##.........#.#..................#...#..",
    "..................................................................................................................................."
};