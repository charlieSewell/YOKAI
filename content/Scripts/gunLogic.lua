
if ((player.gun.ammo == 0) and (player.gun.reserveAmmo == 0))
then
	player.gun.canFire = false;
	player.gun.gunAnimation.ticksPerSecond = 20;
	player.gun.gunAnimation:setCurrentAnimation("idle");
elseif (player.gun.ammo == 0)
then
	player.gun.canFire = false;
	player.gun.gunAnimation.ticksPerSecond = 30;
	player.gun.gunAnimation:setCurrentAnimation("emptyreload");
	player.gun:reload();
end

if (player.gun:getIsReloading())
then
    if ((player.gun.ammo ~= 0) and (player.gun.ammo ~= player.gun.maxAmmo) and (player.gun.reserveAmmo ~= 0))
    then
		player.gun.canFire = false;
        player.gun.gunAnimation.ticksPerSecond = 30;
	    player.gun.gunAnimation:setCurrentAnimation("reload");
        player.gun:reload();
    end
end

if(player.gun:getIsFiring())
then
    if (player.gun.ammo ~= 0)
    then
        if (player.gun.gunAnimation:getCurrentAnimation() == "idle" or player.gun.gunAnimation:getCurrentAnimation() == "ads")
        then
			player.gun.canFire = false;
            player.gun.gunAnimation.ticksPerSecond = 30;
            player.gun.gunAnimation:setCurrentAnimation("fire");
            player.gun:decrementAmmo();
        elseif (player.gun.gunAnimation:getAnimationFinished())
        then
			player.gun.canFire = false;
            player.gun.gunAnimation.ticksPerSecond = 30;
            player.gun.gunAnimation:setCurrentAnimation("fire");
            player.gun:decrementAmmo();
        end
    end
end

if(player.gun:getIsMeleeing())
then
    if (player.gun.gunAnimation:getCurrentAnimation() == "idle" or player.gun.gunAnimation:getCurrentAnimation() == "ads")
    then
		player.gun.canFire = false;
        player.gun.gunAnimation.ticksPerSecond = 30;
        player.gun.gunAnimation:setCurrentAnimation("melee");
	end
end

if(player.movement.sprint > 1)
then
	player.gun.canFire = false;
	player.gun.gunAnimation.ticksPerSecond = 15;
	player.gun.gunAnimation:setCurrentAnimation("sprint");
end
        
player.gun.gunAnimation:checkAnimationFinished();

if (player.gun.gunAnimation:getAnimationFinished())
then
	player.gun.canFire = true;
	player.gun.gunAnimation.ticksPerSecond = 20;

	if(player.gun.ads)
	then
		uiManager:setActive(crosshair, false);
		player.gun.gunAnimation:setCurrentAnimation("ads");
		player.movement.lookSensitivityMultiplier = 0.65;
	else
		uiManager:setActive(crosshair, true);
		player.gun.gunAnimation:setCurrentAnimation("idle");
		player.movement.lookSensitivityMultiplier = 1;
	end
end