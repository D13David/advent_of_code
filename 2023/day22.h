const char* data1[] =
{
    "1,0,1~1,2,1",
    "0,0,2~2,0,2",
    "0,2,3~2,2,3",
    "0,0,4~0,2,4",
    "2,0,5~2,2,5",
    "0,1,6~2,1,6",
    "1,1,8~1,1,9"
};

const char* data[] =
{
    "7,6,107~7,8,107",
    "4,6,229~4,6,231",
    "6,4,110~8,4,110",
    "2,8,255~2,8,258",
    "8,3,318~9,3,318",
    "7,7,41~9,7,41",
    "8,5,285~8,7,285",
    "7,5,23~9,5,23",
    "3,2,67~6,2,67",
    "3,5,299~4,5,299",
    "2,0,257~2,0,258",
    "6,0,6~6,4,6",
    "7,0,31~7,0,34",
    "5,6,133~5,7,133",
    "4,0,241~4,2,241",
    "9,2,255~9,4,255",
    "5,5,29~7,5,29",
    "5,7,334~5,9,334",
    "6,2,169~8,2,169",
    "4,4,299~6,4,299",
    "1,3,26~3,3,26",
    "4,7,204~4,9,204",
    "6,1,121~6,3,121",
    "3,6,146~4,6,146",
    "5,7,97~5,9,97",
    "0,3,68~2,3,68",
    "5,7,85~6,7,85",
    "0,0,29~0,2,29",
    "0,4,223~2,4,223",
    "9,3,217~9,5,217",
    "1,2,256~1,3,256",
    "7,0,315~7,2,315",
    "7,7,93~8,7,93",
    "2,1,88~4,1,88",
    "6,8,232~6,9,232",
    "1,5,270~3,5,270",
    "9,1,19~9,1,21",
    "0,1,323~2,1,323",
    "2,0,331~4,0,331",
    "4,6,275~7,6,275",
    "0,1,278~2,1,278",
    "1,4,188~1,7,188",
    "5,1,184~5,3,184",
    "1,2,80~3,2,80",
    "6,1,280~6,5,280",
    "0,5,316~2,5,316",
    "1,5,156~1,7,156",
    "8,7,292~8,9,292",
    "9,1,178~9,3,178",
    "0,3,203~2,3,203",
    "1,1,36~1,4,36",
    "6,1,268~6,4,268",
    "3,4,269~5,4,269",
    "2,8,271~5,8,271",
    "9,3,118~9,6,118",
    "9,1,65~9,3,65",
    "0,9,193~1,9,193",
    "6,9,97~6,9,98",
    "5,2,188~5,5,188",
    "2,5,86~2,7,86",
    "1,5,317~1,7,317",
    "0,6,70~2,6,70",
    "7,3,336~7,3,336",
    "7,1,145~7,4,145",
    "3,1,83~6,1,83",
    "2,2,332~2,4,332",
    "3,5,32~6,5,32",
    "2,0,112~2,3,112",
    "5,2,122~6,2,122",
    "7,4,117~8,4,117",
    "4,4,245~6,4,245",
    "3,8,72~6,8,72",
    "1,3,341~1,3,343",
    "0,6,230~2,6,230",
    "9,1,105~9,1,109",
    "2,8,140~4,8,140",
    "5,4,181~7,4,181",
    "5,8,52~7,8,52",
    "2,2,199~2,4,199",
    "0,7,101~2,7,101",
    "9,0,131~9,1,131",
    "2,2,122~2,3,122",
    "4,9,299~7,9,299",
    "3,2,99~3,5,99",
    "5,1,90~7,1,90",
    "0,0,195~0,1,195",
    "4,9,211~7,9,211",
    "6,3,124~8,3,124",
    "3,2,246~5,2,246",
    "1,3,282~1,4,282",
    "9,8,98~9,8,100",
    "3,6,344~3,6,344",
    "4,5,61~4,6,61",
    "5,1,217~7,1,217",
    "6,1,104~8,1,104",
    "2,6,83~2,7,83",
    "9,2,64~9,5,64",
    "0,2,78~2,2,78",
    "2,8,151~2,9,151",
    "8,3,98~8,5,98",
    "3,6,244~3,9,244",
    "4,0,210~5,0,210",
    "3,9,19~3,9,19",
    "3,7,59~5,7,59",
    "9,9,76~9,9,79",
    "0,8,141~2,8,141",
    "1,1,34~3,1,34",
    "7,1,295~7,3,295",
    "3,9,331~5,9,331",
    "5,4,247~8,4,247",
    "0,6,241~2,6,241",
    "8,5,263~8,6,263",
    "4,0,255~6,0,255",
    "4,0,150~6,0,150",
    "0,7,281~2,7,281",
    "0,2,2~0,5,2",
    "5,0,26~8,0,26",
    "6,1,220~7,1,220",
    "0,6,141~0,7,141",
    "7,6,184~7,8,184",
    "6,0,129~8,0,129",
    "7,9,159~7,9,161",
    "5,6,143~7,6,143",
    "9,0,253~9,3,253",
    "6,3,256~6,5,256",
    "0,4,196~2,4,196",
    "3,6,92~3,6,94",
    "3,0,237~3,3,237",
    "7,8,280~9,8,280",
    "5,3,170~5,3,173",
    "4,6,266~6,6,266",
    "9,7,119~9,9,119",
    "5,9,303~7,9,303",
    "3,1,26~6,1,26",
    "5,6,5~5,8,5",
    "3,4,265~6,4,265",
    "7,8,7~7,9,7",
    "8,6,75~8,8,75",
    "9,4,199~9,5,199",
    "2,8,69~4,8,69",
    "6,1,198~6,1,200",
    "1,1,160~1,4,160",
    "5,5,18~8,5,18",
    "3,2,94~3,3,94",
    "1,4,245~1,5,245",
    "0,6,199~0,6,200",
    "5,4,52~5,7,52",
    "3,5,295~3,7,295",
    "8,5,68~8,6,68",
    "3,1,306~5,1,306",
    "0,3,94~2,3,94",
    "7,7,65~7,7,67",
    "1,7,215~1,8,215",
    "0,3,273~2,3,273",
    "1,2,191~3,2,191",
    "6,4,80~6,6,80",
    "7,7,149~9,7,149",
    "5,9,259~5,9,259",
    "4,3,213~4,5,213",
    "1,3,322~2,3,322",
    "8,2,62~8,4,62",
    "3,8,230~5,8,230",
    "8,2,84~9,2,84",
    "2,4,346~2,6,346",
    "4,7,140~7,7,140",
    "5,3,66~8,3,66",
    "7,3,28~7,6,28",
    "3,0,242~4,0,242",
    "2,4,187~2,6,187",
    "4,2,90~4,3,90",
    "3,5,165~5,5,165",
    "1,2,9~2,2,9",
    "6,0,17~9,0,17",
    "0,0,200~0,0,201",
    "7,3,72~7,4,72",
    "4,4,227~5,4,227",
    "4,7,215~6,7,215",
    "7,4,234~7,7,234",
    "7,1,8~7,2,8",
    "0,5,217~2,5,217",
    "0,6,142~2,6,142",
    "1,3,297~4,3,297",
    "1,4,9~3,4,9",
    "8,4,26~8,7,26",
    "6,8,213~6,9,213",
    "8,5,322~8,7,322",
    "2,4,156~2,6,156",
    "2,0,45~2,3,45",
    "1,3,275~4,3,275",
    "4,1,6~4,1,7",
    "7,4,291~7,6,291",
    "1,0,158~1,3,158",
    "7,0,294~7,3,294",
    "7,6,261~9,6,261",
    "2,0,114~2,3,114",
    "7,8,279~7,8,279",
    "0,6,157~3,6,157",
    "4,5,88~4,7,88",
    "0,7,271~3,7,271",
    "2,5,90~2,7,90",
    "0,8,100~2,8,100",
    "3,2,278~3,5,278",
    "3,7,82~5,7,82",
    "7,9,255~8,9,255",
    "0,8,101~1,8,101",
    "7,6,263~7,7,263",
    "5,6,23~5,8,23",
    "3,7,77~5,7,77",
    "4,8,243~6,8,243",
    "8,2,186~8,2,188",
    "3,3,102~3,3,105",
    "0,6,323~3,6,323",
    "2,6,67~4,6,67",
    "0,2,165~0,4,165",
    "7,0,103~7,3,103",
    "6,4,58~9,4,58",
    "8,1,15~9,1,15",
    "3,2,222~3,3,222",
    "6,0,245~8,0,245",
    "5,2,143~5,3,143",
    "2,3,319~2,5,319",
    "0,5,39~3,5,39",
    "8,8,271~9,8,271",
    "7,3,236~9,3,236",
    "1,0,201~3,0,201",
    "0,9,3~1,9,3",
    "4,4,289~4,6,289",
    "0,1,160~0,3,160",
    "8,5,39~8,7,39",
    "1,1,66~1,4,66",
    "2,7,282~2,7,284",
    "9,5,72~9,8,72",
    "5,1,193~5,3,193",
    "6,0,190~9,0,190",
    "3,5,245~3,7,245",
    "2,4,249~2,5,249",
    "8,9,195~8,9,196",
    "2,8,172~3,8,172",
    "6,5,270~9,5,270",
    "0,0,167~0,0,169",
    "6,1,336~6,2,336",
    "6,1,66~6,2,66",
    "2,3,295~2,5,295",
    "8,0,189~8,2,189",
    "5,3,239~5,3,241",
    "0,0,170~0,1,170",
    "5,5,19~6,5,19",
    "2,2,194~2,4,194",
    "3,2,122~3,5,122",
    "8,7,288~8,8,288",
    "4,1,78~5,1,78",
    "7,2,249~7,5,249",
    "6,3,41~6,5,41",
    "0,4,242~3,4,242",
    "0,2,189~0,2,189",
    "5,0,140~5,2,140",
    "7,2,129~7,3,129",
    "2,2,17~3,2,17",
    "4,3,266~6,3,266",
    "6,7,224~7,7,224",
    "3,1,206~5,1,206",
    "1,2,178~1,5,178",
    "0,7,144~0,8,144",
    "0,9,194~1,9,194",
    "3,7,297~3,9,297",
    "6,9,14~8,9,14",
    "2,5,214~2,6,214",
    "5,2,55~5,4,55",
    "0,4,1~0,7,1",
    "8,1,201~8,4,201",
    "3,0,75~5,0,75",
    "0,1,132~4,1,132",
    "3,2,304~5,2,304",
    "0,3,121~3,3,121",
    "5,2,313~9,2,313",
    "1,3,339~1,6,339",
    "7,7,260~8,7,260",
    "4,1,27~6,1,27",
    "3,4,217~4,4,217",
    "8,0,277~8,3,277",
    "4,4,324~7,4,324",
    "7,7,201~7,9,201",
    "0,3,299~2,3,299",
    "6,2,195~6,5,195",
    "2,5,41~4,5,41",
    "0,4,197~0,6,197",
    "3,3,42~3,5,42",
    "2,3,305~4,3,305",
    "1,1,244~3,1,244",
    "7,0,188~8,0,188",
    "6,6,221~8,6,221",
    "6,6,95~9,6,95",
    "8,2,243~8,2,245",
    "0,2,148~0,5,148",
    "7,0,127~7,4,127",
    "9,1,17~9,1,17",
    "8,5,218~8,7,218",
    "8,5,141~8,5,144",
    "2,0,320~2,3,320",
    "4,8,331~7,8,331",
    "7,5,175~7,6,175",
    "9,7,270~9,7,273",
    "6,9,252~9,9,252",
    "4,7,191~6,7,191",
    "0,9,18~3,9,18",
    "1,5,19~4,5,19",
    "2,1,150~6,1,150",
    "3,2,119~3,6,119",
    "1,9,72~3,9,72",
    "6,0,243~6,1,243",
    "0,7,74~0,7,75",
    "2,7,63~5,7,63",
    "4,9,328~7,9,328",
    "9,7,296~9,7,298",
    "6,2,81~8,2,81",
    "0,6,286~2,6,286",
    "7,5,266~7,6,266",
    "2,2,181~5,2,181",
    "2,9,214~4,9,214",
    "3,0,22~3,2,22",
    "7,4,242~9,4,242",
    "4,3,223~6,3,223",
    "5,3,228~5,3,228",
    "7,6,173~7,6,173",
    "7,1,275~8,1,275",
    "5,0,261~5,0,265",
    "5,4,73~5,5,73",
    "7,3,88~7,5,88",
    "3,1,177~7,1,177",
    "8,4,273~8,7,273",
    "6,1,136~6,1,138",
    "4,1,2~6,1,2",
    "2,3,293~2,5,293",
    "6,8,150~7,8,150",
    "7,6,238~7,7,238",
    "2,7,267~5,7,267",
    "8,3,189~8,7,189",
    "4,8,219~6,8,219",
    "7,8,168~7,8,170",
    "4,7,22~4,9,22",
    "5,0,29~7,0,29",
    "6,8,294~7,8,294",
    "3,9,52~5,9,52",
    "0,1,100~0,2,100",
    "6,9,248~8,9,248",
    "0,0,328~1,0,328",
    "0,9,219~1,9,219",
    "4,4,39~6,4,39",
    "3,0,93~4,0,93",
    "3,2,266~3,4,266",
    "9,4,24~9,7,24",
    "4,6,240~4,8,240",
    "7,4,171~9,4,171",
    "5,4,280~5,6,280",
    "4,9,56~7,9,56",
    "3,2,142~5,2,142",
    "2,4,37~2,4,38",
    "4,4,169~7,4,169",
    "7,0,261~9,0,261",
    "0,0,8~2,0,8",
    "1,1,14~1,4,14",
    "7,6,287~9,6,287",
    "1,7,318~1,8,318",
    "6,4,184~8,4,184",
    "1,4,236~1,6,236",
    "5,7,323~5,9,323",
    "4,6,138~4,9,138",
    "8,0,185~8,2,185",
    "8,7,192~8,9,192",
    "4,3,262~6,3,262",
    "3,6,95~3,9,95",
    "3,5,273~5,5,273",
    "2,7,301~5,7,301",
    "6,3,186~6,4,186",
    "0,5,155~0,5,157",
    "0,3,154~0,5,154",
    "1,3,152~1,5,152",
    "4,1,110~6,1,110",
    "0,1,168~2,1,168",
    "0,6,140~2,6,140",
    "7,1,197~7,4,197",
    "7,1,338~8,1,338",
    "8,4,90~8,6,90",
    "1,7,172~3,7,172",
    "8,7,139~8,9,139",
    "9,3,272~9,4,272",
    "4,9,251~6,9,251",
    "4,3,246~4,5,246",
    "5,4,115~5,6,115",
    "0,5,231~0,6,231",
    "6,3,125~6,3,126",
    "5,0,327~5,3,327",
    "3,7,254~4,7,254",
    "4,2,20~6,2,20",
    "7,6,176~7,8,176",
    "4,0,249~4,2,249",
    "1,2,204~2,2,204",
    "7,7,75~7,7,75",
    "6,6,280~6,8,280",
    "1,0,11~4,0,11",
    "0,2,97~0,3,97",
    "2,9,319~4,9,319",
    "6,1,15~6,2,15",
    "1,3,49~3,3,49",
    "1,2,176~3,2,176",
    "6,9,94~8,9,94",
    "1,0,45~1,1,45",
    "2,7,79~2,9,79",
    "1,5,190~1,6,190",
    "1,8,176~1,8,178",
    "7,3,84~7,3,85",
    "4,2,75~6,2,75",
    "9,2,155~9,5,155",
    "6,2,163~6,2,166",
    "0,6,103~0,8,103",
    "1,0,154~1,2,154",
    "3,5,102~3,5,102",
    "0,6,198~0,7,198",
    "0,7,128~3,7,128",
    "0,7,233~0,8,233",
    "0,1,109~3,1,109",
    "3,9,300~3,9,302",
    "3,1,188~4,1,188",
    "6,2,288~6,3,288",
    "8,4,291~9,4,291",
    "5,5,331~6,5,331",
    "5,3,95~5,4,95",
    "7,8,165~7,8,167",
    "7,7,282~7,8,282",
    "5,0,72~5,3,72",
    "3,5,193~3,6,193",
    "3,3,220~5,3,220",
    "3,6,155~6,6,155",
    "3,6,170~3,8,170",
    "3,8,280~3,9,280",
    "5,7,130~5,9,130",
    "5,0,9~6,0,9",
    "7,5,158~7,7,158",
    "4,4,226~6,4,226",
    "6,6,136~7,6,136",
    "7,2,73~7,3,73",
    "3,2,218~3,4,218",
    "7,2,207~7,3,207",
    "1,5,290~4,5,290",
    "5,5,142~5,5,144",
    "1,0,120~3,0,120",
    "5,5,47~5,7,47",
    "7,9,92~9,9,92",
    "5,5,134~5,8,134",
    "6,5,260~6,7,260",
    "0,9,20~2,9,20",
    "1,6,148~2,6,148",
    "7,8,118~9,8,118",
    "2,6,349~4,6,349",
    "4,5,217~6,5,217",
    "2,6,188~2,9,188",
    "5,3,82~5,3,82",
    "5,8,329~5,9,329",
    "8,1,310~8,2,310",
    "2,0,40~2,3,40",
    "9,0,319~9,2,319",
    "6,1,105~6,3,105",
    "7,8,6~9,8,6",
    "6,4,120~9,4,120",
    "6,7,117~8,7,117",
    "2,9,89~6,9,89",
    "5,2,245~7,2,245",
    "0,1,38~2,1,38",
    "4,4,314~6,4,314",
    "9,4,99~9,7,99",
    "5,3,157~5,3,159",
    "1,9,69~3,9,69",
    "7,3,176~9,3,176",
    "5,0,71~5,3,71",
    "1,1,162~1,1,165",
    "4,6,213~4,7,213",
    "2,0,78~3,0,78",
    "4,6,315~6,6,315",
    "2,1,279~2,4,279",
    "4,0,303~4,3,303",
    "6,8,155~8,8,155",
    "4,7,65~6,7,65",
    "2,4,28~5,4,28",
    "4,3,214~4,5,214",
    "2,6,264~2,6,265",
    "4,4,328~5,4,328",
    "7,3,260~7,4,260",
    "7,6,280~8,6,280",
    "9,0,62~9,2,62",
    "4,3,187~4,4,187",
    "3,3,336~5,3,336",
    "4,2,157~4,5,157",
    "6,4,61~6,6,61",
    "3,3,91~3,5,91",
    "1,8,218~2,8,218",
    "1,2,12~2,2,12",
    "9,8,283~9,9,283",
    "6,7,266~9,7,266",
    "9,6,238~9,7,238",
    "0,6,220~3,6,220",
    "3,7,55~5,7,55",
    "8,4,294~8,5,294",
    "5,5,70~5,5,72",
    "0,4,275~0,6,275",
    "0,0,160~3,0,160",
    "2,5,268~2,8,268",
    "1,2,60~1,2,62",
    "3,3,158~3,7,158",
    "2,3,91~2,4,91",
    "6,2,68~6,3,68",
    "6,7,37~9,7,37",
    "7,5,207~8,5,207",
    "7,0,128~9,0,128",
    "5,4,140~5,6,140",
    "1,0,116~3,0,116",
    "1,3,3~1,4,3",
    "6,0,297~9,0,297",
    "4,5,330~6,5,330",
    "9,4,10~9,6,10",
    "8,3,193~8,4,193",
    "6,2,338~8,2,338",
    "4,6,211~5,6,211",
    "0,2,350~0,6,350",
    "4,3,253~4,6,253",
    "8,3,20~8,6,20",
    "3,8,308~4,8,308",
    "1,1,20~3,1,20",
    "1,2,198~1,4,198",
    "7,8,301~7,9,301",
    "5,7,147~7,7,147",
    "6,6,92~9,6,92",
    "4,2,172~4,4,172",
    "5,2,9~8,2,9",
    "9,4,293~9,6,293",
    "2,0,166~6,0,166",
    "3,1,229~3,3,229",
    "4,0,203~5,0,203",
    "6,0,64~9,0,64",
    "5,0,200~5,3,200",
    "8,2,164~9,2,164",
    "6,0,67~9,0,67",
    "7,7,297~7,9,297",
    "7,2,240~9,2,240",
    "0,5,106~0,7,106",
    "3,2,232~3,2,235",
    "8,1,119~8,3,119",
    "7,8,302~9,8,302",
    "7,9,306~9,9,306",
    "4,6,218~4,8,218",
    "0,7,232~3,7,232",
    "6,8,299~6,8,301",
    "0,9,323~1,9,323",
    "3,2,18~3,3,18",
    "1,5,230~1,5,233",
    "7,1,179~8,1,179",
    "5,1,133~7,1,133",
    "3,9,160~6,9,160",
    "6,1,194~6,3,194",
    "6,5,140~8,5,140",
    "9,4,36~9,7,36",
    "1,2,95~1,3,95",
    "4,2,78~6,2,78",
    "2,2,158~2,4,158",
    "4,4,292~5,4,292",
    "6,6,301~6,6,303",
    "0,3,250~3,3,250",
    "0,4,277~0,5,277",
    "8,2,224~8,5,224",
    "3,3,199~3,5,199",
    "1,4,247~3,4,247",
    "6,6,295~6,8,295",
    "3,5,142~3,7,142",
    "0,5,192~2,5,192",
    "2,9,298~3,9,298",
    "5,1,143~6,1,143",
    "2,7,100~4,7,100",
    "7,2,161~9,2,161",
    "1,5,157~1,5,161",
    "4,6,212~5,6,212",
    "2,4,280~2,4,282",
    "8,5,237~8,8,237",
    "8,0,299~8,2,299",
    "8,6,152~8,9,152",
    "2,2,174~5,2,174",
    "6,7,235~9,7,235",
    "7,6,196~9,6,196",
    "9,2,102~9,4,102",
    "4,4,183~6,4,183",
    "2,5,223~2,6,223",
    "0,3,248~0,3,249",
    "4,7,89~6,7,89",
    "2,2,202~2,2,202",
    "0,9,83~4,9,83",
    "0,4,348~1,4,348",
    "1,2,127~3,2,127",
    "3,6,196~4,6,196",
    "1,8,103~2,8,103",
    "6,2,233~6,4,233",
    "0,0,3~3,0,3",
    "4,3,167~7,3,167",
    "9,3,295~9,4,295",
    "3,7,66~3,7,68",
    "0,2,241~0,2,243",
    "1,7,175~1,7,177",
    "5,3,80~5,5,80",
    "9,4,33~9,6,33",
    "0,1,166~2,1,166",
    "3,1,25~3,3,25",
    "5,3,235~7,3,235",
    "8,4,241~8,5,241",
    "2,3,29~2,5,29",
    "5,2,118~8,2,118",
    "0,6,5~0,6,7",
    "0,1,157~2,1,157",
    "1,9,93~4,9,93",
    "1,2,269~1,4,269",
    "3,4,281~3,5,281",
    "4,4,71~5,4,71",
    "0,2,85~0,5,85",
    "0,0,325~3,0,325",
    "4,5,279~6,5,279",
    "7,6,1~7,6,3",
    "7,3,279~7,6,279",
    "0,1,209~3,1,209",
    "5,0,197~5,2,197",
    "6,7,227~6,9,227",
    "6,0,288~7,0,288",
    "3,7,270~4,7,270",
    "7,1,107~7,3,107",
    "8,0,251~8,2,251",
    "5,7,316~7,7,316",
    "0,7,71~3,7,71",
    "6,4,93~8,4,93",
    "2,1,6~2,1,9",
    "8,4,115~8,6,115",
    "2,8,305~5,8,305",
    "5,2,149~7,2,149",
    "3,9,151~5,9,151",
    "9,4,267~9,7,267",
    "9,6,32~9,8,32",
    "6,2,309~8,2,309",
    "7,4,285~7,7,285",
    "9,1,111~9,2,111",
    "5,7,8~8,7,8",
    "5,6,80~5,8,80",
    "8,4,244~8,5,244",
    "3,2,4~3,4,4",
    "3,6,26~3,6,29",
    "4,5,248~4,5,249",
    "2,7,228~2,8,228",
    "6,1,141~6,2,141",
    "7,8,187~7,8,188",
    "6,8,225~6,9,225",
    "9,5,121~9,5,122",
    "6,4,37~6,6,37",
    "4,6,152~6,6,152",
    "6,8,147~8,8,147",
    "8,5,258~8,7,258",
    "3,4,152~5,4,152",
    "5,8,252~7,8,252",
    "5,6,60~5,6,60",
    "2,6,139~5,6,139",
    "1,2,150~3,2,150",
    "6,9,156~7,9,156",
    "4,3,15~5,3,15",
    "7,0,12~7,3,12",
    "4,5,20~4,7,20",
    "5,3,337~7,3,337",
    "1,8,90~3,8,90",
    "4,5,332~4,5,334",
    "1,7,42~3,7,42",
    "2,7,220~2,7,223",
    "5,4,42~5,5,42",
    "7,5,247~7,6,247",
    "4,1,198~4,1,200",
    "7,0,132~7,2,132",
    "6,6,205~6,8,205",
    "5,2,92~5,4,92",
    "4,5,160~4,8,160",
    "0,0,60~0,2,60",
    "0,7,5~0,8,5",
    "7,4,195~7,8,195",
    "7,9,183~8,9,183",
    "8,3,99~8,3,100",
    "2,6,233~2,7,233",
    "3,1,239~3,3,239",
    "8,4,65~8,6,65",
    "2,7,62~4,7,62",
    "3,3,225~5,3,225",
    "1,4,336~2,4,336",
    "2,1,308~5,1,308",
    "2,3,159~3,3,159",
    "3,7,154~6,7,154",
    "2,6,7~2,8,7",
    "6,5,214~9,5,214",
    "5,1,211~5,1,214",
    "0,6,277~1,6,277",
    "7,7,214~7,9,214",
    "0,4,73~0,6,73",
    "5,0,239~5,2,239",
    "6,6,175~6,8,175",
    "4,3,12~4,5,12",
    "5,0,57~5,2,57",
    "1,2,251~1,2,252",
    "9,4,198~9,6,198",
    "4,4,182~6,4,182",
    "2,1,342~2,4,342",
    "0,1,282~0,4,282",
    "1,8,276~2,8,276",
    "2,8,148~4,8,148",
    "3,5,187~5,5,187",
    "0,0,198~2,0,198",
    "2,8,242~2,9,242",
    "4,4,228~6,4,228",
    "3,1,23~3,2,23",
    "8,6,220~8,7,220",
    "1,6,57~4,6,57",
    "1,2,193~1,4,193",
    "7,6,30~9,6,30",
    "0,1,85~2,1,85",
    "1,4,280~1,7,280",
    "9,8,253~9,9,253",
    "8,4,51~8,7,51",
    "1,6,238~1,8,238",
    "6,3,225~6,5,225",
    "9,4,292~9,6,292",
    "2,4,222~2,6,222",
    "6,7,204~9,7,204",
    "1,4,104~1,5,104",
    "7,5,44~7,8,44",
    "7,2,115~7,4,115",
    "0,4,150~2,4,150",
    "8,0,140~8,1,140",
    "8,5,136~8,7,136",
    "8,5,48~8,7,48",
    "3,1,148~3,3,148",
    "2,7,9~4,7,9",
    "2,3,226~3,3,226",
    "7,6,325~7,8,325",
    "2,1,47~4,1,47",
    "2,5,350~2,9,350",
    "7,8,115~9,8,115",
    "2,5,325~2,7,325",
    "2,1,65~2,3,65",
    "5,4,112~7,4,112",
    "3,0,147~4,0,147",
    "7,6,191~8,6,191",
    "4,2,40~5,2,40",
    "0,2,317~0,5,317",
    "6,2,290~6,2,292",
    "7,6,292~7,6,295",
    "6,8,222~8,8,222",
    "2,2,329~5,2,329",
    "2,1,190~3,1,190",
    "4,6,174~6,6,174",
    "3,6,290~3,8,290",
    "1,5,147~3,5,147",
    "3,6,324~4,6,324",
    "7,1,333~7,5,333",
    "5,0,209~8,0,209",
    "6,4,104~6,7,104",
    "5,4,11~6,4,11",
    "4,9,325~6,9,325",
    "4,2,238~7,2,238",
    "7,4,133~8,4,133",
    "4,0,209~4,2,209",
    "3,6,228~3,7,228",
    "0,1,112~1,1,112",
    "1,6,287~4,6,287",
    "2,7,207~4,7,207",
    "8,3,319~8,5,319",
    "7,5,293~7,5,295",
    "6,4,142~8,4,142",
    "5,1,190~5,3,190",
    "7,3,259~9,3,259",
    "3,7,40~3,9,40",
    "6,9,46~8,9,46",
    "6,0,282~6,1,282",
    "6,5,62~6,5,64",
    "7,6,202~9,6,202",
    "1,6,163~1,7,163",
    "0,5,315~2,5,315",
    "7,0,304~7,2,304",
    "6,9,71~8,9,71",
    "3,5,150~3,5,150",
    "2,5,313~4,5,313",
    "2,4,339~2,6,339",
    "1,7,226~5,7,226",
    "1,4,283~1,8,283",
    "3,6,236~3,7,236",
    "0,0,115~0,1,115",
    "3,8,292~6,8,292",
    "7,8,104~8,8,104",
    "6,7,142~6,9,142",
    "3,5,167~3,8,167",
    "1,3,188~4,3,188",
    "2,2,258~2,4,258",
    "5,1,134~7,1,134",
    "3,7,3~3,9,3",
    "7,2,158~9,2,158",
    "8,7,69~8,9,69",
    "4,9,157~6,9,157",
    "3,6,53~6,6,53",
    "4,1,195~6,1,195",
    "0,8,213~2,8,213",
    "7,7,289~7,7,292",
    "3,1,241~3,2,241",
    "2,1,160~2,1,163",
    "9,0,256~9,0,256",
    "3,5,189~3,8,189",
    "7,6,323~7,8,323",
    "3,1,155~5,1,155",
    "3,0,87~3,2,87",
    "4,2,91~4,2,92",
    "7,4,215~9,4,215",
    "3,4,171~3,6,171",
    "5,9,258~7,9,258",
    "2,8,232~4,8,232",
    "2,6,158~2,7,158",
    "1,0,100~2,0,100",
    "3,1,154~3,4,154",
    "0,5,181~1,5,181",
    "7,0,124~9,0,124",
    "7,4,254~9,4,254",
    "1,0,189~4,0,189",
    "7,2,296~7,3,296",
    "3,1,84~3,2,84",
    "8,0,294~9,0,294",
    "0,3,181~2,3,181",
    "4,1,251~5,1,251",
    "6,5,16~7,5,16",
    "3,6,300~3,8,300",
    "0,3,245~0,4,245",
    "9,6,208~9,8,208",
    "8,6,89~8,7,89",
    "8,0,321~8,0,322",
    "9,7,155~9,8,155",
    "9,0,166~9,3,166",
    "3,4,16~3,6,16",
    "0,9,304~3,9,304",
    "5,6,304~5,8,304",
    "2,6,98~2,8,98",
    "3,0,76~3,2,76",
    "4,8,135~5,8,135",
    "4,7,286~6,7,286",
    "7,3,273~7,3,273",
    "6,7,14~9,7,14",
    "6,0,291~9,0,291",
    "3,1,254~3,3,254",
    "7,0,137~8,0,137",
    "3,8,212~5,8,212",
    "0,3,301~0,4,301",
    "6,0,318~8,0,318",
    "2,7,11~2,9,11",
    "1,5,288~1,8,288",
    "1,1,129~1,3,129",
    "2,9,281~3,9,281",
    "9,7,232~9,8,232",
    "6,3,231~6,5,231",
    "5,7,41~5,8,41",
    "7,8,101~9,8,101",
    "9,5,63~9,7,63",
    "8,5,113~8,8,113",
    "2,8,202~3,8,202",
    "0,0,280~0,3,280",
    "2,7,293~4,7,293",
    "4,6,142~8,6,142",
    "1,0,322~3,0,322",
    "6,2,222~6,5,222",
    "1,7,306~4,7,306",
    "5,6,236~7,6,236",
    "5,6,162~8,6,162",
    "5,8,3~8,8,3",
    "4,8,132~5,8,132",
    "5,5,184~5,8,184",
    "0,1,23~2,1,23",
    "0,9,154~3,9,154",
    "7,8,68~9,8,68",
    "0,6,263~3,6,263",
    "3,8,143~5,8,143",
    "1,6,89~3,6,89",
    "3,0,146~3,0,146",
    "1,5,266~1,7,266",
    "3,4,1~3,5,1",
    "1,0,88~1,2,88",
    "4,0,138~5,0,138",
    "6,3,8~6,6,8",
    "4,0,256~6,0,256",
    "8,1,172~8,3,172",
    "6,8,216~8,8,216",
    "8,0,2~8,3,2",
    "7,7,163~7,8,163",
    "3,1,118~3,4,118",
    "5,2,204~7,2,204",
    "9,1,103~9,3,103",
    "7,2,69~7,5,69",
    "3,5,280~3,7,280",
    "7,3,89~7,3,91",
    "9,4,243~9,4,243",
    "3,0,304~6,0,304",
    "8,4,74~8,6,74",
    "8,5,82~8,5,84",
    "8,0,182~8,2,182",
    "4,1,117~4,4,117",
    "1,6,15~1,9,15",
    "2,9,192~5,9,192",
    "6,4,96~8,4,96",
    "1,4,34~3,4,34",
    "2,5,260~2,7,260",
    "3,7,101~3,8,101",
    "0,6,59~1,6,59",
    "2,7,314~5,7,314",
    "7,6,159~8,6,159",
    "7,1,128~7,4,128",
    "5,4,26~5,6,26",
    "1,9,163~2,9,163",
    "4,1,8~4,1,10",
    "1,1,29~1,4,29",
    "9,6,269~9,6,269",
    "8,2,129~8,3,129",
    "7,1,29~7,2,29",
    "0,4,128~0,5,128",
    "4,1,4~7,1,4",
    "7,7,219~7,9,219",
    "3,7,224~5,7,224",
    "4,5,307~4,7,307",
    "0,7,176~0,8,176",
    "6,7,6~6,9,6",
    "4,3,154~6,3,154",
    "5,6,58~7,6,58",
    "9,2,123~9,4,123",
    "8,7,52~8,8,52",
    "0,1,239~0,1,241",
    "1,7,217~1,7,218",
    "4,6,198~5,6,198",
    "5,3,69~5,5,69",
    "9,0,320~9,0,322",
    "3,8,86~5,8,86",
    "1,7,286~3,7,286",
    "0,7,216~0,9,216",
    "1,4,318~1,5,318",
    "8,5,240~8,8,240",
    "4,4,209~4,7,209",
    "0,5,203~2,5,203",
    "6,6,330~6,9,330",
    "4,3,72~4,4,72",
    "3,7,235~3,8,235",
    "4,3,282~4,6,282",
    "5,7,222~8,7,222",
    "1,1,301~1,3,301",
    "4,1,87~6,1,87",
    "8,7,11~8,9,11",
    "7,8,178~9,8,178",
    "5,7,318~7,7,318",
    "7,6,245~7,9,245",
    "1,7,160~1,9,160",
    "5,8,209~5,9,209",
    "7,2,101~7,5,101",
    "5,0,241~7,0,241",
    "4,2,3~5,2,3",
    "1,6,321~3,6,321",
    "2,4,237~5,4,237",
    "8,6,172~8,8,172",
    "8,1,315~8,3,315",
    "8,3,127~8,6,127",
    "4,1,122~6,1,122",
    "7,7,64~9,7,64",
    "4,8,43~6,8,43",
    "3,5,327~3,8,327",
    "7,0,109~7,4,109",
    "5,4,127~5,7,127",
    "1,8,14~4,8,14",
    "6,6,170~9,6,170",
    "7,4,205~7,6,205",
    "4,6,228~4,7,228",
    "5,4,138~6,4,138",
    "2,7,257~4,7,257",
    "0,2,151~1,2,151",
    "6,6,133~8,6,133",
    "0,0,43~3,0,43",
    "0,5,48~0,7,48",
    "3,7,304~3,7,304",
    "8,5,324~8,8,324",
    "5,8,246~8,8,246",
    "4,1,75~7,1,75",
    "3,0,185~3,2,185",
    "9,1,14~9,2,14",
    "9,6,67~9,8,67",
    "2,3,90~3,3,90",
    "7,0,6~7,1,6",
    "8,3,68~8,4,68",
    "8,4,60~8,6,60",
    "5,1,303~7,1,303",
    "2,1,334~2,4,334",
    "4,6,144~4,7,144",
    "7,0,247~7,3,247",
    "3,4,312~3,7,312",
    "5,5,74~5,6,74",
    "0,1,95~0,4,95",
    "0,4,166~0,5,166",
    "1,7,329~3,7,329",
    "4,6,254~7,6,254",
    "2,2,6~2,5,6",
    "4,7,316~4,9,316",
    "6,5,298~6,7,298",
    "6,7,189~7,7,189",
    "3,3,195~3,3,198",
    "6,5,79~8,5,79",
    "8,0,126~8,2,126",
    "1,5,309~1,8,309",
    "9,6,97~9,8,97",
    "5,5,269~5,7,269",
    "0,0,82~0,0,84",
    "5,2,39~5,3,39",
    "6,3,192~9,3,192",
    "4,3,106~4,6,106",
    "6,1,175~8,1,175",
    "4,4,234~6,4,234",
    "7,5,168~7,7,168",
    "6,7,257~9,7,257",
    "4,5,327~6,5,327",
    "2,2,281~4,2,281",
    "9,2,39~9,5,39",
    "6,2,282~6,3,282",
    "3,7,242~4,7,242",
    "3,7,38~6,7,38",
    "2,2,95~2,3,95",
    "2,6,239~2,9,239",
    "8,8,224~8,8,227",
    "6,4,171~6,5,171",
    "1,5,229~1,7,229",
    "6,1,249~9,1,249",
    "9,1,252~9,4,252",
    "3,0,143~6,0,143",
    "5,4,74~5,4,76",
    "2,5,310~5,5,310",
    "4,0,78~6,0,78",
    "2,4,322~4,4,322",
    "4,4,120~4,5,120",
    "3,6,23~4,6,23",
    "6,3,200~8,3,200",
    "5,1,7~7,1,7",
    "0,5,4~0,7,4",
    "9,8,69~9,8,70",
    "6,1,77~8,1,77",
    "0,7,282~1,7,282",
    "3,0,98~5,0,98",
    "4,6,177~4,7,177",
    "1,2,67~2,2,67",
    "4,4,329~6,4,329",
    "7,1,84~9,1,84",
    "5,1,80~5,2,80",
    "6,4,219~6,5,219",
    "0,1,164~0,4,164",
    "6,5,273~7,5,273",
    "4,3,328~7,3,328",
    "0,2,145~3,2,145",
    "1,3,32~1,5,32",
    "1,9,191~4,9,191",
    "2,6,342~5,6,342",
    "2,1,235~2,3,235",
    "2,1,32~2,3,32",
    "0,4,298~2,4,298",
    "4,2,272~4,4,272",
    "8,2,87~8,3,87",
    "3,1,108~3,3,108",
    "3,4,160~3,6,160",
    "4,6,40~4,7,40",
    "8,1,279~9,1,279",
    "9,2,12~9,4,12",
    "2,1,146~2,2,146",
    "6,0,63~9,0,63",
    "4,5,210~7,5,210",
    "7,2,164~7,3,164",
    "5,5,20~5,7,20",
    "1,7,159~1,9,159",
    "7,5,199~7,7,199",
    "6,2,84~6,5,84",
    "0,1,101~0,3,101",
    "3,8,87~3,8,88",
    "3,0,95~5,0,95",
    "2,3,240~2,5,240",
    "0,3,224~0,4,224",
    "7,6,276~7,8,276",
    "1,8,274~1,9,274",
    "3,8,59~6,8,59",
    "5,3,36~5,5,36",
    "0,0,63~0,0,65",
    "0,2,249~2,2,249",
    "3,5,172~4,5,172",
    "0,3,272~2,3,272",
    "1,6,60~1,9,60",
    "6,2,63~6,4,63",
    "3,3,337~3,6,337",
    "3,2,188~3,2,190",
    "5,9,150~5,9,150",
    "3,4,70~3,6,70",
    "3,3,304~5,3,304",
    "7,5,81~7,6,81",
    "2,0,284~2,2,284",
    "4,2,158~4,3,158",
    "6,5,4~6,8,4",
    "0,3,38~1,3,38",
    "8,1,129~8,1,129",
    "4,3,298~4,6,298",
    "4,2,331~5,2,331",
    "5,1,334~5,2,334",
    "3,5,275~3,7,275",
    "3,4,116~6,4,116",
    "1,6,90~1,6,92",
    "6,1,108~6,2,108",
    "6,0,210~8,0,210",
    "2,1,3~2,4,3",
    "9,5,239~9,8,239",
    "7,6,300~7,7,300",
    "5,0,168~6,0,168",
    "0,6,322~0,9,322",
    "0,9,81~2,9,81",
    "5,5,233~7,5,233",
    "4,5,252~4,8,252",
    "3,9,147~6,9,147",
    "8,6,72~8,8,72",
    "8,3,300~8,5,300",
    "3,2,308~7,2,308",
    "8,5,54~8,5,56",
    "3,2,28~5,2,28",
    "3,5,14~6,5,14",
    "5,4,243~5,5,243",
    "5,6,117~7,6,117",
    "2,7,219~4,7,219",
    "6,7,321~8,7,321",
    "2,0,159~2,1,159",
    "9,6,9~9,9,9",
    "5,6,68~5,9,68",
    "5,5,245~5,6,245",
    "5,6,171~7,6,171",
    "2,5,80~2,7,80",
    "0,0,193~3,0,193",
    "0,1,18~3,1,18",
    "0,9,92~2,9,92",
    "0,0,165~2,0,165",
    "9,1,281~9,4,281",
    "9,5,152~9,7,152",
    "3,2,56~5,2,56",
    "7,9,1~7,9,1",
    "9,7,135~9,9,135",
    "3,1,98~3,4,98",
    "6,3,113~6,5,113",
    "0,8,278~0,8,280",
    "3,3,87~5,3,87",
    "1,3,232~3,3,232",
    "1,2,268~1,5,268",
    "5,7,233~5,9,233",
    "0,7,316~3,7,316",
    "3,0,24~5,0,24",
    "1,0,6~1,2,6",
    "0,3,10~0,6,10",
    "4,0,205~4,2,205",
    "9,5,255~9,8,255",
    "5,6,124~6,6,124",
    "7,7,180~7,9,180",
    "8,2,217~8,4,217",
    "1,2,39~1,2,42",
    "4,9,9~6,9,9",
    "2,2,283~3,2,283",
    "4,5,42~4,5,43",
    "7,0,121~7,2,121",
    "4,2,301~4,3,301",
    "8,2,48~8,4,48",
    "3,4,14~5,4,14",
    "1,0,187~4,0,187",
    "8,7,268~8,9,268",
    "3,6,85~5,6,85",
    "0,6,62~1,6,62",
    "5,7,91~5,7,94",
    "4,3,151~4,7,151",
    "3,5,192~3,7,192",
    "3,0,330~3,3,330",
    "1,6,37~3,6,37",
    "8,2,82~8,3,82",
    "6,1,274~6,3,274",
    "3,6,178~5,6,178",
    "1,4,163~3,4,163",
    "1,7,5~3,7,5",
    "9,2,61~9,5,61",
    "3,6,217~3,9,217",
    "3,0,100~3,0,101",
    "2,0,192~4,0,192",
    "7,2,327~7,4,327",
    "4,3,181~6,3,181",
    "1,1,169~1,1,171",
    "4,5,10~6,5,10",
    "0,0,26~0,3,26",
    "6,8,298~9,8,298",
    "5,1,136~5,4,136",
    "9,5,173~9,6,173",
    "7,7,191~8,7,191",
    "0,0,81~0,2,81",
    "5,7,159~5,8,159",
    "0,1,276~0,3,276",
    "6,4,121~6,6,121",
    "6,2,102~7,2,102",
    "1,6,100~3,6,100",
    "3,6,191~5,6,191",
    "3,4,240~5,4,240",
    "8,4,86~8,7,86",
    "7,2,130~7,5,130",
    "6,7,161~8,7,161",
    "4,3,254~6,3,254",
    "5,6,88~5,9,88",
    "5,7,49~5,9,49",
    "3,1,332~4,1,332",
    "5,2,333~5,4,333",
    "6,8,203~8,8,203",
    "4,4,312~4,7,312",
    "2,5,263~5,5,263",
    "3,9,55~5,9,55",
    "7,4,179~7,7,179",
    "6,3,178~6,5,178",
    "0,1,82~0,4,82",
    "7,7,187~9,7,187",
    "3,3,95~4,3,95",
    "6,3,271~9,3,271",
    "3,2,179~5,2,179",
    "9,3,273~9,5,273",
    "0,7,45~1,7,45",
    "2,3,124~2,6,124",
    "1,2,98~1,3,98",
    "8,5,122~8,6,122",
    "1,2,17~1,2,19",
    "0,4,50~0,5,50",
    "7,2,305~9,2,305",
    "6,3,270~6,4,270",
    "1,8,277~4,8,277",
    "9,6,132~9,7,132",
    "4,7,137~5,7,137",
    "9,0,3~9,3,3",
    "8,4,161~8,6,161",
    "5,6,343~8,6,343",
    "4,3,44~6,3,44",
    "5,4,78~6,4,78",
    "4,2,273~4,4,273",
    "8,4,290~8,7,290",
    "8,3,297~8,5,297",
    "6,8,110~8,8,110",
    "5,1,203~5,2,203",
    "0,7,236~2,7,236",
    "7,2,242~9,2,242",
    "5,8,249~7,8,249",
    "1,9,329~4,9,329",
    "0,0,238~0,2,238",
    "6,2,259~6,3,259",
    "3,1,230~3,2,230",
    "5,2,315~5,3,315",
    "5,2,285~7,2,285",
    "2,1,75~2,4,75",
    "1,0,139~4,0,139",
    "3,2,311~3,2,314",
    "7,1,198~7,2,198",
    "3,0,285~7,0,285",
    "4,1,84~5,1,84",
    "3,5,152~3,5,154",
    "9,3,73~9,5,73",
    "9,7,160~9,9,160",
    "6,6,181~7,6,181",
    "1,7,74~3,7,74",
    "7,7,287~7,8,287",
    "0,4,345~2,4,345",
    "7,3,193~7,4,193",
    "5,7,83~5,9,83",
    "6,2,26~8,2,26",
    "1,2,253~3,2,253",
    "5,1,95~5,2,95",
    "5,3,283~6,3,283",
    "7,5,335~7,5,338",
    "3,4,144~3,6,144",
    "0,2,247~0,4,247",
    "4,8,207~5,8,207",
    "3,8,70~3,9,70",
    "7,9,75~9,9,75",
    "9,5,159~9,7,159",
    "7,3,146~7,5,146",
    "4,5,24~4,8,24",
    "4,7,91~4,9,91",
    "1,4,185~4,4,185",
    "0,3,200~0,5,200",
    "7,4,213~7,6,213",
    "2,4,72~2,6,72",
    "5,5,265~5,7,265",
    "2,4,320~2,5,320",
    "0,1,84~0,3,84",
    "4,4,149~4,6,149",
    "7,0,138~7,3,138",
    "5,0,208~5,2,208",
    "3,3,325~3,4,325",
    "3,6,291~5,6,291",
    "7,6,130~9,6,130",
    "1,8,71~3,8,71",
    "1,0,97~1,3,97",
    "1,7,94~1,9,94",
    "7,5,72~7,8,72",
    "2,0,119~2,2,119",
    "2,8,201~5,8,201",
    "4,6,82~6,6,82",
    "6,8,254~8,8,254",
    "2,7,12~2,7,14",
    "8,1,221~8,4,221",
    "2,3,200~2,4,200",
    "2,1,15~2,3,15",
    "5,2,89~5,5,89",
    "6,5,15~8,5,15",
    "6,8,269~9,8,269",
    "6,4,66~6,5,66",
    "8,0,68~9,0,68",
    "1,5,302~3,5,302",
    "0,0,163~0,2,163",
    "1,3,281~3,3,281",
    "5,6,271~5,6,272",
    "4,0,252~7,0,252",
    "2,9,218~3,9,218",
    "4,0,124~4,2,124",
    "1,0,204~3,0,204",
    "8,3,137~8,6,137",
    "2,5,272~2,5,274",
    "1,7,79~1,7,81",
    "2,8,321~2,9,321",
    "1,7,77~2,7,77",
    "6,1,127~6,3,127",
    "0,2,63~2,2,63",
    "4,1,157~5,1,157",
    "7,1,302~9,1,302",
    "6,0,317~9,0,317",
    "8,7,73~8,9,73",
    "3,9,163~5,9,163",
    "2,8,211~5,8,211",
    "5,0,112~7,0,112",
    "6,3,339~9,3,339",
    "6,7,190~6,9,190",
    "2,6,212~2,9,212",
    "5,4,164~5,6,164",
    "1,4,325~1,7,325",
    "3,6,56~3,8,56",
    "8,4,47~8,5,47",
    "5,2,264~5,4,264",
    "9,0,258~9,4,258",
    "6,7,144~6,9,144",
    "6,1,335~7,1,335",
    "5,1,186~5,3,186",
    "7,2,71~7,4,71",
    "8,7,114~8,7,115",
    "2,1,46~2,3,46",
    "8,8,285~9,8,285",
    "9,2,201~9,5,201",
    "0,4,194~0,6,194",
    "9,6,207~9,8,207",
    "1,3,236~4,3,236",
    "0,2,205~2,2,205",
    "4,3,175~7,3,175",
    "4,3,83~8,3,83",
    "1,7,272~1,8,272",
    "4,4,103~7,4,103",
    "2,6,65~2,8,65",
    "1,8,105~1,9,105",
    "7,6,94~9,6,94",
    "5,2,17~5,4,17",
    "6,9,300~7,9,300",
    "5,2,235~6,2,235",
    "5,6,100~7,6,100",
    "0,6,272~0,8,272",
    "2,8,238~4,8,238",
    "5,1,10~5,2,10",
    "6,4,44~9,4,44",
    "6,8,230~9,8,230",
    "7,3,166~7,5,166",
    "7,0,286~9,0,286",
    "1,2,197~1,4,197",
    "4,7,278~4,9,278",
    "0,2,59~3,2,59",
    "0,1,236~2,1,236",
    "7,3,116~9,3,116",
    "4,5,60~4,6,60",
    "6,1,218~8,1,218",
    "7,1,331~7,3,331",
    "1,0,123~3,0,123",
    "5,2,326~5,5,326",
    "1,4,101~1,6,101",
    "3,4,139~6,4,139",
    "4,3,238~6,3,238",
    "6,0,15~8,0,15",
    "2,6,146~2,9,146",
    "6,5,180~8,5,180",
    "7,0,122~7,2,122",
    "3,0,135~7,0,135",
    "7,0,11~7,2,11",
    "3,1,193~3,3,193",
    "7,2,147~9,2,147",
    "4,7,229~4,7,232",
    "3,2,184~3,3,184",
    "0,5,153~2,5,153",
    "2,6,126~2,9,126",
    "4,7,156~7,7,156",
    "8,2,76~8,5,76",
    "1,4,284~1,5,284",
    "7,6,250~7,7,250",
    "2,0,255~2,2,255",
    "3,4,351~3,6,351",
    "3,5,34~6,5,34",
    "0,4,126~2,4,126",
    "2,7,67~2,9,67",
    "7,4,99~7,6,99",
    "5,9,252~5,9,254",
    "3,5,36~3,7,36",
    "7,4,288~7,5,288",
    "6,9,154~8,9,154",
    "0,2,187~3,2,187",
    "3,0,267~3,2,267",
    "6,6,216~8,6,216",
    "8,6,121~9,6,121",
    "6,1,203~6,1,204",
    "6,5,277~6,7,277",
    "5,6,45~5,8,45",
    "7,2,25~7,5,25",
    "6,7,324~6,7,326",
    "7,6,194~7,9,194",
    "8,1,272~8,3,272",
    "3,3,1~4,3,1",
    "1,8,254~4,8,254",
    "0,4,12~0,7,12",
    "5,7,321~5,9,321",
    "5,1,82~7,1,82",
    "9,2,106~9,3,106",
    "3,4,241~4,4,241",
    "2,6,94~2,9,94",
    "6,4,55~6,7,55",
    "4,2,145~4,4,145",
    "9,4,157~9,6,157",
    "3,6,199~3,8,199",
    "3,3,84~4,3,84",
    "5,0,307~5,2,307",
    "0,6,60~0,8,60",
    "1,8,96~3,8,96",
    "3,7,64~3,9,64",
    "1,8,144~3,8,144",
    "6,1,241~6,2,241",
    "0,6,158~0,6,158",
    "8,5,282~8,7,282",
    "6,2,11~6,2,13",
    "3,1,124~3,3,124",
    "1,2,45~1,4,45",
    "5,7,181~7,7,181",
    "6,6,283~6,7,283",
    "0,8,274~0,8,275",
    "0,8,174~2,8,174",
    "9,9,162~9,9,164",
    "5,0,258~7,0,258",
    "7,8,45~7,9,45",
    "9,5,294~9,7,294",
    "2,0,90~5,0,90",
    "3,4,101~3,5,101",
    "5,2,160~8,2,160",
    "8,7,91~8,9,91",
    "5,5,229~5,8,229",
    "8,6,69~9,6,69",
    "5,2,172~7,2,172",
    "0,6,320~3,6,320",
    "6,8,242~8,8,242",
    "0,1,96~0,1,98",
    "2,8,173~2,9,173",
    "8,8,13~8,8,14",
    "0,1,285~0,3,285",
    "6,0,45~6,3,45"
};