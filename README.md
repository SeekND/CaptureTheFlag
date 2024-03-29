# Capture The Flag for drones
![Alt text](pictures/CTF.jpg?raw=true "CTF")

// Current version: 0.8 alpha //


I would like to share something I’ve been wanting for a while so I just decided to learn Arduino and do it myself.

**It’s Capture The Flag for your drones (with FPV).**


## See explanation video here: ##
## https://www.youtube.com/watch?v=plKc7N_GApc ##

If you happen to stumble here and don't know what FPV you can read about it in [Wikipedia](https://en.wikipedia.org/wiki/First-person_view_(radio_control)) or simply visit my youtube channel *www.youtube.com/SeekNDFPV*



This mod was made with Tiny Whoops (check *TinyWhoop.com*) in mind but really you can use it with any size drone as long as it has a 5.8 Ghz video transmitter on it.

It’s fairly easy to build, **costs around £9 (or $12) per flag in materials** and you just need to solder a few cables 🙂

You can battle **4 drones (BLUE TEAM) vs 4 drones (RED TEAM)** - (using any frequency) - in a game of Capture The Flag (as long as your VTX signals allow for that many to be flying at the same time) with as many flags as you are bothered to build!
There are also several new modes you can now try out, including a SINGLE PLAYER game - read more on this below.

The code itself was built from Chorus RF Laptimer, but most of that code is gone now.
Visit their repo if you are interested in knowing more about it here: https://github.com/voroshkov/Chorus-RF-Laptimer

Unlike Chorus RF Laptimer, at this moment this mod is standalone and cannot be accessed remotely but can be fully configured on the go via 1 button you can add to the unit.

You can also change the code to match your needs.
I've created a special setup section right at the start of the first page of the code where you can change and adapt every possible setting to your needs.


## Materials you need

> 1x Arduino Nano (or an uno if you have one should also work)
https://www.banggood.com/ATmega328P-Arduino-Compatible-Nano-V3-Improved-Version-No-Cable-p-959231.html

> 1x FPV Receiver module with SPI mod (these below already have the mod but double check - google vtx spi mod or check the pictures in this repo)
https://www.banggood.com/FPV-5_8G-Wireless-Audio-Video-Receiving-Module-RX5808-p-84775.html

> !!!UPDATED!!! 1x WS2812 8 led strip (works even better then the previous version AND is available in more countries)
https://www.banggood.com/CJMCU-8-Bit-WS2812-5050-RGB-LED-Driver-Development-Board-p-958214.html

> !!!UPDATE!!! You can now configure\reconfigure the whole system without going into the code. All you need is to add a button.
https://www.banggood.com/6-x-6-x-6-4-Pin-Momentary-Schalter-Tactile-Micro-Drucktaster-p-1027296.html

> The ability to solder a few cables :)  ( oh .. you also need a few cables :P )

 
## How to assemble it

1. Start by soldering the WS2812 strip Ground cable (black) to Arduino ground, the WS2812 strip 5V cable (red) to Arduino 5V and the WS2812 strip din cable (blue) to Arduino D5
2. Now solder the Channel 1 pin in your VTX receiver to your Arduino D10 (SS)
3. Solder the Channel 2 pin in your VTX receiver to your Arduino D11 (MOSI)
4. Solder the Channel 3 pin in your VTX receiver to your Arduino D12 (MISO)
5. Solder the Ground pin in your VTX receiver to your Arduino Ground (the same ground you connected the WS2812 ground to)
6. Solder the 5v pin in your VTX receiver to your Arduino 5V (the same 5v you connected the WS2812 5v to)
7. Solder the RSSI pin in your VTX receiver to your Arduino A3
8. And finally, solder one leg of the micro button to D3 and the other one to Ground. You will need to use the same side tabs on the button. You can break the other side tabs off.
9. You can now also 3D print this AWESOME folding cover by James Cowel: https://www.thingiverse.com/thing:2780523 
or my very crappy attempt of making one: https://www.thingiverse.com/thing:2766437




[Picture 1](pictures/IMG_1432.JPG) - [Picture 2](pictures/IMG_1433.JPG) - [Picture 3](pictures/IMG_1434.JPG)





## You can see a build video here: ##
## https://www.youtube.com/watch?v=enudy0pY3R4 ##

What? That's it?
Almost! You just need to upload the code to your Arduino via usb and you are done.


## How to upload the code

1. Start by downloading and installing Arduino IDE (https://www.arduino.cc/en/Main/Software)
2. Next, download THIS repository and unzip it somewhere in your desktop.
3. Go to the new folder you downloaded and open the file called CTF.INO
4. You will now be able to see a bunch of code and several files open.
5. Goto Tools/Board and pick Arduino Nano (if you bought an arduino nano, otherwise pick the one you have). The processor is ATMega328P.
6. Now to go port and pick the port your Arduino Nano is connected to. If you don't know which one it is, disconnect the nano and check what ports are available. Reconnect the nano, the new port will be the nano. If you don't get any new ports I'm afraid you will need to google how to troubleshoot it :)
7. You will need to download the following libraries: FASTLED / ADAFRUITSSD1306 / ADAFRUIT GFX . Goggle this if you don't know how. You can do it directly from Arduino IDE.
8. VERY IMPORTANT. You will need to play with the RSSITHRESHOLD value to find what works best for you. I find that most receivers work differently and that value can be between 190 to 260. Test it out with with EACH nano you build
9. You can also change MODES (view further down) by changing the MODE value in the code.
10. Also, you will need to update the INTERNALLEDS reference in the code to the number of LEDS you have.
11. Finally, when you are ready, goto sketch menu and select upload. If you done everything right you will see an increasing bar on the bottom right handside of the program and then a message saying Done uploading on the lower left handside.




# Congratulations!
You are now the proud owner of a CTF flag!

1. The arduino board can be powered by connecting 5v to the 5v connection OR by connecting it to a power bank via USB.
2. Once you power up the arduino board it will start scanning for all RACEBAND frequencies. It takes ~6 seconds to do a complete loop. 
3. Once it finds the first frequency it will change the LED colour depending if you are BLUE TEAM (RACEBAND 1-4) or RED TEAM (RACEBAND 5-8)
4. Once the flag changes colour it will only scan for the other team frequencies so the scanning takes place faster (~3 seconds for a loop)
5. Protect your flags anyway you can!


# NEW >>> FLAG CONFIGURATION ON THE GO!!!!

You can now configure all settings for the flag on the go by using only 1 button.
## Watch the explanation video here: ##
## https://www.youtube.com/watch?v=I-ONz2Xr1Us ##

Colour configuration:

- Blue = Raceband
- Red = Band A
- Yellow = Band B
- Green = Band E
- Purple = Band F
- Cyan = Band D


## MODES

Modes available

Mode 2. Capture the flag. Your standard capture the flag where two teams battle it out to have their flag and their opponents flag captured
Pre-setup values below but you can also change it with the button now
- R1, R3, R5, R7 TEAM BLUE
- R2, R4, R6, R8 TEAM RED

Mode 3. DOMINATION Capture the flag. Two teams will battle for domination of the flag. You must stay near the flag for it to be captured.

Mode 4. Single Player CTF. Change your frequency to the first frequency that is setup in the code (you can also change it with the button now). Turn all flags on and place them around your house. Get ready to go mental trying to get your flags not to drop to 0 leds. Good luck :)

Mode 5. Free For All Deathmatch. You are on your own and need to capture as many flags for yourself as you can.



 ### GAME IDEA 1 (2 flags - MODE 2) ###
  Setup both teams in each flag area. Prime your flag by putting your team's drone next to it.
  Try to capture the other team's flag and defend yours. 
  Once the timer finishes the flag will show which team won by showing the team colour and how many points they got.
  
 Game restarts automatically once the timer finishes.
 

   ### GAME IDEA 2 (multiple flags - MODE 2) ###
  Team death match. Both teams start from a staging area and try to capture and hold as many flags as you can.
  Once the timer finishes the flag will show which team won by showing the team colour and how many points they got.
  
 Game restarts automatically once the timer finishes.
 

  ### GAME IDEA 3 (DEATH MATCH - MODE 5) ###
  Up to 8 players (each frequency can now be configured) start from a staging area and try to capture as many flags as they can before everyone runs out of battery.
  The one with the most flags captured wins.

  
 Game restarts automatically once the timer finishes.


 ### GAME IDEA 5 (SINGLEPLAYER CTF - MODE 4)  ###
  Set your whoop to the first configured frequency. Turn all the flags and spread them in several places of your house.
  Once you start capturing a flag the timer for that flag will start. If you go away from that flag the leds will start decreasing.
  If the leds of the flag get to 0 you will not be able to recapture the flag. See how long you will managed to keep all flags alive. 
  
Once the timer finishes the flag will show how many points they got.
If you fail the flag will turn red.

 
 
 Game restarts automatically once the timer finishes.

 ### GAME IDEA 6 (DOMINATION CTF - MODE 3)  ###
  Setup both teams in each flag area. Prime your flag by putting your team's drone next to it.
  Try to capture the other team's flag and defend yours. Game ends when the timer set expires (default 2m 30s).
Once the timer finishes the flag will show which team won by showing the team colour and how many points they got.
  
 Game restarts automatically once the timer finishes.


# CONTACTS

- https://www.youtube.com/SeekNDFPV
- https://www.facebook.com/SeekNDFPV/


# SUPPORT

If you'd like to help support the project please contribute with ideas.

If you would like to contribute in another way, I would be very grateful as well.
http://paypal.me/SeekND

Thank you for your support!!
