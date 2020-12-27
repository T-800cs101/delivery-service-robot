# delivery-service-robot
The Programm imitates the delivery robot. This robot get a "world map" and finds with BFS-Algorithm the shortest way to the delivery point.
The delivery points are many and dynamic, so the robot must find the shortest way for all of this point save them in list and process all this deliveries in loop.
For this Project was used an AKSEN-Board (http://ots.fh-brandenburg.de/cat_aksen.html) that has own libary with specific methods that used from the Root like strat the motors or light sensors. 

the map:  xxFxFxx
          x..x..x
          F.x.x.F
          x.x...x
          x.x..xx
          x..x..x
          x...x.x
          xx..x.x
          F..x..F
          x0.x.0x
delivery points: "F"
free way: "."
blocked way: "x"
start point: "0"
