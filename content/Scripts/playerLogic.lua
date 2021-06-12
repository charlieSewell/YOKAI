engine = Yokai:getInstance();

velocity = player.physics:getVelocity();
if(velocity.y < -35 and velocity.y < player.physics:getMaxVelocity()) then
    player.physics:setMaxVelocity(velocity.y);
end
if(player.onGround) then
    player.health = player.health + (player.physics:getMaxVelocity() * 2);
    if player.health <= 0 then
        player.health = 0;
    end
    player.physics:setMaxVelocity(0);
end


if(player.health <= 0 or numZombies == 0)
then
    uiManager:setActive(lostScreen, true);
end

if(uiManager:getActive(lostScreen))
then
    engine.isPaused = true;
end