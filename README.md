Brain-game
=============

Interactive piece for participants live-coding in Csound over internet and performers wearing brainwave and GSR sensors.
Developed for Tarmo Johannes's concert PASSAGGIO in Tallinn, Estonia, April 16, 2015.

Performers on spot wear brainwave sensors (like Neurosky Mindwave) that forward info to server and galvanic skin response sensors (based on arduino)
Csounders can send over internet their isntruments that use the data from sensors, start and stop or recompose them, change variables, tables etc.
The remote participants communicate with the central computer (serer) via a html-based UI, using websockets protocol.

The resulting sound is played on spot from PA and streamed up using Jamulus http://llcon.sourceforge.net/

The sensor values and incoming messages are displayed locally.
It is best to use two computers for the performance - one on the stage gathering information from sensors, another for sound production, UI and websocketserver (communication with remote participants).

Files and folders:

brain-serverver (just typo, did not change) - source code of the main program (websocket server, csound engine, UI displaying sensor values and messages, UDP listener for receiving data from another computer communicating with the sensors).

braingame.csd - Csound file including initial instrumnets.

braingame.html - web UI to send messages and try sounds and changes in code. Requires Csound Chrome to be able to try out the sounds locally.

gsr-arduino.py - reads messages about skin response (conductance) using arduino and firmata library.
neuropy-multi-device.py - reads data from one Neurosky Mindwave sensor (over bluetooth).
starter.py - simple UI to sart sensor reading programs


Copyright: Tarmo Johannes 2015 tarmo@otsakool.edu.ee
