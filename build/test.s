segment data
export a
global a type=array 4 of int sclass=auto scope=GLOBAL flags=0 ref=0.000000
defconst int.4 1
defconst int.4 2
defconst int.4 3
defconst int.4 4
export main
segment text
function main type=int function(void) sclass=auto scope=GLOBAL flags=0 ref=0.000000 ncalls=0
blockbeg off=0
local i type=int sclass=register scope=LOCAL flags=0 offset=0 ref=32.000000
local r type=int sclass=register scope=LOCAL flags=0 offset=4 ref=10.000000
blockbeg off=8
blockend off=8
blockend off=8
 2. ADDRLP4 i
3. CNSTI4 0
1' ASGNI4 #2 #3 4 4
 2:
 2. ADDRLP4 r
7. ADDRLP4 i
6. INDIRI4 #7
8. CNSTI4 2
5. LSHI4 #6 #8
9. ADDRGP4 a
4. ADDP4 #5 #9
3. INDIRI4 #4
1' ASGNI4 #2 #3 4 4
 3:
 2. ADDRLP4 count=2 i
4. INDIRI4 #2
5. CNSTI4 1
3. ADDI4 #4 #5
1' ASGNI4 #2 #3 4 4
 3. ADDRLP4 i
2. INDIRI4 #3
4. CNSTI4 3
1' LEI4 #2 #4 2
 3. ADDRLP4 i
2. INDIRI4 #3
1' RETI4 #2
 1:
maxoff=8
progend
