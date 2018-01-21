# Capture The Flag

I would like to share something I’ve been wanting for a while so I just decided to learn Arduino and do it myself.

It’s Capture The Flag for your drones (with FPV).
If you happen to stumble here and don't know what FPV you can read about it in [Wikepedia](https://en.wikipedia.org/wiki/First-person_view_(radio_control)) or simply visit my youtube channel *www.youtube.com/SeekNDFPV*



This mod was made with Tiny Whoops (check *TinyWhoop.com*) in mind but really you can use it with any size drone as long as it has a video transmitter on it.

It’s fairly easy to build, **costs around £9 (or $12) per flag in materials** and you just need to solder a few cables 🙂

You can battle **4 drones (BLUE TEAM - RACEBAND 1 to 4) vs 4 drones (RED TEAM - RACEBAND 5 to 8)** in a game of Capture The Flag (as long as your VTX signals allow for that many to be flying at the same time) with as many flags as you are bothered to build!

The code itself is GREATELY based off Chorus RF Laptimer
Visit their repo if you are interested in knowing more about it here: https://github.com/voroshkov/Chorus-RF-Laptimer

Unlike Chorus RF Laptimer, at this moment this mod is standalone and cannot be accessed remotely (yet, maybe someone would like to help code that?)

You can though, change the code to match your needs.
I've commented everything that I've changed in the code with (CC) and the explanation behind it so it's easy for you to find it and replace it. Pretty sure the code can be improved by A LOT but hey .. it's working!

Materials you need

> 1x Arduino Nano (or an uno if you have one should also work)
https://www.banggood.com/ATmega328P-Arduino-Compatible-Nano-V3-Improved-Version-No-Cable-p-959231.html

> 1x FPV Receiver module with SPI mod (these below already have the mod, otherwise please see the image below
https://www.banggood.com/FPV-5_8G-Wireless-Audio-Video-Receiving-Module-RX5808-p-84775.html

[https://static.rcgroups.net/forums/attachments/8/3/4/8/6/t8233448-151-thumb-rx5808-new-top.jpg]


> 1x WS2812 led strip (I used the one below - do not recommend using a bigger strip then 10 leds without external power)
https://www.banggood.com/Eachine-Aurora-90-100-Mini-FPV-Racer-Spare-Part-WS2812-LED-Board-LED-Strip-Light-p-1122903.html

> The hability to solder 9 cables :)

 
##How to connect it

1. Start by soldering the WS2812 strip Ground cable (black) to Arduino ground, the WS2812 strip 5V cable (red) to Arduino 5V and the WS2812 strip din cable (blue) to Arduino D5
2. Now solder the Channel 1 pin in your VTX receiver to your Arduino D10
3. Solder the Channel 2 pin in your VTX receiver to your Arduino D11
4. Solder the Channel 3 pin in your VTX receiver to your Arduino D12
5. Solder the Ground pin in your VTX receiver to your Arduino Ground (the same ground you connected the WS2812 ground to)
6. Solder the 5v pin in your VTX receiver to your Arduino 5V (the same 5v you connected the WS2812 5v to)
7. And finally, solder the RSSI pin in your VTX receiver to your Arduino A3

What? That's it?
Almost! You just need to upload the code to your Arduino via usb and you are done.


##How to upload the code (NOT YET RELEASED - BE PATIENT IF YOU HAPPEN TO BE READING THIS RIGHT NOW)

1. Start by downloading and installing Arduino IDE (https://www.arduino.cc/en/Main/Software)
2. Next, download THIS repository and unzip it somewhere in your desktop.
3. Go to the new folder you downloaded and open the file called CTF.INO
4. You will now be able to see a bunch of code and several files open.
5. Goto Tools/Board and pick Arduino Nano (if you bought an arduino nano, otherwise pick the one you have). The processor is ATMega328P.
6. Now to go port and pick the port your Arduino Nano is connected to. If you don't know which one it is, disconnect the nano and check what ports are available. Reconnect the nano, the new port will be the nano. If you don't get any new ports I'm afraid you will need to google how to troubleshoot it :)
7.Finally, goto sketch menu and select upload. If you done everything right you will see an increasing bar on the bottom right handside of the program and then a message saying Done uploading on the lower left handside.



#Congratulations!
You are now the proud owner of a CTF flag!

1. The arduino board can be powered by connecting 5v to the 5v connection OR by connecting it to a power bank via USB.
2. Once you power up the arduino board it will start scanning for all RACEBAND frequencies. It takes ~6 seconds to do a complete loop. 
3. Once it finds the first frequency it will change the LED colour depending if you are BLUE TEAM (RACEBAND 1-4) or RED TEAM (RACEBAND 5-8)
4. Once the flag changes colour it will only scan for the other team frequencies so the scanning takes place faster (~3 seconds for a loop)
Protect your flags anyway you can!


###GAME IDEA 1 (2 flags)
- Setup both teams in each flag area. Prime your flag by putting your team's drone next to it.
- Try to capture the other team's flag and defend yours. Game ends when everyone runs out of their battery (TEAM WIN BOTH FLAGS or DRAW 1 FLAG EACH).
- Reset by replugging arduino to power

###GAME IDEA 2 (multiple flags)
- Team death math. Both teams start from a staging area and try to capture and hold as many flags as you can.
- Game ends when everyone runs out of their battery (TEAM WIN FOR MOST FLAGS).
- Reset by replugging arduino to power
