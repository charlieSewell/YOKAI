terrFac = TerrainFactory:getInstance()
objManager = ObjectManager:getInstance()


--Creating Player Object
playerID = objManager:Create(Types.player(),"");
player = objManager:GetPlayer();
player:setPosition(855.0, 90.0, 620.0);
player:setCollider(4, 4, 4.0);
player.movement.movementSpeed = 27000;
player.health = 100;
player.shields = 100;
player.movement.sprintMultiplier = 1.75;
player.movement.lookSensitivityMultiplier = 1;

player.gun.maxAmmo = 30;
player.gun.maxReserveAmmo = 150;
player.gun.gunAnimation.ticksPerSecond = 20;
player.gun.gunAnimation:readFile("content/Models/guntest.txt");
player.gun.gunAnimation:addAnimation("fire", 1, 7);
player.gun.gunAnimation:addAnimation("reload", 7, 55);
player.gun.gunAnimation:addAnimation("emptyreload", 55, 108);
player.gun.gunAnimation:addAnimation("idle", 142, 164);
player.gun.gunAnimation:addAnimation("melee", 164, 177);
player.gun.gunAnimation:addAnimation("ads", 1, 1);
player.gun.gunAnimation:addAnimation("sprint", 109, 118);

player.gun.gunAnimation:setCurrentAnimation("idle");


playerPos = player:getPosition();

--Creating SkyBox
skyBoxID = objManager:Create(Types.static(),"content/Models/skybox1.fbx");
skyBox = objManager:GetObject(skyBoxID);
skyBox:setPosition(TerrainSettings.terrainSize/2, 0, TerrainSettings.terrainSize/2);
skyBox:setScale(0.1, 0.1, 0.1);

spawnRange = 500;
--Creating Rocks in random places
for i=0,100 do
        x = math.random(0,TerrainSettings.terrainSize);
        z = math.random(0,TerrainSettings.terrainSize);
        val = terrFac:getHeight(x,z)
        asset = objManager:Create(Types.static(),"content/Models/rock.fbx");
        gameObj = objManager:GetObject(asset);
        gameObj:setScale(0.02,0.02,0.02);
        gameObj:setPosition(x,val-2,z);
        gameObj:setCollider(3,4,3);

end

for i=0, 50 do
        x = math.random(playerPos.x - spawnRange, playerPos.x + spawnRange);
        z = math.random(playerPos.z - spawnRange, playerPos.z + spawnRange);
        val = terrFac:getHeight(x,z)
        asset = objManager:Create(Types.static(),"content/Models/rock.fbx");
        gameObj = objManager:GetObject(asset);
        gameObj:setScale(0.02,0.02,0.02);
        gameObj:setPosition(x,val-2,z);
        gameObj:setCollider(3,4,3);

end

--Creating Trees in random places
for i=0,100 do
        x= 0;
        z = 0;
        val = 0;
        while val < 60 do
            x = math.random(0,TerrainSettings.terrainSize);
            z = math.random(0,TerrainSettings.terrainSize);
                val = terrFac:getHeight(x,z)
        end
        asset = objManager:Create(Types.static(),"content/Models/tree.fbx");
        gameObj = objManager:GetObject(asset);
        gameObj:setScale(0.01,0.01,0.01);
        gameObj:setPosition(x,val-1,z);
        gameObj:setCollider(1,20,1);
end

for i=0,100 do
        x= 0;
        z = 0;
        val = 0;
        while val < 60 do
            x = math.random(playerPos.x - spawnRange, playerPos.x + spawnRange);
			z = math.random(playerPos.z - spawnRange, playerPos.z + spawnRange);
            val = terrFac:getHeight(x,z)
        end
        asset = objManager:Create(Types.static(),"content/Models/tree.fbx");
        gameObj = objManager:GetObject(asset);
        gameObj:setScale(0.01,0.01,0.01);
        gameObj:setPosition(x,val-1,z);
        gameObj:setCollider(1,20,1);
end

--Creating Zombies in random places

numZombies = 60;
spawnRange = 225;
for i=0, numZombies-1 do
        x = math.random(playerPos.x - spawnRange, playerPos.x + spawnRange);
        z = math.random(playerPos.z - spawnRange, playerPos.z + spawnRange);
        val = terrFac:getHeight(x,z)
        asset = objManager:Create(Types.npc(),"content/Models/Zombie/ZombieSmooth.gltf");
        npc = objManager:GetNPC(asset);
        npc:setScale(0.5,0.5,0.5);
        npc:setPosition(x,val,z);
        npc:setCollider(1,2,1);
		npc.behaviours.rotationSpeed = 0.005;
end

waterID = objManager:Create(Types.static(),"content/Models/water.gltf");
water = objManager:GetObject(waterID);
water:setPosition(1428.0, 30.0, 1000.0);
water:setScale(60, 1, 60);