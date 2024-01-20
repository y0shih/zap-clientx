# xap-client  [LINUX]
**Updated to Game Version v3.0.54.31 (18.01.24)**

By **Gerosity**

All credits to original owners

Instructions & help down below

# Changelog:
    20.01.24
    No Recoil Fixed (Offset issue)

    19.01.24
    Aimbot:
       - Added Delay (Not sure what its called, but it affects smoothing speed? So good for legit players ig
    Sense:
       - Added Status Text (Current Health & Armor)
           - Added Max Status Text (Max Health & Armor)
       - Moved Name and distance positions, distance may get in the way of box/skeleton, will fix eventually

    Crashing still occurs after going back to the lobby, not sure while and will do some testing about it tommorow.
    Not a big deal since you can just run the cheat again after crashing

    18.01.24
    Updated Offsets to v3.0.54.31

    17.01.24
    Aimbot:
       - Removed Keybinds, replaced with On ADS? or On Fire? Self explanitory
    Triggerbot:
       - Removed Keybinds, replaced with On ADS? Self explanitory
    ESP:
       - Filled Box ESP
       - Filled FOV Circle
    Other:
       - Fixed Config Saving/Loading issues
           - Colors do not save!

    16.01.24
    Updated Offsets - UC Forum
    Aimbot:
       - Keybind & Extra Keybind (If you want aimbot to be on left + right click) - https://github.com/GitDev28/xap-client-CG
       - Select Bone (Head, Neck, Upper Chest, Lower Chest, Stomach, Hip) - https://github.com/GitDev28/xap-client-CG
       - Select Weapons (e.g. only aim with R-99) - https://github.com/GitDev28/xap-client-CG
    Triggerbot:
       - Keybind (Hold to enabled)
       - Always On (Ignores keybind, always on)
       - Select Weapons (e.g. only with snipers) - https://github.com/GitDev28/xap-client-CG
    Sense/ESP:
       - Color Picker (Change Visible & Invisible colors for most features)
       - Visibile Only (Only draws ESP on those who are visible)
       - Show Near (?)
           - Not sure if it works anymore
       - Draw Team (Displays ESP on teammates)
           - Draw Team Names
       - Tracer Screen Position (Where tracers start e.g. Top, Middle (Crosshair), Bottom)
       - Tracer Bone Position (Where tracers goto/end e.g. Top (Head), Bottom)
       - Thickness Slider
           - For Box, Tracers, Skeleton, FOV Circle, Crosshair
       - Crosshair
           - Color, Size, Thickness
    Misc:
       - Team Gamemode (Enable for BR, Gun Run or Training. Disable for Control or TDM)
       - Superglide [!] - https://github.com/Savage3e/Nika or https://github.com/FlixEarth/nika-fixed
           - Works (most) of the time, freezes overlay until space is no longer held down (Needs Fix)
    Menu:
       - Layout (Simple or Compact)
       
# ToDo List:
    Multi-Monitor Support (? / ✅) 
       - Doesnt work for me but others have said it works. Needs testing
    Aimbot:
       - Visibility Check
    Triggerbot:
       - Crash fix
       - Hitbox Select (e.g. only shoot if on head)
    ESP/Sense:
       - Filled FOV
       - Filled Box ESP (?) 
       - Health/Shield Bar ESP
       - Weapon ESP
       - Deathbox ESP
       - Item ESP
     Themes:
       - Change Theme (Change menu theme (Style, Colors) 

# Help
**Features not working after changing them? (e.g. aim bind)**
Save config/Load config

**Aimbot not working?**

Check the speed/smoothness, keybind and if you have team gamemode on/off in the wrong mode

**ESP not working?**

Check team gamemode

**Experience Crashes?**

Try toggling features off (namely glow and triggerbot)

# Original README.md

xap-client UC Link: https://www.unknowncheats.me/forum/apex-legends/606842-xap-client-aimbot-esp-triggerbot.html

So yeah, this thing was made by me, I was very bored so I took T_Tape's Menu and grinder's features and put them together to create this monstrosity. The code is still very messy so if you want to improve it, go ahead.
I'll will be very grateful if you do so.

**Disclaimer: This code is for educational purposes only .**

# Credits
arturzxc: for the features (ESP, Triggerbot, Aimbot) and X11Display's XTestFakeRelativeMotionEvent

Koelion (Braziliana): menu, aimbot calculations

unguhelvu : Seer-Styled ESP

unknowncheats: basic knowledge and offsets


# Previews

![enter image description here](https://i.imgur.com/7mVlPrr.png)

# Installation
**1.Install dependencies**

    sudo apt-get install -y libudev-dev
    sudo apt install cmake xorg-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
    sudo apt-get install build-essential
    sudo apt-get install libx11-dev
    sudo apt-get install libxtst-dev

**2.Build glfw**

    git clone https://github.com/glfw/glfw.git
    cd glfw
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

**3. Clone repo**

    git clone https://github.com/Gerosity/zap-client.git
    cd zap-client

**4. Build and Run**

    mkdir build
    cd build
    cmake ..
    make
    sudo ./zapclient
    
**5. Press Insert to toggle the Menu (You can only interact with the Menu and the game when the menu is active).**
