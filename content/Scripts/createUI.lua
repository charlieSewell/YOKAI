uiManager = UIManager:getInstance();

crosshair = uiManager:add("crosshair","content/Textures/crosshair.png");
uiManager:setUpPanel(crosshair, (1920/2) - 25, (1920/2) + 25, (1080/2) - 25, (1080/2) + 25);

ammoOne = uiManager:add("ammoOne", "content/Textures/3.png");
uiManager:setUpPanel(ammoOne, 1700, 1750, 800, 900);

ammoTwo = uiManager:add("ammoTwo", "content/Textures/0.png");
uiManager:setUpPanel(ammoTwo, 1750, 1800, 800, 900);

zombieOne = uiManager:add("zombieOne", "content/Textures/3.png");
uiManager:setUpPanel(zombieOne, 50, 100, 50, 120);

zombieTwo = uiManager:add("zombieTwo", "content/Textures/0.png");
uiManager:setUpPanel(zombieTwo, 100, 150, 50, 120);

reserveOne = uiManager:add("reserveOne", "content/Textures/1.png");
uiManager:setUpPanel(reserveOne, 1750, 1800, 900, 1000);

reserveTwo = uiManager:add("reserveTwo", "content/Textures/5.png");
uiManager:setUpPanel(reserveTwo, 1800, 1850, 900, 1000);

reserveThree = uiManager:add("reserveThree", "content/Textures/0.png");
uiManager:setUpPanel(reserveThree, 1850, 1900, 900, 1000);

healthBar = uiManager:add("health", "content/Textures/health.jpg");
uiManager:setUpPanel(healthBar, 50, 700, 950, 1000);

shieldBar = uiManager:add("shields", "content/Textures/shield.png");
uiManager:setUpPanel(shieldBar, 50, 700, 875, 925);

lostScreen = uiManager:add("lostScreen", "content/Textures/exit_screen.png");
uiManager:setUpPanel(lostScreen, 200, 1700, 100, 900);
uiManager:setActive(lostScreen, false);
