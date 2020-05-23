texture_id = 0
sprite_id = 0

add = 1

function main() -- SFML Initialize
	opaque.title("Opaque Engine Lua Test")
	texture_id = sprite.loadTexture("test.bmp")
	sprite_id = sprite.loadSprite(texture_id)
	return 0
end


function loop()
	--log("Lua -- Loop begin")
	local ev = opaque.pollEvent() -- Poll SFML Events
	if(ev == 1) then		-- SFML Close Requested
		log("Window closed")
		return -2 -- Request close
	end
	x, y = sprite.getCoords(sprite_id)
	if(add == 1) then
		x = x + (opaque.deltaTime() * 100)
		y = y + (opaque.deltaTime() * 100)
		if(x > 300) then
			add = 0
		end
	else
		x = x - (opaque.deltaTime() * 100)
		y = y - (opaque.deltaTime() * 100)
		if(x < 0) then
			add = 1
		end
	end
	sprite.setCoords(sprite_id, x, y)
	-- Draw everything
	opaque.clearScreen()
	sprite.drawSprite(sprite_id)
	opaque.flip() -- Flip also logs delta time
end