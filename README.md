# ArduinoProj
Arduino CPT (TER4M1)
Repo for code backup, annotations, and TinkerCAD link


arduino_cpt1 is the code for the output processor

arduino_cpt2 is the code for the data processor

# Link:
https://www.tinkercad.com/things/9ygR4qt1Uxi-arduino-cpt/editel?sharecode=gmU6vivAuLOO19DqDWojV-h8KZxD2X3rLbY9I7a_FBE

# Annotations:

1. If given more time, LED indicator would light up sequentially and then flash red in the middle as distance changes. This was delayed due to interconnect and tinkercad autosave issues.
2. LCD is connected to main arduino since it displays the most important data to the user and is the most latency-sensitive information. This improves reliability and safety for the system.
3. If given the parts, i would incorporate a permanent storage SD card reader to timestamp and save critical distances and the distance readings before and after. This would be used for collision data collection.
