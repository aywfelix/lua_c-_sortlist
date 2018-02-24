package.cpath = "./?.so"

local SortList = require 'SortList'
local sortlist = SortList.create();
sortlist:add_node("AA", os.time()+math.random(0,100))
sortlist:add_node("bb", os.time()+math.random(0,100))
sortlist:add_node("sdsd", os.time()+math.random(0,100))
sortlist:print_nodes()
