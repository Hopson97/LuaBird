rects = {}
test_table = {5,6,7,8}

local function newRect(width, height, x, y)
	local rect = Rectangle.new(width, height, x, y);
	table.insert(rects, rect);
	return rect;
end


function update( ... )
	
end



local rect = newRect(100, 100, 100, 100)