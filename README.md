# xap-client  [LINUX]
**DO NOT USE, NEEDS UPDATING**, **Update soon**
# ToDo List:
    Rename project to something else (as not to confuse) (All credits to original devs) (e.g. xap-client-remastered) 
    Updated Offsets ✅
    Multi-Monitor Support (? / ✅) 
       - Doesnt work for me but others have said it works. Needs testing
    Aimbot:
       - Aim Keybind ✅
       - Aim Bone ✅
       - Visibility Check
    Triggerbot:
       - Always On
       - Triggerbot Keybind ✅
       - Crash fix
    ESP/Sense:
       - Filled Box ESP (?) 
       - Box thickness slider ✅
       - Tracer Screen Position (Top, Middle, Bottom) ✅
       - Tracer Bone Position (Top (Head) , Bottom) ✅
       - Tracer thickness slider
       - Skeleton thickness slider ✅
       - Show Teammates (Draw ESP on teammates, seperate color to enemies) ✅
          - Draw Teammates Names (Can get in the way of ingame names) ✅
       - Crosshair
     Misc:
       - Gamemode toggle (For switching between BR, Gun Run & Training - > TDM & Control) ✅
       - Superglide (!)
          - When enabled, breaks the cheat when holding down space. Let go and it fixes. Not good + needs fixing
     Themes:
       - Change Theme (Change menu theme (Style, Colors) 
     Colors:
       - Color Picker for everything (!) 
          - (Tried before and failed, will try again eventually) 

Will release as soon as I can :) 

**Old README.md**

For **v3.0.52.26 (Final Fantasy Update)**
By **Gerosity**
All credits to original owners

# Changelog:

    Updated Offsets - UC Forum
    Team Gamemode (Toggle, Load Config after changing) - https://github.com/Pesci-Apu/Apu
    Draw Box - https://www.unknowncheats.me/forum/3956658-post524.html
    Draw Skeleton- https://www.unknowncheats.me/forum/3956658-post524.html
    Draw Names - https://github.com/Pesci-Apu/Apu
    Show Near - https://www.unknowncheats.me/forum/3956658-post524.html
    ESP Max Distance - https://www.unknowncheats.me/forum/3956658-post524.html
    Load Config

xap-client UC Link: https://www.unknowncheats.me/forum/apex-legends/606842-xap-client-aimbot-esp-triggerbot.html

# Original README.md
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

    git clone https://github.com/Gerosity/xap-client-v3.0.53.30
    cd xap-client-v3.0.53.30

**4. Build and Run**

    mkdir build
    cd build
    cmake ..
    make
    sudo ./xapclient
    
**5. Press Insert to toggle the Menu (You can only interact with the Menu and the game when the menu is active).**
