objManager = ObjectManager:getInstance()

--States
wander		= 0
seek		= 1
attack		= 2
dead		= 3

function update(obj)

	stateMachine(obj)

end

function stateMachine(obj)
	if(obj.hit == true)
	then
		obj.animator:setAnimation("ZombieBite")
		obj.behaviours.acceleration = -0.015;
		obj.health = obj.health - 10;
		obj.hit = false
		obj.behaviours.state = seek;
	elseif(obj.health < 20)
	then
		obj.animator:setAnimation("ZombieCrawl")
		obj.behaviours:accelerate(0.010);
		obj.behaviours.rotationSpeed = 0.0015;
		obj.behaviours:seek(player:getPosition());
	elseif(obj.behaviours.state == wander)
	then
		obj.animator:setAnimation("ZombieWalk");
		obj.behaviours:wander();
		obj.behaviours:accelerate(0.015);

		if(objManager:distance(player:getPosition(), obj:getPosition()) < 30 or obj.behaviours.active == true)
		then
			obj.behaviours.state = seek
		end

		if(objManager.elapsedTime > 180)
		then
			obj.behaviours.state = seek
		end 
	elseif(obj.behaviours.state == seek)
	then
		obj.animator:setAnimation("ZombieRun")
		obj.behaviours:seek(player:getPosition());
		obj.behaviours:accelerate(0.115);
		obj.behaviours.rotationSpeed = 0.075;

		if(objManager:distance(player:getPosition(), obj:getPosition()) < 5)
		then
			obj.behaviours.state = attack
		end
	elseif(obj.behaviours.state == attack)
	then
		obj.animator:setAnimation("ZombieBite")
		obj.behaviours.rotationSpeed = 0.05;
		player.hit = true;
		if(objManager:distance(player:getPosition(), obj:getPosition()) > 5)
		then
			obj.behaviours.state = seek
		end
	end
end
